//******************************************************************************
/*!
	\file
	\author		Raphael Zulliger, &copy; INDEL AG
	\version
	\verbatim
	2.00	06.08.1997-CH: * Origin.
	2.01	21.02.2001-FC: - Removed obsolete calls.
						   + Added inco types, characteristics, error codes.
	3.00	30.09.2003-RZ: + Added functions for (de-)initializing of the
							 inco_32.dll. Needed for compatibility with 
							 new inco_32.dll (version 3.0) for IncoServer 3.0.
	3.01	10.05.2004-FC: ! Deprecated DF_KEY_INDEL_PATH (read from IncoServer).
						   + New error ER_INCO_SERVER_TOO_OLD.
	3.02	03.06.2004-RZ: + Added declspec(dllexport/dllimport) needed for 
						 	 using this file for Windows CE (Pocket PC) programs
						   ! Renamed ER_INCO_SUBDEVICE_UNKNOWN to ER_INCO_DEVICE_UNKNOWN
						  	 and added ER_INCO_SUBDEVICE_UNKNOWN with a new error-number
	3.03.02	25.10.2004-RZ: + Due to the change of the version system, GetRevisions
							 has been changed too.
	3.03.03	01.11.2004-RZ: ! Fixed 2 memory leaks in ProcessIncoFrame()
	3.03.04	15.11.2004-RZ: ! Changed char* to const char*.
	3.03.04	16.11.2004-RZ: ! PutVariable() and GetVariable() do now check the 
							 Lenght-argument. Before the inco32.dll crashed if 
							 those values were greater than 256 (which is the
							 maximum amount of bytes the incoserver/inco32 3.x 
							 supports. If the Length arg ist to high now, an
							 ER_INCO_VAR_STRING_LENGTH error is returned by 
							 PutVariable. GetVariable tries to perform the 
							 INCOCall with the Maximum size (256) and if this
							 is enough, it doesn't return an error, otherwise
							 it does also return ER_INCO_VAR_STRING_LENGTH.
	3.03.05	04.01.2004-RZ: ! DbgTasksState, DbgTasksList: didn't return an error
							 If the given buffer was too small (instead they 
							 returned the amount of information fitting into
							 the buffer - but didn't complain about the to small
							 buffer. Now they behave like in the 2.x INCOServer.
	3.04.00	17.01.2005-RZ: ! The size of data has changed to 464 (from 256) in
							 the libindel/defsw.h. Put/GetBlocks do still use
							 256 bytes as max data size - because of 2 resons:
							 1. The incoserver does use an array on stack with 
							    256 Bytes for Put/GetBlocks from/to the DPR of 
								a PPC.
							 2. The ACSr-6A does only have such a small buffer
							    and would crash if we make PutBlocks greater
								than 256*2 (e.g. trans32 does that).
	3.04.01	25.01.2005-RZ: ! There are new XML config entries which allows the
							 user to configure the maximum length of Put-/Get-
							 Block's. Therefore a new List has been invented to 
							 hold those setting (called CTargetOverride).
						   ! PutBlock/GetBlock-max default-length has been 
						     increased to 464 Bytes again - because now the size 
							 is adjustable by the configurtin xml file (see above)
 	3.04.04	24.02.2005-MS: ! Added #define for "Template" and "Edit" state.
	3.05.00	05.04.2005-RZ: ! PutBlock, GetBlock fixed wrong error code when data
							 length where 0. Before an undefined error number was
							 returned.
						   + Added functions and calls, so that CallProcedure,
						     PutVariable and GetVariable will recognise if an 
							 INCO call has the target of the "own" process - and
							 does therefore not send the frame to the server.
	3.05.01 20.04.2005-RZ: ! Fixed small bug in GetRevisions which affects only 
							 person who are working with the INIXServer. Concrete:
							 GetRevisions failed if performed with the dll not 
							 matching the server (e.g. faile when inco_32.dll 
							 accessed an INIXServer or vice versa).
	3.05.02 16.05.2005-RZ: ! Fixed crash that happened if a call was made to 
							 target '.' and 0 dispatchers were registered.

	713, 2006-05-29 11:00:32 +0200 (Mo, 29 Mai 2006), fabi
	+ New error codes ER_INCO_DBG_NO_DEVICE and ER_INCO_DBG_NO_SOFT_RESET.

	762, 2006-07-26 15:04:55 +0200 (Mi, 26 Jul 2006), fabi
	+ Added ULL makros for unsigned long long constants.

	838, 2006-08-15 09:12:36 +0200 (Di, 15 Aug 2006), fabi
	! Fixed InternLog definition if logging is disabled.

	974, 2006-09-18 15:51:52 +0200 (Mo, 18 Sep 2006), walther
	+ Copied ISMGetBlockXX() etc. functions from Ism_inco_32.dll
	  (https://indel.dyndns.org/private/sw/old/trunk/inco/Ism_inco_32/Ism_inco_32.cpp
	  r68) into libinix32, with small changes to remove Windows dependencies.
	  These functions are used in the memdump plugin, which can't use
	  Ism_inco_32.dll because of conflicts between libinix32 and inco_32.dll.

	975, 2006-09-19 08:30:58 +0200 (Di, 19 Sep 2006), walther
	! Changed Slave argument of ISM functions from char * to const char *.

	1043, 2006-11-08 16:59:12 +0100 (Mi, 08 Nov 2006), walther
	+ Added a ticket system to allow synchronous calls of asynchronous
	  procedures within INIX (see documentation in inix32.h).

	1130, 2006-12-11 10:46:06 +0100 (Mo, 11 Dez 2006), walther
	+ Added a facility for asynchronous procedures to return result values.

	1149, 2006-12-12 08:42:24 +0100 (Di, 12 Dez 2006), zulliger
	! Minor error code cleanups. No functional changes.

	1199, 2007-01-10 07:38:50 +0100 (Mi, 10 Jan 2007), zulliger
	+ New errorcode "Async result lost"

	1223, 2007-01-22 14:19:42 +0100 (Mo, 22 Jan 2007), walther
	! Some documentation clarifications.
	- Removed unnecessary GetVariableSync() function (GetVariable() is already
	  synchronous).

	1326, 2007-02-27 14:55:39 +0100 (Di, 27 Feb 2007), fabi
	+ New errors ER_INCO_RPC_MULTIDISPATCH, ER_INCO_RPC_ARG_FORMAT.

	1492, 2007-03-30 15:08:21 +0200 (Fr, 30 Mrz 2007), zulliger
	- Removed Get/PutVariableBlock functions. INIXServer 3.x apps are not 
	  allowed to use those functions anymore.

	1664, 2007-06-27 17:17:59 +0200 (Wed, 27 Jun 2007), walther
	! Fixed some more messed up changelogs.

	1716, 2007-07-06 17:31:52 +0200 (Fr, 06 Jul 2007), walther
	+ Added LL macro for int64 constants.

	2324, 2007-12-18 11:09:33 +0100 (Di, 18 Dez 2007), zulliger
	! Set svn:keywords (why were these lost?).

	2370, 2007-12-20 10:09:47 +0100 (Do, 20 Dez 2007), zulliger
	- Removed ISM function defintions from header. Users of ISM functionality 
	  must include the ism_inco_32.h file.

	2398, 2007-12-24 16:07:03 +0100 (Mo, 24 Dez 2007), zulliger
	+ Readded GetServerRevisionS
	! Better const correctness

	2428, 2008-01-04 11:28:45 +0100 (Fr, 04 Jan 2008), zulliger
	! If neither INDEL_WINDOWS nor INDEL_LINUX are defined, we assume 
	  INDEL_WINDOWS by default. This helps to be backward compatible with old
	  inco_32.h files.

	2434, 2008-01-09 08:07:19 +0100 (Wed, 09 Jan 2008), zulliger
	+ Additional functions moved over from inix32.h

	2440, 2008-01-09 16:30:33 +0100 (Mi, 09 Jan 2008), zulliger
	+ Added define when compiled on Linux

	2518, 2008-02-07 14:38:59 +0100 (Thu, 07 Feb 2008), zulliger
	+ If INCO32_EXPORT is already defined, do not change its definition. Was
	  introduced for incoserver, where the define is set to nothing (neither
	  dll import, nor dll export)

	2546, 2008-02-08 13:25:34 +0100 (Fri, 08 Feb 2008), walther
	! Fixed compile issue on Linux boxes

	2618, 2008-02-27 15:46:42 +0100 (Wed, 27 Feb 2008), walther
	! Set svn:eol-style property where appropriate and svn:ignore a generated
	  file. [25 files]

	2629, 2008-02-29 15:30:15 +0100 (Fr, 29 Feb 2008), walther
	! Just noticed that I made a bit of a mess in the changelogs in r2618. Not
	  sure what happened - cleaning this up...

	3894, 2010-01-14 16:05:50 +0100 (Do, 14 Jan 2010), walther
	+ Support for asynchronous calls to external targets. The API functions
	  taking asynchronous call tickets now also take a target name to
	  disambiguate the tickets. This breaks binary compatibility for
	  applications that use these functions (only INIX to my knowledge), hence
	  the version number bump by tagging the previous revision. Ticket
	  machineries now exist one per target, the one for target "." is special
	  in that it also generates tickets (handles both the caller and the target
	  side of asynchronous calls), while the others only manage foreign tickets
	  (only handle the caller side). There is no support for handling incoming
	  asynchronous calls from the server yet. Documentation is not updated yet.

	3962, 2010-02-08 15:06:25 +0100 (Mo, 08 Feb 2010), walther
	+ Added function WaitForAsyncCallWithTimeout, like WaitForAsyncCallToFinish
	  but with timeout.

	3965, 2010-02-09 09:05:09 +0100 (Di, 09 Feb 2010), walther
	! Updated documentation for the recent API changes.

	3994, 2010-02-23 10:20:37 +0100 (Di, 23 Feb 2010), fabi
	! Adjusted to generate java classes with swig.

	3999, 2010-02-25 16:41:54 +0100 (Do, 25 Feb 2010), fabi
	! Exclude the 3.0 functions when generating the java interface as they are
	  not needed and pollute the interface.

	4186, 2010-06-10 16:37:37 +0200 (Do, 10 Jun 2010), zulliger
	+ Added include required for the INCO-types (indeldefs.h)
	+ Added include useful for customers to check for error returned by INCO
	  functions (errinco.h)

	4208, 2010-06-15 13:41:21 +0200 (Di, 15 Jun 2010), zulliger
	+ Added API documentation for CallProcedureEx & friends. No interface 
	  changes

	4212, 2010-06-15 16:00:43 +0200 (Tue, 15 Jun 2010), walther
	+ Added ProcedureExAddResult and ProcedureExAddAppError functions to
	  complete the new asynchronous procedure API.
	- Removed the previous asynchronous procedure API superseded by the
	  CallProcedureEx* functions, since due to the change in CallProcedure there
	  was no way to keep it backwards compatible.

	4227, 2010-06-16 09:05:18 +0200 (Mi, 16 Jun 2010), walther
	! Fixed Linux build ("error: 'NULL' was not declared in this scope").

	4228, 2010-06-16 16:56:42 +0200 (Mi, 16 Jun 2010), walther
	! Updated documentation for the added and removed functions from r4212 and
	  4214, and a lot of other small documentation tweaks.

	4248, 2010-06-24 11:38:29 +0200 (Do, 24 Jun 2010), walther
	! When a procedure that normally returns named results returns an
	  application error instead, the first attempt to get a result by name now
	  returns that application error instead of ER_INCO_RPC_UNKNOWN_TICKET, just
	  like the first attempt to get an unnamed result would.
	! It is now supported for both process-internal and inter-process calls to
	  return additional results after an application error (e.g. details about
	  the error). To enable consistent behavior among process-internal calls,
	  inter-process calls to inco_32 processes, and calls to INOS, it is now
	  specified that there may be at most one application error and it must come
	  before any other results. ProcedureExAddAppError() will now wipe out any
	  previously set results and app errors to enforce this.

	4481, 2010-08-11 15:27:59 +0200 (Mi, 11 Aug 2010), walther
	+ Handle error ER_INCO_RPC_INTERRUPTED that occurs when the INCOServer
	  detects a target reset while an asynchronous procedure is in progress.
	  Caveat: CallProcedureExWait() returns ER_INCO_NO_ERROR in such a
	  situation, ER_INCO_RPC_INTERRUPTED is only returned from
	  CallProcedureExResult(). This was simpler to implement and seems
	  sufficient for now.

	4578, 2010-10-08 14:36:44 +0200 (Fri, 08 Oct 2010), fabi
	! Removed INDEL_JAVA def check to include everything in the java binding.

	4700, 2010-12-03 17:14:06 +0100 (Fr, 03 Dez 2010), zulliger
	! Adjusted Eclipse projects

	4770, 2011-02-17 14:23:07 +0100 (Do, 17 Feb 2011), zulliger
	+ Added new interface functions: DbgEmeCommStatus and DbgOsContinue.

	4914, 2011-06-14 09:33:59 +0200 (Di, 14 Jun 2011), zulliger
	! Reworked inco_32.h in order to have better doxygen documentation. Thereby
	  adjusted argument names, ordering of functions, documentation itself,
	  etc. Other than documentation, nothing should have changed.

	4969, 2011-09-02 17:31:38 +0200 (Fri, 02 Sep 2011), walther
	! Clarify documentation regarding ER_INCO_RPC_NO_RETURN_VALUE and
	  ER_INCO_RPC_UNKNOWN_TICKET.

	4984, 2011-10-04 14:09:50 +0200 (Di, 04 Okt 2011), zulliger
	+ Added support for new Dbg INCO command: DbgTaskGetReg. This command has
	  initially been introduced to support getting registers from P2020. At the
	  same time, the command has been designed to optimize getting taks
	  specific registers for all targets, in the way GDB requires them.
	  Therefore, this new command will help minimizing communication overhead
	  when debugging with Gdb/iDev.

	4996, 2011-10-21 15:30:28 +0200 (Fr, 21 Okt 2011), walther
	+ Add a new interface function IncoControl() that provides a generic way of
	  querying and manipulating miscellaneous library state or settings. Its
	  one currently implemented function permits setting the address of the
	  INCOServer to connect to when using TCP.

	4997, 2011-10-21 16:09:33 +0200 (Fr, 21 Okt 2011), walther
	+ Port libinco_32 to Mac OS X and iOS. Only TCP communication is supported
	  at this time. Building for Mac OS X works using ibuild.py like on Linux.
	  For iOS, an Xcode project is provided. It requires wxWidgets-2.9.2
	  (unmodified source distribution), placed relative to the project as
	  specified by the WXROOT build setting.

	5174, 2012-05-10 15:23:55 +0200 (Do, 10 Mai 2012), walther
	! Don't use __declspec(dllexport) in addition to specifying exported
	  symbols in libinco_32.def, as doing both results in warnings from the
	  Microsoft x64 linker. See http://support.microsoft.com/kb/835326/.
	  Removing it makes no difference in the produced binary.

	5218, 2012-06-07 18:28:02 +0200 (Do, 07 Jun 2012), zulliger
	+ Added data transfer feature. "Data transfers" serves two major purposes:
	  The first is to send huge amount of data from PC to target and vice versa
	  by getting the most out from the transfer technology (e.g. use 1500 byte
	  for each ethernet frame) and second do this "directly" (i.e. not by using
	  the INCOServer process).

	5354, 2012-10-29 09:07:05 +0100 (Mon, 29 Oct 2012), walther
	! Fix some mistakes and omissions from when syntax documentation was copied
	  from inixdev/doc/user/syntax.dox (r4914).

	5386, 2012-11-19 15:05:26 +0100 (Mon, 19 Nov 2012), zulliger
	+ Added support for watchpoints

	5497, 2013-02-07 15:35:38 +0100 (Thu, 07 Feb 2013), tjericke
	+ Added DTClose and DTGetBufferSizes functions.
	! Made DataChannels (DT) available for pure C.

	5556, 2013-03-20 14:33:17 +0100 (Wed, 20 Mar 2013), pauli
	! Fixed documentation: Renamed INCO_ERROR_NO_ERROR to ER_INCO_NO_ERROR.

	5703, 2013-06-18 09:19:36 +0200 (Di, 18 Jun 2013), zulliger
	+ Added new INCO functions: DbgTaskRangeStep, DbgTargetGetDataMulti,
	  DbgTaskGetDataMulti, DbgTaskGetDataFromCache to speed up debugging with
	  iDev.

	5740, 2013-07-22 08:45:29 +0200 (Mon, 22 Jul 2013), walther
	! Fix syntax error that confused JNAerator.

	5773, 2013-09-23 17:37:29 +0200 (Mon, 23. Sep 2013), zulliger
	+ Added new INCO function: DbgTaskPutGdbReg. It has initially been
	  introduced to support new ARM CPUs. This function passes the register
	  setting string, produced by GDB, down to the INOS. Those string look like
	  "40=00001580" where the "40" is the register number and the rest is the
	  hex encoded register value. This function has been added to simplify the
	  gdb stub so that it does not need to know which register is meant by
	  "40".

	5960, 2014-02-19 10:37:05 +0100 (Mi, 19 Feb 2014), zulliger
	+ Added new API call: GetMessage. This function can be used to resolve an
	  error code (e.g. received by CallProcedureExSync) to a McRobot message.
	! Fixed compiler warnings when including this header in a .c file using
	  a C-compiler (had to add 'void' to function with empty argument list)

	5971, 2014-02-20 08:42:09 +0100 (Do, 20 Feb 2014), zulliger
	! Fixed C-function name conflict: GetMessage is part of the Windows C-API.
	  Therefore, renamed GetMessage into GetMcMessage

	5978, 2014-02-24 16:01:16 +0100 (Mo, 24 Feb 2014), pauli
	+ Added comment stating Data Transfer usage rule to avoid deadlocks 
	  when dealing with unreliable channels.

	5989, 2014-03-03 10:42:42 +0100 (Mo, 03 Mrz 2014), pauli
	! DT documentation review by zulliger.

	6181, 2014-08-06 17:05:08 +0200 (Wed, 06 Aug 2014), pauli
	+ Added new INIX frame dispatching functions (Indel internal use):
	  Register-/UnregisterAdditionalDispatcherByThread. These functions allow
	  to register a INCO frame handler specific to the calling thread so that
	  multiple top-level dispatchers ("") can exist per process. This
	  functionality is required by the INIX mapwatch plugin which needs to
	  register a dispatcher per crash target besides the dispatcher for the
	  INIX application.

	6534, 2015-11-12 00:51:52 +0100 (Don, 12 Nov 2015), zulliger
	! Slightly doxygen doc (no functional changes). Namely: explicitly mention
	  that CallProcedureExWait does NOT return application errors and that
	  CallProcedureExResult has to be used for that.

	6539, 2015-12-11 09:54:24 +0100 (Fr, 11 Dez 2015), pauli
	+ Added INCO recording feature. It can be used to log INCO calls to a file
	  for analysis. The file contains timing information, so the calls can be
	  replayed to e.g. simulate an HMI. The recorder can be started/stopped via
	  the IncoControl call using commands IncoCtlStartRecorder and
	  IncoCtlStopRecorder. Currently, only CallProcedures and data transfers
	  are recorded.

	$LastChangedRevision: 6633 $ $Date: 2016-06-17 09:34:39 +0200 (Fri, 17 Jun 2016) $ $Author: zulliger $
	! Slightly clarified the handling of the 'timeout' parameter of DTRecive.
	  No functional changes.

	$Comment$


	u = unreleased
	+ = new feature
	! = change, bugfix
	- = removed

	\endverbatim

	\remarks
	\verbatim
	project			: Inco32 Version 3
	language		: C++ (Gnu, Visual C++)
	system			: Linux, Windows
	\endverbatim

	\brief Interface functions for the libinco_32 dll/so

	All dll/so function provided by this project (the interface) are defined and
	implemented here.

*/
//******************************************************************************


#ifndef INCO_32_H
#define INCO_32_H


#ifdef __cplusplus
extern "C" {
#endif


//----------------------------------------------------------------------------
// 'INCO 2.0 standard' type definitions
//----------------------------------------------------------------------------

#include <inco_32/indeltypes.h>
#include <inco_32/indeldefs.h>
#include <inco_32/errinco.h>

#ifndef INCO32_EXPORT
	#if defined(INDEL_LINUX) || defined(INDEL_MACOSX)
		// for Linux and Mac OS X, the symbols do not have to be exported explicitely
		#define INCO32_EXPORT
	#else // assume window by default
		#if defined(INCO32_CREATE_DLL)
			#define INCO32_EXPORT
			// don't define it as __declspec(dllexport) because we specify exported symbols in a .def file, and doing both results in warnings from the Microsoft x64 linker
		#else
			#define INCO32_EXPORT __declspec(dllimport)
		#endif
	#endif
#endif

#ifndef WINAPI
	#if defined(INDEL_LINUX) || defined(INDEL_MACOSX)
		#define WINAPI
	#else // assume windows by default
		#include <windows.h> // to have definition of  WINAPI^M
	#endif
#endif


// path to INDEL in windows registry
// Attention!!
// This is deprecated. Since IncoServer 2.50 targets should be read from the
// IncoServer with the funtion GetIncoTarget (see below).
#define DF_KEY_INDEL_PATH_DEP        "SOFTWARE\\Indel"

#define DF_TASK_NUMBER_OF_GPR        32			// array size for DbgTaskGetGPRs
#define DF_TASK_NUMBER_OF_FPR        32			// array size for DbgTaskGetFPRs
#define DF_TASK_NUMBER_OF_SPR        8			// array size for DbgTaskGetSPRs

//----------------------------------------------------------------------------
// 'INCO 2.0 standard' calls
//----------------------------------------------------------------------------

/*! \defgroup commonfunctions Commonly used functions for target communication.

\page incodefinitions INCO definitions
\section targetpath Definition of the TargetPath
\verbatim
<target path> = [("//" | "\\") <server name or address> ("/" | "\")] {<target name> ("/" | "\")}
              | "."       //current process
              | ".."      //parent of current process
              | "..."     //current INCO server
\endverbatim

The "normal" case:
\code
char TargetPath[] = "MyTarget";
\endcode
Accessing a target connected to a remote computer:
\code 
char TargetPath[] = "\\\\RemotePcName\\MyTarget";
char TargetPath[] = "//RemotePcName/MyTarget";
\endcode
Accessing a slave (XAxis) of a target connected to a remote computer:
\code 
char TargetPath[] = "\\\\RemotePcName\\MyTarget\\XAxis";
char TargetPath[] = "//RemotePcName/MyTarget/XAxis";
\endcode

\section incoitemname Definition of the ItemPath
\verbatim
<inco path> = <inco item path>
            | <inco item path> "!" <property name>
            | <inco item path> ":" <bit number>
            | <inco item path> "[" <array index> "]"
\endverbatim
\verbatim
<inco item path> = <inco item name> {"." <inco item name>}
\endverbatim
\verbatim
<inco item name> = <nonempty sequence of alphanumeric ASCII characters, spaces, underscores (_), hyphen-minuses (-), and backslash-escaped periods (\.)>
\endverbatim
Periods in INCO item names are only allowed if they are preceded by a backslash. Backslashes are only allowed if they are followed by a period. Unescaped periods are always considered as path separators, and non-period-escaping backslashes as target separators.

The path to the timer variable of the target:
\code
char ItemPath[] = "Target.Prop.Timer";
\endcode

\section callproceduresyntax Definition of the CallProcedure(Ex) syntax
\verbatim
<callprocedure> = <inco item path> {whitespace} "(" [<value> {"," <value>}] ")"
\endverbatim

\anchor incovaluesyntax
\verbatim
<value> = {whitespace} <trimmed value> {whitespace}
\endverbatim
\verbatim
<trimmed value> = <number> { {whitespace} ("+"|"-") {whitespace} <number> }
                | <string literal> { {whitespace} <string literal> }
\endverbatim
\verbatim
<number> = ("0x"|"0X") <hexadecimal integer> ":" ("l"|"f"|"d"|"L"|"F"|"D")
         | <decimal integer> [":" ("l"|"L")]
         | <decimal real number> [":" ("f"|"d"|"F"|"D")]
\endverbatim
\verbatim
<string literal> = """ <string contents with " and \ escaped as \" and \\, optionally LF as \n> """
\endverbatim
Decimal numbers without a type suffix are accepted and interpreted as <em>float</em> values for backwards compatibility, but should be avoided in new applications.

Multiple adjacent string literals are concatenated into one string.

Joining multiple numbers with "+" or "-" computes the respective sum or difference. The type of the result is determined as follows: If any summand is a double, the result is a double. Else, if any summand is a float, the result is a float. Else, if any summand is a signed integer, the result is a signed integer. Else (i.e. if all summands are unsigned integers), the result is an unsigned integer.

A function that takes no arguments:
\code
char CallProcedure[] = "Target.Cmd.Reset()";
\endcode
A function taking one uint32 argument (decimal and hex notation):
\code
char CallProcedure[] = "Target.MyFunction(12345:l)";
char CallProcedure[] = "Target.MyFunction(0xabcd:l)";
\endcode
A function taking a negative number:
\code
char CallProcedure[] = "Target.MyFunction(-1234:l)";
\endcode
A function taking one a string argument:
\code
char CallProcedure[] = "Target.MyStringFunction(\"The string argument value\")";
\endcode
A function taking one double argument:
\code
char CallProcedure[] = "Target.MyFunction(1.23456789:d)";
\endcode
A function taking one float argument:
\code
char CallProcedure[] = "Target.MyFunction(1.2345:f)";
\endcode

*/

/*! \name INCO variable reading and writing */
//@{
#ifdef __cplusplus
INCO32_EXPORT uint32 WINAPI GetVariable						(const char* TargetPath, const char* ItemPath, void* Result, uint32 Length=0);
INCO32_EXPORT uint32 WINAPI PutVariable						(const char* TargetPath, const char* ItemPath, const void* Value, uint32 Length=0);
#else
INCO32_EXPORT uint32 WINAPI GetVariable						(const char* TargetPath, const char* ItemPath, void* Result, uint32 Length);
INCO32_EXPORT uint32 WINAPI PutVariable						(const char* TargetPath, const char* ItemPath, const void* Value, uint32 Length);
#endif
//@}

/*! \name Remote INCO procedure call (RPC)
(see also \ref syncasync) */
//@{
INCO32_EXPORT uint32 WINAPI CallProcedure					(const char* TargetPath, const char* CallProcedure, double* Result);
#ifdef __cplusplus
INCO32_EXPORT  int32 WINAPI CallProcedureEx					(const char* TargetPath, const char* CallProcedure, double* SyncResult=0);
INCO32_EXPORT uint32 WINAPI CallProcedureExSync				(const char* TargetPath, const char* CallProcedure, void* Result=0, 
															 uint32 BufferSize=8/*sizeof(double)*/, uint32 TypeFlags=DF_INCO_TYPE_NUMBER_VALUE);
INCO32_EXPORT uint32 WINAPI CallProcedureExWait				(const char* TargetPath, int32 Ticket, int32 TimeoutMs=-1/*infinite*/);
INCO32_EXPORT uint32 WINAPI CallProcedureExResult			(const char* TargetPath, int32 Ticket, void* Result=0, 
															 uint32 BufferSize=8/*sizeof(double)*/, uint32 TypeFlags=DF_INCO_TYPE_NUMBER_VALUE, 
															 char* ResultName=0, uint32 ResultNameBufSize=0);
INCO32_EXPORT uint32 WINAPI CallProcedureExResultByName		(const char* TargetPath, int32 Ticket, const char* ResultName, void* Result, 
															 uint32 BufferSize=8/*sizeof(double)*/, uint32 TypeFlags=DF_INCO_TYPE_NUMBER_VALUE);

#else
INCO32_EXPORT  int32 WINAPI CallProcedureEx					(const char* TargetPath, const char* CallProcedure, double* SyncResult);
INCO32_EXPORT uint32 WINAPI CallProcedureExSync				(const char* TargetPath, const char* CallProcedure, void* Result, 
															 uint32 BufferSize, uint32 TypeFlags);
INCO32_EXPORT uint32 WINAPI CallProcedureExWait				(const char* TargetPath, int32 Ticket, int32 TimeoutMs);
INCO32_EXPORT uint32 WINAPI CallProcedureExResult			(const char* TargetPath, int32 Ticket, void* Result, 
															 uint32 BufferSize, uint32 TypeFlags, 
															 char* ResultName, uint32 ResultNameBufSize);
INCO32_EXPORT uint32 WINAPI CallProcedureExResultByName		(const char* TargetPath, int32 Ticket, const char* ResultName, void* Result, 
															 uint32 BufferSize, uint32 TypeFlags);
#endif
//@}

/*! \name Raw target memory access functions */
//@{
INCO32_EXPORT uint32 WINAPI PutBlock8						(const char* TargetPath, uint32 DestAddress, const uint8* Data, uint32 Number);
INCO32_EXPORT uint32 WINAPI GetBlock8						(const char* TargetPath, uint32 SourceAddress, uint8* Data, uint32 Number);
INCO32_EXPORT uint32 WINAPI GetBlock8Real					(const char* TargetPath, uint32 SourceAddress, uint8* Data, uint32 Number);
INCO32_EXPORT uint32 WINAPI PutBlock16						(const char* TargetPath, uint32 DestAddress, const uint16* Data, uint32 Number);
INCO32_EXPORT uint32 WINAPI GetBlock16						(const char* TargetPath, uint32 SourceAddress, uint16* Data, uint32 Number);
INCO32_EXPORT uint32 WINAPI PutBlock32						(const char* TargetPath, uint32 DestAddress, const uint32* Data, uint32 Number);
INCO32_EXPORT uint32 WINAPI GetBlock32						(const char* TargetPath, uint32 SourceAddress, uint32* Data, uint32 Number);
INCO32_EXPORT uint32 WINAPI PutBlock64						(const char* TargetPath, uint32 DestAddress, const uint64* Data, uint32 Number);
INCO32_EXPORT uint32 WINAPI GetBlock64						(const char* TargetPath, uint32 SourceAddress, uint64* Data, uint32 Number);
//@}

/*! \name INCO error information */
//@{
INCO32_EXPORT uint32 WINAPI GetErrorDescription				(const char* TargetPath, uint32 Error, char* Description, uint32 Length);
/** Gets the error message of a McRobot message container. Usually, a McRobot 
 based machine has 1 message handler, often located at "Machine.Msg"
 \param MessagePath INCO Path to the message handler. Usually, this path is 
        "Machine.Msg"
 \param Error The INCO error code as returned from e.g. CallProcedure. Note 
        that this function will care about 'reply codes' by masking them off 
        the error). If the error is not a "McRobot error code" (McRobot errors
        have the bits set defined by ER_APPERROR_BASE (0x40000000) or 
        ER_APPERROR_CUSTOMER (0x80000000)), this function returns 
        ER_INCO_VAR_NOT_FOUND.
 \param Message Pointer to the buffer were the message text will be copied
 \param Length Size of the buffer defined by Message in [Bytes]
 \return Technically, this function tries to resolve the error passed by 
         param "Error" by accessing the target with GetVariable. Therefore, 
         this function may reutrn any error that may occur by a GetVariable. */
INCO32_EXPORT uint32 WINAPI GetMcMessage					(const char* TargetPath, const char* MessageHandlerPath, uint32 Error, char* Message, uint32 Length);
//@}

/*! \name INCO32 version information */
//@{
INCO32_EXPORT uint32 WINAPI GetRevisions					(const char* TargetPath, uint32* ServerRevision, uint32* DllRevision);
//@}

/*! \name Data Transfer. Always prefer INCO over data transfer unless
you have a good reason to use the latter. Do only choose to use

Data transfer is an alternative way of transferring data to and from a
target. The key features of the data transfer technology are:

  - Transfer of arbitrary sized data (e.g. 100MByte) is supported
  - Direct data channel to the target, without having an additional
    task switch to another process (e.g. INCOServer). (Note that
    a data transfer may be performed by INCO frames - so that this
    statement is not always true)

Data transfers are always configured/setup by the target. The target
defines all properties of the transfer, such as maximum allowed transfer
size, timeouts, retries, etc. A target may offer "multiple data transfer"
endpoints (e.g.: One for "Fast load", one for "Customer log data", etc.)
and each endpoint may allow the data to be transferred by different 
technologies (such as UDP, PCIe, INCO, etc.)

It's the duty of the user of the libinco_32 data transfer functions
to choose the right endpoint. Libinco_32 will then automatically choose 
the "best" transfer technology.

The data transfer technology is *not* meant to be used just by chance...
Instead: The decission to use data transfers must be done very conscious.
Also the properties, such as retries, timeout, etc. must be choosen with
care and must be well tested in long-durance tests. 

<b>IMPORTANT :</b> To avoid lags or even deadlocks when transferring over 
unreliable channels such as UDP, it is mandatory to obey the following rule: 

After issuing a DTReceive call, Data Transfer clients must either immediately 
call DTReceive again or immediately shutdown the connection via DTClose. 
This implies that it is not allowed to perform a DTSend directly after a 
DTReceive within the same thread.

To illustrate the necessity of this rule, consider the following scenario:
The PC wants to receive data from the target by calling DTReceive. 
The target replies within the timeout, so DTReceive sends an acknowledgement 
to the target and returns the received data to the caller. If the acknowledgement is lost, 
the target will run into a timeout and retransmit its reply to the PC, 
assuming that the PC did not receive the first transmission. Now, if the PC is not 
listening via DTReceive, the retransmission will never be handled, leading 
to subsequent retransmissions issued by the target until all retries are exhausted.

*/
//@{
typedef uintptr tLDTFileDescriptor;
/** Opens a data transfer. This function tries to establish a connection
 to the endpoint on the target.
\param TargetPath \ref targetpath
\param Endpoint A zero-terminated string of the INCO path of the endpoint 
to which the connection should be established
\param FileDescriptor Pointer to a tLDTFileDescriptor. If the function 
succeeds, the file descriptor will be set to a valid value that must be 
passed to every call of DTClose, DTSend and DTReceive
\return ::ER_INCO_NO_ERROR on success.
\return ::ER_INCO_DT_ALREADY_CONNECTED if the target reports that a 
 connection is already established. If it is desired t re-establish 
 the connection, the DTControl can be called using DTCtlForceConnect
 followed by another attempt to DTOpen.
\return A request-specific error code from <inco_32/errinco.h> (see \ref page_inco32errors).
 */
INCO32_EXPORT  uint32 WINAPI DTOpen							(const char* TargetPath, const char* Endpoint, tLDTFileDescriptor* FileDescriptor);
/** Closes a data transfer connection
\param FileDescriptor The file descriptor that was set by DTOpen */
INCO32_EXPORT  void WINAPI DTClose							(tLDTFileDescriptor FileDescriptor);
/** Sends the data pointed to by DataBuffer to the target. 
This function returns when sending the data completed or failed. 
The function applies the timeout and retry properties as defined
by the target. Therefore, the execution time of this function may
significantly increase in case of transfer problems (e.g. UDP frame 
loss, etc.)
\param DataBuffer Pointer to the data that should be sent to the target
\param DataLength Count of Bytes sent to the target.
\param FileDescriptor The file descriptor that was set by DTOpen
\return ::ER_INCO_NO_ERROR on success.
\return A request-specific error code from <inco_32/errinco.h> (see \ref page_inco32errors).
 */
INCO32_EXPORT  uint32 WINAPI DTSend							(tLDTFileDescriptor FileDescriptor, const void* DataBuffer, uint32 DataLength);
/**
\param FileDescriptor The file descriptor that was set by DTOpen
\param DataBuffer Pointer to the buffer where this function puts received data into
\param DataBufferSize Buffer size in bytes. The buffer size *must* be big enough 
 to take the maximum configured data transfer size as specified by the target.
\param DataLength Output parameter that'll contain the number of received bytes.
\param TimeoutMs Maximum time to wait for a data transfer to start. Moreover, if a 
 data transfer is big enough so that it requires multiple "sub-data transfers" 
 (i.e. multiple UDP frames) then the timeout is also used to wait for every 
 sub-data transfer. Therefore: If sub-data transfers are required, the overall time
 spent in this function may be significantly higher than TimeoutMs. More technically
 spoken: This timeout is used for each attempt of reading one UDP/Ethernet frame.
 This also implies that, assuming you transfer 15'000 Bytes (= 10 Ethernet frames in
 case of a DataTransfer), the underlying code needs 10 times to read a UDP frame and
 thus the timeout is applied on every read attempt. Therefore, if only one of these
 10 frames would not arrive within TimeoutMs, the whole transfer would be aborted
 with a timeout error, whether some frames were received successfully or not. The
 very same holds true for transfer technologies other than UDP, just that the 
 'frame sizes' are different from 1500 Bytes.
\return ::ER_INCO_NO_ERROR on success.
\return A request-specific error code from <inco_32/errinco.h> (see \ref page_inco32errors).
 */
#ifdef __cplusplus
INCO32_EXPORT  uint32 WINAPI DTReceive						(tLDTFileDescriptor FileDescriptor, void* DataBuffer, uint32 DataBufferSize, uint32* DataLength, int32 TimeoutMs=-1/*INFINITE*/);
#else
INCO32_EXPORT  uint32 WINAPI DTReceive						(tLDTFileDescriptor FileDescriptor, void* DataBuffer, uint32 DataBufferSize, uint32* DataLength, int32 TimeoutMs);
#endif
/*! \name Querying and modifying data transfer parameters */
//@{
/*! \brief Request identifiers for IncoControl(). */
enum DTCtlRequest {
	DTCtlForceConnect ///! e.g. DTControl("SUT", DTCtlForceConnect, "DataTransfer.Endpoints.TestUtilEndpoint", strlen("DataTransfer.Endpoints.TestUtilEndpoint")+1);
};
INCO32_EXPORT uint32 WINAPI DTControl						(const char* TargetPath, int32 aiRequest, void* apData, uint32 auDataLength);

INCO32_EXPORT uint32 WINAPI DTGetBufferSizes				(tLDTFileDescriptor FileDescriptor, uint32* LocalBufferSize, uint32* TargetBufferSize);

//@}

/*! \name Database functions (for Indel internal use) */
//@{
#ifdef __cplusplus
INCO32_EXPORT uint32 WINAPI CreateTable						(const char* TargetPath, const char* TableName, const char* DatabaseName, uint32 NumberRecords, uint32 RecordSize, uint32 Flags=0);
#else
INCO32_EXPORT uint32 WINAPI CreateTable          (const char* TargetPath, const char* TableName, const char* DatabaseName, uint32 NumberRecords, uint32 RecordSize, uint32 Flags);
#endif
INCO32_EXPORT uint32 WINAPI DeleteTable						(const char* TargetPath, const char* TableName);
INCO32_EXPORT uint32 WINAPI PutRecord						(const char* TargetPath, const char* TableName, const char* Record, void* Data, uint32 Size);
INCO32_EXPORT uint32 WINAPI GetRecord						(const char* TargetPath, const char* TableName, const char* Record, void* Data, uint32 Size);
//@}

/*! \name TargetPath debugging functionality (for Indel internal use) */
INCO32_EXPORT uint32 WINAPI DbgOsPrepareLoad      (const char* TargetPath);
INCO32_EXPORT uint32 WINAPI DbgOsReset            (const char* TargetPath, uint32 aFlags);
INCO32_EXPORT uint32 WINAPI DbgTasksList          (const char* TargetPath, void* aResult, uint32 aLength);
INCO32_EXPORT uint32 WINAPI DbgTasksState         (const char* TargetPath, void* aResult, uint32 aLength);
INCO32_EXPORT uint32 WINAPI DbgTaskGetId          (const char* TargetPath, const char* aTaskName, uint32* aTaskId);
INCO32_EXPORT uint32 WINAPI DbgTaskSetBreakpoint  (const char* TargetPath, const char* aTaskName, uint32 aAddress);
INCO32_EXPORT uint32 WINAPI DbgTaskClrBreakpoint  (const char* TargetPath, const char* aTaskName, uint32 aAddress);
INCO32_EXPORT uint32 WINAPI DbgTaskGetBreakpoint  (const char* TargetPath, uint32 aNumber, void* aResult, uint32 aLength);
INCO32_EXPORT uint32 WINAPI DbgTaskGetName        (const char* TargetPath, uint32 aTaskId, char* aTaskName, uint32 aLength);
INCO32_EXPORT uint32 WINAPI DbgTaskHalt           (const char* TargetPath, uint32 aTaskId);
INCO32_EXPORT uint32 WINAPI DbgTaskRun            (const char* TargetPath, uint32 aTaskId);
INCO32_EXPORT uint32 WINAPI DbgTaskSingleStep     (const char* TargetPath, uint32 aTaskId);
/** Performs at least one task single-steps. Performs more task single-steps
 as long as the task PC is >= auFrom and < auTo. This function is a pure debug
 performance optimization, as the same functionality can be get by issuing 
 several DbgTaskSingleStep from the PC side. */
INCO32_EXPORT uint32 WINAPI DbgTaskRangeStep      (const char* TargetPath, uint32 aTaskId, uint32 auFrom, uint32 auTo);
INCO32_EXPORT uint32 WINAPI DbgTaskGetGPRs        (const char* TargetPath, uint32 aTaskId, uint32 (*aResult)[DF_TASK_NUMBER_OF_GPR]);
INCO32_EXPORT uint32 WINAPI DbgTaskGetFPRs        (const char* TargetPath, uint32 aTaskId, double (*aResult)[DF_TASK_NUMBER_OF_FPR]);
INCO32_EXPORT uint32 WINAPI DbgTaskGetSPRs        (const char* TargetPath, uint32 aTaskId, uint32 (*aResult)[DF_TASK_NUMBER_OF_SPR]);
INCO32_EXPORT uint32 WINAPI DbgTaskGetGPR         (const char* TargetPath, uint32 aTaskId, uint32 aNumber, uint32* aValue);
INCO32_EXPORT uint32 WINAPI DbgTaskGetFPR         (const char* TargetPath, uint32 aTaskId, uint32 aNumber, double* aValue);
INCO32_EXPORT uint32 WINAPI DbgTaskGetSPR         (const char* TargetPath, uint32 aTaskId, uint32 aNumber, uint32* aValue);
INCO32_EXPORT uint32 WINAPI DbgTaskPutGPR         (const char* TargetPath, uint32 aTaskId, uint32 aNumber, uint32 aValue);
INCO32_EXPORT uint32 WINAPI DbgTaskPutFPR         (const char* TargetPath, uint32 aTaskId, uint32 aNumber, double aValue);
INCO32_EXPORT uint32 WINAPI DbgTaskPutSPR         (const char* TargetPath, uint32 aTaskId, uint32 aNumber, uint32 aValue);
INCO32_EXPORT uint32 WINAPI DbgTaskGetData        (const char* TargetPath, uint32 aTaskId, uint32 aDataDef, void* aResult, uint32 aLength);
INCO32_EXPORT uint32 WINAPI DbgTaskPutData        (const char* TargetPath, uint32 aTaskId, uint32 aDataDef, void* aData, uint32 aLength);
INCO32_EXPORT uint32 WINAPI DbgCpuGetSPR          (const char* TargetPath, uint32 aNumber, uint32* aResult);
INCO32_EXPORT uint32 WINAPI DbgCpuPutSPR          (const char* TargetPath, uint32 aNumber, uint32 aValue);
INCO32_EXPORT uint32 WINAPI DbgCpuGetDCR          (const char* TargetPath, uint32 aNumber, uint32* aResult);
INCO32_EXPORT uint32 WINAPI DbgCpuPutDCR          (const char* TargetPath, uint32 aNumber, uint32 aValue);
/** Get status about 'emergency INCO communication' of target \a TargetPath.
 Value at \a apEmeCommStatus will be set to 0 if the emergency system is not
 running. It'll be set to 1 if it is running. */
INCO32_EXPORT uint32 WINAPI DbgEmeCommStatus      (const char* TargetPath, uint32* apEmeCommStatus);
/** Continue execution of OS. If auFlags is 0 and the 'emergency INCO 
 communication' is running, this emergency communication will be left and
 "normal" OS execution will be continued. */
INCO32_EXPORT uint32 WINAPI DbgOsContinue         (const char* TargetPath, uint32 auFlags);
/** \deprecated This function has been replaced by the more powerful 
 DbgTaskGetDataMulti. */
INCO32_EXPORT uint32 WINAPI DbgTaskGetReg         (const char* TargetPath, uint32 aTaskId, uint32* apCookie, uint32* apFlags, void* apBuffer, uint32* apBufferLength);
/** Set a watchpoint on address auAddress with auAddress and auFlags.
 * \param auAddress The desired address of the watchpoint.
 * \param auSize The desired size of the watchpoint
 * \param auFlags 1: read acces, 2: write access, 3: read & write access
 * \param apAddress The effective watchpoint address, which may differ from
 *  auAddress because certain CPU have certain watchpoint constraints (such as
 *  the IBM 750, which may only cover addresses which are 8Byte aligned).
 * \param auSize The effetive watchpoint size, which may differ from auSize
 *  because certain CPU have certain watchpoint constraints (such as
 *  the IBM 750, which may only cover 8Bytes of data). */
INCO32_EXPORT uint32 WINAPI DbgSetWatchpoint      (const char* TargetPath, uint32 auAddress, uint32 auSize, uint32 auFlags, uint32* apAddress, uint32* apSize);
/** Clears the watchpoint at address auAddress.
 * \param auAddress The address of the watchpoint that should be cleared.
 *  The address must be within the watched range. Means: it doesn't
 *  necessarily need to be the same value as returned by DbgSetWatchpoint
 *  (apAddress), as long as the address lies within the watched
 *  memory region.
 *
 * \note As of this writing, all INOS targets only support 1 watchpoint.
 *  These implementation do not even check auAddress. Instead, they
 *  always just remove the watchpoint if one is set. */
INCO32_EXPORT uint32 WINAPI DbgClrWatchpoint      (const char* TargetPath, uint32 auAddress);
/** Get all kind of target specific data, such as: task list, their state and
 tbentries, breakpoint/watchpoint/testpoint list, etc. The caller decides which
 data to be read by *apFlags. INOS reports which data were actually sent back
 by *apFlags. Each version of INOS may support different kind of data. 
 Therefore, check the INOS sources for a list of supported flags. If the data 
 don't fit into a single INCO ACK frame, then *apCookie will be set to !=0, 
 *apRemainingDataLength will be set to the count of bytes of additionally
 available data. The caller can invoke this function again, passing *apCookie
 to get the remainig data.
 may pass that cookie to the next  */
INCO32_EXPORT uint32 WINAPI DbgTargetGetDataMulti (const char* TargetPath, uint32* apCookie,
	uint32* apFlags, void* apBuffer, uint32* apBufferLength, uint32* apRemainingDataLength);
/** Get all kind of task specific data, such as: task state, trap number, 
 registers values, tb entries, etc. This function works the same way as
 DbgTargetGetDataMulti. */
INCO32_EXPORT uint32 WINAPI DbgTaskGetDataMulti   (const char* TargetPath, uint32 aTaskId,
	uint32* apCookie, uint32* apFlags, void* apBuffer, uint32* apBufferLength, uint32* apRemainingDataLength);
/** For certain INCO calls (i.e. SingleStep, RangeStep, Halt), new INOS 
 versions return task state data in the ACK frame to optimize the amount of
 frames to be exchanged between the PC and INOS during debugging. These data
 are stored within libinco_32 and can be get by this function. The format
 of the data and the way to get possibly "remaining data" is the same as
 for DbgTargetGetDataMulti. */
INCO32_EXPORT uint32 WINAPI DbgTaskGetDataFromCache (const char* TargetPath, uint32* apCookie,
	uint32* apFlags, void* apBuffer, uint32* apBufferLength, uint32* apRemainingDataLength);
/** Set a register at the target in 'GDB style' syntax. This syntax is defined
 by GDB's serial remote protocol and looks like this:
   "RegNum=RegValue"
 So for example, to set the value of the PC on a PPC603, you'd have a string
 like that:
   "40=deadbeef"
 Initially, this function has been introduced to support targets with ARM
 CPUs (i.e. COP-MAS2). Thereby, we adjusted the GDB stub so that it doesn't
 need to know anything about register numbers anymore (means: doesn't need
 to know that register number 40 is the PC). Thereby, we moved that know
 how to INOS, thus this new function. */
INCO32_EXPORT uint32 WINAPI DbgTaskPutGdbReg		(const char* TargetPath, uint32 aTaskId, const uint32 auRegister, const void* apData, uint32 auDataLength);
//@}


/*! \name INIX frame dispatching functionality (for Indel internal use) */
//@{
// typdef for Callback-function ( format: uint32 MyFunction( char* aIncoFrameStream, uint32 Length ); )
typedef uint32 (WINAPI *frameCallbackFct)( uint32 ahPlugin, const char* aIncoFrameStream, uint32 Length,
										char* apResponseFrameStream, uint32* apResponseStreamLength);
INCO32_EXPORT uint32 WINAPI IncoInitialize(void);
INCO32_EXPORT uint32 WINAPI IncoUninitialize(void);
// hopefully not used anymore: INCO32_EXPORT uint32 WINAPI UnregisterDevice( const char* aName );
// hopefully not used anymore: INCO32_EXPORT uint32 WINAPI RegisterDevice( const char* aName, uint32 aAutoregister, char apEffectiveName[], uint32 auMaxStringLength );
INCO32_EXPORT uint32 WINAPI RegisterDispatcher( const char* apFullPluginPath, uint32 aPluginId, frameCallbackFct aProcessFramePtr );
INCO32_EXPORT uint32 WINAPI UnregisterDispatcher( const char* apFullPluginPath );
INCO32_EXPORT uint32 WINAPI RegisterAdditionalDispatcherByThread( const char* apFullPluginPath, uint32 aPluginId, frameCallbackFct aProcessFramePtr );
INCO32_EXPORT uint32 WINAPI UnregisterAdditionalDispatcherByThread( const char* apFullPluginPath );
INCO32_EXPORT uint32 WINAPI INCOSetThreadName( const char* apThreadName );
INCO32_EXPORT uint32 WINAPI INCOGetThreadName( char* apThreadName, uint32 apThreadNameBufferLength );
INCO32_EXPORT void WINAPI INCOClearThreadName(void);
INCO32_EXPORT uint32 WINAPI HandleINCOFrameFromServer( int32 aiTimeout );
//@}

/*! \name Querying and modifying library parameters */
//@{
/*! \brief Request identifiers for IncoControl(). */
enum IncoCtlRequest {
	/*! \brief Set the IP address or hostname of the INCOServer when TCP communication is used.
		
		Arguments:
		- \a TargetPath: ignored
		- \a apData: <tt>const char *</tt>; pointer to a null-terminated string, or NULL
		- \a auDataLength: ignored
		
		Return value: always ::ER_INCO_NO_ERROR
		
		Changing the server address affects all INCO calls done afterwards from any thread.
		Be careful when changing the address after doing asynchronous INCO calls: disconnecting from the server will make it impossible to receive their completion notification or results, and waiting for them afterwards may block forever.
		
		The default server address before calling this for the first time or after calling it with a NULL or empty string argument is <em>127.0.0.1</em>.
		
		This request always succeeds as it only stores the passed value. The connection to the server is only opened at the first subsequent INCO call using TCP, and any errors in address resolution or connection to the server will be reported at that time by returning an appropriate error code (e.g. ::ER_TARGET_REMOTE_SRV_NOT_FOUND).
	*/
	IncoCtlSetTcpServerAddress,
	
	/*! \brief Start recording INCO calls into a file for later replay.
		
		Arguments:
		- \a TargetPath: ignored
		- \a apData: <tt>const char *</tt>; output file path
		- \a auDataLength: ignored
		
		Return value: ::ER_INCO_NO_ERROR on success
	*/
	IncoCtlStartRecorder,
	
	/*! \brief Stops the current recording of INCO calls.
		
		Arguments:
		- \a TargetPath: ignored
		- \a apData: ignored
		- \a auDataLength: ignored
		
		Return value: always ::ER_INCO_NO_ERROR
	*/
	IncoCtlStopRecorder	
};

/*! \brief Query and manipulate miscellaneous internal library state and settings.

\param TargetPath if \a aiRequest is target-specific, specifies the target (\ref targetpath). Ignored for non-target-specific requests.
\param aiRequest a constant from enum ::IncoCtlRequest, determines the action to be performed.
\param apData pointer to request-specific input and output parameters.
\param auDataLength size of the structure or buffer pointed to by \a apData, request-specific.

\return ::ER_INCO_NO_ERROR on success.
\return ::ER_INCO_CTL_UNKNOWN_REQUEST if \a aiRequest is invalid.
\return A request-specific error code from <inco_32/errinco.h> (see \ref page_inco32errors).

See documentation of individual actions in ::IncoCtlRequest for information about use and meaning of \a TargetPath, \a apData, \a auDataLength, and possible return values.
*/
INCO32_EXPORT uint32 WINAPI IncoControl(const char* TargetPath, int32 aiRequest, void* apData, uint32 auDataLength);
//@}


//----------------------------------------------------------------------------
/*! \name Synchronous Calling of Asynchronous Procedures - Procedure Part (for Indel internal use)
(see also \ref syncasync) */
//----------------------------------------------------------------------------
//@{
INCO32_EXPORT  int32 WINAPI CheckoutAsyncCallTicket(void);
#ifdef __cplusplus
INCO32_EXPORT uint32 WINAPI ProcedureExAddResult		(int32 Ticket, const void* Result,
														 uint32 auResultSize=8/*sizeof(double)*/, uint32 auType=DF_INCO_TYPE_DOUBLE,
														 const char* ResultName=0);
#else
INCO32_EXPORT uint32 WINAPI ProcedureExAddResult		(int32 Ticket, const void* Result,
														 uint32 auResultSize, uint32 auType,
														 const char* ResultName);
#endif
INCO32_EXPORT uint32 WINAPI ProcedureExAddAppError		(int32 Ticket, uint32 auAppError);
INCO32_EXPORT   void WINAPI ReturnAsyncCallTicket(int32 Ticket);
INCO32_EXPORT  int32 WINAPI ReturnAsyncCallTicketAfterCallHasFinished(int32 aiMyTicket, int32 aiTicketToWaitFor);
//@}


/*! \name Synchronous Calling of Asynchronous Procedures (for Indel internal use) */
//@{
//---- functions to be called by deferred CallProcdure handlers --------------
//     (those that interrupt the call stack between CallProcedure()
//     and CINCOProcedure::ExecuteCallProc())
INCO32_EXPORT   void WINAPI PushDeferredCallTicket(int32 Ticket);
INCO32_EXPORT  int32 WINAPI PopDeferredCallTicket(void);
//@}

/*! \name Deprecated functions */
//@{
INCO32_EXPORT uint32 WINAPI PutBit               (const char* TargetPath, uint32 Address, uint32 Number, uint32* Value);
INCO32_EXPORT uint32 WINAPI GetBit               (const char* TargetPath, uint32 Address, uint32 Number, uint32* Value);
INCO32_EXPORT uint32 WINAPI PutOutput            (const char* TargetPath, const char* Output, uint32* Value);
INCO32_EXPORT uint32 WINAPI GetOutput            (const char* TargetPath, const char* Output, uint32* Value);
INCO32_EXPORT uint32 WINAPI PutInput             (const char* TargetPath, const char* Input, uint32* Value);
INCO32_EXPORT uint32 WINAPI GetInput             (const char* TargetPath, const char* Input, uint32* Value);
INCO32_EXPORT uint32 WINAPI PutFlag              (const char* TargetPath, const char* Flag, uint32* Value);
INCO32_EXPORT uint32 WINAPI GetFlag              (const char* TargetPath, const char* Flag, uint32* Value);
INCO32_EXPORT uint32 WINAPI GetError             (const char* TargetPath);
INCO32_EXPORT uint32 WINAPI GetServerRevisionS	 (uint8* aServerVersion);
//@}

/*!
\fn INCO32_EXPORT uint32 WINAPI GetVariable          (const char* TargetPath, const char* ItemPath, void* Result, uint32 Length=0);
\ingroup commonfunctions 
\brief Remote INCO variable read

Reads variable \a ItemPath on target \a TargetPath and stores the return value, cast to a <tt>double</tt> if \a Length is 0 
or cast to a sequence of <tt>char</tt>s if length is unequal 0, in \a *Result.
If the variable must be read asynchronously, this function waits for the asynchronous reading to complete. Caution: this waiting means that asynchronous variable getters must be implemented carefully to avoid deadlocks!
\param TargetPath \ref targetpath
\param ItemPath \ref incoitemname
\param Result Pointer to the buffer to which the value will be written to. Must be a <tt>double</tt> in \a Length is 0 or a <tt>char*</tt> of at least \a Length size.
\param Length A value of 0 means that a <tt>double</tt> (or any other number item) should be read. A value > 0 means to read a data buffer (usually a char*) of size \a Length
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).

See also \ref syncasync

\fn INCO32_EXPORT uint32 WINAPI PutVariable          (const char* TargetPath, const char* ItemPath, const void* Value, uint32 Length=0);
\ingroup commonfunctions 
\brief Remote INCO variable write

Writes the data pointed to by \a Value to the INCO variable \a ItemPath on target \a TargetPath. The data type to which \a Value points to depends on the value of \a Length and must 
either be a <tt>char*</tt> (\a Length > 0) or a <tt>double</tt> (\a Length 0).
\param TargetPath \ref targetpath
\param ItemPath \ref incoitemname
\param Value Pointer to the value that should be written. If \a Length is 0, \a Value is expected to point to a <tt>double</tt>. Otherwise a <tt>char*</tt>.
\param Length If 0, then \a Value must point to a <tt>double</tt>. If > 0, this function writes as many bytes as defined by \a Length to \a ItemPath.
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).


\fn INCO32_EXPORT uint32 WINAPI CallProcedure(const char* TargetPath, const char* CallProcedure, double* Result);
\ingroup commonfunctions
\brief Remote procedure call

Calls procedure \a ItemPath on target \a TargetPath and stores the return value, cast to a <tt>double</tt>, in \a *Result.
\note This function can not properly handle RPCs with asynchronous actions, because it can't wait for its asynchronous part. Use CallProcedureEx if asynchronously executing procedures needs to be called.
\param TargetPath \ref targetpath
\param CallProcedure \ref callproceduresyntax
\param Result Pointer to a <tt>double</tt> into which the function writes the value returned by the remote procedure
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).


\fn INCO32_EXPORT  int32 WINAPI CheckoutAsyncCallTicket();
\brief Called by an asynchronous procedure when an asynchronous action starts

During its synchronous part, a procedure calls this function to tell libinco_32 that it is about to start an asynchronous part. It must make sure that the returned ticket is eventually returned to libinco_32 using ReturnAsyncCallTicket() (when the asynchronous part finishes) or ReturnAsyncCallTicketAfterCallHasFinished(). May be called multiple times, but each one must be balanced by a call to ReturnAsyncCallTicket() or ReturnAsyncCallTicketAfterCallHasFinished().

See also \ref syncasyncdetails in \ref syncasync


\fn INCO32_EXPORT uint32 WINAPI ProcedureExAddResult(int32 Ticket, const void* Result, uint32 auResultSize=8, uint32 auType=DF_INCO_TYPE_DOUBLE, const char* ResultName=NULL);
\brief Called by an asynchronous procedure to return a result value

When an asynchronous part of a procedure wants to return one or more values, it calls this function before calling ReturnAsyncCallTicket(). If this function is called multiple times (or by multiple asynchronous parts), multiple results are stored in the order of the calls. The caller of the asynchronous procedure, if interested, can later fetch the returned values using CallProcedureExResult() (this happens automatically in CallProcedureExSync()).

\param Ticket The ticket that the synchronous part of the procedure got from CheckoutAsyncCallTicket().
\param Result Pointer to the value to be set, e.g. a <tt>uint32*</tt> or <tt>double*</tt> for typical numerical results or a <tt>char*</tt> for strings.
\param auResultSize Size of the value stored at \a Result in bytes, e.g. <tt>sizeof(uint32)</tt> = 4 or <tt>sizeof(double)</tt> = 8 for typical numerical results or the string length plus one (for the terminating zero) for strings.
\param auType An INCO type constant from <inco_32/indeldefs.h> such as ::DF_INCO_TYPE_UINT32, ::DF_INCO_TYPE_DOUBLE, ::DF_INCO_TYPE_STRING etc., matching \a Result and \a auResultSize.
\param ResultName A string specifying the name under which the result can later be retrieved using CallProcedureExResultByName(), if NULL (the default) or empty, the result is anonymous.

\return ::ER_INCO_NO_ERROR on success
\return ::ER_INCO_RPC_NOT_A_TICKET if \a Ticket is not a ticket (i.e. not negative)
\return ::ER_INCO_RPC_RESULT_BUFFER_TO_SMALL if the specified result is too large to fit into the ring buffer for asynchronous results

See also \ref syncasyncretval in \ref syncasync


\fn INCO32_EXPORT uint32 WINAPI ProcedureExAddAppError(int32 Ticket, uint32 auAppError);
\brief Called by an asynchronous procedure to return an application error

When an asynchronous part of a procedure wants to return an application error (see \ref incoreturn_application_erros), it calls this function before calling ReturnAsyncCallTicket(). Application errors differ from ordinary result values (as set by ProcedureExAddResult()) in that they are retrieved as the return value of CallProcedureExResult() rather that through its pointer arguments. For a given ticket, there is at most one application error and it always comes before any other results. Calling this function will wipe out any results previously added using ProcedureExAddResult() and replace any previously set application error. You can, however, add more results after setting the application error, e.g. to give details about the error.

\param Ticket The ticket that the synchronous part of the procedure got from CheckoutAsyncCallTicket().
\param auAppError The error code to be set. Should be in the range reserved for application errors, as defined in \ref incoreturn_application_erros, however this is not enforced.

\return ::ER_INCO_NO_ERROR on success
\return ::ER_INCO_RPC_NOT_A_TICKET if \a Ticket is not a ticket (i.e. not negative)

See also \ref syncasyncretval in \ref syncasync


\fn INCO32_EXPORT   void WINAPI ReturnAsyncCallTicket(int32 Ticket);
\brief Called by an asynchronous procedure when an asynchronous action finishes

When an asynchronous part of a procedure finishes, it calls this function to return the ticket that its invoker got from CheckoutAsyncCallTicket() to libinco_32. Libinco_32 considers a procedure finished when all checked out tickets have been returned.

If \a Ticket is 0, this function does nothing. If it is called with any other non-ticket (i.e. positive) value, or if it is called too many times with the same ticket (more times than CheckoutAsyncCallTicket()), an assertion failure occurs.

See also \ref syncasyncdetails in \ref syncasync


\fn INCO32_EXPORT  int32 WINAPI ReturnAsyncCallTicketAfterCallHasFinished(int32 aiMyTicket, int32 aiTicketToWaitFor);
\brief Called by an asynchronous procedure to declare an asynchronous action completed as soon as another asynchronous procedure finishes

Used when an asynchronous procedure A calls another asynchronous procedure B, and A can only be considered finished when B is finished as well (in other words, the call to B is an asynchronous part of A). This function does not wait for B to finish, it merely instructs libinco_32 to perform (the equivalent of) \link ReturnAsyncCallTicket() ReturnAsyncCallTicket(\endlink\a aiMyTicket) later and returns immediately.

If \a aiTicketToWaitFor is not a ticket (negative) but a success/error code (zero/positive), \a aiMyTicket is immediately returned to libinco_32 and this function returns the non-ticket \a aiTicketToWaitFor. Therefore, it can be used as a transparent wrapper around CallProcedureEx() as seen in this common idiom, which does the right thing whether or not ProcB is asynchronous and whether or not the call to it succeeds:
\par
\code
uint32 INCOProcA() {
	int32 err = ReturnAsyncCallTicketAfterCallHasFinished(
		CheckoutAsyncCallTicket(),
		CallProcedureEx(".", "Cmd.ProcB(17:l)")
	);
	if (err > 0) {
		yell("Error!");
		return 1;
	}
	else return 0;
}
\endcode

\return Zero on success, \a aiTicketToWaitFor if it is not a ticket.

See also \ref syncasyncwithin in \ref syncasync


\fn INCO32_EXPORT  int32 WINAPI CallProcedureEx(const char* TargetPath, const char* CallProcedure, double* SyncResult=NULL);
\ingroup commonfunctions
\brief Remote procedure call (extended).

Replaces CallProcedure() and adds support for asynchronous procedures. Calls procedure \a CallProcedure on target \a TargetPath and stores any return value, cast to a <tt>double</tt>, in \a *SyncResult. If the called procedure is asynchronous, this function returns before the asynchronous part of the procedure action has completed.

\param TargetPath \ref targetpath
\param CallProcedure \ref incoitemname
\param SyncResult Will be set to the return value of synchronously executing procedures. If NULL is passed (default), the result will be ignored. If \a CallProcedure is an asynchronous procedure, then \a SyncResult will not be altered (because such a function does not return any synchronous result).
\return A ticket (negative number) or an error (see \ref page_inco32errors).

Typical use case: CallProcedureEx() is a perfect replacement for CallProcedure(). Therefore, whenever CallProcedure() can be used, you may prefer using CallProcedureEx(). In some certain use cases, it may be more straight-forward to use CallProcedureExSync().

\sa \ref page_callprocedure_usecase_syncprocedure\n
	\ref page_callprocedureex_usecase_withoutresults\n
	\ref page_callprocedureex_usecase_withresults\n
	\ref page_callprocedureex_usecase_withnamedresults


\fn INCO32_EXPORT uint32 WINAPI CallProcedureExSync(const char* TargetPath, const char* CallProcedure, void* Result=NULL, uint32 BufferSize=8, uint32 TypeFlags=DF_INCO_TYPE_NUMBER_VALUE);
\ingroup commonfunctions
\brief Remote procedure call (extended). If the procedure has an asynchronous part, the function will wait for it to complete.

Calls procedure \a CallProcedure on target \a TargetPath. If the called procedure is asynchronous, this function implicitly waits for the asynchronous part of the procedure action to complete.

\param TargetPath \ref targetpath
\param CallProcedure \ref incoitemname
\param Result If not NULL (default) and the procedure has no asynchronous part, then the synchronous result value will be set and \a Result is expected to be of type <tt>double*</tt> (and accordingly \a BufferSize = <tt>sizeof(double)</tt> = 8 and \a TypeFlags = ::DF_INCO_TYPE_NUMBER_VALUE). If the procedure has an asynchronous part and the asynchronous part returns at least one result, this function will return the first result and write it to \a Result (if it's not NULL). Note that all results (except the first one) are lost, because the caller doesn't get the ticket. Use CallProcedureEx() if you want to get more than one result.

Typical use case: Using CallProcedureExSync() makes sense if the programmer knows that the remote procedure does either have no asynchronous part, or it has an asynchronous part and returns zero or one result.

Note that for process-internal calls (\a TargetPath = "."), the included waiting may carry a risk of deadlocking - see CallProcedureExWait() for details.

\sa \ref page_callprocedure_usecase_syncprocedure for a code exmaple.


\fn INCO32_EXPORT uint32 WINAPI CallProcedureExWait(const char* TargetPath, int32 Ticket, int32 TimeoutMs=-1);
 \brief Wait for the asynchronous part of a remote procedure call (CallProcedureEx) to finish (optionally with timeout).

 This function is usually used waiting for the asynchronous part shouldn't be done infinitely. If waiting infinitely is ok, it's slightly more efficiently to use CallProcedureExResult directly.

 \param TargetPath \ref targetpath. The name of the target to which \a Ticket belongs. Must exactly match the target name that was passed to the CallProcedureEx() call that produced \a Ticket, behavior is undefined if different names that refer to the same target are used (with/without server name, with / or \\ as separator, aliases, etc.).
 \param Ticket Should be a valid ticket previously returned by CallProcedureEx()
 \param TimeoutMs Timeout used while waiting for the asynchronous part in [ms]. If -1 is passed, then the call will block forever, until the asynchronous part completed, or an error occurs. If 0 is passed, then the function will not wait but instead just check whether the asynchronous part has already completed and will return immediately. This can be used for "polling". Note that, depending on the used OS (Windows vs. Linux), the smallest applicable timeout may be around 10ms. Thus, even if you pass 1ms here, it'll probably result in 10ms.
 \return ::ER_INCO_NO_ERROR if the async part referred to by \a Ticket has completed, or the INCOServer has detected that it was interrupted by a target reset (check for return value ::ER_INCO_RPC_INTERRUPTED from CallProcedureExResult() to detect the latter situation).
 \return ::ER_INCO_RPC_WAIT_TIMEOUT if the async part has not yet completed and waiting for it has timed out (or there was no waiting because \a TimeoutMs = 0).
 \return An INCO error code (see <inco_32/errinco.h>) in case of INCO communication problems (e.g. INCOServer not running). Note that this function does not return application errors, therefore, it can't be used to check whether an async part has completed with success or error. Instead, it can just be used to check whether the async part has finished.
 \return This function does NOT return application errors and reply codes (i.e. the errors set by MsgError & co in McRobot). Always use CallProcedureExResult for that purpose.

\sa \ref page_callprocedure_usecase_syncprocedure\n
	\ref page_callprocedureex_usecase_withoutresults\n
	\ref page_callprocedureex_usecase_withresults\n
	\ref page_callprocedureex_usecase_withnamedresults

Typical use case: CallProcedureExWait() is usually only used if the programmer wants to wait with a timeout. For all other cases, CallProcedureExResult is the preferred way to wait for the completion for the asynchronous procedure becuase it does not only wait, but also return any occurred application error.

No guarantees are made about the accuracy of the timeout duration. The given number is a lower bound, but the total execution time of the function may be longer than that, since various parts of its internal implementation are not counted against the total.

If the called procedure is not in the same process, but the call goes to an external target via INCOServer (i.e. \a TargetPath is not <tt>"."</tt>), this function must only be called by the same thread that made the original CallProcedureEx() call. For calls within a process, no such restriction exists and any number of threads can wait.

For process-internal calls, be careful when using this function, particularly with infinite timeout: Make sure that by waiting, you are not inadvertently blocking the action that you are waiting for, causing a deadlock. In particular, this can happen in the following two situations:
- The asynchronous action waited for is queued to be executed in the same thread that calls CallProcedureExWait(). Putting that thread to sleep now means that it never gets to attend its queue.
- The thread that calls CallProcedureExWait() is holding some lock that the thread running the asynchronous action needs to acquire before or during the action.

Within another INCO procedure in particular, a better solution than
\code
CallProcedureExWait(".", CallProcedureEx(".", "Cmd.Proc()"));
\endcode
is usually
\code
ReturnAsyncCallTicketAfterCallHasFinished(
	CheckoutAsyncCallTicket(),
	CallProcedureEx(".", "Cmd.Proc()")
);
\endcode

See also \ref syncasyncwithin


\fn INCO32_EXPORT uint32 WINAPI CallProcedureExResult			(const char* TargetPath, int32 Ticket, void* Result=NULL, 
															 uint32 BufferSize=8, uint32 TypeFlags=DF_INCO_TYPE_NUMBER_VALUE, 
															 char* ResultName=NULL, uint32 ResultNameBufSize=0);
\ingroup commonfunctions
\brief Get the next asynchronous result (or application error) of a remote procedure call (CallProcedureEx).

Get the next available (means: not yet gotten) result that was returned by the asynchronous part of the procedure that returned \a Ticket. The function implicitly waits indefinitely for the asynchronous part of the procedure to complete. The caller task will therefore be blocked until the async part has finished. (Note that in the case of process-internal calls (\a TargetPath is "."), this may be dangerous! See CallProcedureExWait() for details.)

There are two pieces of information that are considered "results", both returned by the asynchronous part of a procedure:

 - Zero or one application error (if any)
 - Zero or multiple results (or named results)

The function is used to get these results. The results can either be get as "number values" cast to a double (by passing ::DF_INCO_TYPE_NUMBER_VALUE for \a TypeFlags) or as "type safe" values by passing one of the other supported types (see <inco_32/indeldefs.h>). 

The same result can exactly be read once. This is the case because the result will be removed from the internal buffer after being read. Result values that are not explicitly removed from libinco_32's storage by calling this funtion will eventually be dropped anyway if required to free up space for the results of newer asynchronous procedure calls.

To mention it explictly: To check whether a asynchronous call which does not return any results (such as the CINOSMcRobot::Off command) returned an application error, you need to call this function with \a Result set to NULL.

\param TargetPath \ref targetpath. The name of the target to which \a Ticket belongs. Must exactly match the target name that was passed to the CallProcedureEx() call that produced \a Ticket, behavior is undefined if different names that refer to the same target are used (with/without server name, with / or \\ as separator, aliases, etc.).
\param Ticket The ticket that belongs to the asynchronous part of the procedure of which this function returns the next result. The value of \a Ticket is usually returned by CallProcedureEx().
\param Result If not NULL (NULL is default), then the result value will be written to the memory pointed to by \a Result. Note that the function writes at most \a BufferSize [Bytes]. If the result is a string, it will always be zero-terminated (even if truncated). Truncation is indicated by returning ::ER_INCO_RPC_RESULT_BUFFER_TO_SMALL, and in this case the result will not be removed from storage, so that another call with a sufficiently sized buffer can get its entire value.
\param BufferSize Memory size in [Bytes] where \a Result points to. The function will at most write this amount of data to \a Result
\param TypeFlags Any supported type (DF_INCO_TYPE_*) as defined in <inco_32/indeldefs.h> can be passed. The function expects the passed type to match the type of the result. Example: If the asynchronous part of an INOS procedure uses pMsg->AddResult((uint8)77), then the caller must pass ::DF_INCO_TYPE_UINT8\n
There's an exception to the rule above: Any number value (except (u)int64) can automatically be converted to a double by passing ::DF_INCO_TYPE_NUMBER_VALUE.\n
Alternatively, pass ::DF_INCO_FLAG_GET_RESULT_TYPE to get the type (as defined in <inco_32/indeldefs.h>) of the result, instead of its value. Pass ::DF_INCO_FLAG_GET_RESULT_LENGTH to get its length in bytes (mainly used for strings, where it includes the terminating zero). In these two cases, \a Result must be a pointer to a <tt>uint32</tt> and \a BufferSize must be <tt>sizeof(uint32)</tt> = 4, and the result will (of course) not be removed from the internal buffer and thus the caller can get the actual result by a subsequent call to this function.
\param ResultName [out] Optional pointer to a string buffer that will take the result name, if any. The name will not be set if the pointer is NULL (default).
\param ResultNameBufSize Buffer size (= string length + 1) in [Bytes] of the available buffer \a ResultName. The function will at most write \a ResultNameBufSize - 1 Bytes of the result name and will ensure that the string in \a ResultName will be zero-terminated.
\return On success: ::ER_INCO_NO_ERROR
\return If the procedure returned no results and no application error, only an indication that it is done (only for calls to external targets): ::ER_INCO_RPC_NO_RETURN_VALUE
\return If all results (or completion indication or application error) have already been retrieved or were dropped to free up space because they were not retrieved in time (or no results were returned for process-internal calls): ::ER_INCO_RPC_UNKNOWN_TICKET
\return On INCO failure: Any INCO error, as defined in <inco_32/errinco.h>
\return If the procedure was interrupted by a target reset: ::ER_INCO_RPC_INTERRUPTED. No results are available in that case.
\return Application error: If the asynchronous part of the procedure encountered any problem, the application error will be returned on the first call to this function for a given ticket. See \ref incoreturn_application_erros. Additional results may still be available after that.

\sa \ref page_callprocedure_usecase_syncprocedure\n
	\ref page_callprocedureex_usecase_withoutresults\n
	\ref page_callprocedureex_usecase_withresults\n
	\ref page_callprocedureex_usecase_withnamedresults\n
	\ref syncasyncretval in \ref syncasync


\fn INCO32_EXPORT uint32 WINAPI CallProcedureExResultByName		(const char* TargetPath, int32 Ticket, const char* ResultName, void* Result, 
															 uint32 BufferSize=8, uint32 TypeFlags=DF_INCO_TYPE_NUMBER_VALUE);
\ingroup commonfunctions
\brief Get the next asynchronous named result (or application error) of a remote procedure call (CallProcedureEx).

This function is very similar to CallProcedureExResult(). The only difference is that this function does not return the 'next result' but the result with the name referred to by ResultName. Similar to CallProcedureExResult(), once a certain result has been read, it can't be read again. This is true independently of whether you use CallProcedureExResult() or CallProcedureExResultByName() the second time.

Lets make an example to clarify this: Assume there are three results for a certain ticket. Assume they have the name "Result1", "Result2" and "Result3". If the caller performs the following code (pseudocode):
\code
CallProcedureExResultByName(..., "Result2", ...);
\endcode
Then the following is true:
\code
CallProcedureExResult(...);	// return the value of "Result1"
CallProcedureExResult(...);	// return the value of "Result3"
\endcode

\param TargetPath \ref targetpath
\param ResultName Zero terminated string of the result name

\sa \ref page_callprocedure_usecase_syncprocedure\n
	\ref page_callprocedureex_usecase_withoutresults\n
	\ref page_callprocedureex_usecase_withresults\n
	\ref page_callprocedureex_usecase_withnamedresults


\fn INCO32_EXPORT uint32 WINAPI GetErrorDescription  (const char* TargetPath, uint32 Error, char* Description, uint32 Length);
\ingroup commonfunctions
\brief Convert an INCO error (see also \ref incoreturn_inco_errors) to human readable string.

\param TargetPath \ref targetpath. The name of the slave/target for which a previous call failed
\param Error The error code that was previously returned by an INCO function, such as CallProcedure(), GetVariable(), PutVariable(), etc.
\param Description If \a Length is unequal 0, this parameter should point to a string buffer. The function copies the error text into that buffer.\n
	If \a Length is 0, then \a Description should point to a long.
\param Length If \a Length is unequal 0, then its value is the maximum allowed string length (not buffer size!). Internally, the function call 'strncpy(Description, {TheErrorText}, Length);'.\n
	If \a Length is 0, then the function assumes that \a Description points to a 'long' value and the function writes the required buffer size (not string length!) to it.

Trivial example (complicated):
\code
// Create a buffer that's huge enough:
char cErrorMsg[512];
if( GetErrorDescription("TargetName", uError, cErrorMsg, sizeof(cErrorMsg)-1) == ER_INCO_NO_ERROR ) {
	cout << "Error occurred: " << cErrorMsg << endl;
}
\endcode

Example (complicated):
\code
// Get the required buffer size:
long iRequiredBufferSize;
if( GetErrorDescription("TargetName", uError, &iRequiredBufferSize, 0) == ER_INCO_NO_ERROR ) {
	char pErrorText = new char[iRequiredBufferSize];
	// get the actual error text:
	if( GetErrorDescription("TargetName", uError, pErrorText, iRequiredBufferSize-1) == ER_INCO_NO_ERROR ) {
		cout << "Error occurred: " << pErrorText << endl;
		delete [] pErrorText;
	}
}
\endcode


\fn INCO32_EXPORT   void WINAPI PushDeferredCallTicket(int32 Ticket);
\brief Called by a deferred CallProcedure handler to put a ticket back on libinco_32's stack

This function is used in the inner workings of \ref syncasync and is not of general interest. See CDeferredProcedureCallData::Perform() in libinix for an example of its use.


\fn INCO32_EXPORT  int32 WINAPI PopDeferredCallTicket();
\brief Called by a deferred CallProcedure handler to remove a ticket from libinco_32's stack

This function is used in the inner workings of \ref syncasync and is not of general interest. See CDeferredProcedureCallData::Perform() in libinix for an example of its use.


\fn INCO32_EXPORT uint32 WINAPI PutBlock8            (const char* TargetPath, uint32 DestAddress, const uint8* Data, uint32 Number);
\ingroup commonfunctions
\brief Write raw data in 8 byte chunks to the target.

Writes \a Number bytes of the data pointed to by \a Data to the address \a DestAddress in the INCO target \a TargetPath. \a DestAddress may by any address available at the target. Note that the target does usually allow arbitrary memory writes - even if modifying the data will cause target crashes. Therefore, using this function is only recommended in rare cases. The function assumes that \a Data is at least as big as \a Number bytes.

\param TargetPath \ref targetpath
\param DestAddress The 32 bit memory address (target side)
\param Data Pointer to the data that should be written to the target
\param Number Number of 8 byte chunks to transfer
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).

\fn INCO32_EXPORT uint32 WINAPI GetBlock8            (const char* TargetPath, uint32 SourceAddress, uint8* Data, uint32 Number);
\ingroup commonfunctions
\brief Reads raw data in 8 byte chunks from the target.

Reads \a Number of bytes of data from the memory at \a SourceAddress in the INCO target \a TargetPath and copies that data into the buffer pointed to by \a Data. The function assumes that \a Data is at least as big as \a Number bytes.

\param TargetPath \ref targetpath
\param SourceAddress The 32 bit memory address (target side)
\param Data Pointer to the data to which the read data should be written
\param Number Number of 8 byte chunks to transfer
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).


\fn INCO32_EXPORT uint32 WINAPI GetBlock8Real        (const char* TargetPath, uint32 SourceAddress, uint8* Data, uint32 Number);
\brief For Indel internal use: Read 8 byte chunks of data from target by resolving breakpoints.
\param TargetPath \ref targetpath
\param SourceAddress The 32 bit memory address (target side)
\param Data Pointer to the data to which the read data should be written
\param Number Number of 8 byte chunks to transfer
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).

\fn INCO32_EXPORT uint32 WINAPI PutBlock16           (const char* TargetPath, uint32 DestAddress, const uint16* Data, uint32 Number);
\ingroup commonfunctions
\brief Write raw data in 16 bytes chungs to the target.

Same as ::PutBlock8, but writes \a Number times 16 byte of data. This function automatically changes endianness of the data if the target and host endiannes are different.

\param TargetPath \ref targetpath
\param DestAddress The 32 bit memory address (target side)
\param Data Pointer to the data that should be written to the target
\param Number Number of 16 byte chunks to transfer
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).

\fn INCO32_EXPORT uint32 WINAPI GetBlock16           (const char* TargetPath, uint32 SourceAddress, uint16* Data, uint32 Number);
\ingroup commonfunctions
\brief Read raw data in 16 bytes chungs from the target.

Same as ::GetBlock8, but reads \a Number times 16 byte of data. This function automatically changes endianness of the data if the target and host endiannes are different.
\param TargetPath \ref targetpath
\param SourceAddress The 32 bit memory address (target side)
\param Data Pointer to the data to which the read data should be written
\param Number Number of 16 byte chunks to transfer
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).

\fn INCO32_EXPORT uint32 WINAPI PutBlock32           (const char* TargetPath, uint32 DestAddress, const uint32* Data, uint32 Number);
\ingroup commonfunctions
\brief Write raw data in 32 bytes chungs to the target.

Same as ::PutBlock8, but writes \a Number times 32 byte of data. This function automatically changes endianness of the data if the target and host endiannes are different.
\param TargetPath \ref targetpath
\param DestAddress The 32 bit memory address (target side)
\param Data Pointer to the data that should be written to the target
\param Number Number of 32 byte chunks to transfer
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).

\fn INCO32_EXPORT uint32 WINAPI GetBlock32           (const char* TargetPath, uint32 SourceAddress, uint32* Data, uint32 Number);
\ingroup commonfunctions
\brief Read raw data in 32 bytes chungs from the target.

Same as ::GetBlock8, but reads \a Number times 32 byte of data. This function automatically changes endianness of the data if the target and host endiannes are different.
\param TargetPath \ref targetpath
\param SourceAddress The 32 bit memory address (target side)
\param Data Pointer to the data to which the read data should be written
\param Number Number of 32 byte chunks to transfer
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).

\fn INCO32_EXPORT uint32 WINAPI PutBlock64           (const char* TargetPath, uint32 DestAddress, const uint64* Data, uint32 Number);
\ingroup commonfunctions
\brief Write raw data in 64 bytes chungs to the target.

Same as ::PutBlock8, but writes \a Number times 64 byte of data. This function automatically changes endianness of the data if the target and host endiannes are different.
\param TargetPath \ref targetpath
\param DestAddress The 32 bit memory address (target side)
\param Data Pointer to the data that should be written to the target
\param Number Number of 64 byte chunks to transfer
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).

\fn INCO32_EXPORT uint32 WINAPI GetBlock64           (const char* TargetPath, uint32 SourceAddress, uint64* Data, uint32 Number);
\ingroup commonfunctions
\brief Read raw data in 64 bytes chungs from the target.

Same as ::GetBlock8, but reads \a Number times 64 byte of data. This function automatically changes endianness of the data if the target and host endiannes are different.
\param TargetPath \ref targetpath
\param SourceAddress The 32 bit memory address (target side)
\param Data Pointer to the data to which the read data should be written
\param Number Number of 64 byte chunks to transfer
\return An error code from <inco_32/errinco.h> (see \ref page_inco32errors).


\fn INCO32_EXPORT uint32 WINAPI GetRevisions         (const char* TargetPath, uint32* ServerRevision, uint32* DllRevision);
\ingroup commonfunctions
\brief Function to get the INCOServer and libinco_32 revisions.

\fn INCO32_EXPORT uint32 WINAPI GetServerRevisionS	 (uint8* aServerVersion);
\deprecated
\brief Function to get the INCOServer revision.
*/


#ifdef __cplusplus
}	// extern "C"
#endif


//------------------------------------------------------------------------------

#endif		// INCO_32_H


//------------------------------------------------------------------------------
// end of file

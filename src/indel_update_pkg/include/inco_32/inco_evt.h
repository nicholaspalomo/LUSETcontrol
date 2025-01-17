//**************************************************************************
/*!
	\file
	\author		Raphael Zulliger <zulliger@indel.ch>, &copy; INDEL AG
	\version
	\verbatim

	2397, 2007-12-24 16:04:14 +0100 (Mo, 24 Dez 2007), zulliger
	+ Initially added the standard-Indel header to the files and thereby making
	  the files icommit ready

	2398, 2007-12-24 16:07:03 +0100 (Mo, 24 Dez 2007), zulliger
	+ Initially added the standard-Indel header to the files and thereby making
	  the files icommit ready

	2447, 2008-01-29 11:45:20 +0100 (Di, 29 Jan 2008), walther
	! Disable logging on Windows CE since it doesn't have <sstream>.

	2618, 2008-02-27 15:46:42 +0100 (Wed, 27 Feb 2008), walther
	! Set svn:eol-style property where appropriate and svn:ignore a generated
	  file. [25 files]

	2629, 2008-02-29 15:30:15 +0100 (Fr, 29 Feb 2008), walther
	! Just noticed that I made a bit of a mess in the changelogs in r2618. Not
	  sure what happened - cleaning this up...

	3838, 2009-12-14 14:40:59 +0100 (Mon, 14 Dec 2009), walther
	! eColorYellow, used for warnings in event logs, was hard to read on light
	  backgrounds, and besides, not remotely yellow - changed.

	5880, 2013-12-19 15:23:25 +0100 (Thu, 19 Dec 2013), zulliger
	+ Added possibility to adjust log levels of traces generated by libinco_32
	  itself by a new API call that doesn't require a callback to be installed.
	  This is especially important for languages (such as .Net) for which
	  calling a 'callback' for each log message is expensive.

	$LastChangedRevision: 5883 $ $Date: 2013-12-20 07:46:20 +0100 (Fri, 20 Dec 2013) $ $Author: zulliger $
	! Completely reworked libinco_32 tracing: The library is now using the
	  INIX-trace mechanism as well (INIX_ERROR, INIX_WARNING, ...). All traces
	  to stderr have been removed. Thanks to this change, INIX apps (as well as
	  customer applications, such as HMIs) are easily able to get all logs
	  generated by libinco_32 (such as error messages which are generated when
	  async results are dropped).

	$Comment$

	u = unreleased
	+ = new feature
	! = change, bugfix
	- = removed

	\endverbatim

	\remarks
	\verbatim
	project			: incoserver
	language		: C++
	system			: Linux, Windows - x86/PPC
	\endverbatim

	\brief Eventlog API for inco_32 applications

*/
//**************************************************************************


#ifndef INCO_EVT_H
#define INCO_EVT_H

#include <inco_32/inco_32.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(UNDER_CE) && !defined(INIX_DISABLE_LOGGING)
	// Windows CE doesn't have <sstream>
	#define INIX_DISABLE_LOGGING
#endif

//----------------------------------------------------------------------------
// 'INIX 1.0 Logging' function calls
//----------------------------------------------------------------------------
typedef uint32 (WINAPI *tLoggingCallback)( uint16 auBitNumber, const char* apFctName, const char* apFileName, uint32 auLineNumber, uint32 auFontColor, const char* apLogText );
typedef uint32 (WINAPI *tLoggingLevelCallback)( uint16 auBitNumber );
typedef uint32 (WINAPI *tLoggingCreateLevelCallback)( const char* apLevelName, int32* apBitNumber );
/** Initializes the logging framework used by this "INCO library" and,
 optionally, also by applications that link to this library (e.g. INIX
 uses it).
 \param apCallback The callback to the function that takes the actual log
 	 message.
 \param apLevelCallback The callback to the function that is called to detect
	whether a specific log level is active
 \param apCreateLevelCallback The callback used to create an additional log
 	 level (e.g. used by inix.exe to create log levels). Note that there exist
 	 	certain predefined log levels, see EPredefinedLogLevels

 There are two common use cases how this logging framework is used:

  - An application sets all callbacks: Then the application has a "managment
  	  facility" to create log levels and also to manage whether they're
  	  active or not. This is how inix.exe uses the logging facility. inix.exe
  	  does create its own log levels and uses the logging API for its own log
  	  information.
  - An application just wants to receive logs created by this INCO library in
  	  order to have useful information in case of misbehavior. In this use case,
  	  it makes sense to register the apCallback (to receive the log message)
  	  but you usually don't set apLevelCallback (used to decide whether a level
  	  is active or not). Instead, the application may prefer to leave the
  	  apLevelCallback NULL and use LogActivateLevels to activate/deactivate
  	  certain levels. See EPredefinedLogLevels for a list of available levels
  	   */
INCO32_EXPORT uint32 WINAPI LogInit( tLoggingCallback apCallback, tLoggingLevelCallback apLevelCallback, tLoggingCreateLevelCallback apCreateLevelCallback );
/** Used by the log system to check whether a certain log level is active.
 See e.g. INIX_ERROR, INIX_WARNING, etc. to see how its used. */
INCO32_EXPORT uint32 WINAPI LogLevelActive( uint32 auBitNumber );
/** Used by applications, such as inix.exe, to create additional log levels
 used to generate application specific log messsages. */
INCO32_EXPORT uint32 WINAPI LogCreateLevel( const char* apLevelName, int32* apBitNumber );
/** Used by the log system to actually create a log entry. See e.g.
 INIX_ERROR, INIX_WARNING, etc. to see how its used. This function should
 only be called when LogLevelActive returned that the level is 'active'. If
 that rule is not followed, the message will be logged anyway. */
INCO32_EXPORT uint32 WINAPI LogMessage( uint16 auBitNumber, const char* apFctName, const char* apFileName, uint32 auLineNumber, uint32 auFontColor, const char* apLogText ) ;
/*! \brief activates or deactivates specific log levels
	\param auFrom the first bitnumber that should be modified
	\param auTo the last bitnumber that should be modified (if only
		   one specific bit should be modified, auTo has the same value
		   as auFrom). Note: auTo will also be modified!
	\param abActive specifies, if the given bit(s) should be activated
		   (in the case of abActive != 0) or deactivated.
	\note auFrom and auTo are uint16, although uint8 would be sufficient
		  but for easier handling in the function (see code) in the case
		  where the maximal levels are set to 256, these args are uint16 */
INCO32_EXPORT uint32 WINAPI LogActivateLevels( uint16 auFrom, uint16 auTo, uint8 abActive );

//----------------------------------------------------------------------------
// Logging helper macros
//----------------------------------------------------------------------------

enum EColors { eColorStd = 0, 
			eColorRed = 0x000000ff,
			eColorGreen = 0x0000c000,
			eColorYellow = 0x00005266,
			eColorBlue = 0x00ff0000,
			eColorWhite = 0x00ffffff };

enum EPredefinedLogLevels { eFatalError = 0,
							eError = 1,
							eWarning = 2,
							eMessage = 3,
							eVerbose = 4,
							eServerFrames = 5,
							eInProcessFrames = 6,
							eCallProcedureEx = 7,

							eFirstUserSpecific = 10
};

//--- InternLog (Helper macro used by every "real" log macro) ------------------
#ifdef INIX_DISABLE_LOGGING
	#define InternLog( auBitNumber, auFctName, auColor, aLogText )
#else
	#define InternLog( auBitNumber, auFctName, auColor, aLogText ) \
		if( LogLevelActive(auBitNumber) == DF_ER_INIX_LOGGER_LEVEL_IS_ACTIVE ) \
		{ \
			do \
			{ \
				using namespace std; \
				ostringstream Text; \
				Text << aLogText; \
				LogMessage( auBitNumber, \
				auFctName, \
				__FILE__, \
				__LINE__, \
				auColor, \
				Text.str().c_str() ); \
			} while(0); \
		} 
#endif // INIX_DISABLE_LOGGING

//--- INIX_FATALERROR ------------------------------------------------------------
#define INIX_FATALERROR( auFctName, aStream ) \
	InternLog( eFatalError, auFctName, eColorRed, aStream ) \
	wxASSERT(0)

//--- INIX_ERROR ------------------------------------------------------------
#define INIX_ERROR( auFctName, aStream ) \
	InternLog( eError, auFctName, eColorRed, aStream )

//--- INIX_WARNING ---------------------------------------------------------------
#define INIX_WARNING( auFctName, aStream ) \
	InternLog( eWarning, auFctName, eColorYellow, aStream )

//--- INIX_MESSAGE ---------------------------------------------------------------
#define INIX_MESSAGE( auFctName, aStream ) \
	InternLog( eMessage, auFctName, eColorBlue, aStream )

//--- INIX_VERBOSE ---------------------------------------------------------------
#define INIX_VERBOSE( auFctName, aStream ) \
	InternLog( eVerbose, auFctName, eColorStd, aStream )

//--- INIX_TRACE ---------------------------------------------------------------
#define INIX_TRACE( auBitNumber, auFctName, aStream ) \
	InternLog( auBitNumber, auFctName, eColorStd, aStream )



//--- INIX_FATALERROR_COLOR ------------------------------------------------------------
#define INIX_FATALERROR_COLOR( auFctName, auColor, aStream ) \
	InternLog( eFatalError, auFctName, auColor,  \
			aStream ) \
	wxASSERT(0)

//--- INIX_ERROR_COLOR ------------------------------------------------------------
#define INIX_ERROR_COLOR( auFctName, auColor, aStream ) \
	InternLog( eError, auFctName, auColor, aStream )

//--- INIX_WARNING_COLOR ---------------------------------------------------------------
#define INIX_WARNING_COLOR( auFctName, auColor, aStream ) \
	InternLog( eWarning, auFctName, auColor, aStream )

//--- INIX_MESSAGE_COLOR ---------------------------------------------------------------
#define INIX_MESSAGE_COLOR( auFctName, auColor, aStream ) \
	InternLog( eMessage, auFctName, auColor, aStream )

//--- INIX_VERBOSE_COLOR ---------------------------------------------------------------
#define INIX_VERBOSE_COLOR( auFctName, auColor, aStream ) \
	InternLog( eVerbose, auFctName, auColor, aStream )

//--- INIX_TRACE_COLOR ---------------------------------------------------------------
#define INIX_TRACE_COLOR( auFctName, auColor, auBitNumber, aStream ) \
	InternLog( auBitNumber, auFctName, auColor, aStream )




#ifdef __cplusplus
}	// extern "C"
#endif


//------------------------------------------------------------------------------

#endif // INCO_EVT_H


//------------------------------------------------------------------------------
// end of file

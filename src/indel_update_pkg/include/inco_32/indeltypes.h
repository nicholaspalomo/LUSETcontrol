//******************************************************************************
/*!
	\file		indeltypes.h
	\author		Raphael Zulliger, &copy; INDEL AG
	\version	1.00
	\verbatim

  	2322, 2007-12-18 09:15:36 +0100 (Di, 18 Dez 2007), zulliger
  	! Many many changes. Too much to list in detail. But: A lot of
  	  McINCOFrame adjustments (especially regarding little/big-endian), a lot
  	  of cleanups in library structure, etc.

  	2323, 2007-12-18 10:49:05 +0100 (Di, 18 Dez 2007), zulliger
	- Removed obsolete definitions from file

  	2427, 2008-01-04 11:28:37 +0100 (Fr, 04 Jan 2008), zulliger
	- Removed error-clause if neither INDEL_WINDOWS nor INDEL_LINUX is defined.

  	2474, 2008-02-04 15:29:26 +0100 (Mo, 04 Feb 2008), zulliger
  	+ Added some commonly useful defs

  	3995, 2010-02-23 10:21:17 +0100 (Tue, 23 Feb 2010), fabi
  	! Adjusted to generate java classes with swig.

  	4292, 2010-07-01 16:49:46 +0200 (Do, 01 Jul 2010), tjericke
  	Added support for 64bit systems

  	4294, 2010-07-02 07:32:07 +0200 (Fr, 02 Jul 2010), tjericke
	! Don't define ptr_t types for windows projects, they are already defined.

  	4295, 2010-07-02 09:16:47 +0200 (Fr, 02 Jul 2010), tjericke
	! Changed intptr_t and uintptr_t to intptr and uintptr

	4296, 2010-07-02 09:42:39 +0200 (Fri, 02 Jul 2010), walther
	! Defining macro UL instead of ULL in r4292 was a typo. (We use the same
	  definition for both the 32 bit and 64 bit cases to stay true to the name
	  of the macro, I guess on an LP64 system using the resulting long long
	  constant in a long (int64) context should work fine.)

	4383, 2010-07-27 15:00:12 +0200 (Tue, 27 Jul 2010), tjericke
	! Changed defines of uint32 and int32 to use int instead of long. On windows the INDEL_NOLONG define 
	  has to be set (for backwards compatibility). Otherwise the old definition is used.

	4649, 2010-11-15 09:21:07 +0100 (Mo, 15 Nov 2010), zulliger
	! Fixed the Linux 64Bit definition of ULL and UL. The error popped up
	  because the unittests are now compiled by default when using ibuild.py

	4688, 2010-11-26 10:15:36 +0100 (Fr, 26 Nov 2010), fabi
	- Removed VC6 workaround.

	4987, 2011-10-19 16:13:42 +0200 (Wed, 19 Oct 2011), walther
	+ Port libindel to Mac OS X and iOS. Not all parts are implemented, but
	  enough to get libinco_32 to work (using TCP). Missing in particular:
	  global semaphores, shared-memory communication, network interface
	  functions. Linux implementation files that are also used on Mac OS X are
	  moved from src/src/linux to src/src/shared. Building for Mac OS X works
	  using ibuild.py like on Linux. For iOS, an Xcode project is provided. It
	  requires wxWidgets-2.9.2 (unmodified source distribution), placed
	  relative to the project as specified by the WXROOT build setting.

	5993, 2014-03-10 10:11:42 +0100 (Mon, 10 Mar 2014), zulliger
	! Changed inclusion of C++ header file to C header file. This allows using
	  the header file for C-only compilers, such as used by Matlab/Simulink to
	  access C-DLLs

	$LastChangedRevision: 6646 $ $Date: 2016-07-12 10:17:15 +0200 (Tue, 12 Jul 2016) $ $Author: walther $
	! Don't define snprintf as _snprintf on MSVC14, which now has a standards-
	  compliant implementation. (Using _snprintf as snprintf seems questionable
	  anyway, as it behaves differently from what is expected of a snprintf.)

	$Comment$

	u = unreleased
	+ = new feature
	! = change, bugfix
	- = removed

	\endverbatim

	\remarks
	\verbatim
	project			: IndelLib
	language		: C++ (Gnu, Visual C++)
	system			: Linux, Windows
	\endverbatim

	\brief Not yet described

*/
//******************************************************************************

#ifndef INDELTYPES_H
#define INDELTYPES_H

// --- 64bit definitions
#if defined(INDEL_LINUX) || defined(INDEL_INOS) || defined(INDEL_JAVA)
  #include <limits.h>
 #if __WORDSIZE == 64
    #define INDEL_64
  #endif
#elif defined(INDEL_MACOSX)
  #ifdef __LP64__
    #define INDEL_64
  #endif
#else
  #if defined(_WIN64)
    #define INDEL_64
  #endif
#endif

// --- general type definitions ---
typedef unsigned char         uint8;
typedef signed char           int8;
typedef unsigned short        uint16;
typedef signed short          int16;

#if defined(INDEL_LINUX) || defined(INDEL_MACOSX) || defined(INDEL_INOS) || defined(INDEL_JAVA)
	// defines for linux
	
	typedef unsigned int        uint32;
	typedef signed int           int32;
	
	#if defined(INDEL_64) 
	  // note: these typedefs have been choosen like this to match the
	  // definition of the C-Standard (see stdint.h). Thanks to this, 
	  // we may switch to the stdint.h typedefs, as soon as they've become
	  // part of the C++ standard as well
	  typedef unsigned  long	uint64;
	  typedef signed  long	int64;
	  #define LONGLONGFORMAT "l"
	  // The names ULL and UL may not be very appropriate anymore... but
	  // due to historical reason, we kept them like this
	  #define ULL(number)   number ## UL
	  #define LL(number)    number ## L
	 #else
	  typedef unsigned long long	uint64;
	  typedef signed long long	int64;
	  #define LONGLONGFORMAT "ll"
	  #define ULL(number)   number ## ULL
	  #define LL(number)    number ## LL
	 #endif


#else // assume windows
	// windows for windows
	#if defined(INDEL_NOLONG)
	  typedef unsigned int          uint32;
	  typedef signed int            int32; 
	#else
	  typedef unsigned long         uint32;
	  typedef signed long           int32;
	#endif
	
	typedef unsigned __int64	uint64;
	typedef signed __int64      int64;
	#define ULL(number)   number ## UI64
	#define LL(number)    number ## I64
	#define LONGLONGFORMAT "I64"

	#define strcasecmp _stricmp
	#define strncasecmp _strnicmp
	// MSVC14 now has a standards-compliant snprintf (whereas _snprintf has never been, so using it as snprintf is technically incorrect)
	#if !defined(snprintf) && _MSC_VER < 1900
		#include <stdio.h>
		#define snprintf _snprintf
	#endif
#endif

#if defined(INDEL_64)
   typedef int64    intptr;
   typedef uint64   uintptr;
#else
   typedef int32    intptr;
   typedef uint32   uintptr;
#endif


#endif // INDELTYPES_H

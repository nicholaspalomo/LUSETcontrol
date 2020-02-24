//******************************************************************************
/*!
	\file		indeldefs.h
	\author		Raphael Zulliger, &copy; INDEL AG
	\version	1.00
	\verbatim
	1.00	03.02.2005-RZ : + origin

	876, 2006-08-23 08:28:09 +0200 (Mi, 23 Aug 2006), walther
	+ Added DF_INCO_TYPE_INVALID (for CINCOValue, but may also be useful elsewhere).

	895, 2006-08-25 11:37:13 +0200 (Fri, 25 Aug 2006), walther
	+ Merged changes from branches/simplification r851:891 to trunk.

	1657, 2007-06-27 10:47:34 +0200 (Mi, 27 Jun 2007), walther
	! Cleaning up the mess caused by committing r1656 even with icommit.py... :|

	2222, 2007-11-29 17:03:48 +0100 (Do, 29 Nov 2007), zulliger
	

	2295, 2007-12-14 18:04:05 +0100 (Fr, 14 Dez 2007), zulliger
	! Many many changes. Too much to list in detail. But: A lot of McINCOFrame
	  adjustments (especially regarding little/big-endian), a lot of cleanups
	  in library structure, etc.

	2322, 2007-12-18 09:15:36 +0100 (Di, 18 Dez 2007), zulliger
	! Renamed indellib to libindel to have consistent naming. Change all
	  includes in all projects to #include <indel/whatever.h>. Note: currently,
	  ibuild.py will still create the ${INDEL_ROOT}/include/indellib folder for
	  backward compatibility

	2323, 2007-12-18 10:49:05 +0100 (Di, 18 Dez 2007), zulliger
	! Changes needed because some headers were moved to the new 'inco_32'
	  include folder

	2347, 2007-12-18 11:46:17 +0100 (Di, 18 Dez 2007), zulliger
	+ Added missing defintions

	2357, 2007-12-18 17:15:35 +0100 (Di, 18 Dez 2007), walther
	+ Introduced the ENG number format for engineering notation (multiple-of-3
	  exponents). The constant coincides with DEC, ENG notation is used if the
	  number of decimal places specified in the characteristics is greater than
	  zero (due to this, the actual number of decimal places displayed is one
	  less than what the characteristics field says).

	2360, 2007-12-19 07:46:05 +0100 (Mi, 19 Dez 2007), walther
	+ Added characteristics constant for the "touched" bit.

	2382, 2007-12-20 16:06:51 +0100 (Do, 20 Dez 2007), zulliger
	- Removed obsolete INCO type: list. It was used for inco path extensions
	  like '*', '?', etc.

	2384, 2007-12-20 18:08:09 +0100 (Do, 20 Dez 2007), zulliger
	! Fixed bug: float arguments of callprocedures sent to non-float targets
	  were wrongly converted. They are were sent as fixed32, but INOS expects
	  them to be uint32

	2421, 2008-01-04 07:08:08 +0100 (Fr, 04 Jan 2008), zulliger
	+ Added some definitions used by IncoExp.
	- Removed defs which are already defined by inco_32.h

	3202, 2008-09-16 14:00:16 +0200 (Di, 16 Sep 2008), walther
	+ I knew there was another place where characteristics constants were
	  kept... adding the new ones from inos r1306 / libinix r3190.

	-1,,
	+ Added Inco alignment mask.

	4185, 2010-06-10 16:33:52 +0200 (Do, 10 Jun 2010), zulliger
	+ New INCO type and flag definitions required for async callprocedure 
	  handling.

	4211, 2010-06-15 15:55:54 +0200 (Di, 15 Jun 2010), zulliger
	! Doxygenized documentation

	4213, 2010-06-15 16:03:29 +0200 (Di, 15 Jun 2010), walther
	+ Added DF_INCO_FLAG_GET_RESULT_LENGTH.

	4229, 2010-06-16 16:58:36 +0200 (Mi, 16 Jun 2010), walther
	! Documentation tweaks.

	4234, 2010-06-17 14:34:51 +0200 (Thu, 17 Jun 2010), zulliger
	! Synchronized types with INOS by adding DF_INCO_TYPE_POINTER
   
	4726, 2010-12-31 11:35:07 +0100 (Fr, 31 Dez 2010), tjericke
    + Added some comments to the INCO type declarations, to keep all INCO
	  declerations consistent.

	4731, 2011-01-04 14:13:45 +0100 (Di, 04 Jan 2011), tjericke
	+ Re-added accidentally deleted lines.

	5099, 2012-01-19 18:06:20 +0100 (Don, 19 Jan 2012), hirzel
	+ Added DF_INCO_CHAR2_OVERSAMPLED.

	$LastChangedRevision: 6734 $ $Date: 2017-02-20 17:31:23 +0100 (Mon, 20 Feb 2017) $ $Author: zulliger $
	+ Added 'DF_INCO_ASYNC_RESULT_STRING_MAX' which defines the maximum payload
	  of an async callprocedure result.

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

	\brief Various defines related to INCO data types and item characteristics

*/
//******************************************************************************

#if !defined(__INCODEFS_H__)
#define __INCODEFS_H__


//
// Definition of arrays for the error messages
//

//--------------------------------------------------------------------------
// Some other defines
//--------------------------------------------------------------------------

/*! \name INCO type target characteristics */
//@{
#define DF_SLAVE_CHAR_FLOAT			 0x00000001L	//!< floating point available
//@}


/*! \name INCO type manipulation flags */
//@{
#define DF_INCO_TYPE_MASK_TYPE_ONLY	 0x0FFF //!< Use this mask to get rid of any flags, such as the defType_With_Name
#define DF_INCO_TYPE_WITH_NAME       0x8000	//!< "flag" that indicates that the data is sent including its name. Used e.g. by the async callprocedure mechanism if results are named.
//@}

/*! \name INCO type definitions */
//@{
#define DF_INCO_TYPE_INVALID         0x7FFF	//!< invalid or undefined INCO type

// Types with prefix 0x00?? are container types (types whos main purpose is to contain other items)
#define DF_INCO_TYPE_OBJECT          0x0000 //!< type object
#define DF_INCO_TYPE_SUBPLUGIN	     0x0001 //!< type INCO-SubPlugin

// Types with prefix 0x01?? are scalar types (single value variables)
#define DF_INCO_TYPE_VARIABLE        0x0100	//!< type variable
#define DF_INCO_TYPE_UINT64          0x0101	//!< type uint32
#define DF_INCO_TYPE_INT64           0x0102	//!< type int32
#define DF_INCO_TYPE_UINT32          0x0103	//!< type uint32
#define DF_INCO_TYPE_INT32           0x0104	//!< type int32
#define DF_INCO_TYPE_UINT16          0x0105	//!< type uint16
#define DF_INCO_TYPE_INT16           0x0106	//!< type int16
#define DF_INCO_TYPE_UINT8           0x0107	//!< type uint8
#define DF_INCO_TYPE_INT8            0x0108	//!< type int8
#define DF_INCO_TYPE_DOUBLE          0x0109	//!< type double
#define DF_INCO_TYPE_FLOAT           0x010A	//!< type float, single
#define DF_INCO_TYPE_DATETIME        0x010B	//!< type date/time
#define DF_INCO_TYPE_BIT             0x010C	//!< type bit
#define DF_INCO_TYPE_FIXED64         0x010D //!< type fixed64
#define DF_INCO_TYPE_FIXED32         0x010E //!< type fixed32
// Depricated! Because of inconsistent definition this type should not be used anymore
// on INOS, this is defined (it's too bad but it's the way it is for historical reason): #define DF_INCO_TYPE_BOOL			 0x010F	  //!< type INCO bool
#define DF_INCO_TYPE_DOUBLE_N_FIXED64 0x010F //!< type double and fixed64
#define DF_INCO_TYPE_FLOAT_N_FIXED32  0x0110 //!< type float and uint32 (used for very old style callprocedure (non-ex)).
#define DF_INCO_TYPE_BOOLEAN		  0x0111 //!< type bool using 8bit! (in constrast to DF_INCO_TYPE_BOOL - which is platform dependent)
#define DF_INCO_TYPE_NUMBER_VALUE	  0x0112 //!< type for 'number values' that can be represented by a 64bit floating point number. (such as bool, (u)int8, 16, 32, float and double)
#define DF_INCO_TYPE_POINTER		  0x0113 //!< type INCO (void*) pointer

// Types with prefix 0x02?? are non-scalar types (multy value variables/buffers/arrays)
#define DF_INCO_TYPE_STRING          0x0200	//!< type string
#define DF_INCO_TYPE_FILE			 0x0201 //!< type file (path/filename)
#define DF_INCO_TYPE_BINARY          0x0202 //!< type binary (file data)

// Types with prefix 0x03?? defines actions (active elements)
#define DF_INCO_TYPE_PROCEDURE       0x0300	//!< type procedure
//@}

/*! \name INCO type flags. They can be passed to some functions, such as CallProcedureExResult */
//@{
#define DF_INCO_FLAG_GET_RESULT_TYPE	0x00010000L	//!< flag to get the type of the result value. result type is expected to be uint32
#define DF_INCO_FLAG_GET_RESULT_LENGTH	0x00020000L	//!< flag to get the length of the result value. result type is expected to be uint32
//@}

#define DF_INCO_ASYNC_RESULT_STRING_MAX	1024 //! Using this buffer when calling CallProcedureExResult for a string type guarantees to always provide a 'large enough' buffer.

/*! \name INCO item characteristics */
//@{
#define DF_INCO_CHAR_READ_ONLY       0x00000001L	//!< variable is read only
#define DF_INCO_CHAR_INVISIBLE       0x00000002L	//!< variable is invisible
#define	DF_INCO_CHAR_OBJECT_WITH_VALUE	0x00000004L	//!< object has value (member with same name)
#define	DF_INCO_CHAR_OBJECT_NO_MEMBER	0x00000008L	//!< object has no members
#define DF_INCO_CHAR_MUST_CALL       0x00004000L	//!< should be called with Get()
#define DF_INCO_CHAR_SHOW_EXP        0x00000000L	//!< show item in exponential
#define DF_INCO_CHAR_SHOW_HEX        0x00000004L	//!< show item in hexadecimal
#define DF_INCO_CHAR_SHOW_DEC        0x00000008L	//!< show item in decimal
#define DF_INCO_CHAR_OBJECT_BMP      0x00000010L	//!< take bitmap from parent folder
#define DF_INCO_CHAR_SHOW_FIX        0x0000000CL	//!< show item in fixed point
#define DF_INCO_CHAR_SHOW_DIG_1      0x00000010L	//!< show 1 digit after point
#define DF_INCO_CHAR_SHOW_DIG_2      0x00000020L	//!< show 2 digit after point
#define DF_INCO_CHAR_SHOW_DIG_3      0x00000030L	//!< show 3 digit after point
#define DF_INCO_CHAR_SHOW_DIG_4      0x00000040L	//!< show 4 digit after point
#define DF_INCO_CHAR_SHOW_DIG_5      0x00000050L	//!< show 5 digit after point
#define DF_INCO_CHAR_SHOW_DIG_6      0x00000060L	//!< show 6 digit after point
#define DF_INCO_CHAR_SHOW_DIG_7      0x00000070L	//!< show 7 digit after point
#define DF_INCO_CHAR_SHOW_DIG_8      0x00000080L	//!< show 8 digit after point
#define DF_INCO_CHAR_SHOW_DIG_9      0x00000090L	//!< show 9 digit after point
#define DF_INCO_CHAR_SHOW_DIG_10     0x000000A0L	//!< show 10 digit after point
#define DF_INCO_CHAR_SHOW_DIG_11     0x000000B0L	//!< show 11 digit after point
#define DF_INCO_CHAR_SHOW_DIG_12     0x000000C0L	//!< show 12 digit after point
#define DF_INCO_CHAR_SHOW_DIG_13     0x000000D0L	//!< show 13 digit after point
#define DF_INCO_CHAR_SHOW_DIG_14     0x000000E0L	//!< show 14 digit after point
#define DF_INCO_CHAR_SHOW_DIG_15     0x000000F0L	//!< show 15 digit after point
#define DF_INCO_CHAR_SHOW_ENG_0      0x00000018L	//!< show item in engineering notation with 0 decimal places
#define DF_INCO_CHAR_SHOW_ENG_1      0x00000028L	//!< show item in engineering notation with 1 decimal place
#define DF_INCO_CHAR_SHOW_ENG_2      0x00000038L	//!< show item in engineering notation with 2 decimal places
#define DF_INCO_CHAR_SHOW_ENG_3      0x00000048L	//!< show item in engineering notation with 3 decimal places
#define DF_INCO_CHAR_SHOW_ENG_4      0x00000058L	//!< show item in engineering notation with 4 decimal places
#define DF_INCO_CHAR_SHOW_ENG_5      0x00000068L	//!< show item in engineering notation with 5 decimal places
#define DF_INCO_CHAR_SHOW_ENG_6      0x00000078L	//!< show item in engineering notation with 6 decimal places
#define DF_INCO_CHAR_SHOW_ENG_7      0x00000088L	//!< show item in engineering notation with 7 decimal places
#define DF_INCO_CHAR_SHOW_ENG_8      0x00000098L	//!< show item in engineering notation with 8 decimal places
#define DF_INCO_CHAR_SHOW_ENG_9      0x000000A8L	//!< show item in engineering notation with 9 decimal places
#define DF_INCO_CHAR_SHOW_ENG_10     0x000000B8L	//!< show item in engineering notation with 10 decimal places
#define DF_INCO_CHAR_SHOW_ENG_11     0x000000C8L	//!< show item in engineering notation with 11 decimal places
#define DF_INCO_CHAR_SHOW_ENG_12     0x000000D8L	//!< show item in engineering notation with 12 decimal places
#define DF_INCO_CHAR_SHOW_ENG_13     0x000000E8L	//!< show item in engineering notation with 13 decimal places
#define DF_INCO_CHAR_SHOW_ENG_14     0x000000F8L	//!< show item in engineering notation with 14 decimal places
#define DF_INCO_CHAR_BMP_ID			 0x00FF0000L	//!< bitmap id (1..223 for user, 224..255 for predefined bitmaps)
#define DF_INCO_CHAR_HASCOMBOBOX	 0x01000000L	//!< item has a combobox
#define DF_INCO_CHAR_MUSTDELETE		 0x02000000L	//!< item has to be deleted in inco-exp if not found
#define DF_INCO_CHAR_INTERNALUSE	 0x04000000L	//!< more invisible than defCharInvisible
#define DF_INCO_CHAR_HASEXTCONFIG    0x08000000l	//!< item has extended config (characteristics2)
#define DF_INCO_CHAR_TOUCHED		 0x80000000L	//!< item touched
//@}

/*! \name INCO item extended characeristics */
//@{
#define DF_INCO_CHAR2_COLORS		 0x00000001l	//!< item has fore- and backcolor
#define DF_INCO_CHAR2_PERSISTENT	 0x00000002l	//!< item value is saved in IGD file (INIX)
#define DF_INCO_CHAR2_TRIGGER_SUPP	 0x00000004l	//!< item supports triggers (INIX)
#define DF_INCO_CHAR2_ALIGN_RIGHT	 0x00000008l	//!< display value right-aligned
#define DF_INCO_CHAR2_ALIGN_LEFT	 0x00000010l	//!< display value left-aligned
#define DF_INCO_CHAR2_ALIGN_CENTER	 0x00000018l	//!< display value centered
#define DF_INCO_CHAR2_ALIGN_MASK	 0x00000018l	//!< all alignment flags
#define DF_INCO_CHAR2_ASYNC_RESULT	 0x00000020l	//!< async result (e.g. async CallProcedure or GetVariable)
#define DF_INCO_CHAR2_RET_MCRESULT	 0x00000040l	//!< CallProcedure returns CMcResult
#define DF_INCO_CHAR2_OVERSAMPLED	 0x00000080l	//!< variable is oversampled
//@}

#endif // __INCODEFS_H__

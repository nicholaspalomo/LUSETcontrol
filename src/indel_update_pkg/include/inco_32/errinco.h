//******************************************************************************
/*!
	\file
	\author		Raphael Zulliger, &copy; INDEL AG
	\version	1.00
	\verbatim
	1.00	03.02.2005-RZ	: + origin
	1.01	29.07.2005-FC	: + New errors and comment corrected.

	731, 2006-07-07 16:56:28 +0200 (Fr, 07 Jul 2006), fabi
	+ Added/corrected errors 0x0005060A, 0x0005060B and 0x0005060C.

	1148, 2006-12-12 08:41:01 +0100 (Di, 12 Dez 2006), zulliger
	! Some minor error code cleanups (synch'ed with INOS and version 2 inco)

	1196, 2006-12-18 13:08:58 +0100 (Mo, 18 Dez 2006), zulliger
	+ Added new error number needed for asynchronous GetVariables (p.s. the
	  previous changelog text was wrong!)

	1201, 2007-01-10 09:20:41 +0100 (Mi, 10 Jan 2007), zulliger
	+ New error codes

	1325, 2007-02-27 14:51:13 +0100 (Di, 27 Feb 2007), fabi
	+ New error ER_INCO_RPC_ARG_FORMAT.

	1550, 2007-04-20 13:42:42 +0200 (Fri, 20 Apr 2007), zulliger
	+ Added new error code ER_INCO_VAR_TRIGGERSYNTAX.

	2095, 2007-11-06 11:14:11 +0100 (Di, 06 Nov 2007), zulliger
	! Cleaning up the mess caused by committing r1656 even with icommit.py... :|

	1929, 2007-09-24 15:22:13 +0200 (Mo, 24 Sep 2007), zulliger
	! Merged with revision 1859

	1987, 2007-10-12 15:39:37 +0200 (Fr, 12 Okt 2007), zulliger
	! Some minor cleanups (especially deleted definitions used by incoserver
	  3.x)

	2022, 2007-10-18 14:51:05 +0200 (Do, 18 Okt 2007), zulliger
	+ Added new error function for PCI specific failures

	2036, 2007-10-23 13:56:18 +0200 (Di, 23 Okt 2007), zulliger
	+ New errors for remote incoserver 4.x connections

	2041, 2007-10-25 07:16:20 +0200 (Do, 25 Okt 2007), zulliger
	+ Additional errors for remote incoserver 4.x connections

	2044, 2007-10-25 14:16:27 +0200 (Do, 25 Okt 2007), zulliger
	+ New errors used by the CTcpSocketServer/Client classes

	2048, 2007-10-26 10:20:54 +0200 (Fr, 26 Okt 2007), zulliger
	+ Additional errors

	2054, 2007-10-29 17:50:55 +0100 (Mo, 29 Okt 2007), zulliger
	+ Additional errors

	2068, 2007-11-01 13:21:14 +0100 (Do, 01 Nov 2007), zulliger
	+ Additional errors used by auto target scan

	2095, 2007-11-06 11:14:11 +0100 (Di, 06 Nov 2007), zulliger
	+ Again new errors

	2124, 2007-11-09 09:40:58 +0100 (Fr, 09 Nov 2007), zulliger
	! Error definitions cleanup

	2143, 2007-11-15 11:25:35 +0100 (Do, 15 Nov 2007), zulliger
	+ New error used when empty target name is passed to some of the servers inco procedures

	2241, 2007-12-03 15:47:16 +0100 (Mo, 03 Dez 2007), zulliger
	+ Added new error

	2295, 2007-12-14 18:04:05 +0100 (Fr, 14 Dez 2007), zulliger
	! Many many changes. Too much to list in detail. But: A lot of McINCOFrame
	  adjustments (especially regarding little/big-endian), a lot of cleanups
	  in library structure, etc.

	2322, 2007-12-18 09:15:36 +0100 (Di, 18 Dez 2007), zulliger
	+ Added new error ("sub target count exceeded")

	2323, 2007-12-18 10:49:05 +0100 (Di, 18 Dez 2007), zulliger
	! Changes needed because some headers were moved to the new 'inco_32'
	  include folder

	2394, 2007-12-24 15:29:59 +0100 (Mo, 24 Dez 2007), zulliger
	+ Many new PCI related error codes

	2412, 2008-01-03 13:39:11 +0100 (Do, 03 Jan 2008), zulliger
	+ Some new error codes

	2415, 2008-01-03 17:27:58 +0100 (Do, 03 Jan 2008), zulliger
	! Cleanup of all error codes. Some where removed, some renamed and many
	  of them were renumbered.

	2421, 2008-01-04 07:08:08 +0100 (Fr, 04 Jan 2008), zulliger
	! Some error code number adjustments
	+ New error code used to inform the caller that fragmented frames are not
	  supported.

	2766, 2008-04-10 14:55:09 +0200 (Do, 10 Apr 2008), zulliger
	+ New error code needed by the INCOServer if two net target are using the
	  same IP address (= the same target)

	3216, 2008-09-23 09:34:46 +0200 (Di, 23 Sep 2008), fabi
	+ Added ER_INCO_VAR_UNKNOWN error and some comments and cleanups.

	3274, 2008-12-24 10:15:04 +0100 (Mi, 24 Dez 2008), zulliger
	! Fragmented frame handling (beta): Merged from
	  branches/Issue_385_SplittedINCOFrameSupport.

	3284, 2008-12-30 11:42:37 +0100 (Di, 30 Dez 2008), zulliger
	+ New error if reading bootcode.bin fails.

	3818, 2009-12-08 15:11:57 +0100 (Di, 08 Dez 2009), zulliger
	+ Added propper error handling for the McINCOFrames to ClassicFrames
	  conversion: Respect maximum communication buffer size (which should not
	  exceed 494 bytes). This avoids NAK frames to be returned by targets in
	  case of veeeeeery long variable names or value strings for GetVariables
	  and PutVariables.

	3866, 2009-12-31 11:40:55 +0100 (Do, 31 Dez 2009), zulliger
	+ New error types used when the target executes a CallProcedure
	  or GetVariable with 'asynchronous results'.

	3961, 2010-02-08 14:57:21 +0100 (Mo, 08 Feb 2010), walther
	+ New error code ER_INCO_ASYNC_TIMEOUT, "Waiting for completion of
	  asynchronous call timed out."

	3975, 2010-02-16 17:13:22 +0100 (Di, 16 Feb 2010), zulliger
	+ Added some more NET target specific error codes

	4141, 2010-05-27 11:19:38 +0200 (Do, 27 Mai 2010), fabi
	+ Added error code 0x500F8, device is offline.

	4185, 2010-06-10 16:33:52 +0200 (Do, 10 Jun 2010), zulliger
	+ Added some new error codes useful for the async callprocedure handling.

	4211, 2010-06-15 15:55:54 +0200 (Di, 15 Jun 2010), zulliger
	! Doxygenized documentation

	4215, 2010-06-15 16:11:51 +0200 (Di, 15 Jun 2010), walther
	! Fixed typo in API while we still can.

	4229, 2010-06-16 16:58:36 +0200 (Wed, 16 Jun 2010), walther
	! Documentation tweaks.

	4282, 2010-06-29 22:37:58 +0200 (Di, 29 Jun 2010), zulliger
	+ Added new error codes to have 'unique' error codes for certain error
	  situations.

	4479, 2010-08-11 15:25:48 +0200 (Mi, 11 Aug 2010), walther
	+ Added error code ER_INCO_RPC_INTERRUPTED, "Asynchronous procedure was
	  interrupted by target reset".

	4781, 2011-02-25 15:02:37 +0100 (Fr, 25 Feb 2011), fabi
	+ Added ER_INCO_DB_NOT_ENOUGH_MEMORY as defined in inos.

	4829, 2011-03-22 16:19:06 +0100 (Tue, 22 Mar 2011), zulliger
	+ Added ER_INCO_BLK_SIZE_TOO_BIG, ER_INCO_BLK_P08_NOT_ALLOWED & friends

	4983, 2011-10-04 14:07:02 +0200 (Di, 04 Okt 2011), zulliger
	+ Added support for new Dbg INCO command: DbgTaskGetReg. This command has
	  initially been introduced to support getting registers from P2020. At the
	  same time, the command has been designed to optimize getting taks
	  specific registers for all targets, in the way GDB requires them.
	  Therefore, this new command will help minimizing communication overhead
	  when debugging with Gdb/iDev.

	4991, 2011-10-21 13:29:31 +0200 (Fr, 21 Okt 2011), walther
	+ A new error code for IncoControl() (libinco_32 4.5).

	5000, 2011-10-24 15:45:34 +0200 (Mo, 24 Okt 2011), zulliger
	! Slightly improved comments and error messages for certain INCO errors.

	5080, 2012-01-10 16:51:18 +0100 (Tue, 10 Jan 2012), zulliger
	+ Added GIN-PCIe specific errors that may occur during board reset

	5110, 2012-01-25 06:41:39 +0100 (Mi, 25 Jan 2012), zulliger
	+ Added new error: ER_INCO_TIMEOUT_TARGET_SERIALIZER = "Timeout while 
	  waiting to get exclusive access to the target communication port 
	(within INCOServer)"

	5159, 2012-05-03 09:51:09 +0200 (Do, 03 Mai 2012), zulliger
	+ Added new error codes related to Plx/PCI and data channels

	5165, 2012-05-03 15:37:11 +0200 (Do, 03 Mai 2012), zulliger
	+ New error code "PCI board doens't support interrupt"

	5217, 2012-06-07 18:24:15 +0200 (Do, 07 Jun 2012), zulliger
	! Fixed error code for ER_SHMEM_CONN_CLOSED which used the same code as 
	  ER_TCPSOCKET_FIONBIO_FAILED.
	+ Added data transfer related error codes and message

	5224, 2012-06-08 16:48:51 +0200 (Fr, 08 Jun 2012), zulliger
	+ Added failure code: PCI datachannel received data with wrong checksum

	5228, 2012-06-11 10:34:21 +0200 (Mo, 11 Jun 2012), zulliger
	! Fixed typos... thanks Christian for pointing me to them.

	5243, 2012-06-25 14:54:04 +0200 (Mon, 25 Jun 2012), zulliger
	+ Added several new error messages. All may occur during Tcp-connection
	  establishment between libinco32 and incoserver. Before, we only used 1
	  error message for all connection failure types.

	5384, 2012-11-19 14:01:56 +0100 (Mo, 19 Nov 2012), zulliger
	+ Added support-functions for new INCO calls: SetWatchpoint and
	  ClrWatchpoint

	5487, 2013-02-01 16:00:11 +0100 (Fr, 01 Feb 2013), pauli
	+ Added new error codes and messages for GinPCIe driver version checking.

	5552, 2013-03-12 13:08:00 +0100 (Tue, 12 Mar 2013), fabi
	+ Added new errors for failed receive (20015) and port unreachable (20016).

	5558, 2013-03-28 07:40:23 +0100 (Thu, 28 Mar 2013), zulliger
	+ Introduced several new error codes to allow unique error 
	  messages for the different Tcp/Ip connection failure reasons
	  (such as errors returned by connect(), select(), etc.)

	5695, 2013-06-17 17:09:14 +0200 (Mon, 17 Jun 2013), zulliger
	+ Added some new debugging related errors

	5878, 2013-12-19 15:10:33 +0100 (Do, 19 Dez 2013), zulliger
	+ New error codes required for up coming 'logging API extensions' (see
	  libinco_32)

	6090, 2014-05-09 11:40:40 +0200 (Fr., 09 Mai 2014), pauli
	+ Added error codes for safe concurrent UDP DataTransfer:
	  ER_INCO_DT_LOCK_FAILED and ER_INCO_DT_LOCK_TIMEOUT.

	6683, 2016-10-24 08:33:14 +0200 (Mon, 24 Oct 2016), zulliger
	+ Added new error message used if an unexpected 'Indel PCI board' is found
	  at the configured bus/slot

	6781, 2017-04-06 13:52:47 +0200 (Do., 06 Apr 2017), zulliger
	! Added new error code for 'RPC keylevel not sufficient', used if a
	  callprocedure has keylevel > 0 but the caller does not provide the
	  required access level. Required by INCOV.

	6864, 2017-10-06 15:15:17 +0200 (Fr., 06 Okt 2017), pauli
	! Fixed duplicate error code: ER_TCPSOCKET_REMOTE_GONE and
	  ER_TCPSOCKET_CONNECT_FAILED (credits to eberhardt).

	7053, 2018-12-19 13:33:58Z, pauli
	+ Added "URL target" related error codes to be used by INCOServer.

	$LastChangedRevision: 7095 $ $iDate: 2019-02-21 14:54:43Z $ $Author: walther $
	! Fix error code ER_INCO_RPC_KEY_LEVEL from r6781 to match what INOS
	  actually returns.

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

	\brief Error handling related defines.

	As discussed in \ref page_inco32errors, this file contains the following
	pieces of information:

	 - defines for checking the type of an error (INCO, application error, etc.)
	 - defines for all possible INCO errors

*/
//******************************************************************************

#if !defined(__INCOERRORS_H__)
#define __INCOERRORS_H__

/*! \name Error ranges */
//@{
#define ER_APPERROR_BASE						0x40000000	//!< use this mask to check for an application error defined by the McRobot framework
#define ER_APPERROR_CUSTOMER					0x80000000	//!< use this mask to check for an application error defined by customer code
//@}


/*! \name Error range masks */
//@{
#define ER_MASK_APPERROR						0xF0FFFFFF	//!< use this mask to get the application error value (without the RplId)
#define ER_MASK_APPERROR_TYPE					0xF0000000	//!< use this mask to check for an application error defined by the McRobot framework
#define ER_MASK_APPLICATION_RPL_ID				0x0F000000	//!< use this mask to extract the reply id (e.g. ok, skip, error, etc.) from the application error
#define ER_MASK_APPLICATION_RPL_ID_OFFSET		24			//!< use this offset to shift the RplId to the right when read from an application error, like this: uRplId = (uError & ER_MASK_APPLICATION_RPL_ID) >> ER_MASK_APPLICATION_RPL_ID_OFFSET;
//@}

/*! \name INCO errors */
//@{
// --- error codes from inco server ---
#define ER_INCO_NO_ERROR						0x00000000L	//!< ok
#define ER_INCO_DEPRECATED						0x00010000L	//!< deprecated function or functionality

// 0x0001xxxx
#define ER_INCO_REGISTRY						0x00010001L	//!< error in local registry
#define ER_INCO_SERVER_REGISTRY					0x00010002L	//!< error in server registry
#define ER_INCO_TARGET							0x00010003L	//!< target not available
#define ER_INCO_MASTER_NAME						0x00010004L	//!< master name not available
#define ER_INCO_TIMEOUT							0x00010005L	//!< no answer from target
#define ER_INCO_TIMEOUT_SEMAPHORE				0x00010006L	//!< could not reserve semaphore
#define ER_INCO_RESET_SEMAPHORE					0x00010007L	//!< could not reset semaphore
#define ER_INCO_PASSWORD_REQUIRED				0x00010008L	//!< password needs to be set
#define ER_INCO_STRING_TOO_LONG					0x00010009L	//!< string too long for buffer
#define ER_INCO_NO_FUNCTION						0x00010010L	//!< function not defined
#define ER_INCO_MEM_DRIVER						0x00010011L	//!< server could not load memdriver
#define ER_INCO_TIMOUT_FRAME					0x00010012L	//!< timeout while waiting for incoframe
// load boot code errors
#define ER_INCO_DPR_WRITE						0x00010013L	//!< write error in dual-port or no target
#define ER_INCO_BOOT_CODE						0x00010014L	//!< boot code for target not found
// pc-master error
#define ER_INCO_ONLY_NUMBERS					0x00010016L	//!< only numbers supported (no names)
// ppc-master error
#define ER_INCO_NO_PPC_AT_ADDRESS				0x00010017L	//!< no PPC found at given address
#define ER_INCO_PLX_OPEN_FAILED					0x00010018L	//!< The Plx api wasn't able to open the device at specified bus/slot
#define ER_INCO_SERVER_TOO_OLD					0x00010020L	//!< IncoServer too old for this functionality
#define ER_INCO_TIMEOUT_FRAME_TCP				0x00010021L	//!< timeout while waiting for incoframe in libinco_32 using Tcp/Ip
#define ER_INCO_TIMEOUT_TARGET_SERIALIZER			0x00010022L	//!< Timeout while waiting to get exclusive access to the target communication port (within INCOServer)

#define ER_INCO_TARGET_COUNT_EXCEEDED			0x00010030L	//!< Maximum count of target-subtarget reached. The amount of subtargets is limited.
#define ER_INCO_TARGET_PORT_INVALID				0x00010031L	//!< Invalid target name passed to inco function
#define ER_INCO_TARGET_NAME_INVALID				0x00010032L	//!< Invalid target name passed to inco function
#define ER_INCO_TARGET_ALREADY_EXISTS			0x00010033L	//!< a target with this name already exists.
#define ER_INCO_TARGETALIAS_NAME				0x00010034L	//!< No target alias with that name exists.
#define ER_INCO_TARGETALIAS_ALREADY_EXISTS		0x00010035L	//!< a target alias with this name already exists.
#define ER_INCO_FRAGMENTATION_UNSUPPORTED		0x00010036L	//!< Fragmented INCO frames are not supported by this target/server

#define ER_INCO_SERVER4_NOT_RUNNING				0x00010040L	//!< incoserver 4.x is not running. Connection failed.

#define ER_INCO_FRAME_BUFFER_FULL				0x00010050L	//!< the frame buffer is full - therfore the frame couldn't be processed.
#define ER_INCO_FRAME_CONVERSION_BUFFER			0x00010051L	//!< The inco frame conversion failed because the frame buffer of the classic frame is too small.
#define ER_INCO_FRAME_DATA_SIZE_TOO_SMALL		0x00010052L	//!< The data size of the inco frame is not big enough to perform the operation
#define ER_INCO_FRAME_FRAGMENTED_SIZE_TOO_SMALL	0x00010053L	//!< The data size exceeds the maximum possible data size of fragmented frames.
#define ER_INCO_FRAME_FRAGMENTED_DOESNT_MATCH	0x00010054L	//!< The two frames are not from the same fragmented INCO frame.
#define ER_INCO_FRAME_FRAGMENTED_MAX_SIZE		0x00010055L	//!< The receiving target can't handle that big fragmented frames.

#define ER_INCO_CTL_UNKNOWN_REQUEST				0x00010100L	//!< Unknown request to ::IncoControl.

// 0x0002xxxx
#define ER_TARGET_SIO_PORT_RANGE				0x00020000L	//!< the comport is out of range
#define ER_TARGET_SIO_PORT_IN_USE				0x00020001L	//!< the comport is already used by an other target
#define ER_TARGET_SIO_SEND_FAILED				0x00020002L	//!< the data couldn't be written to the sio port
#define ER_TARGET_SIO_DISABLED					0x00020003L	//!< the sio port is currently disabled
#define ER_TARGET_SIO_OPEN_FAILED				0x00020004L	//!< opening the comport failed

#define ER_TARGET_NET_SEND_FAILED				0x00020010L	//!< sending the UDP frame to the target failed.
#define ER_TARGET_NET_MALFORMED_IP				0x00020011L	//!< the target ip address is malformed.
#define ER_TARGET_NET_IP_ALREADY_IN_USE			0x00020012L	//!< the target ip address is already in use by another network target.
#define ER_TARGET_NET_NO_NETWORK_FOR_TARGET		0x00020013L	//!< no network card could be found with a suitable IP range to reach the target.
#define ER_TARGET_NET_BIND_FAILED				0x00020014L	//!< binding the udp socket to the specific ip/port failed (bind returned an error).
#define ER_TARGET_NET_RECV_FAILED				0x00020015L	//!< receiving the UDP frame from the target failed.
#define ER_TARGET_NET_PORT_UNREACHABLE			0x00020016L	//!< target UDP port unreachable (nobody listening on port 1964?)

#define ER_TARGET_REMOTE_NO_SOCKET						0x00020020L	//!< socket for remote target couldn't be found
#define ER_TARGET_REMOTE_SEND_FAILED					0x00020021L	//!< sending data to remote server failed.
#define ER_TARGET_RECEIVE_FAILED						0x00020022L	//!< receiving data from remote server failed.
#define ER_TARGET_REMOTE_CONNECTED_SRV_GONE				0X00020023L	//!< a remote server that was connected to this server has gone
#define ER_TARGET_REMOTE_SRV_NOT_FOUND					0x00020024L	//!< the remote server name or IP could not be resolved
#define ER_TARGET_REMOTE_SRV_CONNECTING_FAILED			0x00020025L	//!< connecting to the remote server failed. Maybe server not running?
#define ER_TARGET_REMOTE_SRV_CONNECTING_TIMEDOUT		0x00020026L	//!< Connecting to the remote server failed: Time out. Maybe server not running?
#define ER_TARGET_REMOTE_SRV_CONNECTING_SOCKOPT_FAILED	0x00020027L	//!< Connecting to the remote server failed: getsockopt returned an error. Maybe server not running?
#define ER_TARGET_REMOTE_SRV_CONNECTING_WRONG_SELECT	0x00020028L	//!< Connecting to the remote server failed. select returned wrong set. Maybe server not running?
#define ER_TARGET_REMOTE_SRV_CONNECTING_NOBLOCK			0x00020029L	//!< Connecting to the remote server failed. connect didn't return 'wouldblock'. Maybe server not running?
#define ER_TARGET_REMOTE_SRV_CONNECTING_CONNECT_FAILED	0x0002002AL	//!< Connecting to the remote server failed. connect returned error. Maybe server not running?
#define ER_TARGET_REMOTE_CONNECTION_SHUTDOWN			0X0002002BL	//!< the Tcp/Ip connection was gracefully shutdown by the remote peer
#define ER_TARGET_REMOTE_SELECT_FAILED					0X0002002CL	//!< The Tcp/Ip connection could not be established, select() returned an invalid result
#define ER_TARGET_REMOTE_CONNECT_FAILED					0X0002002DL	//!< The Tcp/Ip connection could not be established, connect() returned an error
#define ER_TARGET_REMOTE_CONNECT_NOT_EINPROGRESS		0X0002002EL	//!< The Tcp/Ip connection could not be established, connect() didn't return EINPROGRESS

#define ER_TARGET_PCI_DPR_VERIFY				0x00020030L	//!< Writing to the DPR failed: Verifying the value was wrong.
#define ER_TARGET_PCI_NO_BOARD_AT_BUS_SLOT		0x00020031L	//!< No board could be found at configured bus/slot pair
#define ER_TARGET_PCI_BOARD_ALREADY_USED		0x00020032L	//!< The configured board at configured bus/slot is already in use.
#define ER_TARGET_PCI_PLXBARMAP_FAILED			0x00020033L	//!< PlxBarMap returned an error. The PCI board can't be opened
#define ER_TARGET_PCI_READ_EEPROM_FAILED		0x00020034L	//!< Reading the EEPROM of the PCI board failed.
#define ER_TARGET_PCI_BUFFER_TOO_SMALL			0x00020035L	//!< The data length in the DPR is longer than the buffer available by the INOCServer. Very strange.
#define ER_TARGET_PCI_BOOTCODE_READ_FAILED		0x00020036L	//!< Reading the bootcode failed (fread() returned error)
#define ER_TARGET_PCI_GINPCIE_RESET_FAILED		0x00020037L	//!< The GIN-PCIe reset failed
#define ER_TARGET_PCI_1ST_STAGE_UBOOT_NOT_RUN	0x00020038L	//!< The GIN-PCIe 1st stage u-boot seems to be not running
#define ER_TARGET_PCI_INOS_BOOTLOADER_NOT_RUN	0x00020039L	//!< The GIN-PCIe INOS bootloader seems to be not running
#define ER_TARGET_PCI_NOT_YET_OPENED			0x0002003AL //!< The PCMaster has not yet been opened
#define ER_TARGET_PCI_IRQ_UNSUPPORTED			0x0002003BL //!< The PCMaster does not support interrupts (e.g. "ISA compatibility" flag set)
#define ER_TARGET_PCI_VERSION_MISMATCH			0x0002003CL //!< The PCMaster is not compatible to the device driver. Maybe outdated GIN-PCIe driver?
#define ER_TARGET_PCI_WRONG_BOARD_TYPE			0x0002003DL //!< The Indel PCI board is of the wrong type (e.g. GIN-PCIe instead of PCI2)

#define ER_TARGET_PLX_NTFY_WAIT_HANDLE			0x00020040L	//!< PlxPci_NotificationWait return 'invalid handle' error.
#define ER_TARGET_PLX_NTFY_WAIT_TIMEOUT			0x00020041L	//!< PlxPci_NotificationWait return 'timeout' error.
#define ER_TARGET_PLX_NTFY_WAIT_CANCELED		0x00020042L	//!< PlxPci_NotificationWait return 'canceled' error.
#define ER_TARGET_PLX_NTFY_WAIT_GENERIC			0x00020043L	//!< PlxPci_NotificationWait return a not further specified error.
#define ER_TARGET_PLX_NTFY_REG_GENERIC			0x00020044L	//!< PlxPci_NotificationRegisterFor return a not further specified error.

#define ER_TARGET_PCI_DC_APP_ERROR				0x00020050L //!< PCI datachannel received an application error
#define ER_TARGET_PCI_DC_BUF_TO_SMALL			0x00020051L //!< PCI datachannel receive data failed because the buffer is too small
#define ER_TARGET_PCI_DC_SPURIOUS_IRQ			0x00020052L //!< PCI datachannel received interrupt but not valid data were available
#define ER_TARGET_PCI_DC_RECEIVER_WRONG_ID		0x00020053L //!< PCI datachannel sending data failed because the receiver read wrong data (wrong unique id)
#define ER_TARGET_PCI_DC_CHECKUSM_FAILURE		0x00020054L //!< PCI datachannel received data with wrong checksum

// autoscan related
#define ER_TARGET_AUTOSCAN_TARGET_NAME_EXISTS	0x000200F0L	//!< a target with the same name as the autoscanned target already exists.
#define ER_TARGET_AUTOSCAN_SOCKET_OPEN_FAILED	0x000200F1L	//!< creating a socket failed.
#define ER_TARGET_AUTOSCAN_SOCKET_BIND_FAILED	0x000200F2L	//!< binding the socket failed.
#define ER_TARGET_AUTOSCAN_NET_SENDTO_FAILED	0x000200F3L	//!< sendto function returned failure

// url target related (0x00021xxx)
#define ER_TARGET_URL_MISSING_URL				0x00021000L //!< no target URL specified
#define ER_TARGET_URL_MALFORMED_URL				0x00021001L //!< the target URL is malformed
#define ER_TARGET_URL_MISSING_PROTOCOL			0x00021002L //!< the target URL contains no protocol part
#define ER_TARGET_URL_UNSUPPORTED_PROTOCOL		0x00021003L //!< the target URL contains an unsupported protocol
#define ER_TARGET_URL_MISSING_HOSTNAME			0x00021004L //!< the target URL contains no hostname part
#define ER_TARGET_URL_RESOLVE_SYSCALL_FAILED	0x00021005L //!< a system call for resolving target hostname failed
#define ER_TARGET_URL_HOST_NOT_FOUND			0x00021006L //!< the target host was not found
#define ER_TARGET_URL_MALFORMED_IP				0x00021011L	//!< the target ip address is malformed.

// 0x0003xxxx
// IPC locking related
#define ER_REMOTE_PROC_DIED						0x00030010L	//!< remote process has died
#define ER_TIMEOUT_LOCK							0x00030011L	//!< timeout while waiting for global (os wide) mutex or semaphore
// IPC shared memory related
#define ER_SHMEM_OPEN_FAILED					0x00030020L	//!< opening the shared memory connection failed
#define ER_SHMEM_CONN_CLOSED					0x00030021L	//!< the connection to the remote part of the shared memory channel is not opened.
// IPC Tcp/Ip socket related
#define ER_TCPSOCKET_NO_SOCKET					0x00030030L	//!< the socket() function returned no valid socket handle
#define ER_TCPSOCKET_FIONBIO_FAILED				0x00030031L	//!< setting the socket to asynchronous failed: ioctlsocket() returned error
#define ER_TCPSOCKET_BIND_FAILED				0x00030032L	//!< binding the socket failed: bind() returned error
#define ER_TCPSOCKET_LISTEN_FAILED				0x00030033l	//!< listening on the socket failed: listen() returned error
#define ER_TCPSOCKET_SEND_BUF_FULL				0x00030034L	//!< the sending buffer of the tcp socket is full. Maybe the remote server does not read from socket anymore.
#define ER_TCPSOCKET_REMOTE_GONE				0x00030035L	//!< the remote part of the connection has gone
#define ER_TCPSOCKET_REFUSE_RECONNECT			0x00030036L	//!< the socket is not going to reconnect because the socket has been created with a valid socket file handle during construction. Therefore, we assume that a remote host has connected to this server and thus reconnecting wouldn't make sense
#define ER_TCPSOCKET_ADDR_ALREADY_USED			0x00030037L	//!< the same address is already used by another target. It is not allowed to use the same address multiple times. Create a target alias insted.
#define ER_TCPSOCKET_RECV_GENERIC				0x00030038L	//!< the recv function returned a not further specified error during the attempt of reading data from Tcp socket
#define ER_TCPSOCKET_CONNECT_FAILED				0x00030039L	//!< connecting to the server failed: connect() returned error

// 0x0004xxxx
#define ER_INCO_COM_INIT						0x00040001L	//!< error in initialisation of com-port
#define ER_INCO_COM_CLOSE						0x00040002L	//!< error in closing of com-port
#define ER_INCO_COM_PURGE						0x00040003L	//!< error in flushing of com-buffer
#define ER_INCO_PROTOCOL_READ					0x00040004L	//!< error in protocol while reading
#define ER_INCO_CHECKSUM_READ					0x00040005L	//!< error in checksum while reading
#define ER_INCO_PROTOCOL_WRITE					0x00040006L	//!< error in protocol while writing

// 0x0005xxxx
#define ER_INCO_DEVICE_OFFLINE					0x000500F8L	//!< The device is offline
#define ER_INCO_EME_DISP_NOT_ALLOWED			0x000500F9L	//!< The emergency dispatcher is not allowed to perform that type of inco calls (incodispatcher task is on trap/assert)
#define ER_INCO_NAK_FRAME						0x000500FAL	//!< The target returned a NAK frame. This means that the frame content checksum was incorrect. Most probably a transfer error occurred
#define ER_INCO_DEVICE_UNKNOWN					0x000500FBL	//!< The target/device is unknown (i.e. not configured)
#define ER_INCO_TOO_MANY_SUBDEVICES				0x000500FCL	//!< There are too many (sub)devices in the target path. (obsolete, used by INCOServer 3 only)
#define ER_INCO_SUBDEVICE_UNKNOWN				0x000500FDL	//!< The subtarget can't be reached (e.g. because we're transing)
#define ER_INCO_DEVICE_BUSY						0x000500FEL	//!< Device on frame route is busy (e.g. the device frame queue is full)
#define ER_INCO_UNKNOWN_FRAME					0x000500FFL	//!< Target doesn't support this INCO frame type
// block errors
#define ER_INCO_BLK_ADDRESS						0x00050101L	//!< block invalid address
#define ER_INCO_BLK_ALIGNMENT					0x00050102L	//!< block alignment error
#define ER_INCO_BLK_RANGE						0x00050103L	//!< block invalid address range
#define ER_INCO_BLK_SECTOR_ERASE				0x00050104L	//!< sector erase error (writing to flash)
#define ER_INCO_BLK_WRITE						0x00050105L	//!< writing error (writing to flash)
#define ER_INCO_BLK_P08_NOT_ALLOWED				0x00050110L	//!< putblock8 to address not allowed
#define ER_INCO_BLK_G08_NOT_ALLOWED				0x00050111L	//!< getblock8 to address not allowed
#define ER_INCO_BLK_P16_NOT_ALLOWED				0x00050112L	//!< putblock16 to address not allowed
#define ER_INCO_BLK_G16_NOT_ALLOWED				0x00050113L	//!< getblock16 to address not allowed
#define ER_INCO_BLK_P32_NOT_ALLOWED				0x00050114L	//!< putblock32 to address not allowed
#define ER_INCO_BLK_G32_NOT_ALLOWED				0x00050115L	//!< getblock32 to address not allowed
#define ER_INCO_BLK_P64_NOT_ALLOWED				0x00050116L	//!< putblock64 to address not allowed
#define ER_INCO_BLK_G64_NOT_ALLOWED				0x00050117L	//!< getblock64 to address not allowed
#define ER_INCO_BLK_SIZE_TOO_BIG				0x00050118L	//!< GetBlock or PutBlock has been requested using a too big block size
#define ER_INCO_BLK_UNKNOWN						0x000501FFL	//!< block unknown function call
// variable errors
#define ER_INCO_VAR_NOT_FOUND					0x00050201L	//!< variable not found
#define ER_INCO_VAR_READ_ONLY					0x00050202L	//!< variable is read only
#define ER_INCO_VAR_MINIMUM						0x00050203L	//!< variable minimum reached
#define ER_INCO_VAR_MAXIMUM						0x00050204L	//!< variable maximum reached
#define ER_INCO_VAR_STRING_LENGTH				0x00050205L	//!< variable string length error
#define ER_INCO_VAR_ARRAY_INDEX					0x00050206L	//!< variable array index out of bound
#define ER_INCO_VAR_KEY_LEVEL					0x00050207L	//!< variable keylevel not enough
#define ER_INCO_VAR_PROP_NOT_FOUND				0x00050208L	//!< variable property not found
#define ER_INCO_VAR_BIT_NUMBER					0x00050209L	//!< variable bit number not allowed
#define ER_INCO_VAR_BUFFER_SIZE					0x0005020AL	//!< variable Buffer to small
#define ER_INCO_VAR_MULTIDISPATCH				0x0005020BL	//!< multidispatch failed. INIX specific error code
#define ER_INCO_VAR_VARTRIGGERTWICE				0x0005020CL	//!< a trigger with the same action and of the same type is already registered. INIX specific error code
#define ER_INCO_VAR_EME_NOT_ALLOWED				0x0005020DL	//!< variable read/write not allowed for emergency incodispatcher.
#define ER_INCO_VAR_ASYNC_RESULT_LOST			0x0005020EL	//!< asynchronous variable getter did not return a result, or result was already purged from ring buffer
#define ER_INCO_VAR_TRIGGERSYNTAX				0x0005020FL	//!< the trigger command has wrong syntax
#define ER_INCO_VAR_UNSUPPORTED_TYPE			0x00050210L	//!< the type is unsupported. Depending whether a GetVariable or PutVariable was performed, this means that either INOS or the inco_32.dll should be updated.
#define ER_INCO_VAR_NOT_A_STRING				0x00050211L	//!< GetVariable was called to read a string, but the variable is not of type string.
#define ER_INCO_VAR_NOT_A_NUMBER				0x00050212L	//!< GetVariable was called to read a number, but the variable is not of type number.
#define ER_INCO_VAR_NAME_LENGTH					0x00050213L	//!< The variable name length is too long (i.e. does not fit into the maximum possible frame length)
#define ER_INCO_VAR_PUT_BUFFER_SIZE				0x00050214L	//!< The communication buffer is too small to put the variable. Variable name/path and or variable value exceeds maximum length.
#define ER_INCO_VAR_USER_ERROR					0x00050280L	//!< Variable user error
#define ER_INCO_VAR_ASYNC						0x000502FEL	//!< Variable access is async. This is a 'virtual' error only used for communication between the target and the INCOServer. If you get this error, you need to update your INCOServer version.
#define ER_INCO_VAR_UNKNOWN						0x000502FFL	//!< Target doesn't support this 'variable' frame sub type
// database errors
#define ER_INCO_DB_TABLE_UNKNOWN				0x00050301L	//!< unknown database table
#define ER_INCO_DB_RECORD_UNKNOWN				0x00050302L	//!< unknown record number/name in database table
#define ER_INCO_DB_NOT_ENOUGH_MEMORY			0x00050303L	//!< not enough memory to create database table
#define ER_INCO_DB_UNKNOWN						0x000503FFL	//!< database unknown function call

#define ER_INCO_RPC_NOT_FOUND					0x00050401L	//!< rpc procedure not found
#define ER_INCO_RPC_NO_PROCEDURE				0x00050402L	//!< rpc item is not a procedure object
#define ER_INCO_RPC_PARAM_COUNT					0x00050403L	//!< rpc wrong number of parameters
#define ER_INCO_RPC_PARAM_TYPE					0x00050404L	//!< rpc wrong type of parameters
#define ER_INCO_RPC_NOT_EXECUTABLE				0x00050405L	//!< rpc call not executable at the moment
#define ER_INCO_RPC_IN_PROGRESS					0x00050406L	//!< rpc call in progress
#define ER_INCO_RPC_NO_FLOAT_SUPPORT			0x00050407L	//!< rpc returnvalue as floating not supported. INOS error code.
#define ER_INCO_RPC_VALUE_RANGE					0x00050408L	//!< rpc value out of range
#define ER_INCO_RPC_ARG_TO_LONG					0x00050409L	//!< rpc argument too long
#define ER_INCO_RPC_MULTIDISPATCH				0x0005040AL	//!< failure with multidispatch: at least one callprocedure failed
#define ER_INCO_RPC_ARG_FORMAT					0x0005040BL	//!< error in argument formatting ('\', \", :l...)
#define ER_INCO_RPC_NO_RETURN_VALUE				0x0005040CL	//!< The function didn't return any result
#define ER_INCO_RPC_NOT_A_TICKET				0x0005040DL //!< the passed value (id) was not a ticket! Most probably the number was not negative
#define ER_INCO_RPC_UNKNOWN_TICKET				0x0005040EL	//!< Ticket is either invalid, the results have already been got or it's result has already been purged from ring buffer
#define ER_INCO_RPC_INVALID_RESULT_TYPE			0x0005040FL	//!< the result type differ from the passed data type
#define ER_INCO_RPC_UNKNOWN_FLAGS				0x00050410L	//!< the caller passed unknown flags for getting the callprocedure results
#define ER_INCO_RPC_NOT_CONVERTIBLE_TO_DOUBLE	0x00050411L //!< the CallProcedure result is not castable into a double (e.g. the result type is uint64, char*, etc.)
#define ER_INCO_RPC_RESULT_BUFFER_TO_SMALL		0x00050412L //!< the CallProcedure result cannot be written to the buffer passed by the application because the buffer is to small.
#define ER_INCO_RPC_WAIT_TIMEOUT				0x00050413L //!< waiting for the asynchronous part of the callprocedure timed out
#define ER_INCO_RPC_ASYNC_RESULT_PARSE_ERROR	0x00050414L	//!< parsing the asynchronous result failed. Either there was a transfer error or the target software (i.e. INOS) supports a newer format than the inco_32. Updating the latter may solve the issue.
#define ER_INCO_RPC_EXPECTED_A_DOUBLE			0x00050415L	//!< getting the async procedure result by 'DF_INCO_TYPE_NUMBER_VALUE' expects a double pointer being passed.
#define ER_INCO_RPC_INTERRUPTED					0x00050416L	//!< asynchronous procedure was interrupted by target reset
#define ER_INCO_RPC_KEY_LEVEL					0x00050417L	//!< RPC keylevel not enough
#define ER_INCO_RPC_USER_ERROR					0x00050480L	//!< rpc call user error
#define ER_INCO_RPC_ASYNC						0x000504FEL	//!< Procedure execution is async. This is a 'virtual' error only used for communication between the target and the INCOServer. If you get this error, you need to update your INCOServer version.
#define ER_INCO_RPC_UNKNOWN						0x000504FFL	//!< rpc unknown function call

#define ER_INCO_DBG_ID_INVALID					0x00050601L	//!< task id not valid
#define ER_INCO_DBG_NAME_INVALID				0x00050602L	//!< task name not valid
#define ER_INCO_DBG_NO_FLOATING					0x00050603L	//!< task has no floating point support
#define ER_INCO_DBG_BRK_PT_INVALID				0x00050604L	//!< task breakpoint not valid
#define ER_INCO_DBG_BRK_PT_ALREADY				0x00050605L	//!< task breakpoint already set
#define ER_INCO_DBG_WRONG_LENGTH				0x00050606L	//!< task data wrong length for requested data
#define ER_INCO_DBG_UNKNOWN_DATA				0x00050607L	//!< task data unknown data request
#define ER_INCO_DBG_PUT_FORBIDDEN				0x00050608L	//!< task data put not allowed
#define ER_INCO_DBG_BRK_PT_MEMORY				0x00050609L	//!< not enough memory to set breakpoint
#define ER_INCO_DBG_NO_HARD_RESET				0x0005060AL	//!< hard reset not supported
#define ER_INCO_DBG_NO_DEVICE					0x0005060BL	//!< no load device found to handle request
#define ER_INCO_DBG_NO_SOFT_RESET				0x0005060CL	//!< soft reset not allowed
#define ER_INCO_DBG_BUFFER_TO_SMALL				0x0005060DL //!< The buffer is to small to store all data. Data has been truncated
#define ER_INCO_DBG_INVALID_ARG					0x0005060EL //!< Invalid argument passed (i.e. null pointer)
#define ER_INCO_DBG_NO_WATCHPOINTS_EXCEEDED		0x0005060FL //!< Number of watchpoints exceeded
#define ER_INCO_DBG_WATCHPOINT_CLR_ADDRESS		0x00050610L //!< Trying to clear a watchpoint which was not set before
#define ER_INCO_DBG_TASK_NOT_DEBUG_SUSPENDED	0x00050611L //!< Operation refused because task is not in 'debug suspended' state
#define ER_INCO_DBG_BUFFER_EXCEEDED				0x00050612L //!< The buffer is to small to store all data. No data has been returned
#define ER_INCO_DBG_EMPTY_CACHE					0x00050613L //!< No cached information available. E.g. the target doesn't support that feature or another call has been performed in the meantime
#define ER_INCO_DBG_INVALID_COOKIE				0x00050614L //!< No task register information in INCOFrame
#define ER_INCO_DBG_UNKNOWN						0x000506FFL	//!< task unknown function call

#define ER_INCO_BIT_INVALID						0x00050701L	//!< invalid bit number/name
#define ER_INCO_BIT_UNKNOWN						0x000507FFL	//!< unknown function call

#define ER_INCO_PARSING_NOT_FINISHED			0x00050800L	//!< Parsing of data stream started but was not finished
#define ER_INCO_PARSING_DEST_PATH_LENGTH		0x00050802L	//!< Length of destination path mismatch (missing '\0' ?)
#define ER_INCO_PARSING_SRC_PATH_LENGTH			0x00050803L	//!< Length of source path mismatch (missing '\0' ?)
#define ER_INCO_PARSING_CHECKSUM_HEADER			0x00050804L	//!< Checksum of header was wrong
#define ER_INCO_PARSING_CHECKSUM_CONTENT		0x00050805L	//!< Chechsum of content was wrong
#define ER_INCO_PARSING_TO_MUCH_DATA			0x00050806L	//!< amount of data is to big (see DF_MAX_DATA_LENGTH)
#define ER_INCO_PARSING_VERSION_MISMATCH		0x00050807L	//!< The version of the incoframe mismatched (frame was put to the wrong parser/device)
#define ER_INCO_PARSING_MISC_ERROR				0x00050808L	//!< Miscellanieous frame parsing error
#define ER_INCO_PARSING_SECOND_SOH_DETECTED		0x00050809L	//!< The frame-parser has detected a SOH within the data stream (in fact this is not an error)
#define ER_INCO_PARSING_MORE_DATA_FIRST_OK		0x0005080AL	//!< The given datastream contains more than one SOH. The first incoframe has been parsed successfully!
#define ER_INCO_PARSING_MORE_DATA				0x0005080BL	//!< The given datastream contains more than one SOH. But the first incoframe has produced a parsing error.
#define ER_INCO_PARSING_SOH_RECEIVED			0x0005080CL	//!< Received SOH classic frame but this is not supported.
//@}

/*! \name INCO errors (deprecated, left for old applications) */
//@{
// 0x0006xxxx
#define ER_VB_ERROR								0x00060000	//!< reserved for VB-errors (look Err.Number)

// 0x0007xxxx
#define ER_INCO_COM_INIT_SIO					0x00070001L	//!< error initialising COM
#define ER_INCO_COM_WRITE						0x00070002L	//!< error writing to COM
#define ER_INCO_COM_READ						0x00070003L	//!< error reading from COM
#define ER_INCO_COM_TIMEOUT						0x00070004L	//!< timeout reading from COM

// 0x0008xxxx
#define ER_INCO_DT_CONTROL_UNKNOWN				0x00080000L	//!< Data transfer error: DTControl called with unknown request
#define ER_INCO_DT_NOCONNECTION					0x00080001L	//!< Data transfer error: No connection
#define ER_INCO_DT_TIMEOUT						0x00080002L	//!< Data transfer error: Timeout transmitting data
#define ER_INCO_DT_TRANSMISSION_FAILURE			0x00080003L	//!< Data transfer error: Transmission failure
#define ER_INCO_DT_ALREADY_CONNECTED			0x00080004L	//!< Data transfer error: The remote partner already has a connection established
#define ER_INCO_DT_DEVICE_UNSUPPORTED			0x00080005L	//!< Data transfer error: This device type is not support
#define ER_INCO_DT_METHOD_UNKONWN				0x00080006L	//!< Data transfer error: This transfer method is unkown. Updating libinco_32 may fix the issue
#define ER_INCO_DT_CONNECTING_REFUSED			0x00080007L	//!< Data transfer error: Remote refused to connect
#define ER_INCO_DT_TOO_MUCH_DATA					0x00080008L	//!< Data transfer error: The remote cannot handle that much data
#define ER_INCO_DT_BUFFER_TO_SMALL				0x00080009L	//!< Data transfer error: The provided buffer size is to small. It must at least provide as much memory as defined by the datachannel
#define ER_INCO_DT_LOCK_FAILED					0x0008000AL	//!< Data transfer error: Failed to initialize lock
#define ER_INCO_DT_LOCK_TIMEOUT					0x0008000BL	//!< Data transfer error: Timeout while waiting for lock
//@}


/*! \name Application errors used by INIX */
//@{
// 0x1000xxxx
#define DF_ER_INIX_PLUGIN_STATE_NOT_POSSIBLE	0x10001001L
#define DF_ER_INIX_PLUGIN_STATE_UNKNOWN			0x10001002L
#define ER_INCO_DISP_EXISTS						0x10002001L
#define ER_INCO_DISP_NOT_EXISTS					0x10002002L
//@}


/*! \name Application errors used by the INIX event logger */
//@{
// 0x2000xxxx
#define DF_ER_INIX_LOGGER_ALREADY_INITIALIZED	0x20000001L
#define DF_ER_INIX_LOGGER_NOT_INITIALIZED		0x20000002L
#define DF_ER_INIX_LOGGER_LEVEL_IS_ACTIVE		0x20000003L
#define DF_ER_INIX_LOGGER_LEVEL_IS_NOT_ACTIVE	0x20000004L
#define DF_ER_INIX_LOGGER_NO_MESSAGES			0x20000005L
#define DF_ER_INIX_LOGGER_BUFFER_TO_SMALL		0x20000006L
#define DF_ER_INIX_LOGGER_MISC					0x20000007L
#define DF_ER_INIX_LOGGER_LEVEL_ALREADY_EXISTS	0x20000008L
#define DF_ER_INIX_LOGGER_LEVEL_NO_FREE			0x20000009L
#define DF_ER_INIX_LOGGER_LEVEL_RESERVED		0x2000000AL
#define DF_ER_INIX_LOGGER_LEVEL_RANGE			0x2000000BL
#define DF_ER_INIX_LOGGER_CALLBACK_INSTALLED	0x2000000CL
//@}


/*! \name Application errors used by the McRobot */
//@{
// 0x40xxxxxx
//@}


/*! \name Application errors used by the customer specific application code */
//@{
// 0x80xxxxxx
//@}


#endif // __INCOERRORS_H__

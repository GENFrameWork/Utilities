/*=============================================================================

    Copyright (c) 1998-2001  Microsoft Corporation

    Module Name:

        clfsw32.h

    Abstract:

        Declares the exported API set for the Common Log Win32
        API dynamic link library and static library.

    Author:

        Dexter Bradshaw [DexterB] 24-Apr-2001

    Environment:

        User Mode

    Revision History:


=============================================================================*/
#ifndef __CLFSW32_H__
#define __CLFSW32_H__

#ifdef __BORLANDC__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#endif

//-----------------------------------------------------------------------------
// CLFS INCLUDES
//-----------------------------------------------------------------------------

#ifdef KERNEL_MODE
#   undef KERNEL_MODE
#endif KERNEL_MODE

#include <clfs.h>



//------------------------------------------------------------------------------
// CUSTOM CONSTANTS
//------------------------------------------------------------------------------

const DWORD BLOCK_AVAILABLE         =  WAIT_OBJECT_0;
const DWORD BLOCK_WAIT_ABANDONED    =  WAIT_ABANDONED;
const DWORD BLOCK_WAIT_TIMEDOUT     =  WAIT_TIMEOUT;
const DWORD BLOCK_WAIT_FAILED       =  WAIT_FAILED;

//------------------------------------------------------------------------------
// TYPE DEFINITIONS
//------------------------------------------------------------------------------


#ifdef __cplusplus
extern "C"
{
#endif __cplusplus


//
// PCLFS_COMPLETION_ROUTINE
//

typedef void (__stdcall * PCLFS_COMPLETION_ROUTINE) (
                    IN PVOID pvOverlapped,
                    IN ULONG ulReserved
                    );

//
// PCLFS_PRINT_RECORD_ROUTINE
//
// User defined callback deciphering the format of a log record
// buffer and dumping its content to the log stream.
//

typedef ULONG (__stdcall * CLFS_PRINT_RECORD_ROUTINE) (
                    IN PFILE pstrmOut,
                    IN CLFS_RECORD_TYPE fRecordType,
                    IN PVOID pvBuffer,
                    IN ULONG cbBuffer
                    );

//
// CLFS_LOG_ARCHIVE_CONTEXT
//
// The log archive context is an opaque user data structure allocated by the CLFS
// user-mode runtime after successfully preparing for archival.  Log archive
// clients should make no assumptions about the contents of this data structure
// nor in any way attempt to change it.  The log archive context maintains a copy
// (not a reference) to the log file handle and maintains the cursor state during
// iteration throught the archive descriptor set returned from preparing for
// archival.
//

typedef PVOID CLFS_LOG_ARCHIVE_CONTEXT, *PCLFS_LOG_ARCHIVE_CONTEXT;


//------------------------------------------------------------------------------
// EXPORTED ENTRY POINT DECLARATION
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// LsnCreate
// 
// Create an LSN given a log identifier, a container identifier, a block
// offset and a bucket identifier.  Caller must test for invalid LSN after
// making this call.
//------------------------------------------------------------------------------

CLFSUSER_API CLFS_LSN WINAPI LsnCreate (
                    IN CLFS_CONTAINER_ID    cidContainer,
                    IN ULONG                offBlock,
                    IN ULONG                cRecord
                    );


//-----------------------------------------------------------------------------
// LsnContainer
//
// Entry point to extract the container identifier from the LSN.
//-----------------------------------------------------------------------------

CLFSUSER_API CLFS_CONTAINER_ID WINAPI LsnContainer (
                    IN const CLFS_LSN* plsn
                    );


//-----------------------------------------------------------------------------
// LsnBlockOffset
//
// Entry point to extract the block offset from the LSN.
//-----------------------------------------------------------------------------

CLFSUSER_API ULONG WINAPI LsnBlockOffset (
                    IN const CLFS_LSN* plsn
                    );


//-----------------------------------------------------------------------------
// LsnRecordSequence 
//
// Entry point to extract the bucket identifier from the LSN.
//-----------------------------------------------------------------------------

CLFSUSER_API ULONG WINAPI LsnRecordSequence (
                    IN const CLFS_LSN* plsn
                    );


//------------------------------------------------------------------------------
// CreateLogFile
//
// Entry point to create a physical log file consisting of uniformly sized
// containers lying in a given directory path.
//------------------------------------------------------------------------------

CLFSUSER_API HANDLE WINAPI CreateLogFile (
                    IN LPCWSTR pszLogFileName,
                    IN ACCESS_MASK fDesiredAccess,
                    IN DWORD dwShareMode,
                    IN LPSECURITY_ATTRIBUTES psaLogFile OPTIONAL,
                    IN ULONG fCreateDisposition,
                    IN ULONG fFlagsAndAttributes
                    );


//------------------------------------------------------------------------------
// DeleteLogByHandle
//
// Entry point to delete a physical log file and its underlying container
// storage by handle.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI DeleteLogByHandle (IN HANDLE hLog);


//------------------------------------------------------------------------------
// DeleteLogFile
//
// Entry point to delete a physical log file and its underlying container
// storage by name.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI DeleteLogFile (
                    IN LPCWSTR pszLogFileName,
                    IN LPSECURITY_ATTRIBUTES psaLogFile OPTIONAL
                    );


//------------------------------------------------------------------------------
// AddLogContainer
//
// Adds a log container to a given physical file identified by the log
// handle.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI AddLogContainer (
                    __in HANDLE hLog,
                    __in_opt PULONGLONG pcbContainer,
                    __in LPWSTR pwszContainerPath,
                    __inout_opt LPOVERLAPPED pOverlapped
                    );

//------------------------------------------------------------------------------
// AddLogContainerSet
//
// Adds a set of log containers to a given physical file identified by the log
// handle.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI AddLogContainerSet (
                    __in HANDLE hLog,
                    __in USHORT cContainer,
                    __in_opt PULONGLONG pcbContainer,
                    __in_ecount(cContainer) LPWSTR *rgwszContainerPath,
                    __inout_opt LPOVERLAPPED pOverlapped
                    );

//------------------------------------------------------------------------------
// RemoveLogContainer
//
// Removes a log container from a physical log file identified by
// the log handle.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI RemoveLogContainer (
                    __in HANDLE hLog,
                    __in LPWSTR pwszContainerPath,
                    __in BOOL fForce,
                    __inout_opt LPOVERLAPPED pOverlapped
                    );

//------------------------------------------------------------------------------
// RemoveLogContainerSet
//
// Removes a set of log containers from a physical log file identified by
// the log handle.
//------------------------------------------------------------------------------


CLFSUSER_API BOOL WINAPI RemoveLogContainerSet (
                    __in HANDLE hLog,
                    __in USHORT cContainer,
                    __in_ecount(cContainer) LPWSTR *rgwszContainerPath,
                    __in BOOL fForce,
                    __inout_opt LPOVERLAPPED pOverlapped
                    );


//------------------------------------------------------------------------------
// SetLogArchiveTail
//
// Sets the archive tail for either a client or physical log file
// depending on the type of the log handle.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI SetLogArchiveTail (
                    IN HANDLE hLog,
                    IN PCLFS_LSN plsnArchiveTail,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// SetEndOfLog
//
// This function sets the end of log to the value specified by the plsnEnd 
// parameter.  The operation only works on non-ephemeral logs and is usually
// called by archival or log-shipping engines during dynamic roll forward
// recovery.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI SetEndOfLog (
                    IN HANDLE hLog,
                    IN PCLFS_LSN plsnEnd,
                    IN OUT LPOVERLAPPED lpOverlapped
                    );


//------------------------------------------------------------------------------
// CreateLogContainerScanContext
//
// Create a scan context to enumerate scan descriptors for storage containers 
// that back the physical log file stream.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI CreateLogContainerScanContext (
                    IN HANDLE hLog,
                    IN ULONG cFromContainer,
                    IN ULONG cContainers,
                    IN CLFS_SCAN_MODE eScanMode,
                    IN OUT PCLFS_SCAN_CONTEXT pcxScan,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// ScanLogContainers
//
// Scan descriptors for storage containers backing the physical
// log file stream.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI ScanLogContainers (
                    IN OUT PCLFS_SCAN_CONTEXT pcxScan,
                    IN CLFS_SCAN_MODE eScanMode,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// AlignReservedLog
//
// Given a valid marshalling context calculate the sector algined aggregate
// number of reserved records and bytes.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI AlignReservedLog (
                    IN OUT PVOID pvMarshal,
                    IN ULONG cReservedRecords,
                    IN LONGLONG rgcbReservation [],
                    OUT PLONGLONG pcbAlignReservation
                    );


//------------------------------------------------------------------------------
// AllocReservedLog
//
// Given a valid marshalling context, allocate an aggregate number of reserved
// records and bytes.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI AllocReservedLog (
                    IN OUT PVOID pvMarshal,
                    IN ULONG cReservedRecords,
                    IN OUT PLONGLONG pcbAdjustment
                    );


//------------------------------------------------------------------------------
// FreeReservedLog
//
// Set the reserved log space to a new size or specify a delta
// for the reserved space.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI FreeReservedLog (
                    IN OUT PVOID pvMarshal,
                    IN ULONG cReservedRecords,
                    IN OUT PLONGLONG pcbAdjustment
                    );

//------------------------------------------------------------------------------
// GetLogFileInformation
//
// Get log file information for a physical log and client stream
// specific to the handle.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI GetLogFileInformation (
                    IN HANDLE hLog,
                    IN OUT PCLFS_INFORMATION pinfoBuffer,
                    IN OUT PULONG cbBuffer
                    );

//------------------------------------------------------------------------------
// SetLogArchiveMode
//
// Enable or disable the log's archive support mechanisms.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI SetLogArchiveMode (
                    IN HANDLE hLog,
                    IN CLFS_LOG_ARCHIVE_MODE eMode
                    );

//------------------------------------------------------------------------------
// CopyLogRestartArea
//
// Read and copy the last restart area successfully written to a physical or 
// client log stream into a user defined buffer.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI CopyLogRestartArea (
                    IN PVOID pvMarshal,
                    OUT PVOID pvRestartBuffer,
                    IN ULONG cbRestartBuffer,
                    OUT PULONG pcbBytesRead,
                    OUT PCLFS_LSN plsn,
                    OUT PVOID *ppvContext,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );

//------------------------------------------------------------------------------
// ReadLogRestartArea
//
// Read the last restart area successfully written to a physical or 
// client log stream.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI ReadLogRestartArea (
                    IN PVOID pvMarshal,
                    OUT PVOID* ppvRestartBuffer,
                    OUT PULONG pcbRestartBuffer,
                    OUT PCLFS_LSN plsn,
                    OUT PVOID *ppvContext,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// ReadPreviousLogRestartArea
//
// Read the previous restart area successfully written to a physical or 
// client log stream given the read context created by the a call to
// ReadRestartArea or CopyRestartArea.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI ReadPreviousLogRestartArea (
                    IN PVOID pvReadContext,
                    OUT PVOID *ppvRestartBuffer,
                    OUT PULONG pcbRestartBuffer,
                    OUT PCLFS_LSN plsnRestart,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );

//------------------------------------------------------------------------------
// CopyPreviousLogRestartArea
//
// Read and copy the last restart area successfully written to a physical or 
// client log stream given the read context created by the a call to
// NtReadRestartArea or NtCopyRestartArea.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI CopyPreviousLogRestartArea (
                    IN PVOID pvReadContext,
                    OUT PVOID pvRestartBuffer,
                    IN ULONG cbRestartBuffer,
                    OUT PULONG pcbBytesRead,
                    OUT PCLFS_LSN plsnRestart,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// WriteLogRestartArea
//
// Write a new restart area to a physical or client log stream.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI WriteLogRestartArea (
                    IN OUT PVOID pvMarshal,
                    IN PVOID pvRestartBuffer,
                    IN ULONG cbRestartBuffer,
                    IN PCLFS_LSN plsnBase OPTIONAL,
                    IN ULONG fFlags,
                    OUT PULONG pcbWritten OPTIONAL,
                    OUT PCLFS_LSN plsnNext OPTIONAL,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// AdvanceLogBase
//
// Set a new base LSN for a log stream without writing a restart record.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI AdvanceLogBase (
                    IN OUT PVOID pvMarshal,
                    IN PCLFS_LSN plsnBase,
                    IN ULONG fFlags,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// CloseAndResetLogFile
//
// Orderly shutdown of a client log stream.  This call only works on client
// stream handles and will return ERROR_INVALID_HANDLE on a physical stream.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI CloseAndResetLogFile (IN HANDLE hLog);



//------------------------------------------------------------------------------
// CreateLogMarshallingArea
//
// Initalize a marshalling area for a physical or client log
// file stream.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI CreateLogMarshallingArea (
                    IN HANDLE hLog,
                    IN CLFS_BLOCK_ALLOCATION pfnAllocBuffer OPTIONAL,
                    IN CLFS_BLOCK_DEALLOCATION pfnFreeBuffer OPTIONAL,
                    IN PVOID pvBlockAllocContext OPTIONAL,
                    IN ULONG cbMarshallingBuffer,
                    IN ULONG cMaxWriteBuffers,
                    IN ULONG cMaxReadBuffers,
                    OUT PVOID *ppvMarshal
                    );

//------------------------------------------------------------------------------
// DeleteLogMarshallingArea
//
// Delete a marshalling area for a physical or client log
// file stream.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI DeleteLogMarshallingArea (IN PVOID pvMarshal);


//------------------------------------------------------------------------------
// ReserveAndAppendLog
//
// Reserve space and append log buffers to a physical or client
// log stream.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI ReserveAndAppendLog (
                    IN PVOID pvMarshal,
                    IN PCLFS_WRITE_ENTRY rgWriteEntries OPTIONAL,
                    IN ULONG cWriteEntries,
                    IN PCLFS_LSN plsnUndoNext OPTIONAL,
                    IN PCLFS_LSN plsnPrevious OPTIONAL,
                    IN ULONG cReserveRecords,
                    IN OUT LONGLONG rgcbReservation [] OPTIONAL,
                    IN ULONG fFlags,
                    OUT PCLFS_LSN plsn OPTIONAL,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// ReserveAndAppendLogAligned
//
// Reserve space and append log buffers to a physical or client
// log stream, honoring an alignment between write entries.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI ReserveAndAppendLogAligned (
                    IN PVOID pvMarshal,
                    IN PCLFS_WRITE_ENTRY rgWriteEntries OPTIONAL,
                    IN ULONG cWriteEntries,
                    IN ULONG cbEntryAlignment,
                    IN PCLFS_LSN plsnUndoNext OPTIONAL,
                    IN PCLFS_LSN plsnPrevious OPTIONAL,
                    IN ULONG cReserveRecords,
                    IN OUT LONGLONG rgcbReservation [] OPTIONAL,
                    IN ULONG fFlags,
                    OUT PCLFS_LSN plsn OPTIONAL,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );

//------------------------------------------------------------------------------
// FlushLogBuffers
// 
// Flush move all current buffers in the marshalling area to the flush queue and 
// flush all buffers to the disk.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI FlushLogBuffers (
                    IN PVOID pvMarshal,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// FlushLogToLsn
// 
// Flush all buffers in the marshalling area up to a target LSN to the flush
// queue and flush all buffers up to the target LSN to the disk.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI FlushLogToLsn (
                    IN PVOID pvMarshalContext,
                    IN PCLFS_LSN plsnFlush,
                    OUT PCLFS_LSN plsnLastFlushed OPTIONAL,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// ReadLogRecord
//
// Read a log record from a physical or client log stream given
// a starting LSN.
//------------------------------------------------------------------------------


CLFSUSER_API BOOL WINAPI ReadLogRecord (
                    IN PVOID pvMarshal,
                    IN OUT PCLFS_LSN plsnFirst,
                    IN CLFS_CONTEXT_MODE eContextMode,
                    OUT PVOID* ppvReadBuffer,
                    OUT PULONG pcbReadBuffer,
                    OUT PCLFS_RECORD_TYPE peRecordType,
                    OUT PCLFS_LSN plsnUndoNext,
                    OUT PCLFS_LSN plsnPrevious,
                    OUT PVOID* ppvReadContext,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// ReadNextLogRecord
//
// Read the next log record from a given marshalling context.
//------------------------------------------------------------------------------


CLFSUSER_API BOOL WINAPI ReadNextLogRecord (
                    IN OUT PVOID pvReadContext,
                    OUT PVOID* ppvBuffer,
                    OUT PULONG pcbBuffer,
                    IN OUT PCLFS_RECORD_TYPE peRecordType,
                    IN PCLFS_LSN plsnUser OPTIONAL,
                    OUT PCLFS_LSN plsnUndoNext,
                    OUT PCLFS_LSN plsnPrevious,
                    OUT PCLFS_LSN plsnRecord,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// CopyLogRecord
//
// Read a log record from a physical or client log stream given
// a starting LSN and a user-allocated buffer.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI CopyLogRecord (
                    IN PVOID pvMarshal,
                    IN OUT PCLFS_LSN plsnFirst,
                    IN CLFS_CONTEXT_MODE ecxMode,
                    IN OUT PVOID pvReadBuffer,
                    IN ULONG cbReadBuffer,
                    OUT PCLFS_RECORD_TYPE peRecordType,
                    OUT PCLFS_LSN plsnUndoNext,
                    OUT PCLFS_LSN plsnPrevious,
                    OUT PULONG pcbBytesRead,
                    OUT PVOID* ppvReadContext,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );

//------------------------------------------------------------------------------
// CopyNextLogRecord
//
// Read and copy the next log record from a given marshalling context into a 
// user allocated buffer.
//------------------------------------------------------------------------------


CLFSUSER_API BOOL WINAPI CopyNextLogRecord (
                    IN OUT PVOID pvReadContext,
                    IN OUT PVOID pvReadBuffer,
                    IN ULONG cbReadBuffer,
                    IN OUT PCLFS_RECORD_TYPE peRecordType,
                    IN PCLFS_LSN plsnUser,
                    OUT PCLFS_LSN plsnUndoNext,
                    OUT PCLFS_LSN plsnPrevious,
                    OUT PCLFS_LSN plsnRecord,
                    OUT PULONG pcbRecordLength,
                    IN OUT LPOVERLAPPED pOverlapped OPTIONAL
                    );


//------------------------------------------------------------------------------
// TerminateReadLog
//
// Terminate the read context.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI TerminateReadLog (IN PVOID pvCursorContext);


//------------------------------------------------------------------------------
// GetLastLogLsn
//
// Get the last used LSN.
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI GetLastLogLsn (
                    IN HANDLE hLog,
                    OUT PCLFS_LSN plsnLast
                    );


//------------------------------------------------------------------------------
// DumpLogRecords
//
// Given log file name, scan a log file and dump log records to a file stream.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI DumpLogRecords (
                    __in PWSTR pwszLogFileName,
                    __in CLFS_RECORD_TYPE fRecordType,
                    __in_opt PCLFS_LSN plsnStart,
                    __in_opt PCLFS_LSN plsnEnd,
                    __in_opt PFILE pstrmOut,
                    __in_opt CLFS_PRINT_RECORD_ROUTINE pfnPrintRecord,
                    __in_opt CLFS_BLOCK_ALLOCATION pfnAllocBlock,
                    __in_opt CLFS_BLOCK_DEALLOCATION pfnFreeBlock,
                    __in_opt PVOID pvBlockAllocContext,
                    __in ULONG cbBlock,
                    __in ULONG cMaxBlocks
                    );


//------------------------------------------------------------------------------
// PrepareLogArchive
//
// Snapshots the current active log and builds an ordered set of log archive
// descriptors describing the logically contiguous active log extents. This
// function also allocates and initializes a log archvie context for use in
// GetNextLogArchiveExtent and ReadLogArchiveMetadata.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI PrepareLogArchive (
                __in HANDLE hLog,
                __inout_ecount(cLen) PWSTR pszBaseLogFileName,
                __in ULONG cLen,
                __in_opt const PCLFS_LSN plsnLow,
                __in_opt const PCLFS_LSN plsnHigh,
                __out_opt PULONG pcActualLength,
                __out PULONGLONG poffBaseLogFileData,
                __out PULONGLONG pcbBaseLogFileLength,
                __out PCLFS_LSN plsnBase,
                __out PCLFS_LSN plsnLast,
                __out PCLFS_LSN plsnCurrentArchiveTail,
                __out PCLFS_LOG_ARCHIVE_CONTEXT ppvArchiveContext
                );


//------------------------------------------------------------------------------
// ReadLogArchiveMetadata
//
// Copies a portion of the metadata snapshot taken at the time of an invocation
// of PrepareLogArchvie to a user buffer.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI ReadLogArchiveMetadata(
                IN CLFS_LOG_ARCHIVE_CONTEXT pvArchiveContext,
                IN ULONG     cbOffset,
                IN ULONG     cbBytesToRead,
                IN OUT PBYTE pbReadBuffer,
                OUT PULONG   pcbBytesRead
                );

//------------------------------------------------------------------------------
// GetNextLogArchiveExtent
//
// Iterates through the ordered set of log archive descriptors maintaining
// cursor state through the log archive context returned in PrepareLogArchive.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI GetNextLogArchiveExtent (
                IN CLFS_LOG_ARCHIVE_CONTEXT pvArchiveContext,
                IN OUT CLFS_ARCHIVE_DESCRIPTOR rgadExtent [],
                IN ULONG cDescriptors,
                OUT PULONG pcDescriptorsReturned
                );


//------------------------------------------------------------------------------
// TerminateLogArchive
//
// De-allocates all system resources allocated to a valid log archive context
// on completion of enumeration of all log descriptors.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI TerminateLogArchive (
                IN CLFS_LOG_ARCHIVE_CONTEXT pvArchiveContext
                );



//------------------------------------------------------------------------------
// ValidateLogRestore
//
// Validates the consistency of both log metadata and data before archival and
// after log restore.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI ValidateLogRestore (
                IN LPCWSTR pszLogFileName,
                IN LPSECURITY_ATTRIBUTES psaLogFile OPTIONAL,
                OUT PCLFS_INFORMATION pinfoBuffer OPTIONAL,
                IN OUT PULONG pcbBuffer
                );

//------------------------------------------------------------------------------
// GetLogContainerName
//
// Gets the name of a container given the container identifier.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI GetLogContainerName (
                IN HANDLE hLog,
                IN CLFS_CONTAINER_ID cidLogicalContainer,
                IN OUT LPCWSTR pwstrContainerName,
                IN ULONG cLenContainerName,
                IN OUT PULONG pcActualLenContainerName OPTIONAL
                );

//------------------------------------------------------------------------------
// GetLogIoStatistics
//
// Gets the log I/O statistics for the log associated with a given log handle.
//
//------------------------------------------------------------------------------

CLFSUSER_API BOOL WINAPI GetLogIoStatistics (
                IN HANDLE hLog,
                IN OUT PVOID pvStatsBuffer,
                IN ULONG cbStatsBuffer,
                IN CLFS_IOSTATS_CLASS eStatsClass,
                OUT PULONG pcbStatsWritten OPTIONAL
                );



#ifdef __cplusplus
}
#endif __cplusplus

#ifdef __BORLANDC__
#pragma option pop /*P_O_Pop*/
#endif

#endif  __CLFSW32_H__

//-----------------------------------------------------------------------------
//                                      END OF FILE
//-----------------------------------------------------------------------------

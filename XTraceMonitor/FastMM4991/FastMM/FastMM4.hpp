// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FastMM4.pas' rev: 6.00

#ifndef FastMM4HPP
#define FastMM4HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

#define PatchBCBTerminate

#undef EnableMemoryLeakReporting

#define DetectMMOperationsAfterUninstall

#define CheckCppObjectTypeEnabled

namespace Fastmm4
{
//-- type declarations -------------------------------------------------------
typedef char *PByte;

typedef int NativeInt;

typedef unsigned NativeUInt;

typedef unsigned *PNativeUInt;

typedef int IntPtr;

typedef unsigned UIntPtr;

#pragma pack(push, 4)
struct TSmallBlockTypeState
{
	unsigned InternalBlockSize;
	unsigned UseableBlockSize;
	unsigned AllocatedBlockCount;
	unsigned ReservedAddressSpace;
} ;
#pragma pack(pop)

typedef TSmallBlockTypeState TSmallBlockTypeStates[56];

#pragma pack(push, 4)
struct TMemoryManagerState
{
	TSmallBlockTypeState SmallBlockTypeStates[56];
	unsigned AllocatedMediumBlockCount;
	unsigned TotalAllocatedMediumBlockSize;
	unsigned ReservedMediumBlockAddressSpace;
	unsigned AllocatedLargeBlockCount;
	unsigned TotalAllocatedLargeBlockSize;
	unsigned ReservedLargeBlockAddressSpace;
} ;
#pragma pack(pop)

struct TMemoryManagerUsageSummary
{
	unsigned AllocatedBytes;
	unsigned OverheadBytes;
	double EfficiencyPercentage;
} ;

#pragma option push -b-
enum TChunkStatus { csUnallocated, csAllocated, csReserved, csSysAllocated, csSysReserved };
#pragma option pop

typedef TChunkStatus TMemoryMap[65536];

#pragma pack(push, 4)
struct TRegisteredMemoryLeak
{
	void *LeakAddress;
	TMetaClass*LeakedClass;
	void *LeakedCppTypeIdPtr;
	int LeakSize;
	int LeakCount;
} ;
#pragma pack(pop)

typedef DynamicArray<TRegisteredMemoryLeak >  TRegisteredMemoryLeaks;

#pragma option push -b-
enum TStringDataType { stUnknown, stAnsiString, stUnicodeString };
#pragma option pop

typedef void __fastcall (*TWalkAllocatedBlocksCallback)(void * APBlock, int ABlockSize, void * AUserData);

typedef unsigned __fastcall (*TGetCppVirtObjSizeByTypeIdPtrFunc)(void * APointer);

typedef void * __fastcall (*TGetCppVirtObjTypeIdPtrFunc)(void * APointer, unsigned ASize);

typedef char * __fastcall (*TGetCppVirtObjTypeNameFunc)(void * APointer, unsigned ASize);

typedef char * __fastcall (*TGetCppVirtObjTypeNameByTypeIdPtrFunc)(void * APointer);

typedef char * __fastcall (*TGetCppVirtObjTypeNameByVTablePtrFunc)(void * AVTablePtr, unsigned AVTablePtrOffset);

//-- var, const, procedure ---------------------------------------------------
#define FastMMVersion "4.991"
static const Shortint NumSmallBlockTypes = 0x38;
extern PACKAGE bool FullDebugModeScanMemoryPoolBeforeEveryOperation;
extern PACKAGE bool FullDebugModeRegisterAllAllocsAsExpectedMemoryLeak;
extern PACKAGE bool SuppressMessageBoxes;
extern PACKAGE int *pCppDebugHook;
extern PACKAGE TGetCppVirtObjSizeByTypeIdPtrFunc GetCppVirtObjSizeByTypeIdPtrFunc;
extern PACKAGE TGetCppVirtObjTypeIdPtrFunc GetCppVirtObjTypeIdPtrFunc;
extern PACKAGE TGetCppVirtObjTypeNameFunc GetCppVirtObjTypeNameFunc;
extern PACKAGE TGetCppVirtObjTypeNameByTypeIdPtrFunc GetCppVirtObjTypeNameByTypeIdPtrFunc;
extern PACKAGE TGetCppVirtObjTypeNameByVTablePtrFunc GetCppVirtObjTypeNameByVTablePtrFunc;
extern PACKAGE TMetaClass* __fastcall DetectClassInstance(void * APointer);
extern PACKAGE void * __fastcall FastGetMem(int ASize);
extern PACKAGE int __fastcall FastFreeMem(void * APointer);
extern PACKAGE void * __fastcall FastReallocMem(void * APointer, int ANewSize);
extern PACKAGE void * __fastcall FastAllocMem(unsigned ASize);
extern PACKAGE bool __fastcall RegisterExpectedMemoryLeak(void * ALeakedPointer)/* overload */;
extern PACKAGE bool __fastcall RegisterExpectedMemoryLeak(TMetaClass* ALeakedObjectClass, int ACount = 0x1)/* overload */;
extern PACKAGE bool __fastcall RegisterExpectedMemoryLeak(void * ALeakedCppVirtObjTypeIdPtr, int ACount)/* overload */;
extern PACKAGE bool __fastcall RegisterExpectedMemoryLeak(int ALeakedBlockSize, int ACount = 0x1)/* overload */;
extern PACKAGE bool __fastcall UnregisterExpectedMemoryLeak(void * ALeakedPointer)/* overload */;
extern PACKAGE bool __fastcall UnregisterExpectedMemoryLeak(TMetaClass* ALeakedObjectClass, int ACount = 0x1)/* overload */;
extern PACKAGE bool __fastcall UnregisterExpectedMemoryLeak(void * ALeakedCppVirtObjTypeIdPtr, int ACount)/* overload */;
extern PACKAGE bool __fastcall UnregisterExpectedMemoryLeak(int ALeakedBlockSize, int ACount = 0x1)/* overload */;
extern PACKAGE TRegisteredMemoryLeaks __fastcall GetRegisteredMemoryLeaks();
extern PACKAGE TStringDataType __fastcall DetectStringData(void * APMemoryBlock, int AAvailableSpaceInBlock);
extern PACKAGE void __fastcall WalkAllocatedBlocks(TWalkAllocatedBlocksCallback ACallBack, void * AUserData);
extern PACKAGE bool __fastcall LogMemoryManagerStateToFile(const AnsiString AFileName, const AnsiString AAdditionalDetails = "");
extern PACKAGE void __fastcall GetMemoryManagerState(TMemoryManagerState &AMemoryManagerState);
extern PACKAGE void __fastcall GetMemoryManagerUsageSummary(TMemoryManagerUsageSummary &AMemoryManagerUsageSummary);
extern PACKAGE void __fastcall GetMemoryMap(TChunkStatus * AMemoryMap);
extern PACKAGE System::THeapStatus __fastcall FastGetHeapStatus();
extern PACKAGE void __fastcall FreeAllMemory(void);
extern PACKAGE bool __fastcall CheckCanInstallMemoryManager(void);
extern PACKAGE void __fastcall InitializeMemoryManager(void);
extern PACKAGE void __fastcall InstallMemoryManager(void);
extern PACKAGE void __fastcall FinalizeMemoryManager(void);
extern PACKAGE void __fastcall RunInitializationCode(void);

}	/* namespace Fastmm4 */
using namespace Fastmm4;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FastMM4

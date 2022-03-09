#include "LBSCommon.h"

LBSCommon::PLBSReadFileStream __fastcall LBSCommon::TLBSReadFileStream::Create(Pointer AClass, Boolean Alloc, String FPath)
{
    PLBSReadFileStream Self = (PLBSReadFileStream)AClass;
    if (Alloc)
    {
        CLASSCREATE_STUD;
        Self = (PLBSReadFileStream)System::ClassCreate(Self, Alloc);
    }

    PChar CStr = System::LStrToPChar(FPath);
    Self->FHandle = CreateFileA(CStr, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (Alloc) System::AfterConstruction(Self);
    return Self;
}

void __fastcall LBSCommon::TLBSReadFileStream::Destroy(PLBSReadFileStream Self, Boolean Alloc)
{
    System::BeforeDestruction(Self, Alloc);

    CloseHandle(Self->FHandle);
    System::TObject::Destroy(Self, Alloc & 0xFC);

    if (Alloc) System::ClassDestroy(Self);
}

Integer __fastcall LBSCommon::TLBSReadFileStream::Read(PLBSReadFileStream Self, PChar Buffer, Integer Size)
{
    DWORD RSize = Size;
    ReadFile(Self->FHandle, Buffer, Size, &RSize, 0);
    return RSize;
}

Integer __fastcall LBSCommon::TLBSReadFileStream::Seek(PLBSReadFileStream Self, Integer Offset, Word Method)
{
    return SetFilePointer(Self->FHandle, Offset, 0, Method);
}

Boolean __fastcall LBSCommon::TLBSReadFileStream::SetSize(PLBSReadFileStream Self, Integer Offset)
{
    Self->Seek(Self, Offset, Classes::soBeginning);
    return SetEndOfFile(Self->FHandle);
}

Boolean __fastcall LBSCommon::TLBSReadFileStream::IsOpen(PLBSReadFileStream Self)
{
    return Self->FHandle != (HANDLE)-1;
}

LBSCommon::PLBSReadFileStreamEx __fastcall LBSCommon::TLBSReadFileStreamEx::Create(Pointer AClass, Boolean Alloc, String FPath)
{
    PLBSReadFileStreamEx Self = (PLBSReadFileStreamEx)AClass;
    if (Alloc)
    {
        CLASSCREATE_STUD;
        Self = (PLBSReadFileStreamEx)System::ClassCreate(Self, Alloc);
    }

    LBSCommon::TLBSReadFileStream::Create(Self, 0, FPath);
    if (LBSCommon::TLBSReadFileStream::IsOpen(Self))
    {
        Self->FMapHandler = CreateFileMappingA(Self->FHandle, 0, PAGE_READONLY, 0, 0, 0);
        Self->FMapAddress = MapViewOfFile(Self->FMapHandler, FILE_MAP_READ, 0, 0, 0);
    }

    if (Alloc) System::AfterConstruction(Self);
    return Self;
}

void __fastcall LBSCommon::TLBSReadFileStreamEx::Destroy(PLBSReadFileStreamEx Self, Boolean Alloc)
{
    System::BeforeDestruction(Self, Alloc);

    UnmapViewOfFile(Self->FMapAddress);
    CloseHandle(Self->FMapHandler);
    LBSCommon::TLBSReadFileStream::Destroy(Self, Alloc & 0xFC);

    if (Alloc) System::ClassDestroy(Self);
}

LBSCommon::PLBSMultiFileSimpleStream __fastcall LBSCommon::TLBSMultiFileSimpleStream::Create(Pointer AClass, Boolean Alloc, String FPath)
{
    PLBSMultiFileSimpleStream Self = (PLBSMultiFileSimpleStream)AClass;
    if (Alloc)
    {
        CLASSCREATE_STUD;
        Self = (PLBSMultiFileSimpleStream)System::ClassCreate(Self, Alloc);
    }

    LBSCommon::TLBSReadFileStreamEx::Create(Self, 0, FPath);
    if (!LBSCommon::TLBSReadFileStream::IsOpen(Self))
    {
        String Message = nullptr;
        //System::LStrCatN(&Message, 3, 0, "\r\r", FPath, "MultiFileStream ValidFile Error!!\r\r"); TODO: Implement variadic call
        System::Assert(Message, __FILE__, __LINE__);
        System::LStrClr(&Message);
    }
    Self->Seek(Self, 0, Classes::soBeginning);
    Self->Read(Self, (PChar)GBuffer, 21);

    // Get memory for header and entries
    Integer Count = ((TLBSNTDataFile*)GBuffer)->FHeader.FCount;
    Self->FMemData = (TLBSNTDataFile*)System::GetMemory(sizeof(TLBSNTDataFile::TLBSNTDataEntry) * Count + sizeof(TLBSNTDataFile::TLBSNTDataHeader));

    // Copy Header
    memcpy(Self->FMemData, (PChar)GBuffer, sizeof(TLBSNTDataFile));
    // Read entries
    Self->Read(Self, (PChar)Self->FMemData->FEntries, sizeof(TLBSNTDataFile::TLBSNTDataEntry) * Self->FMemData->FHeader.FCount);
    Self->UnkPtr = 0;
    Self->Unknown3 = (Pointer)-1;

    if (Alloc) System::AfterConstruction(Self);
    return Self;
}

Initialization _LBSCommon {
    {0x0046A140, LBSCommon::TLBSReadFileStream::Create, true},
    {0x0046A194, LBSCommon::TLBSReadFileStream::Destroy, true},
    {0x0046A1C4, LBSCommon::TLBSReadFileStream::Read, true},
    {0x0046A1E4, LBSCommon::TLBSReadFileStream::Seek, true},
    {0x0046A1F8, LBSCommon::TLBSReadFileStream::SetSize, true},
    {0x0046A214, LBSCommon::TLBSReadFileStream::IsOpen, true},

    {0x0046A220, LBSCommon::TLBSReadFileStreamEx::Create, true},
    {0x0046A290, LBSCommon::TLBSReadFileStreamEx::Destroy, true},

    {0x0046A2C8, LBSCommon::TLBSMultiFileSimpleStream::Create, true},
};
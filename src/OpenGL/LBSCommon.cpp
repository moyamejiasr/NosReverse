#include "LBSCommon.h"

Boolean __fastcall LBSCommon::IndexFromId(TLBSNTDataFile* Header, Integer FId, Integer* Index)
{
    if ( Header->FHeader.FIdsOrdered && FId < Header->FHeader.FCount )
    {
        *Index = FId;
        return true;
    }
    else
    {
        Integer AltIndex, i = 0;
        Integer FCount = Header->FHeader.FCount - 1;
        if ( FCount >= 0 )
        {
            do
            {
                AltIndex = (FCount + i) / 2;
                Integer TId = Header->FEntries[AltIndex].FId;
                if ( FId <= TId )
                {
                    FCount = AltIndex - 1;
                    if ( FId == TId )
                    {
                        *Index = AltIndex;
                        return true;
                    }
                }
                else
                {
                    i = AltIndex + 1;
                }
            }
            while ( FCount >= i );
        }
    }
    return false;
}

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
        CERR("Error, cannot load file " << FPath);
    }
    Self->Seek(Self, 0, Classes::soBeginning);
    Self->Read(Self, (PChar)GBuffer, 21);

    // Get memory for header and entries
    Integer Count = ((TLBSNTDataFile*)GBuffer)->FHeader.FCount;
    Self->FDataFile = (TLBSNTDataFile*)System::GetMemory(sizeof(TLBSNTDataFile::Entry) * Count + sizeof(TLBSNTDataFile::Header));

    // Copy Header
    memcpy(Self->FDataFile, (PChar)GBuffer, sizeof(TLBSNTDataFile));
    // Read entries
    Self->Read(Self, (PChar)Self->FDataFile->FEntries, sizeof(TLBSNTDataFile::Entry) * Self->FDataFile->FHeader.FCount);
    Self->UnkPtr = 0;
    Self->Unknown3 = (Pointer)-1;

    if (Alloc) System::AfterConstruction(Self);
    return Self;
}

void __fastcall LBSCommon::TLBSMultiFileSimpleStream::Destroy(PLBSMultiFileSimpleStream Self, Boolean Alloc)
{
    System::BeforeDestruction(Self, Alloc);

    if (Self->UnkPtr) System::FreeMemory(Self->UnkPtr);
    System::FreeMemory(Self->FDataFile);
    LBSCommon::TLBSReadFileStreamEx::Destroy(Self, Alloc & 0xFC);

    if (Alloc) System::ClassDestroy(Self);
}

void __fastcall LBSCommon::TLBSMultiFileSimpleStream::GetIndexEntry(PLBSMultiFileSimpleStream Self, Integer Index, TLBSNTDataFile::Entry *Result)
{
    *Result = Self->FDataFile->FEntries[Index];
}

void __fastcall LBSCommon::TLBSMultiFileSimpleStream::ReadIndexHeader(PLBSMultiFileSimpleStream Self, Integer Index, PChar Buffer, Integer* Result)
{
    if ( Index < Self->FDataFile->FHeader.FCount )
    {
        // Move to start of data & read up to FCState
        SetFilePointer(Self->FHandle, Self->FDataFile->FEntries[Index].FOffset, 0, 0);
        ReadFile(Self->FHandle, Buffer, sizeof(TLBSNTDataItem::Header), (LPDWORD)Result, 0);
        // Return the position past read
        *Result = Self->FDataFile->FEntries[Index].FOffset + sizeof(TLBSNTDataItem::Header);
    }
}

void __fastcall LBSCommon::TLBSMultiFileSimpleStream::ReadIdHeader(PLBSMultiFileSimpleStream Self, Integer FId, PChar Buffer, Integer* Result)
{
    Integer Index;
    if ( LBSCommon::IndexFromId(Self->FDataFile, FId, &Index) )
    {
        // Move to start of data & read up to FCState
        SetFilePointer(Self->FHandle, Self->FDataFile->FEntries[Index].FOffset, 0, 0);
        ReadFile(Self->FHandle, Buffer, sizeof(TLBSNTDataItem::Header), (LPDWORD)Result, 0);
        // Return the position past read
        *Result = Self->FDataFile->FEntries[Index].FOffset + sizeof(TLBSNTDataItem::Header);
    }
}

Boolean __fastcall LBSCommon::TLBSMultiFileSimpleStream::ReadIndexItem(PLBSMultiFileSimpleStream Self, Integer Id, Pointer* Buffer, Boolean Realloc)
{
    Integer Index;
    if (!LBSCommon::IndexFromId(Self->FDataFile, Id, &Index))
        return false;

    SetFilePointer(Self->FHandle, Self->FDataFile->FEntries[Index].FOffset, 0, 0);
    ReadFile(Self->FHandle, LBSCommon::GHeader, sizeof(TLBSNTDataItem::Header), (LPDWORD)LBSCommon::GNumRead, 0);

    if (Realloc) *Buffer = System::ReallocMemory(*Buffer, LBSCommon::GHeader->FSize);
    ReadFile(Self->FHandle, *Buffer, LBSCommon::GHeader->FSize, (LPDWORD)LBSCommon::GNumRead, 0);
    return true;
}

Initialization _LBSCommon {
    {0x0046965C, LBSCommon::IndexFromId, true},

    {0x0046A140, LBSCommon::TLBSReadFileStream::Create, true},
    {0x0046A194, LBSCommon::TLBSReadFileStream::Destroy, true},
    {0x0046A1C4, LBSCommon::TLBSReadFileStream::Read, true},
    {0x0046A1E4, LBSCommon::TLBSReadFileStream::Seek, true},
    {0x0046A1F8, LBSCommon::TLBSReadFileStream::SetSize, true},
    {0x0046A214, LBSCommon::TLBSReadFileStream::IsOpen, true},

    {0x0046A220, LBSCommon::TLBSReadFileStreamEx::Create, true},
    {0x0046A290, LBSCommon::TLBSReadFileStreamEx::Destroy, true},

    {0x0046A2C8, LBSCommon::TLBSMultiFileSimpleStream::Create, true},
    {0x0046A458, LBSCommon::TLBSMultiFileSimpleStream::Destroy, true},
    {0x0046A498, LBSCommon::TLBSMultiFileSimpleStream::GetIndexEntry, true},
    {0x0046A4B0, LBSCommon::TLBSMultiFileSimpleStream::ReadIndexHeader, true},
    {0x0046A510, LBSCommon::TLBSMultiFileSimpleStream::ReadIdHeader, true},
    {0x0046A57C, LBSCommon::TLBSMultiFileSimpleStream::ReadIndexItem, true},
};
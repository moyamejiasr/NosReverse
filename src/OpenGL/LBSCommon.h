#pragma once
#include "../Common.h"
#include "../Delphi/System.h"
#include "../Delphi/Classes.h"

namespace LBSCommon 
{
    typedef struct TLBSReadFileStream *PLBSReadFileStream;
    typedef struct TLBSReadFileStreamEx *PLBSReadFileStreamEx;
    typedef struct TLBSMultiFileSimpleStream *PLBSMultiFileSimpleStream;

    struct __packed TLBSNTDataItem
    {
        Integer FDate;
        Integer FSize;
        Integer FCSize;
        Boolean FCState;
        PChar FData;
    };

    struct __packed TLBSNTDataFile
    {
        struct __packed TLBSNTDataHeader
        {
            Char FSign[12];
            Integer dword;
            Integer FCount;
            Byte FIdsOrdered;
        } FHeader;
        struct TLBSNTDataEntry
        {
            Integer FId;
            TLBSNTDataItem *FOffset;
        } FEntries[];
    };

    PChar *GBuffer = Cast(0x005EDE24);

    struct TLBSReadFileStream: Classes::TStream
    {
        static VMT_ClassDefinition* Class;

        HANDLE FHandle;

        static PLBSReadFileStream __fastcall Create(Pointer, Boolean, String);
        static void __fastcall Destroy(PLBSReadFileStream, Boolean);
        static Integer __fastcall Read(PLBSReadFileStream, PChar, Integer);
        static Integer __fastcall Seek(PLBSReadFileStream, Integer, Word);
        static Boolean __fastcall SetSize(PLBSReadFileStream, Integer);
        static Boolean __fastcall IsOpen(PLBSReadFileStream);
    };

    struct TLBSReadFileStreamEx: TLBSReadFileStream
    {
        static VMT_ClassDefinition* Class;

        HANDLE FMapHandler;
        Pointer FMapAddress;

        static PLBSReadFileStreamEx __fastcall Create(Pointer, Boolean, String);
        static void __fastcall Destroy(PLBSReadFileStreamEx, Boolean);
    };

    struct TLBSMultiFileSimpleStream: TLBSReadFileStreamEx
    {
        static VMT_ClassDefinition* Class;

        TLBSNTDataFile* FMemData;
        Pointer UnkPtr;
        Pointer Unknown3;

        static PLBSMultiFileSimpleStream __fastcall Create(Pointer, Boolean, String);
        static void __fastcall Destroy(PLBSMultiFileSimpleStream, Boolean);
    };
}
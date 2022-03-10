#pragma once
#include "../Common.h"
#include "../Delphi/System.h"
#include "../Delphi/Classes.h"

namespace LBSCommon 
{
    typedef struct TLBSReadFileStream *PLBSReadFileStream;
    typedef struct TLBSReadFileStreamEx *PLBSReadFileStreamEx;
    typedef struct TLBSMultiFileSimpleStream *PLBSMultiFileSimpleStream;

    struct __packed TLBSNTDataFile
    {
        struct __packed Header
        {
            Char FSign[12];
            Integer dword;
            Integer FCount;
            Byte FIdsOrdered;
        } FHeader;
        struct Entry
        {
            Integer FId;
            Integer FOffset;
        } FEntries[];
    };

    struct __packed TLBSNTDataItem
    {
        struct __packed Header
        {
            Integer FDate;
            Integer FSize;
            Integer FCSize;
            Boolean FCState;
        } FHeader;
        PChar FData;
    };

    PChar *GBuffer = Cast(0x005EDE24);

    Boolean __fastcall IndexFromId(TLBSNTDataFile*, Integer, Integer*);

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

        TLBSNTDataFile* FDataFile;
        Pointer UnkPtr;
        Pointer Unknown3;

        static PLBSMultiFileSimpleStream __fastcall Create(Pointer, Boolean, String);
        static void __fastcall Destroy(PLBSMultiFileSimpleStream, Boolean);
        static void __fastcall GetIndexEntry(PLBSMultiFileSimpleStream, Integer, TLBSNTDataFile::Entry*);
        static void __fastcall ReadIndexHeader(PLBSMultiFileSimpleStream, Integer, PChar, Integer*);
        static void __fastcall ReadIdHeader(PLBSMultiFileSimpleStream, Integer, PChar, Integer*);
    };
}
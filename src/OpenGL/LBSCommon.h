#pragma once
#include "../Common.h"
#include "../Delphi/System.h"
#include "../Delphi/Classes.h"

namespace LBSCommon 
{
    typedef struct TLBSReadFileStream *PLBSReadFileStream;

    struct TLBSReadFileStream: Classes::TStream
    {
        static VMT_ClassDefinition* Class;

        HANDLE FHandle;

        static PLBSReadFileStream __fastcall Create(Pointer, Boolean, String);
    };
}
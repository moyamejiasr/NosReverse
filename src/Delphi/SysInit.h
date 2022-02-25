#pragma once
#include "../Common.h"

namespace SysInit
{
    typedef struct TITableType 
    {
        DWORD Size;
        DWORD NextPtr;
        DWORD Functions[338];
    } *PITableType;

	extern PITableType InitTable;

	extern void(__fastcall* InitExe)(PITableType);
};
#pragma once
#include "../Common.h"
#include "System.h"

namespace Classes
{
    typedef struct TList: System::TObject
    {
        static void __fastcall Delete(TList*, Integer);
        static Pointer __fastcall Get(TList*, Integer);
        static Integer __fastcall IndexOf(TList*, Pointer);

    } *PList;
}
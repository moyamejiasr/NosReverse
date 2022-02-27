#pragma once
#include "../Common.h"
#include "System.h"

namespace Classes
{
    typedef struct TList *PList;

    struct TList: System::TObject
    {
        Pointer FList;
        Integer FCount;
        Integer FCapacity;

        virtual void __fastcall Grow(PList) = 0;
        virtual void __fastcall Notify(PList, Pointer, Integer) = 0;
        virtual void __fastcall Clear(PList) = 0;
        virtual void __fastcall Error(PList, PString, Integer) = 0;

        static void __fastcall Delete(PList, Integer);
        static Pointer __fastcall Get(PList, Integer);
        static Integer __fastcall IndexOf(PList, Pointer);
        static void __fastcall Move(PList, Integer, Integer);
    };
}
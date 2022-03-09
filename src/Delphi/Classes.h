#pragma once
#include "../Common.h"
#include "System.h"

namespace Classes
{
    typedef struct TList *PList;
    typedef struct TStream *PStream;

    struct TList: System::TObject
    {
        Pointer FList;
        Integer FCount;
        Integer FCapacity;

        virtual void __fastcall Grow() = 0;
        virtual void __fastcall Notify(Pointer, Integer) = 0;
        virtual void __fastcall Clear() = 0;
        virtual void __fastcall Error(PString, Integer) = 0;

        static Integer __fastcall Add(PList, Pointer);
        static void __fastcall _Clear(PList);
        static void __fastcall Delete(PList, Integer);
        static Pointer __fastcall Get(PList, Integer);
        static Integer __fastcall IndexOf(PList, Pointer);
        static void __fastcall Move(PList, Integer, Integer);
    };

    enum TSeekOrigin : unsigned char
    {
        soBeginning = 0x0,
        soCurrent = 0x1,
        soEnd = 0x2,
    };

    struct TStream: System::TObject
    {
        virtual Int64 __fastcall GetSize(PStream);
        virtual void __fastcall SetSize(PStream, Integer);
        virtual void __fastcall SetSize64(PStream, Int64);
        virtual Integer __fastcall Read(PStream, Char*, Integer);
        virtual Integer __fastcall Write(PStream, Char*, Integer);
        virtual Integer __fastcall Seek(PStream, Integer, Word);
        virtual Int64 __fastcall Seek64(PStream, Int64, TSeekOrigin);
    };
}
#pragma once
#include "../Common.h"
#include "System.h"

namespace Classes
{
    typedef struct TList *PList;
    typedef struct TPersistent *PPersistent;
    typedef struct TInterfacedPersistent *PInterfacedPersistent;
    typedef struct TStream *PStream;

    enum TSeekOrigin : unsigned char
    {
        soBeginning = 0x0,
        soCurrent = 0x1,
        soEnd = 0x2,
    };

    struct TList: System::TObject
    {
        static VMT_ClassDefinition* Class;

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
    ASSERT_SIZE(TList, 0x10);

    struct TPersistent: System::TObject
    {
        static VMT_ClassDefinition* Class;

        virtual void __fastcall AssignTo(PPersistent Dest);
        virtual void __fastcall DefineProperties(Pointer Filer);
        virtual void __fastcall Assign(PPersistent Source);
    };
    ASSERT_SIZE(TPersistent, 0x04);

    struct TInterfacedPersistent: TPersistent
    {
        static VMT_ClassDefinition* Class;

        virtual Pointer __fastcall QueryInterface(Pointer IID, Pointer Obj);
    };

    struct TStream: System::TObject
    {
        static VMT_ClassDefinition* Class;

        virtual Int64 __fastcall GetSize(PStream);
        virtual void __fastcall SetSize(PStream, Integer);
        virtual void __fastcall SetSize64(PStream, Int64);
        virtual Integer __fastcall Read(PStream, Char*, Integer);
        virtual Integer __fastcall Write(PStream, Char*, Integer);
        virtual Integer __fastcall Seek(PStream, Integer, Word);
        virtual Int64 __fastcall Seek64(PStream, Int64, TSeekOrigin);
    };
    ASSERT_SIZE(TStream, 0x04);
}
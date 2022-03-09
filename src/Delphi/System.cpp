#include "System.h"

Integer __fastcall System::ParamCount()
{
    return 0;
}

void __fastcall System::ParamStr(Integer, PString)
{

}

void __fastcall System::LStrCopy(String, Integer, Integer, PString)
{

}

Integer __fastcall System::LStrCmp(String, String)
{
    return 0;
}

PChar __fastcall System::LStrToPChar(PChar)
{
    return nullptr;
}

void __fastcall System::TObject::Destroy(PObject Self, Boolean Alloc)
{

}

void __fastcall System::TObject::Free(PObject Self)
{

}

System::PObject __fastcall System::ClassCreate(Pointer AClass, Boolean Alloc)
{
    return nullptr;
}

void __fastcall System::ClassDestroy(Pointer AClass)
{

}

Pointer __fastcall System::AfterConstruction(PObject Self)
{
    return nullptr;
}

void __fastcall System::BeforeDestruction(PObject Self, Boolean Alloc)
{

}

Initialization _System {
    {0x004031E4, System::ParamCount},
    {0x0040324C, System::ParamStr},
    {0x00405108, System::LStrCopy},
    {0x00404FF4, System::LStrCmp},
    {0x004050A8, System::LStrToPChar},

    {0x00403E00, System::TObject::Destroy},
    {0x00403E10, System::TObject::Free},

    {0x00404148, System::ClassCreate},
    {0x00404198, System::ClassDestroy},
    {0x004041A0, System::AfterConstruction},
    {0x004041B0, System::BeforeDestruction},
};
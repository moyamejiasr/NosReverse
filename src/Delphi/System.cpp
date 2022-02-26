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

Pointer __fastcall System::ClassCreate(Pointer AClass, Boolean Alloc)
{
    return nullptr;
}

void __fastcall System::AfterConstruction(Pointer)
{

}

Initialization _System {
    {0x004031E4, System::ParamCount},
    {0x0040324C, System::ParamStr},
    {0x00405108, System::LStrCopy},
    {0x00404FF4, System::LStrCmp},
    {0x00404148, System::ClassCreate},
    {0x00404148, System::AfterConstruction},
};
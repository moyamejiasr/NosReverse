#include "LBSCommon.h"

LBSCommon::PLBSReadFileStream __fastcall LBSCommon::TLBSReadFileStream::Create(Pointer AClass, Boolean Alloc, String FPath)
{
    PLBSReadFileStream Self = (PLBSReadFileStream)AClass;
    if (Alloc)
    {
        CLASSCREATE_STUD;
        Self = (PLBSReadFileStream)System::ClassCreate(Self, Alloc);
    }

    PChar CStr = System::LStrToPChar(FPath);
    Self->FHandle = CreateFileA(CStr, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (Alloc) System::AfterConstruction(Self);
    return Self;
}

Initialization _System {
    {0x0046A140, LBSCommon::TLBSReadFileStream::Create, true},
};
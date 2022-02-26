#include "SysInit.h"

SysInit::PITableType SysInit::InitTable = Cast(0x005DB128);

void __fastcall SysInit::InitExe(PITableType)
{

}

Initialization _SysInit {
    {0x004072D8, SysInit::InitExe},
};
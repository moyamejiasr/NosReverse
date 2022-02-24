#include "SysInit.h"

SysInit::PITableType SysInit::InitTable = Cast(0x005DB128);

void(__fastcall* SysInit::InitExe)(SysInit::PITableType) = Cast(0x004072D8);
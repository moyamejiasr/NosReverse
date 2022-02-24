#include "System.h"

Integer(__fastcall* System::ParamCount)() = Cast(0x004031E4);
void(__fastcall* System::ParamStr)(Integer, PString) = Cast(0x0040324C);
void(__fastcall* System::LStrCopy)(String, Integer, Integer, PString) = Cast(0x00405108);
Integer(__fastcall* System::LStrCmp)(String, String) = Cast(0x00404FF4);
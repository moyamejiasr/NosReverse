#include "Forms.h"

void(__fastcall* Forms::TApplication::SetTitle)(TApplication*, String) = Cast(0x00457D68);
void(__fastcall* Forms::TApplication::Initialize)(TApplication*) = Cast(0x00458168);
void(__fastcall* Forms::TApplication::CreateForm)(TApplication*, Integer, PCustomForm) = Cast(0x00458180);
void(__fastcall* Forms::TApplication::Run)(TApplication*) = Cast(0x00458200);
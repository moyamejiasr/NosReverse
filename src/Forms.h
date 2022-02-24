#pragma once
#include "Common.h"
#include "System.h"

namespace Forms 
{
	typedef struct CustomForm {} *PCustomForm;
    
	typedef struct TApplication {
        static void(__fastcall* SetTitle)(TApplication*, String);
        static void(__fastcall* Initialize)(TApplication*);
        static void(__fastcall* CreateForm)(TApplication*, Integer, PCustomForm);
        static void(__fastcall* Run)(TApplication*);
	} *PApplication;
}
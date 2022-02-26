#include "Common.h"
#include "Delphi/SysInit.h"
#include "Delphi/System.h"
#include "Delphi/Forms.h"
#include "Nostale/NosTaleMainF.h"

constexpr auto NTGAME = MAKE_STRING("Nostale");
constexpr auto SECRET = MAKE_STRING("EntwellNostaleClient");

Forms::PApplication* Application = Cast(0x005EBDD8);
Forms::PCustomForm CustomForm = Cast(0x00771CC0);

void __fastcall EntryPoint() {
    COUT("Executed custom EntryPoint!");
    SysInit::InitExe(SysInit::InitTable);

    if (HANDLE GameMutex = CreateMutexA(NULL, -1, SECRET.Value))
    {
        if (!GetLastError() && System::ParamCount() >= 1)
        {
            String Arg = NULL, SubArg = NULL;
            System::ParamStr(1, &Arg);
            System::LStrCopy(Arg, 1, 20, &SubArg);

            if (!strcmp(SubArg, (String)SECRET.Value))
            {
                Forms::TApplication::Initialize(*Application);
                Forms::TApplication::SetTitle(*Application, (String)NTGAME.Value);
                Forms::TApplication::CreateForm(*Application, 
                    NosTaleMainF::TNosTaleMainF::Class->SelfPtr, CustomForm);
                Forms::TApplication::Run(*Application);

                if (GameMutex) CloseHandle(GameMutex);
            }
        }
    }
    ExitProcess(0);
}

Initialization _Main {
    {0x005DB678, EntryPoint, true},
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dReason, LPVOID)
{
    if (dReason == DLL_PROCESS_ATTACH)
    {
        AllocConsole();
        freopen("CON", "w", stdout);
        freopen("CON", "r", stdin);
        freopen("CON", "w", stderr);
        DisableThreadLibraryCalls(hModule);
        std::cout << "NT Detourer Lib v1" << std::endl;
    }
    return TRUE;
}
#include "Common.h"
#include "SysInit.h"
#include "System.h"
#include "Forms.h"

constexpr auto NTGAME = MAKE_STRING("Nostale");
constexpr auto SECRET = MAKE_STRING("EntwellNostaleClient");
struct TNosTaleMainF
{
    static VMT_ClassDefinition* Class;
};
VMT_ClassDefinition* TNosTaleMainF::Class = Cast(0x005DACF0);
Forms::PApplication* Application = Cast(0x005EBDD8);
Forms::PCustomForm CustomForm = Cast(0x00771CC0);

auto EntryPoint = Cast((PVOID)0x005DB678, [] {
    // Initialize Delphi
    SysInit::InitExe(SysInit::InitTable);

    GErrMessage("Weirdly.... it works.");

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
                Forms::TApplication::CreateForm(*Application, TNosTaleMainF::Class->SelfPtr, CustomForm);
                Forms::TApplication::Run(*Application);

                if (GameMutex) CloseHandle(GameMutex);
            }
        }
    }
    ExitProcess(0);
});

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dReason, LPVOID)
{
    if (dReason != DLL_PROCESS_ATTACH)
        return TRUE;
    DisableThreadLibraryCalls(hModule);
    return TRUE;
}
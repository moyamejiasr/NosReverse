#include "Common.h"

typedef struct TITableType {
	DWORD Size;
	DWORD NextPtr;
	DWORD Functions[338];
} *PITableType;
namespace SysInit
{
	PITableType InitTable = Cast(0x005DB128);
	void(__fastcall* InitExe)(PITableType) = Cast(0x004072D8);
};

typedef int Integer;
typedef int Pointer;
typedef char AnsiChar;
typedef AnsiChar* PAnsiChar;
typedef PAnsiChar String;
typedef String* PString;
struct VMT_ClassDefinition {
	Pointer SelfPtr;
	Pointer IntfTable, AutoTable, InitTable;
	Pointer TypeInfo;
	Pointer FieldTable, MethodTable, DynamicTable;
	Pointer ClassName;
	Integer InstanceSize;
	VMT_ClassDefinition* Parent;
	Pointer SafeCallException;
	Pointer AfterConstruction;
	Pointer BeforeDestruction;
	Pointer Dispatch, DefaultHandler;
	Pointer NewInstance, FreeInstance;
	Pointer Destroy;
};
namespace System
{
    Integer(__fastcall* ParamCount)() = Cast(0x004031E4);
    void(__fastcall* ParamStr)(Integer, PString) = Cast(0x0040324C);
    void(__fastcall* LStrCopy)(String, Integer, Integer, PString) = Cast(0x00405108);
    Integer(__fastcall* LStrCmp)(String, String) = Cast(0x00404FF4);
};

namespace Forms 
{
	typedef struct CustomForm {} *PCustomForm;
	typedef struct TApplication {
        static void(__fastcall* SetTitle)(TApplication*, String);
        static void(__fastcall* Initialize)(TApplication*);
        static void(__fastcall* CreateForm)(TApplication*, Integer, PCustomForm);
        static void(__fastcall* Run)(TApplication*);
	} *PApplication;
    void(__fastcall* TApplication::SetTitle)(TApplication*, String) = Cast(0x00457D68);
    void(__fastcall* TApplication::Initialize)(TApplication*) = Cast(0x00458168);
    void(__fastcall* TApplication::CreateForm)(TApplication*, Integer, PCustomForm) = Cast(0x00458180);
    void(__fastcall* TApplication::Run)(TApplication*) = Cast(0x00458200);
}

constexpr auto NTGAME = MAKE_STRING("Nostale");
constexpr auto SECRET = MAKE_STRING("EntwellNostaleClient");
struct TNosTaleMainF
{
    static VMT_ClassDefinition* Class;
};
VMT_ClassDefinition* TNosTaleMainF::Class = Cast(0x005DACF0);
Forms::PApplication* Application = Cast(0x005EBDD8);
Forms::PCustomForm CustomForm = Cast(0x00771CC0);

void EntryPoint() {
    // Initialize Delphi
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
                Forms::TApplication::CreateForm(*Application, TNosTaleMainF::Class->SelfPtr, CustomForm);
                Forms::TApplication::Run(*Application);

                if (GameMutex) CloseHandle(GameMutex);
            }
        }
    }
    ExitProcess(0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dReason, LPVOID)
{
    if (dReason != DLL_PROCESS_ATTACH)
        return TRUE;
    DisableThreadLibraryCalls(hModule);
    EntryPoint();
    return TRUE;
}
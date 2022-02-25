#undef UNICODE
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <tlhelp32.h> 

#define GErrMessage(X) MessageBox(0, X, "Unexpected error", MB_SYSTEMMODAL | MB_ICONERROR)
#define GNotMessage(X) MessageBox(0, X, "Process Launcher", MB_SYSTEMMODAL | MB_ICONINFORMATION)

constexpr auto NTDllFName = "NTLibrary.dll";
constexpr auto NTGameWDir = "C:\\Users\\rmoya\\Documents\\Global";
constexpr auto NTGamePath = "C:\\Users\\rmoya\\Documents\\Global\\Nostale.dat";
char NTGameArg[] = "C:\\Users\\rmoya\\Documents\\Global\\Nostale.dat EntwellNostaleClientLoadFromIni";

void TryClosePrevious() 
{
    PROCESSENTRY32 entry = {};
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (Process32First(snapshot, &entry))
    {
        while (Process32Next(snapshot, &entry))
        {
            if (strcmp(entry.szExeFile, "Nostale.dat") == 0)
            {
                HANDLE targetProcess = OpenProcess(PROCESS_TERMINATE, FALSE, entry.th32ProcessID);
                if (!targetProcess)
                {
                    GErrMessage("Error, cannot open process.\nTry as administrator.");
                    ExitProcess(1);
                }
                TerminateProcess(targetProcess, 1);
                CloseHandle(targetProcess);
            }
        }
    }
    CloseHandle(snapshot);
}

void InjectDll(HANDLE ProcessH, const char* LocalPath)
{
    // Allocate space in the process for the dll 
    LPVOID RemotePath = (LPVOID)VirtualAllocEx(ProcessH, NULL, strlen(LocalPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!RemotePath)
    {
        GErrMessage("Error, unexpected problems with VirtualAllocEx.\nSee exit code for more.");
        ExitProcess(GetLastError());
    }

    // Write the string name of the dll in the memory allocated 
    if (!WriteProcessMemory(ProcessH, (LPVOID)RemotePath, LocalPath, strlen(LocalPath), NULL))
    {
        GErrMessage("Error, unexpected problems with WriteProcessMemory.\nSee exit code for more.");
        ExitProcess(GetLastError());
    }

    // Load the dll
    FARPROC Procedure = GetProcAddress(GetModuleHandle("kernel32"), "LoadLibraryA");
    if (!Procedure)
    {
        GErrMessage("Error, unexpected problems with GetProcAddress.\nSee exit code for more.");
        ExitProcess(GetLastError());
    }

    HANDLE hThread = CreateRemoteThread(ProcessH, NULL, NULL, (LPTHREAD_START_ROUTINE)Procedure, (LPVOID)RemotePath, NULL, NULL);
    if (!hThread)
    {
        GErrMessage("Error, unexpected problems with CreateRemoteThread.\nSee exit code for more.");
        ExitProcess(GetLastError());
    }

    if (WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)
    {
        GErrMessage("Error, unexpected problems with WaitForSingleObject.\nSee exit code for more.");
        ExitProcess(GetLastError());
    }

    DWORD ExitCode;
    if (!GetExitCodeThread(hThread, &ExitCode))
    {
        GErrMessage("Error, unexpected problems with GetExitCodeThread.\nSee exit code for more.");
        ExitProcess(GetLastError());
    }

    if (!ExitCode)
    {
        GErrMessage("Error, unexpected problems with LoadLibraryA.\nCannot guess further.");
        ExitProcess(-1);
    }

    // Free the memory that is not being using anymore. 
    VirtualFreeEx(ProcessH, RemotePath, 0, MEM_RELEASE);
    CloseHandle(hThread);
}

int APIENTRY WinMain(HINSTANCE, HINSTANCE, PSTR, int)
{
    // Try closing executable if running
    TryClosePrevious();

    // Create the process
    STARTUPINFOA StartupInfo = { sizeof(StartupInfo) };
    PROCESS_INFORMATION ProcessInfo = {};
    if (!CreateProcessA(NTGamePath, NTGameArg, NULL, NULL, TRUE, // FALSE
        CREATE_SUSPENDED | DETACHED_PROCESS, NULL, NTGameWDir, &StartupInfo, &ProcessInfo))
    {
        GErrMessage("Error, the new process cannot be created.");
        ExitProcess(2);
    }

    // Get the Dll full path
    char fullFilename[MAX_PATH];
    if (!GetFullPathName(NTDllFName, MAX_PATH, fullFilename, nullptr))
    {
        GErrMessage("Error, dynamic library is not present.");
        ExitProcess(3);
    }

    // Inject the dll
    InjectDll(ProcessInfo.hProcess, fullFilename);

    // Terminate suspended thread
    //TerminateThread(ProcessInfo.hThread, 0);
    if (ResumeThread(ProcessInfo.hThread) == (DWORD) -1)
    {
        GErrMessage("Error, unexpected problems with ResumeThread.\nSee exit code for more.");
        ExitProcess(GetLastError());
    }

    // Close all handles
    CloseHandle(ProcessInfo.hThread);
    CloseHandle(ProcessInfo.hProcess);

    return 0;
}
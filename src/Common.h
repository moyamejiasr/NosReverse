#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <initializer_list>

// String macros
#define S(X) #X
#define STR(X) (std::stringstream() << X).str()

// IO macros
#define HEX(X) std::hex << X << std::dec
#define COUT(X) std::cout << "[*] " << X << std::endl
#define CERR(X) std::cout << "[!] " << X << std::endl
#define CGET(X) std::cin >> X
#define CINT std::getchar()

// Bugfix stack issue related to ClassCreate
// Declaring this creates an extra stack pos
// that will be used by the fn to store data
#define CLASSCREATE_STUD volatile int _{}

// Workaround for c++ config
#ifdef _MSVC
#define __naked
#define __asm__
#else
#define __naked __attribute__((naked))
#endif

// Windows MessageBox
#define GErrMessage(X) MessageBoxA(0, X, "Unexpected error", MB_SYSTEMMODAL | MB_ICONERROR)
#define GNotMessage(X) MessageBoxA(0, X, "Process Launcher", MB_SYSTEMMODAL | MB_ICONINFORMATION)

// Delphi String
template <std::size_t N>
struct DString {
    unsigned Reference, Size;
    char Value[N];
};
#define MAKE_STRING(X) DString<sizeof(X)>{ 0x0FFFFFFFF, sizeof(X) - 1, X}

// Cast Wrapper
template <typename T>
class CastWrapper
{
    const T& mX;
    constexpr CastWrapper(const T& x) : mX(x) {}
public:
    template <typename R> constexpr friend CastWrapper<R> Cast(const R& x);
    template <typename U> constexpr operator U() { return reinterpret_cast<U>(mX); }
};
template <typename R>
constexpr CastWrapper<R> Cast(const R& x)
{
    return CastWrapper<R>(x);
}

// Router API
struct Route
{
    DWORD Address; PVOID Function;
    BOOL Detour;
};
struct Initialization
{
    Initialization(std::initializer_list<Route> l) {
        DWORD OldProtect;
        uint8_t Instruction[5] = { 0xE9, 0x0, 0x0, 0x0, 0x0 }; // JMP
        for (auto& route : std::vector<Route>(l))
        {
            if (!route.Detour)
            {
                DWORD tmp = route.Address;
                route.Address = (DWORD)route.Function;
                route.Function = (PVOID)tmp;
            }

            VirtualProtect((LPVOID)route.Address, 5, PAGE_EXECUTE_READWRITE, &OldProtect);
            // Inject code after unprotected
            const uint32_t RelAddr = (DWORD)route.Function - (route.Address + sizeof(Instruction));
            memcpy(Instruction + 1, &RelAddr, 4);
            memcpy((PVOID)route.Address, Instruction, sizeof(Instruction));
        }
    }
};
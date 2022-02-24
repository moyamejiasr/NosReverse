#pragma once
#undef UNICODE
#define WIN32_LEAN_AND_MEAN 
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

#define GErrMessage(X) MessageBoxA(0, X, "Unexpected error", MB_SYSTEMMODAL | MB_ICONERROR)
#define GNotMessage(X) MessageBoxA(0, X, "Process Launcher", MB_SYSTEMMODAL | MB_ICONINFORMATION)

template <typename T>
class CastWrapper
{
    const T& mX;
    CastWrapper(const T& x) : mX(x) {}
public:
    template <typename R> friend CastWrapper<R> Cast(const R& x);
    template <typename U> operator U() { return reinterpret_cast<U>(mX); }
};

template <typename R>
CastWrapper<R> Cast(const R& x)
{
    return CastWrapper<R>(x);
}

template <typename Function>
Function Cast(PVOID address, Function lambda)
{
    DWORD oldProtect;
	BOOL success = VirtualProtect(address, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

    //32 bit relative jump opcode is E9, takes 1 32 bit operand for jump offset
	uint8_t jmpInstruction[5] = { 0xE9, 0x0, 0x0, 0x0, 0x0 };
    //to fill out the last 4 bytes of jmpInstruction, we need the offset between 
	//the payload function and the instruction immediately AFTER the jmp instruction
	const uint32_t relAddr = (DWORD)(PVOID)lambda - ((uint32_t)address + sizeof(jmpInstruction));
	memcpy(jmpInstruction + 1, &relAddr, 4);
	memcpy(address, jmpInstruction, sizeof(jmpInstruction));

    return lambda;
}

template <std::size_t N>
struct DString {
    unsigned Reference, Size;
    char Value[N];
};
#define MAKE_STRING(X) DString<sizeof(X)>{ 0x0FFFFFFFF, sizeof(X) - 1, X}
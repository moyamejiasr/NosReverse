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

template <std::size_t N>
struct DString {
    unsigned Reference, Size;
    char Value[N];
};
#define MAKE_STRING(X) DString<sizeof(X)>{ 0x0FFFFFFFF, sizeof(X) - 1, X}
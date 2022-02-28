#include "LBSVector.h"

Single __fastcall LBSVector::DegToRad(Single Degrees)
{
    return Degrees * cPIdiv180;
}

Single __fastcall LBSVector::RadToDeg(Single Radians)
{
    return Radians * c180divPI;
}

void __fastcall LBSVector::SinCos(Single* Sin, Single* Cos, Single Theta)
{
    *Cos = cos(Theta);
    *Sin = sin(Theta);
}

Single __fastcall LBSVector::Tan(Single X)
{
    return tan(X);
}

Single __fastcall LBSVector::ArcCos(Single X)
{
    return ArcTan2(sqrt(1.0 - X * X), X);
}

Single __fastcall LBSVector::ArcTan2(Single Y, Single X)
{
    return atan2(Y, X);
}

Single __fastcall LBSVector::NormalizeAngle(Single angle)
{
    Single Result = angle - Int(angle * cInv2PI) * c2PI;
    if (Result > c2PI)
        return Result - c2PI;
    else if (Result < -c2PI)
        return Result + c2PI;

    return Result;
}

Integer __fastcall LBSVector::Trunc(Single X)
{
    return X;
}

Extended __fastcall LBSVector::Int(Extended X)
{
    return (DWORD)X;
}

Integer __fastcall LBSVector::Round(Single X)
{
    return X;
}

Single __fastcall LBSVector::FP16To32(Word X)
{
    DWORD Result{};
    if (X)
    {
        // Sign
        Result |= ((X & 0x8000) >> 15 << 31);
        // Exponent
        Result |= ((((X & 0x7800) >> 11) - 7 + 127) << 23);
        // Fraction
        Result |= ((X & 0x7FF) << 12);
    }

    return *(Single*)&Result;
}

LBSVector::TLBSColor __fastcall LBSVector::ColorMake(Byte R, Byte G, Byte B, Byte A)
{
    return {B, G, R, A};
}

LBSVector::TVector2s __fastcall LBSVector::VectorMake2s(Word X, Word Y)
{
    return {X, Y};
}

LBSVector::TVector2s __fastcall LBSVector::VectorAdd2s(TVector2s Pos, Word X, Word Y)
{
    TVector2s Result = Pos;
    Result.X += X;
    Result.Y += Y;
    return Result;
}

Initialization _LBSVector {
    {0x004597EC, LBSVector::DegToRad, true},
    {0x00459808, LBSVector::RadToDeg, true},
    {0x00459824, LBSVector::SinCos, true},
    {0x00459834, LBSVector::Tan, true},
    {0x00459844, LBSVector::ArcCos, true},
    {0x00459878, LBSVector::ArcTan2, true},
    {0x00459888, LBSVector::NormalizeAngle, true},
    {0x00459908, LBSVector::Trunc, true},
    {0x00459928, LBSVector::Int, true},
    {0x00459948, LBSVector::Round, true},
    {0x0045995C, LBSVector::FP16To32, true},
    
    {0x004599A8, LBSVector::ColorMake, true},
    {0x004599C4, LBSVector::VectorMake2s, true},
    {0x004599D4, LBSVector::VectorAdd2s, true},
};
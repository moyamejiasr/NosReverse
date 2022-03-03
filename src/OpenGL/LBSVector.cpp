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

LBSVector::TVector2s __fastcall LBSVector::VectorMake2s(Smallint X, Smallint Y)
{
    return {X, Y};
}

LBSVector::TVector2s __fastcall LBSVector::VectorAdd2s(TVector2s Pos, Smallint X, Smallint Y)
{
    TVector2s Result = Pos; Result.X += X; Result.Y += Y;
    return Result;
}

Boolean __fastcall LBSVector::PointInRect(TVector2s Point, TLBSRect Rect)
{
    TVector2s *Lt = &Rect.LeftTop, *Rb = &Rect.RightBottom;
    return (Lt->X <= Point.X && Point.X <= Rb->X)
        && (Lt->Y <= Point.Y && Point.Y <= Rb->Y);
}

Boolean __fastcall LBSVector::PointInRect2(Smallint PtX, Smallint PtY, 
    Smallint Left, Smallint Bottom, Smallint Right, Smallint Top)
{
    return Left <= PtX && PtX <= Right && PtY >= Bottom && PtY <= Top;
}

Boolean __fastcall LBSVector::Vec2InVec4(TVector4s Square, TVector2s Point)
{
    return (Square.X <= Point.X && Point.X < Square.Z)
        && (Square.Y <= Point.Y && Point.Y < Square.W);
}

Boolean __fastcall LBSVector::Vec2InVec42(Smallint Left, Smallint Bottom, Smallint Right, Smallint Top,
        Smallint PtX, Smallint PtY)
{
    return Left <= PtX && Right > PtX && Bottom <= PtY && PtY < Top;
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
    {0x004599F4, LBSVector::PointInRect, true},
    {0x00459A28, LBSVector::PointInRect2, true},
    {0x00459A4C, LBSVector::Vec2InVec4, false},
    {0x00459A80, LBSVector::Vec2InVec42, false},
};

// TODO:
// - Fix scrolling back when max zoom
// - Fix vector functions
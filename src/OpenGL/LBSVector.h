#pragma once
#include <math.h>
#include "../Common.h"
#include "../Delphi/System.h"

namespace LBSVector 
{
    struct TLBSColor
    {
        Shortint B, G, R, A;
    };

    struct TVector2s
    {
        Smallint X, Y;
    };
    struct TVector4s
    {
        Smallint X, Y, Z, W;
    };

    struct TVector2f
    {
        Single X, Y;
    };
    struct TVector3f
    {
        Single X, Y, Z;
    };
    struct TVector4f
    {
        Single X, Y, Z, W;
    };

    struct TLBSRect
    {
        TVector2s LeftTop;
        TVector2s RightBottom;
    };


    struct TMatrix3f
    {
        TVector3f X;
        TVector3f Y;
        TVector3f Z;
    };

    struct TMatrix4f
    {
        TVector3f X;
        TVector3f Y;
        TVector3f Z;
        TVector3f W;
    };

    const Single cPI = 3.14159265358979323846;
    const Single cPIdiv180 = 0.017453292;
    const Single c180divPI = 57.29577951;
    const Single c2PI = 6.283185307;
    const Single cPIdiv2 = 1.570796326;
    const Single cPIdiv4 = 0.785398163;
    const Single cInv2PI = 1/6.283185307;
    const Single cFact = 1/32767;

    Single __fastcall DegToRad(Single);
    Single __fastcall RadToDeg(Single);
    void __fastcall SinCos(Single*, Single*, Single);
    Single __fastcall Tan(Single);
    Single __fastcall ArcCos(Single);
    Single __fastcall ArcTan2(Single, Single);
    Single __fastcall NormalizeAngle(Single);
    Integer __naked __fastcall Trunc(Single);
    Single __naked __fastcall Int(Single);
    Single __naked __fastcall Round(Single);

    TVector2s __fastcall VectorAdd2s(TVector2s, Word, Word);
}
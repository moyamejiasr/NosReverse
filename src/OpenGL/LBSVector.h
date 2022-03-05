#pragma once
#include <math.h>
#include "../Common.h"
#include "../Delphi/System.h"

namespace LBSVector 
{
    struct TLBSColor
    {
        Byte B, G, R, A;
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
    Integer __fastcall Trunc(Single);
    Extended __fastcall Int(Extended);
    Integer __fastcall Round(Single);
    Single __fastcall FP16To32(Word);

    TLBSColor __fastcall ColorMake(Byte, Byte, Byte, Byte);
    TVector2s __fastcall VectorMake2s(Smallint, Smallint);
    TVector2s __fastcall VectorAdd2s(TVector2s, Smallint, Smallint);
    Boolean __fastcall PointInRect(TVector2s, TLBSRect*);
    Boolean __fastcall PointInRect2(Smallint, Smallint, Smallint, Smallint, Smallint, Smallint);
    Boolean __fastcall Vec2InVec4(TVector4s*, TVector2s);
    Boolean __fastcall Vec2InVec42(Smallint, Smallint, Smallint, Smallint, Smallint, Smallint);
}
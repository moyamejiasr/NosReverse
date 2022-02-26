#pragma once
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

}
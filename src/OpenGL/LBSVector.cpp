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

Single __fastcall LBSVector::Tan(Single x)
{
    return tan(x);
}

Single __fastcall LBSVector::ArcCos(Single x)
{
    return ArcTan2(sqrt(1.0 - x * x), x);
}

Single __fastcall LBSVector::ArcTan2(Single y, Single x)
{
    return atan2(y, x);
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

Integer __naked __fastcall LBSVector::Trunc(Single x)
{
    __asm__(R"(.intel_syntax noprefix
        PUSH    EBP
        MOV     EBP, ESP
        SUB     ESP, 8
        FSTCW   [ESP]
        FLDCW   [0x005DD648]
        FLD     [EBP+8]
        FISTP   [ESP+4]
        FLDCW   [ESP]
        POP     ECX
        POP     EAX
        POP     EBP
        RET     4
    )");
}

Single __naked __fastcall LBSVector::Int(Single v)
{
    __asm__(R"(.intel_syntax noprefix
        PUSH    EBP
        MOV     EBP, ESP
        SUB     ESP,4
        FSTCW   [ESP]
        FLDCW   [0x005DD648]
        FLD     [EBP+8]
        FRNDINT
        FLDCW   [ESP]
        ADD     ESP,4
        POP     EBP
        RET     4
    )");
}

Single __naked __fastcall LBSVector::Round(Single v)
{
    __asm__(R"(.intel_syntax noprefix
        PUSH    EBP
        MOV     EBP, ESP
        SUB     ESP,4
        FLD     [EBP+8]
        FISTP   [ESP]
        POP     EAX
        POP     EBP
        RET     4
    )");
}

LBSVector::TVector2s __fastcall LBSVector::VectorAdd2s(TVector2s Pos, Word X, Word Y)
{
    return {};
}

Initialization _LBSVector {
    {0x004597EC, LBSVector::DegToRad, true},
    {0x00459808, LBSVector::RadToDeg, true},
    {0x00459824, LBSVector::SinCos, true},
    {0x00459834, LBSVector::Tan, true},
    {0x00459844, LBSVector::ArcCos, true},
    {0x00459878, LBSVector::ArcTan2, true},
    {0x00459888, LBSVector::NormalizeAngle, false},
    {0x00459908, LBSVector::Trunc, false},
    {0x00459928, LBSVector::Int, false},
    {0x00459948, LBSVector::Round, true},

    {0x004599D4, LBSVector::VectorAdd2s},
};
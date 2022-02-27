#include "Classes.h"

Integer __fastcall Classes::TList::Add(PList Self, Pointer Item)
{
    return 0;
}

void __fastcall Classes::TList::_Clear(PList Self)
{

}

void __fastcall Classes::TList::Delete(PList Self, Integer Index)
{

}

Pointer __fastcall Classes::TList::Get(PList Self, Integer Index)
{
    return 0;
}

Integer __fastcall Classes::TList::IndexOf(PList Self, Pointer Item)
{
    return 0;
}

void __fastcall Classes::TList::Move(PList Self, Integer CurIndex, Integer NewIndex)
{

}

Initialization _Classes {
    {0x0041BF7C, Classes::TList::Add},
    {0x0041BFB0, Classes::TList::_Clear},
    {0x0041BFC8, Classes::TList::Delete},
    {0x0041C128, Classes::TList::Get},
    {0x0041C184, Classes::TList::IndexOf},
    {0x0041C21C, Classes::TList::Move},
};
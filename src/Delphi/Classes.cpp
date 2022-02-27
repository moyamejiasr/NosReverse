#include "Classes.h"

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
    {0x0041BFC8, Classes::TList::Delete},
    {0x0041C128, Classes::TList::Get},
    {0x0041C184, Classes::TList::IndexOf},
    {0x0041C21C, Classes::TList::Move},
};
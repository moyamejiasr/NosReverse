#pragma once
#include "../Common.h"
#include "../Delphi/System.h"
#include "LBSVector.h"

namespace LBSUICtrl
{
    typedef struct TLBSWidgetList
    {
        static VMT_ClassDefinition* Class;

        static TLBSWidgetList* __fastcall Create(Pointer, Boolean);
        static Integer __fastcall Add(TLBSWidgetList*, Pointer);
    } *PLBSWidgetList;

    typedef struct TLBSWidget
    {
        static TLBSWidget* __fastcall Create(Pointer, Boolean, TLBSWidget*);

        Pointer VTable;

        Byte Flags;
        TLBSWidget* Parent;
        TLBSWidget* FocusChild;
        LBSVector::TVector2s TopLeft;
        LBSVector::TVector2s BottomRight;
        Boolean Visible;
        Boolean Enabled;
        Boolean Focused;
        Word Cursor;
        PLBSWidgetList Children;
    } *PLBSWidget;

}

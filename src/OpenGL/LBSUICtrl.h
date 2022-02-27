#pragma once
#include "../Common.h"
#include "../Delphi/System.h"
#include "../Delphi/Classes.h"
#include "LBSVector.h"

using namespace LBSVector;

namespace LBSUICtrl
{
    typedef struct TLBSWidgetList: Classes::TList
    {
        static VMT_ClassDefinition* Class;

        static TLBSWidgetList* __fastcall Create(Pointer, Boolean);
        static Integer __fastcall Add(TLBSWidgetList*, Pointer);
    } *PLBSWidgetList;

    typedef struct TLBSWidget: System::TObject
    {
        static TLBSWidget* __fastcall Create(Pointer, Boolean, TLBSWidget*);
        static void __fastcall Destroy(TLBSWidget*, Boolean);
        static void __fastcall SetRect(TLBSWidget*, TLBSRect*);
        static void __fastcall SetX(TLBSWidget*, Word);
        static void __fastcall SetY(TLBSWidget*, Word);
        static Smallint __fastcall GetWidth(TLBSWidget*);
        static void __fastcall SetWidth(TLBSWidget*, Word);
        static Smallint __fastcall GetHeight(TLBSWidget*);
        static void __fastcall SetHeight(TLBSWidget*, Word);
        static TVector2s __fastcall GetRootPosition(TLBSWidget*);
        static void __fastcall SetParent(TLBSWidget*, TLBSWidget*);
        static void __fastcall SetFocusChild(TLBSWidget*, TLBSWidget*);
        static void __fastcall SetEnabled(TLBSWidget*, Boolean);
        static void __fastcall SetVisible(TLBSWidget*, Boolean);
        static TVector2s __fastcall CursorToPosition(TLBSWidget*, TVector2s);

        static TLBSWidget* __fastcall NextFocusableChild(TLBSWidget*);

        virtual void __fastcall Redraw() = 0;
        virtual void __fastcall OnMouseBtnDw() = 0;
        virtual void __fastcall OnMouseMove() = 0;
        virtual void __fastcall OnMouseBtnUp() = 0;
        virtual void __fastcall OnMouseWheel() = 0;
        virtual void __fastcall Unknown6() = 0;
        virtual void __fastcall Unknown7() = 0;
        virtual void __fastcall NotifyChange() = 0;
        virtual void __fastcall Unknown9() = 0;
        virtual void __fastcall Unknown10() = 0;
        virtual void __fastcall OnKeyDown() = 0;
        virtual void __fastcall OnCharType() = 0;
        virtual void __fastcall OnKeyUp() = 0;
        virtual void __fastcall Unknown14() = 0;
        virtual void __fastcall Unknown15() = 0;
        virtual void __fastcall ReCreate() = 0;


        Byte Flags;
        TLBSWidget* Parent;
        TLBSWidget* FocusChild;
        TLBSRect Rect;
        Boolean Visible;
        Boolean Enabled;
        Boolean Focused;
        Word Cursor;
        PLBSWidgetList Children;
    } *PLBSWidget;
}

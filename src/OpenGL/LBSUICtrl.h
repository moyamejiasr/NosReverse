#pragma once
#include "../Common.h"
#include "../Delphi/System.h"
#include "../Delphi/Classes.h"
#include "LBSVector.h"

using namespace LBSVector;

namespace LBSUICtrl
{
    typedef struct TLBSWidget *PLBSWidget;
    typedef struct TLBSWidgetList *PLBSWidgetList;

    void __fastcall ProcessFocus();

    struct TLBSWidget: System::TObject
    {
        static VMT_ClassDefinition* Class;

        Byte Flags;
        PLBSWidget Parent;
        PLBSWidget FocusChild;
        TLBSRect Rect;
        Boolean Visible;
        Boolean Enabled;
        Boolean Focused;
        Word Cursor;
        PLBSWidgetList Children;

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

        static PLBSWidget __fastcall Create(Pointer, Boolean, PLBSWidget);
        static void __fastcall Destroy(PLBSWidget, Boolean);
        static void __fastcall SetRect(PLBSWidget, TLBSRect*);
        static void __fastcall SetX(PLBSWidget, Word);
        static void __fastcall SetY(PLBSWidget, Word);
        static Smallint __fastcall GetWidth(PLBSWidget);
        static void __fastcall SetWidth(PLBSWidget, Word);
        static Smallint __fastcall GetHeight(PLBSWidget);
        static void __fastcall SetHeight(PLBSWidget, Word);
        static TVector2s __fastcall GetRootPosition(PLBSWidget);
        static void __fastcall SetParent(PLBSWidget, PLBSWidget);
        static void __fastcall SetFocusChild(PLBSWidget, PLBSWidget);
        static void __fastcall SetEnabled(PLBSWidget, Boolean);
        static void __fastcall SetVisible(PLBSWidget, Boolean);
        static TVector2s __fastcall CursorToPosition(PLBSWidget, TVector2s);
        static PLBSWidget __fastcall GetNextFocusable(PLBSWidget);
        static PLBSWidget __fastcall GetPrevFocusable(PLBSWidget);
        static PLBSWidget __fastcall GetLastFocusedChild(PLBSWidget);
        static PLBSWidget __fastcall GetFirstFocusedParent(PLBSWidget);
        static void __fastcall BringToFront(PLBSWidget);
        static void __fastcall SendToBack(PLBSWidget);
    };
    ASSERT_SIZE(TLBSWidget, 0x24);

    struct TLBSWidgetList: Classes::TList
    {
        static VMT_ClassDefinition* Class;

        static PLBSWidgetList __fastcall Create(Pointer, Boolean);
        static void __fastcall Destroy(PLBSWidgetList, Boolean);
        static PLBSWidget __fastcall Get(PLBSWidgetList, Integer);
        static Integer __fastcall Add(PLBSWidgetList, Pointer);
        static void __fastcall Delete(PLBSWidgetList, Integer);
        static void __fastcall _Clear(PLBSWidgetList);
    };
    ASSERT_SIZE(TLBSWidgetList, 0x10);
}

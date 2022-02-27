#pragma once
#include "../Common.h"
#include "../Delphi/System.h"
#include "LBSVector.h"

using namespace LBSVector;

namespace LBSUICtrl
{
    typedef struct TLBSWidgetList: System::TObject
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
        static void __fastcall SetLeft(TLBSWidget*, Word);
        static void __fastcall SetTop(TLBSWidget*, Word);
        static Smallint __fastcall GetWidth(TLBSWidget*);
        static void __fastcall SetWidth(TLBSWidget*, Word);
        static Smallint __fastcall GetHeight(TLBSWidget*);
        static void __fastcall SetHeight(TLBSWidget*, Word);
        static TVector2s __fastcall GetRootPosition(TLBSWidget*);

        virtual void __fastcall VRedraw() = 0;
        virtual void __fastcall VOnMouseBtnDw() = 0;
        virtual void __fastcall VOnMouseMove() = 0;
        virtual void __fastcall VOnMouseBtnUp() = 0;
        virtual void __fastcall VOnMouseWheel() = 0;
        virtual void __fastcall VUnknown6() = 0;
        virtual void __fastcall VUnknown7() = 0;
        virtual void __fastcall VNotifyChange() = 0;
        virtual void __fastcall VUnknown9() = 0;
        virtual void __fastcall VUnknown10() = 0;
        virtual void __fastcall VOnKeyDown() = 0;
        virtual void __fastcall VOnCharType() = 0;
        virtual void __fastcall VOnKeyUp() = 0;
        virtual void __fastcall VUnknown14() = 0;
        virtual void __fastcall VUnknown15() = 0;
        virtual void __fastcall VCreate() = 0;


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

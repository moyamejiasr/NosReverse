#include "LBSUICtrl.h"

VMT_ClassDefinition* LBSUICtrl::TLBSWidgetList::Class = Cast(0x0046DC5C);

LBSUICtrl::PLBSWidgetList __fastcall LBSUICtrl::TLBSWidgetList::Create(Pointer AClass, Boolean Alloc)
{
    return nullptr;
}

Integer __fastcall LBSUICtrl::TLBSWidgetList::Add(PLBSWidgetList Self, Pointer Item)
{
    return 0;
}

LBSUICtrl::PLBSWidget __fastcall LBSUICtrl::TLBSWidget::Create(Pointer AClass, Boolean Alloc, PLBSWidget FParent)
{
    volatile int _{}; // Bugfix stack issue related to ClassCreate
    // Seems like this function moves the stack 10h and then, when
    // finished, restores Ch. This is needed this way because they
    // use an extra address to store data.

    PLBSWidget Self = (PLBSWidget)AClass;
    if ( Alloc )
        Self = (PLBSWidget)System::ClassCreate(AClass, Alloc);

    Self->Parent = FParent;
    Self->FocusChild = 0;
    Self->Flags = 1;
    Self->Enabled = 1;
    Self->Visible = 1;
    Self->Focused = 0;
    Self->Cursor = 1;
    Self->Children = LBSUICtrl::TLBSWidgetList::Create(TLBSWidgetList::Class->SelfPtr, 1);
    if (PLBSWidget Parent = Self->Parent)
        LBSUICtrl::TLBSWidgetList::Add(FParent->Children, Self);

    if (Alloc) System::AfterConstruction(Self);
    return Self;
}

void __fastcall LBSUICtrl::TLBSWidget::Destroy(PLBSWidget Self, Boolean Alloc)
{
    System::BeforeDestruction(Self, Alloc);
    System::TObject::Free(Self->Children);
    System::TObject::Destroy(Self, Alloc & 0xFC);
    if ( Alloc > 0 )
        System::ClassDestroy(Self);
}

void __fastcall LBSUICtrl::TLBSWidget::SetRect(PLBSWidget Self, TLBSRect* FRect)
{
    Boolean Changed = Self->Rect.RightBottom.X - Self->Rect.LeftTop.X != FRect->RightBottom.X - FRect->LeftTop.X
                    || Self->Rect.RightBottom.Y - Self->Rect.LeftTop.Y != FRect->RightBottom.Y - FRect->LeftTop.Y;
    Self->Rect = *FRect;
    if (Changed) Self->VNotifyChange();
}

void __fastcall LBSUICtrl::TLBSWidget::SetLeft(PLBSWidget Self, Word Offset)
{
    Self->Rect.RightBottom.X += Offset - Self->Rect.LeftTop.X;
    Self->Rect.LeftTop.X = Offset;
}

void __fastcall LBSUICtrl::TLBSWidget::SetTop(PLBSWidget Self, Word Offset)
{
    Self->Rect.RightBottom.Y += Offset - Self->Rect.LeftTop.Y;
    Self->Rect.LeftTop.Y = Offset;
}

Smallint __fastcall LBSUICtrl::TLBSWidget::GetWidth(PLBSWidget Self)
{
    return Self->Rect.RightBottom.X - Self->Rect.LeftTop.X;
}

void __fastcall LBSUICtrl::TLBSWidget::SetWidth(PLBSWidget Self, Word Width)
{
    Smallint Left = Self->Rect.LeftTop.X;
    Smallint Right = Self->Rect.RightBottom.X;
    if ( Right - Left != Width )
    {
        Self->Rect.RightBottom.X = Left + Width;
        Self->VNotifyChange();
    }
}

Smallint __fastcall LBSUICtrl::TLBSWidget::GetHeight(PLBSWidget Self)
{
    return Self->Rect.RightBottom.Y - Self->Rect.LeftTop.Y;
}

void __fastcall LBSUICtrl::TLBSWidget::SetHeight(PLBSWidget Self, Word Height)
{
    Smallint Top = Self->Rect.LeftTop.Y;
    Smallint Bottom = Self->Rect.RightBottom.Y;
    if ( Bottom - Top != Height )
    {
        Self->Rect.RightBottom.Y = Top + Height;
        Self->VNotifyChange();
    }
}

TVector2s __fastcall LBSUICtrl::TLBSWidget::GetRootPosition(PLBSWidget Self)
{
    if ( !Self->Parent )
        return Self->Rect.LeftTop;
    return LBSVector::VectorAdd2s(GetRootPosition(Self->Parent), 
        Self->Rect.LeftTop.X, Self->Rect.LeftTop.Y);
}

Initialization _LBSUICtrl {
    {0x0047023C, LBSUICtrl::TLBSWidgetList::Create},
    {0x0047029C, LBSUICtrl::TLBSWidgetList::Add},

    {0x0046FC18, LBSUICtrl::TLBSWidget::Create, true},
    {0x0046FC84, LBSUICtrl::TLBSWidget::Destroy, true},
    {0x0046FCB4, LBSUICtrl::TLBSWidget::SetRect, true},
    {0x0046FD18, LBSUICtrl::TLBSWidget::SetLeft, true},
    {0x0046FD28, LBSUICtrl::TLBSWidget::SetTop, true},
    {0x0046FD38, LBSUICtrl::TLBSWidget::GetWidth, true},
    {0x0046FD44, LBSUICtrl::TLBSWidget::SetWidth, true},
    {0x0046FD70, LBSUICtrl::TLBSWidget::GetHeight, true},
    {0x0046FD7C, LBSUICtrl::TLBSWidget::SetHeight, true},
    {0x0046FDA8, LBSUICtrl::TLBSWidget::GetRootPosition, true},
};
#include "LBSUICtrl.h"

void __fastcall LBSUICtrl::ProcessFocus()
{

}

VMT_ClassDefinition* LBSUICtrl::TLBSWidget::Class = Cast(0x0046DB9C);

LBSUICtrl::PLBSWidget __fastcall LBSUICtrl::TLBSWidget::Create(Pointer AClass, Boolean Alloc, PLBSWidget FParent)
{
    PLBSWidget Self = (PLBSWidget)AClass;
    if (Alloc)
    {
        CLASSCREATE_STUD;
        Self = (PLBSWidget)System::ClassCreate(Self, Alloc);
    }

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

    if (Alloc) System::ClassDestroy(Self);
}

void __fastcall LBSUICtrl::TLBSWidget::SetRect(PLBSWidget Self, TLBSRect* FRect)
{
    Boolean RChanged = Self->Rect.RightBottom.X - Self->Rect.LeftTop.X != FRect->RightBottom.X - FRect->LeftTop.X
                    || Self->Rect.RightBottom.Y - Self->Rect.LeftTop.Y != FRect->RightBottom.Y - FRect->LeftTop.Y;
    Self->Rect = *FRect;
    if (RChanged) Self->NotifyChange();
}

void __fastcall LBSUICtrl::TLBSWidget::SetX(PLBSWidget Self, Word Offset)
{
    Self->Rect.RightBottom.X += Offset - Self->Rect.LeftTop.X;
    Self->Rect.LeftTop.X = Offset;
}

void __fastcall LBSUICtrl::TLBSWidget::SetY(PLBSWidget Self, Word Offset)
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
        Self->NotifyChange();
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
        Self->NotifyChange();
    }
}

TVector2s __fastcall LBSUICtrl::TLBSWidget::GetRootPosition(PLBSWidget Self)
{
    if ( !Self->Parent )
        return Self->Rect.LeftTop;
    return LBSVector::VectorAdd2s(GetRootPosition(Self->Parent), 
        Self->Rect.LeftTop.X, Self->Rect.LeftTop.Y);
}

void __fastcall LBSUICtrl::TLBSWidget::SetParent(PLBSWidget Self, PLBSWidget Other)
{
    PLBSWidget Parent = Self->Parent;
    if ( Other != Parent )
    {
        if ( Parent )
        {
            if ( Self == Parent->FocusChild )
                Self->Parent->FocusChild = LBSUICtrl::TLBSWidget::GetNextFocusable(Self->Parent);

            Integer Index = Classes::TList::IndexOf(Self->Parent->Children, Self);
            if ( Index >= 0 )
                Classes::TList::Delete(Self->Parent->Children, Index);
        }
        if ( Other )
            LBSUICtrl::TLBSWidgetList::Add(Other->Children, Self);
        Self->Parent = Other;
    }
}

void __fastcall LBSUICtrl::TLBSWidget::SetFocusChild(PLBSWidget Self, PLBSWidget Child)
{
    if ( Child != Self->FocusChild )
        Self->FocusChild = Child;
}

void __fastcall LBSUICtrl::TLBSWidget::SetEnabled(PLBSWidget Self, Boolean IsEnabled)
{
    Self->Enabled = IsEnabled;
}

void __fastcall LBSUICtrl::TLBSWidget::SetVisible(PLBSWidget Self, Boolean IsVisible)
{
    Self->Visible = IsVisible;
}

TVector2s __fastcall LBSUICtrl::TLBSWidget::CursorToPosition(PLBSWidget Self, TVector2s VCursor)
{
  TVector2s Position = LBSUICtrl::TLBSWidget::GetRootPosition(Self);
  return LBSVector::VectorAdd2s(VCursor, -Position.X, -Position.Y);
}


LBSUICtrl::PLBSWidget __fastcall LBSUICtrl::TLBSWidget::GetNextFocusable(PLBSWidget Self)
{
    if (PLBSWidget FocusedChild = Self->FocusChild)
    {
        Integer FocusedIndex = Classes::TList::IndexOf(Self->Children, FocusedChild);
        if (FocusedIndex < 0) return nullptr;  // An error occured here

        // Try to search forward
        for (Integer i = FocusedIndex + 1; i < Self->Children->FCount; i++)
        {
            PLBSWidget Child = LBSUICtrl::TLBSWidgetList::Get(Self->Children, i);
            if (Child->Enabled && Child->Visible && Child->Flags & 8)
                return Child;
        }
        // Try from the beginning otherwise
        for (Integer i = 0; i < FocusedIndex; i++)
        {
            PLBSWidget Child = LBSUICtrl::TLBSWidgetList::Get(Self->Children, i);
            if (Child->Enabled && Child->Visible && Child->Flags & 8)
                return Child;
        }
    }
    else
    {
        // Get first focus if there is no focused child
        if (!FocusedChild)
        {
            for (Integer i = 0; i < Self->Children->FCount; i++)
            {
                PLBSWidget Child = LBSUICtrl::TLBSWidgetList::Get(Self->Children, i);
                if (Child->Enabled && Child->Visible && Child->Flags & 8)
                    return Child;
            }
        }
    }

    // Nohing found
    return nullptr;
}

LBSUICtrl::PLBSWidget __fastcall LBSUICtrl::TLBSWidget::GetPrevFocusable(PLBSWidget Self)
{
    if (PLBSWidget FocusedChild = Self->FocusChild)
    {
        Integer FocusedIndex = Classes::TList::IndexOf(Self->Children, FocusedChild);
        if (FocusedIndex < 0) return nullptr;  // An error occured here

        // Try to search backward
        for (Integer i = FocusedIndex - 1; i >= 0; i--)
        {
            PLBSWidget Child = LBSUICtrl::TLBSWidgetList::Get(Self->Children, i);
            if (Child->Enabled && Child->Visible && Child->Flags & 8)
                return Child;
        }
        // Try from the end otherwise
        for (Integer i = Self->Children->FCount - 1; i >= FocusedIndex + 1; i--)
        {
            PLBSWidget Child = LBSUICtrl::TLBSWidgetList::Get(Self->Children, i);
            if (Child->Enabled && Child->Visible && Child->Flags & 8)
                return Child;
        }
    }
    else
    {
        // Get last focus if there is no focused child
        if (!FocusedChild)
        {
            for (Integer i = Self->Children->FCount - 1; i >= 0; i--)
            {
                PLBSWidget Child = LBSUICtrl::TLBSWidgetList::Get(Self->Children, i);
                if (Child->Enabled && Child->Visible && Child->Flags & 8)
                    return Child;
            }
        }
    }

    // Nohing found
    return nullptr;
}

LBSUICtrl::PLBSWidget __fastcall LBSUICtrl::TLBSWidget::GetLastFocusedChild(PLBSWidget Self)
{
    if (Self->FocusChild)
        return LBSUICtrl::TLBSWidget::GetLastFocusedChild(Self->FocusChild);
    
    if (Self->Enabled && Self->Visible && Self->Flags & 8)
        return Self;
    return nullptr;
}

LBSUICtrl::PLBSWidget __fastcall LBSUICtrl::TLBSWidget::GetFirstFocusedParent(PLBSWidget Self)
{
    if ( Self->Parent )
        return LBSUICtrl::TLBSWidget::GetFirstFocusedParent(Self->Parent);

    if (Self->Enabled && Self->Visible && Self->Flags & 8)
        return Self;
    return nullptr;
}

void __fastcall LBSUICtrl::TLBSWidget::BringToFront(PLBSWidget Self)
{
    if (PLBSWidget Parent = Self->Parent)
    {
        Integer Index = Classes::TList::IndexOf(Parent->Children, Self);
        if ( Index < 0 ) return;  // An error occured here
        
        // Move me to top of Z-Index and give me focus.
        Classes::TList::Move(Parent->Children, Index, Parent->Children->FCount - 1);
        if ( (Self->Flags & 8) == 8 && Self->Visible && Self->Enabled )
        {
            LBSUICtrl::TLBSWidget::SetFocusChild(Self->Parent, Self);
            LBSUICtrl::ProcessFocus();
        }
    }
}

void __fastcall LBSUICtrl::TLBSWidget::SendToBack(PLBSWidget Self)
{
    if (PLBSWidget Parent = Self->Parent)
    {
        Integer Index = Classes::TList::IndexOf(Parent->Children, Self);
        if ( Index < 0 ) return;  // An error occured here
        
        
        // If I was focused it is because I'm on top of Z-Index.
        // Then get the one before.
        Classes::TList::Move(Parent->Children, Index, 0);
        if ( (Self->Flags & 8) == 8 && Self->Visible && Self->Enabled )
        {
            PLBSWidget PrevFocusable = LBSUICtrl::TLBSWidget::GetPrevFocusable(Self->Parent);
            LBSUICtrl::TLBSWidget::SetFocusChild(Self->Parent, PrevFocusable);
            LBSUICtrl::ProcessFocus();
        }
    }
}

VMT_ClassDefinition* LBSUICtrl::TLBSWidgetList::Class = Cast(0x0046DC5C);

LBSUICtrl::PLBSWidgetList __fastcall LBSUICtrl::TLBSWidgetList::Create(Pointer AClass, Boolean Alloc)
{
    PLBSWidgetList Self = (PLBSWidgetList)AClass;
    if ( Alloc )
    {
        CLASSCREATE_STUD;
        Self = (PLBSWidgetList)System::ClassCreate(Self, Alloc);
    }
        
    if ( Alloc )
        System::AfterConstruction(Self);
    return Self;
}

void __fastcall LBSUICtrl::TLBSWidgetList::Destroy(PLBSWidgetList Self, Boolean Alloc)
{
    System::BeforeDestruction(Self, Alloc);

    Self->Clear();
    Classes::TList::Destroy(Self, Alloc & 0xFC);

    if (Alloc) System::ClassDestroy(Self);
}

LBSUICtrl::PLBSWidget __fastcall LBSUICtrl::TLBSWidgetList::Get(PLBSWidgetList Self, Integer Index)
{
    return (PLBSWidget)Classes::TList::Get(Self, Index);
}

Integer __fastcall LBSUICtrl::TLBSWidgetList::Add(PLBSWidgetList Self, Pointer Item)
{
    return Classes::TList::Add(Self, Item);
}

void __fastcall LBSUICtrl::TLBSWidgetList::Delete(PLBSWidgetList Self, Integer Index)
{
    PLBSWidget Child = LBSUICtrl::TLBSWidgetList::Get(Self, Index);
    System::TObject::Free(Child);
    Classes::TList::Delete(Self, Index);
}

void __fastcall LBSUICtrl::TLBSWidgetList::_Clear(PLBSWidgetList Self)
{
    Integer Count = Self->FCount - 1;
    if ( Count >= 0 )
    {
        do
            LBSUICtrl::TLBSWidgetList::Delete(Self, Count--);
        while ( Count != -1 );
    }
    Classes::TList::_Clear(Self);
}

Initialization _LBSUICtrl {
    {0x0046E488, LBSUICtrl::ProcessFocus},

    {0x0046FC18, LBSUICtrl::TLBSWidget::Create, true},
    {0x0046FC84, LBSUICtrl::TLBSWidget::Destroy, true},
    {0x0046FCB4, LBSUICtrl::TLBSWidget::SetRect, true},
    {0x0046FD18, LBSUICtrl::TLBSWidget::SetX, true},
    {0x0046FD28, LBSUICtrl::TLBSWidget::SetY, true},
    {0x0046FD38, LBSUICtrl::TLBSWidget::GetWidth, true},
    {0x0046FD44, LBSUICtrl::TLBSWidget::SetWidth, true},
    {0x0046FD70, LBSUICtrl::TLBSWidget::GetHeight, true},
    {0x0046FD7C, LBSUICtrl::TLBSWidget::SetHeight, true},
    {0x0046FDA8, LBSUICtrl::TLBSWidget::GetRootPosition, true},
    {0x0046FDDC, LBSUICtrl::TLBSWidget::SetParent, true},
    {0x0046FE34, LBSUICtrl::TLBSWidget::SetFocusChild, true},
    {0x0046FE40, LBSUICtrl::TLBSWidget::SetEnabled}, // Too small
    {0x0046FE44, LBSUICtrl::TLBSWidget::SetVisible}, // Too small
    {0x0046FE64, LBSUICtrl::TLBSWidget::CursorToPosition, true},
    {0x0046FEA0, LBSUICtrl::TLBSWidget::GetNextFocusable, true},
    {0x0046FFD4, LBSUICtrl::TLBSWidget::GetPrevFocusable, true},
    {0x00470100, LBSUICtrl::TLBSWidget::GetLastFocusedChild, true},
    {0x0047012C, LBSUICtrl::TLBSWidget::GetFirstFocusedParent, true},
    {0x00470158, LBSUICtrl::TLBSWidget::BringToFront, true},
    {0x004701A8, LBSUICtrl::TLBSWidget::SendToBack, true},

    {0x0047023C, LBSUICtrl::TLBSWidgetList::Create, true},
    {0x0047025C, LBSUICtrl::TLBSWidgetList::Destroy, true},
    {0x00470288, LBSUICtrl::TLBSWidgetList::Get, true},
    {0x0047029C, LBSUICtrl::TLBSWidgetList::Add, true},
    {0x004702A4, LBSUICtrl::TLBSWidgetList::Delete, true},
    {0x004702C4, LBSUICtrl::TLBSWidgetList::_Clear, true},
};
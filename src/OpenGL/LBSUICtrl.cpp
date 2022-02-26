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
        LBSUICtrl::TLBSWidgetList::Add(Parent->Children, Self);
    if ( Alloc ) System::AfterConstruction(Self);
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

Initialization _LBSUICtrl {
    {0x0047023C, LBSUICtrl::TLBSWidgetList::Create},
    {0x0047029C, LBSUICtrl::TLBSWidgetList::Add},

    {0x0046FC18, LBSUICtrl::TLBSWidget::Create},
    {0x0046FC84, LBSUICtrl::TLBSWidget::Destroy},
};
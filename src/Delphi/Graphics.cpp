#include "Graphics.h"

void __fastcall Graphics::TFont::SetColor(PFont Self, Cardinal Value)
{

}

HFONT __fastcall Graphics::TFont::GetHandle(PFont Self)
{
    return nullptr;
}

void __fastcall Graphics::TFont::SetHandle(PFont Self, HFONT Value)
{

}

void __fastcall Graphics::TBrush::SetColor(PBrush Self, Cardinal Value)
{

}

void __fastcall Graphics::TBrush::SetStyle(PBrush Self, TBrushStyle Style)
{

}

void __fastcall Graphics::TCanvas::FillRect(PCanvas Self, TRect* Rect)
{

}

void __fastcall Graphics::TCanvas::GetClipRect(PCanvas Self, TRect* Rect)
{

}

VMT_ClassDefinition* Graphics::TBitmap::Class = Cast(0x004241E0);

Graphics::PBitmap __fastcall Graphics::TBitmap::Create(Pointer AClass, Boolean Alloc)
{
    return nullptr;
}

Graphics::PCanvas __fastcall Graphics::TBitmap::GetCanvas(PBitmap Self)
{
    return nullptr;
}

Pointer __fastcall Graphics::TBitmap::GetScanline(PBitmap Self, Integer Row)
{
    return nullptr;
}

void __fastcall Graphics::TBitmap::SetMonochrome(PBitmap Self, Boolean Value)
{

}

void __fastcall Graphics::TBitmap::SetPixelFormat(PBitmap Self, TPixelFormat Value)
{

}

Initialization _Graphics {
    {0x004251B0, Graphics::TFont::SetColor, false},
    {0x004251C4, Graphics::TFont::GetHandle, false},
    {0x0042536C, Graphics::TFont::SetHandle, false},

    {0x0042597C, Graphics::TBrush::SetColor, false},
    {0x00425A98, Graphics::TBrush::SetStyle, false},
    
    {0x00425D20, Graphics::TCanvas::FillRect, false},
    {0x00426008, Graphics::TCanvas::GetClipRect, false},

    {0x0042A4CC, Graphics::TBitmap::Create, false},
    {0x0042AA9C, Graphics::TBitmap::GetCanvas, false},
    {0x0042AC0C, Graphics::TBitmap::GetScanline, false},
    {0x0042B8F8, Graphics::TBitmap::SetMonochrome, false},
    {0x0042BA4C, Graphics::TBitmap::SetPixelFormat, false},
};
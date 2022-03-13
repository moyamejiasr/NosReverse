#include "LBSCanvasTexture.h"

LBSCanvasTexture::PLBSCanvasTexture __fastcall LBSCanvasTexture::TLBSCanvasTexture::Create(Pointer AClass, Boolean Alloc, Smallint Width, Smallint Height, Byte Format)
{
    PLBSCanvasTexture Self = (PLBSCanvasTexture)AClass;
    if (Alloc)
    {
        CLASSCREATE_STUD;
        Self = (PLBSCanvasTexture)System::ClassCreate(Self, Alloc);
    }
    System::TObject::Create(Self, 0);

    LBSCanvasTexture::TLBSCanvasTexture::FixDimension(Self, &Width);
    LBSCanvasTexture::TLBSCanvasTexture::FixDimension(Self, &Height);
    Self->FBitmap = Graphics::TBitmap::Create(Graphics::TBitmap::Class->SelfPtr, 1);
    Self->PixelFormat = Format;
    switch ( Format & 0x7F )
    {
        case 0:
            Graphics::TBitmap::SetMonochrome(Self->FBitmap, true); break;
        case 1:
            Graphics::TBitmap::SetPixelFormat(Self->FBitmap, Graphics::pf8bit); break;
        case 2: case 4:
            Graphics::TBitmap::SetPixelFormat(Self->FBitmap, Graphics::pf16bit); break;
        case 3: case 5:
            Graphics::TBitmap::SetPixelFormat(Self->FBitmap, Graphics::pf32bit); break;
        default:
            break;
    }
    Self->FBitmap->SetWidth(Width);
    Self->FBitmap->SetHeight(Height);

    TRect Rect;
    Graphics::TFont::SetColor(Graphics::TBitmap::GetCanvas(Self->FBitmap)->Font, 0xFFFFFFu);
    Graphics::TBrush::SetColor(Graphics::TBitmap::GetCanvas(Self->FBitmap)->Brush, 0);
    Graphics::TCanvas::GetClipRect(Graphics::TBitmap::GetCanvas(Self->FBitmap), &Rect);
    Graphics::TCanvas::FillRect(Graphics::TBitmap::GetCanvas(Self->FBitmap), &Rect);
    Graphics::TBrush::SetStyle(Graphics::TBitmap::GetCanvas(Self->FBitmap)->Brush, Graphics::bsClear);

    LOGFONTA LogFont;
    HFONT FontHandle = Graphics::TFont::GetHandle(Graphics::TBitmap::GetCanvas(Self->FBitmap)->Font);
    GetObjectA(FontHandle, 60, &LogFont);
    LogFont.lfQuality = 4;
    HFONT NewFontHandle = CreateFontIndirectA(&LogFont);
    Graphics::TFont::SetHandle(Graphics::TBitmap::GetCanvas(Self->FBitmap)->Font, NewFontHandle);

    if (Self->PixelFormat)
    {
        Integer BmpHeight = Self->FBitmap->GetHeight();
        Self->LastScnLine = Graphics::TBitmap::GetScanline(Self->FBitmap, BmpHeight - 1);
        Self->SizeScnLine = (Integer)Graphics::TBitmap::GetScanline(Self->FBitmap, 0) - (Integer)Graphics::TBitmap::GetScanline(Self->FBitmap, 1);
    }

    (*glGenTextures)(1, (GLuint*)&Self->GLTexture);
    LBSCanvasTexture::TLBSCanvasTexture::LoadTexture(Self);

    (*glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    (*glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    (*glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    (*glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
    if (Alloc) System::AfterConstruction(Self);
    return Self;
}

void __fastcall LBSCanvasTexture::TLBSCanvasTexture::FixDimension(PLBSCanvasTexture Self, Smallint* Dimension)
{
    unsigned char i;
    for (i = 1; 1 << i < *Dimension; ++i);
    *Dimension = 1 << i;
}

void __fastcall LBSCanvasTexture::TLBSCanvasTexture::LoadTexture(PLBSCanvasTexture Self)
{

}

Initialization _LBSCanvasTexture {
    {0x004704A8, LBSCanvasTexture::TLBSCanvasTexture::Create, true},
    {0x00470708, LBSCanvasTexture::TLBSCanvasTexture::FixDimension, true},
    {0x00470824, LBSCanvasTexture::TLBSCanvasTexture::LoadTexture, false},
};
#include "LBSCanvasTexture.h"

void __fastcall LBSCanvasTexture::RowTransform(Pointer a1, Pointer a2, Integer Width)
{

}

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
    switch (Format & 0x7F)
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

void __fastcall LBSCanvasTexture::TLBSCanvasTexture::Destroy(PLBSCanvasTexture Self, Boolean Alloc)
{
    System::BeforeDestruction(Self, Alloc);

    (*glDeleteTextures)(1, (GLuint*)&Self->GLTexture);
    System::TObject::Free(Self->FBitmap);
    System::TObject::Destroy(Self, Alloc & 0xFC);

    if (Alloc) System::ClassDestroy(Self);
}

void __fastcall LBSCanvasTexture::TLBSCanvasTexture::FixDimension(PLBSCanvasTexture Self, Smallint* Dimension)
{
    unsigned char i;
    for (i = 1; 1 << i < *Dimension; ++i);
    *Dimension = 1 << i;
}

void __fastcall LBSCanvasTexture::TLBSCanvasTexture::_SetDimensions(PLBSCanvasTexture Self, Smallint Width, Smallint Height)
{
    Integer BWidth, BHeight;
    LBSCanvasTexture::TLBSCanvasTexture::FixDimension(Self, &Width);
    LBSCanvasTexture::TLBSCanvasTexture::FixDimension(Self, &Height);
    BWidth = Self->FBitmap->GetWidth();
    if ( BWidth != Width || (BHeight = Self->FBitmap->GetHeight(), BHeight != Height) )
    {
        Self->FBitmap->SetWidth(Width);
        Self->FBitmap->SetHeight(Height);
        TRect Rect;
        Graphics::TBrush::SetColor(Graphics::TBitmap::GetCanvas(Self->FBitmap)->Brush, 0);
        Graphics::TCanvas::GetClipRect(Graphics::TBitmap::GetCanvas(Self->FBitmap), &Rect);
        Graphics::TCanvas::FillRect(Graphics::TBitmap::GetCanvas(Self->FBitmap), &Rect);
        Graphics::TBrush::SetStyle(Graphics::TBitmap::GetCanvas(Self->FBitmap)->Brush, Graphics::bsClear);
        if ( Self->PixelFormat )
        {
            Integer BmpHeight = Self->FBitmap->GetHeight();
            Self->LastScnLine = Graphics::TBitmap::GetScanline(Self->FBitmap, BmpHeight - 1);
            Self->SizeScnLine = (Integer)Graphics::TBitmap::GetScanline(Self->FBitmap, 0) - (Integer)Graphics::TBitmap::GetScanline(Self->FBitmap, 1);
        }
        LBSCanvasTexture::TLBSCanvasTexture::LoadTexture(Self);
    }
}

void __fastcall LBSCanvasTexture::TLBSCanvasTexture::LoadTexture(PLBSCanvasTexture Self)
{
    (*glBindTexture)(GL_TEXTURE_2D, (GLuint)Self->GLTexture);
    Integer Height = Self->FBitmap->GetHeight(), Width = Self->FBitmap->GetWidth();
    switch (Self->PixelFormat)
    {
        case 0:
            GetBitmapBits(Self->FBitmap->GetHandle(), Height * Width / 8, LBSCommon::GBuffer);
            (*glTexImage2D)(GL_TEXTURE_2D, 0, GL_ALPHA, Width, Height, 0, GL_COLOR_INDEX, GL_BITMAP, (GLvoid*)LBSCommon::GBuffer);
            break;
        case 1: case 2: case 3:
            GetBitmapBits(Self->FBitmap->GetHandle(), Height * Width, LBSCommon::GBuffer);
            (*glTexImage2D)(GL_TEXTURE_2D, 0, GL_ALPHA, Width, Height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, (GLvoid*)LBSCommon::GBuffer);
            break;
        case 4:
            GetBitmapBits(Self->FBitmap->GetHandle(), 2 * Height * Width, LBSCommon::GBuffer);
            (*glTexImage2D)(GL_TEXTURE_2D, 0, GL_ALPHA, Width, Height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, (GLvoid*)LBSCommon::GBuffer);
            break;
        case 5:
            GetBitmapBits(Self->FBitmap->GetHandle(), 4 * Height * Width, LBSCommon::GBuffer);
            (*glTexImage2D)(GL_TEXTURE_2D, 0, GL_RGBA4, Width, Height, 0, GL_BGR_EXT, GL_UNSIGNED_SHORT_4_4_4_4_REV, (GLvoid*)LBSCommon::GBuffer);
            break;
    }
}

Boolean __fastcall LBSCanvasTexture::TLBSCanvasTexture::LoadSubTexture(PLBSCanvasTexture Self)
{
    (*glBindTexture)(GL_TEXTURE_2D, (GLuint)Self->GLTexture);
    Integer Height = Self->FBitmap->GetHeight(), Width = Self->FBitmap->GetWidth();
    switch (Self->PixelFormat)
    {
        case 0:
            GetBitmapBits(Self->FBitmap->GetHandle(), Height * Width / 8, LBSCommon::GBuffer);
            (*glTexSubImage2D)(GL_TEXTURE_2D, 0, 0, 0, Width, Height, GL_COLOR_INDEX, GL_BITMAP, (GLvoid*)LBSCommon::GBuffer);
            break;
        case 1:
            GetBitmapBits(Self->FBitmap->GetHandle(), Height * Width, LBSCommon::GBuffer);
            (*glTexSubImage2D)(GL_TEXTURE_2D, 0, 0, 0, Width, Height, GL_ALPHA, GL_UNSIGNED_BYTE, (GLvoid*)LBSCommon::GBuffer);
            break;
        case 3:
            for (Integer Row = 0; Row < Height; Row++)
            {
                LBSCanvasTexture::RowTransform((Pointer)((Integer)Self->LastScnLine + Self->SizeScnLine * (Height - 1 - Row)), 
                    LBSCommon::GBuffer + Row * Width, Width);
            }
            (*glTexSubImage2D)(GL_TEXTURE_2D, 0, 0, 0, Width, Height, GL_ALPHA, GL_UNSIGNED_BYTE, (GLvoid*)LBSCommon::GBuffer);
            break;
        case 4:
            GetBitmapBits(Self->FBitmap->GetHandle(), 2 * Height * Width, LBSCommon::GBuffer);
            (*glTexSubImage2D)(GL_TEXTURE_2D, 0, 0, 0, Width, Height, GL_BGRA_EXT, GL_UNSIGNED_SHORT_4_4_4_4_REV, (GLvoid*)LBSCommon::GBuffer);
            break;
        case 5:
            GetBitmapBits(Self->FBitmap->GetHandle(), 4 * Height * Width, LBSCommon::GBuffer);
            (*glTexSubImage2D)(GL_TEXTURE_2D, 0, 0, 0, Width, Height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (GLvoid*)LBSCommon::GBuffer);
            break;
        default:
            return true;
  }
  return true;
}

LBSCanvasTexture::PLBSCanvasTextureEx __fastcall LBSCanvasTexture::TLBSCanvasTextureEx::Create(Pointer AClass, Boolean Alloc, Word Width, Word Height, Byte Format)
{
    PLBSCanvasTextureEx Self = (PLBSCanvasTextureEx)AClass;
    if (Alloc)
    {
        CLASSCREATE_STUD;
        Self = (PLBSCanvasTextureEx)System::ClassCreate(Self, Alloc);
    }
    System::TObject::Create(Self, 0);
    Self->Scale.X = Width;
    Self->Scale.Y = Height;
    LBSCanvasTexture::TLBSCanvasTexture::Create(Self, 0, Width, Height, Format);
    Self->WidthPerc = 1.0 / Self->FBitmap->GetWidth();
    Self->HeightPerc = 1.0 / Self->FBitmap->GetHeight();
    Self->Changed = 0;

    if (Alloc) System::AfterConstruction(Self);
    return Self;
}

Boolean __fastcall LBSCanvasTexture::TLBSCanvasTextureEx::_BindTexture(PLBSCanvasTextureEx Self)
{
    if (!Self->Changed)
    {
        (*glBindTexture)(GL_TEXTURE_2D, (GLuint)Self->GLTexture);
        return true;
    }
    Self->Changed = false;
    return LBSCanvasTexture::TLBSCanvasTexture::LoadSubTexture(Self);
}

Graphics::PCanvas __fastcall LBSCanvasTexture::TLBSCanvasTextureEx::GetCanvas(PLBSCanvasTextureEx Self)
{
    return Graphics::TBitmap::GetCanvas(Self->FBitmap);
}

void __fastcall LBSCanvasTexture::TLBSCanvasTextureEx::SetDimensions(PLBSCanvasTextureEx Self, Smallint Width, Smallint Height)
{
    Self->Scale.X = Width; Self->Scale.Y = Height;
    TLBSCanvasTexture::_SetDimensions(Self, Width, Height);
    Self->WidthPerc = 1.0 / Self->FBitmap->GetWidth();
    Self->HeightPerc = 1.0 / Self->FBitmap->GetHeight();
}

Initialization _LBSCanvasTexture {
    {0x00470454, LBSCanvasTexture::RowTransform},

    {0x004704A8, LBSCanvasTexture::TLBSCanvasTexture::Create, true},
    {0x004706CC, LBSCanvasTexture::TLBSCanvasTexture::Destroy, true},
    {0x00470708, LBSCanvasTexture::TLBSCanvasTexture::FixDimension, true},
    {0x00470730, LBSCanvasTexture::TLBSCanvasTexture::_SetDimensions, true},
    {0x00470824, LBSCanvasTexture::TLBSCanvasTexture::LoadTexture, true},
    {0x00470A04, LBSCanvasTexture::TLBSCanvasTexture::LoadSubTexture, true},
    
    {0x00470C70, LBSCanvasTexture::TLBSCanvasTextureEx::Create, true},
    {0x00470CFC, LBSCanvasTexture::TLBSCanvasTextureEx::_BindTexture, true},
    {0x00470D28, LBSCanvasTexture::TLBSCanvasTextureEx::GetCanvas, true},
    {0x00470D34, LBSCanvasTexture::TLBSCanvasTextureEx::SetDimensions, true},
};
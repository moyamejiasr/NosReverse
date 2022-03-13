#pragma once
#include "../Common.h"
#include "System.h"

namespace Graphics
{
    typedef struct TGraphic *PGraphic;
    typedef struct TBitmap *PBitmap;

    struct TGraphic : System::TObject
    {
        Pointer FOwnerInterface;
        Pointer InterfaceUnk;
        Pointer Unknown;
        TMethod FOnChange;
        TMethod FOnProgress;
        Boolean FModified;
        Boolean FTransparent;
        Boolean FPaletteModified;
        Pointer InterfaceUnk2;

        virtual Pointer __fastcall QueryInterface(Pointer IID, Pointer Obj);
        virtual void __fastcall Changed(Pointer Sender);
        virtual void __fastcall Draw(Pointer ACanvas, Pointer Rect);
        virtual Boolean __fastcall Equals(PGraphic Graphic);
        virtual Boolean __fastcall GetEmpty();
        virtual Integer __fastcall GetHeight();
        virtual HPALETTE __fastcall GetPalette();
        virtual Boolean __fastcall GetTransparent();
        virtual Integer __fastcall GetWidth();
        virtual void __fastcall ReadData(Pointer Stream);
        virtual void __fastcall SetHeight(Integer Value);
        virtual void __fastcall SetPalette(HPALETTE Value);
        virtual void __fastcall SetTransparent(Boolean Value);
        virtual void __fastcall SetWidth(Integer Value);
        virtual void __fastcall WriteData(Pointer Stream);
        virtual PGraphic __fastcall Create(char Alloc);
        virtual void __fastcall LoadFromFile(PString Filename);
        virtual void __fastcall SaveToFile(PString Filename);
        virtual void __fastcall LoadFromStream(Pointer Stream);
        virtual void __fastcall SaveToStream(Pointer Stream);
        virtual void __fastcall LoadFromClipboardFormat(Word AFormat, Pointer AData);
        virtual void __fastcall SaveToClipboardFormat(Word AFormat, Pointer AData);
    };
    ASSERT_SIZE(TGraphic, 0x28);

    struct TBitmap : TGraphic
    {
        Pointer FImage; // PBitmapImage
        Pointer FCanvas; // PCanvas
        Boolean FIgnorePalette;
        Boolean FMaskBitsValid;
        Integer FTransparentColor;
        Integer FTransparentmode;
    };

}
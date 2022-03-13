#pragma once
#include "../Common.h"
#include "System.h"
#include "Classes.h"

namespace Graphics
{
    typedef struct TGraphicsObject *PGraphicsObject;
    typedef struct TFont *PFont;
    typedef struct TPen *PPen;
    typedef struct TBrush *PBrush;
    typedef struct TCanvas *PCanvas;
    typedef struct TGraphic *PGraphic;
    typedef struct TBitmap *PBitmap;

    enum TBrushStyle : unsigned char 
    { 
        bsSolid, 
        bsClear, 
        bsHorizontal, 
        bsVertical, 
        bsFDiagonal, 
        bsBDiagonal, 
        bsCross, 
        bsDiagCross,
    };

    enum TPixelFormat : unsigned char
    {
        pfDevice = 0x0,
        pf1bit = 0x1,
        pf4bit = 0x2,
        pf8bit = 0x3,
        pf15bit = 0x4,
        pf16bit = 0x5,
        pf24bit = 0x6,
        pf32bit = 0x7,
        pfCustom = 0x8,
    };

    struct TGraphicsObject : Classes::TPersistent
    {
        static VMT_ClassDefinition* Class;

        Pointer Unknown;
        TMethod FOnChange;
        Pointer FResource;
        Pointer FOwnerlock;

        virtual void __fastcall Changed();
    };
    ASSERT_SIZE(TGraphicsObject, 0x18);

    struct TFont : TGraphicsObject
    {
        static VMT_ClassDefinition* Class;

        Integer Color;
        Integer FPixelsPerInch;
        Pointer FNotify;

        static void __fastcall SetColor(PFont, Cardinal);
        static HFONT __fastcall GetHandle(PFont);
        static void __fastcall SetHandle(PFont, HFONT);
    };
    ASSERT_SIZE(TFont, 0x24);
    
    struct TPen : TGraphicsObject
    {
        static VMT_ClassDefinition* Class;

        Integer Mode;
    };
    ASSERT_SIZE(TPen, 0x1C);

    struct TBrush : TGraphicsObject
    {
        static VMT_ClassDefinition* Class;
        
        static void __fastcall SetColor(PBrush, Cardinal);
        static void __fastcall SetStyle(PBrush, TBrushStyle);
    };
    ASSERT_SIZE(TBrush, 0x18);

    struct TCanvas : Classes::TPersistent
    {
        static VMT_ClassDefinition* Class;

        HDC FHandle;
        Integer State;
        PFont Font;
        PPen Pen;
        PBrush Brush;
        TPoint FPenPos;
        Integer CopyMode;
        Integer Unknown;
        TMethod FOnChange;
        TMethod FOnChanging;
        Integer FLock[6];
        Integer FLockCount;
        Integer FTextFlags;
        
        virtual void __fastcall Changed();
        virtual void __fastcall Changing();
        virtual void __fastcall CreateHandle();

        static void __fastcall FillRect(PCanvas, TRect*);
        static void __fastcall GetClipRect(PCanvas, TRect*);
    };
    ASSERT_SIZE(TCanvas, 0x58);

    struct TGraphic : Classes::TInterfacedPersistent
    {
        static VMT_ClassDefinition* Class;

        Pointer FOwnerInterface;
        Pointer InterfaceUnk;
        Pointer Unknown;
        TMethod FOnChange;
        TMethod FOnProgress;
        Boolean FModified;
        Boolean FTransparent;
        Boolean FPaletteModified;
        Pointer InterfaceUnk2;

        virtual void __fastcall Changed(Pointer Sender);
        virtual void __fastcall Draw(Pointer ACanvas, Pointer Rect);
        virtual Boolean __fastcall Equals(PGraphic Graphic);
        virtual Boolean __fastcall GetEmpty();
        virtual Integer __fastcall GetHeight();
        virtual HPALETTE __fastcall GetPalette();
        virtual Boolean __fastcall GetTransparent();
        virtual Integer __fastcall GetWidth();
        virtual void __fastcall ReadData(Classes::PStream Stream);
        virtual void __fastcall SetHeight(Integer Value);
        virtual void __fastcall SetPalette(HPALETTE Value);
        virtual void __fastcall SetTransparent(Boolean Value);
        virtual void __fastcall SetWidth(Integer Value);
        virtual void __fastcall WriteData(Classes::PStream Stream);
        virtual PGraphic __fastcall Create(Boolean Alloc);
        virtual void __fastcall LoadFromFile(PString Filename);
        virtual void __fastcall SaveToFile(PString Filename);
        // START IStreamPersist
        virtual void __fastcall LoadFromStream(Classes::PStream Stream);
        virtual void __fastcall SaveToStream(Classes::PStream Stream);
        // END IStreamPersist
        virtual void __fastcall LoadFromClipboardFormat(Word AFormat, Pointer AData);
        virtual void __fastcall SaveToClipboardFormat(Word AFormat, Pointer AData);
    };
    ASSERT_SIZE(TGraphic, 0x28);

    struct TBitmap : TGraphic
    {
        static VMT_ClassDefinition* Class;

        Pointer FImage; // PBitmapImage
        Pointer FCanvas; // PCanvas
        Boolean FIgnorePalette;
        Boolean FMaskBitsValid;
        Integer FTransparentColor;
        Integer FTransparentmode;

        virtual HBITMAP __fastcall GetHandle();
        virtual HBITMAP __fastcall GetMaskHandle();
        virtual void __fastcall SetHandleType(Integer Value);

        static PBitmap __fastcall Create(Pointer, Boolean);
        static PCanvas __fastcall GetCanvas(PBitmap);
        static Pointer __fastcall GetScanline(PBitmap, Integer);
        static void __fastcall SetMonochrome(PBitmap, Boolean);
        static void __fastcall SetPixelFormat(PBitmap, TPixelFormat);
    };
    ASSERT_SIZE(TBitmap, 0x3C);

}
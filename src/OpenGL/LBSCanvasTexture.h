#pragma once
#include "../Common.h"
#include "../Delphi/System.h"
#include "../Delphi/Classes.h"
#include "../Delphi/Graphics.h"
#include "LBSVector.h"
#include "LBSOpenGL12.h"

namespace LBSCanvasTexture
{
    typedef struct TLBSCanvasTexture *PLBSCanvasTexture;
    typedef struct TLBSCanvasTextureEX *PLBSCanvasTextureEX;
    typedef struct TLBSTextRender *PLBSTextRender;

    struct TLBSCanvasTexture : System::TObject
    {
        static VMT_ClassDefinition* Class;

        Graphics::PBitmap FBitmap;
        Pointer LastScnLine;
        Integer SizeScnLine;
        Pointer GLTexture;
        Byte PixelFormat;

        virtual void __fastcall SetDimensions(Word x, Word y);

        static PLBSCanvasTexture __fastcall Create(Pointer, Boolean, Smallint, Smallint, Byte);
        static void __fastcall FixDimension(PLBSCanvasTexture, Smallint*);
        static void __fastcall LoadTexture(PLBSCanvasTexture);
    };
    ASSERT_SIZE(TLBSCanvasTexture, 0x18);

    struct TLBSCanvasTextureEX : TLBSCanvasTexture
    {
        static VMT_ClassDefinition* Class;

        LBSVector::TVector2s Scale;
        Single WidthPerc;
        Single HeightPerc;
        Boolean Changed;

        virtual void __fastcall BindTexture();
    };
    ASSERT_SIZE(TLBSCanvasTextureEX, 0x28);

    /*struct TLBSTextRender : System::TObject
    {
        static VMT_ClassDefinition* Class;
    };
    ASSERT_SIZE(TLBSTextRender, 0x2C);*/
}
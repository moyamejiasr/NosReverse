#pragma once
#include "../Common.h"
#include "../Delphi/System.h"
#include "../Delphi/Classes.h"
#include "../Delphi/Graphics.h"
#include "LBSVector.h"
#include "LBSOpenGL12.h"
#include "LBSCommon.h"

namespace LBSCanvasTexture
{
    typedef struct TLBSCanvasTexture *PLBSCanvasTexture;
    typedef struct TLBSCanvasTextureEx *PLBSCanvasTextureEx;
    typedef struct TLBSTextRender *PLBSTextRender;

    void __fastcall RowTransform(Pointer, Pointer, Integer);

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
        static void __fastcall Destroy(PLBSCanvasTexture, Boolean);
        static void __fastcall FixDimension(PLBSCanvasTexture, Smallint*);
        static void __fastcall _SetDimensions(PLBSCanvasTexture, Smallint, Smallint);
        static void __fastcall LoadTexture(PLBSCanvasTexture);
        static Boolean __fastcall LoadSubTexture(PLBSCanvasTexture);
    };
    ASSERT_SIZE(TLBSCanvasTexture, 0x18);

    struct TLBSCanvasTextureEx : TLBSCanvasTexture
    {
        static VMT_ClassDefinition* Class;

        LBSVector::TVector2s Scale;
        Single WidthPerc;
        Single HeightPerc;
        Boolean Changed;

        virtual void __fastcall BindTexture();

        static PLBSCanvasTextureEx __fastcall Create(Pointer, Boolean, Word, Word, Byte);
        static Boolean __fastcall _BindTexture(PLBSCanvasTextureEx);
        static Graphics::PCanvas __fastcall GetCanvas(PLBSCanvasTextureEx);
        static void __fastcall SetDimensions(PLBSCanvasTextureEx, Smallint, Smallint);
    };
    ASSERT_SIZE(TLBSCanvasTextureEx, 0x28);

    /*struct TLBSTextRender : System::TObject
    {
        static VMT_ClassDefinition* Class;
    };
    ASSERT_SIZE(TLBSTextRender, 0x2C);*/
}
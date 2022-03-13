#pragma once
#include "../Common.h"

typedef void* Pointer;
typedef char Char;
typedef Char *PChar;
typedef const char* Literal;
typedef unsigned char Byte;
typedef bool Boolean;
typedef unsigned short Word;
typedef signed char Shortint;
typedef short Smallint;
typedef int Integer;
typedef unsigned int Cardinal;
typedef long long Int64;
typedef float Single;
typedef double Double;
typedef long double Extended;

typedef char AnsiChar;
typedef AnsiChar* PAnsiChar;
typedef PAnsiChar String;
typedef String* PString;

struct TPoint
{
  Integer X;
  Integer Y;
};

struct TRect
{
    TPoint LeftTop, RightBottom;
};

struct TMethod
{
  Pointer Code;
  Pointer Data;
};

struct VMT_ClassDefinition 
{
	Pointer SelfPtr;
	Pointer IntfTable, AutoTable, InitTable;
	Pointer TypeInfo;
	Pointer FieldTable, MethodTable, DynamicTable;
	Pointer ClassName;
	Integer InstanceSize;
	VMT_ClassDefinition* Parent;
	Pointer SafeCallException;
	Pointer AfterConstruction;
	Pointer BeforeDestruction;
	Pointer Dispatch, DefaultHandler;
	Pointer NewInstance, FreeInstance;
	Pointer Destroy;
};

namespace System
{
    typedef struct TObject *PObject;

	void __fastcall Assert(String, Literal, Integer);
    Integer __fastcall ParamCount();
    void __fastcall ParamStr(Integer, PString);
	void __fastcall LStrClr(PString);
    void __fastcall LStrCopy(String, Integer, Integer, PString);
    void __fastcall LStrCat4(PString, Integer, Pointer, Literal, Literal, Literal);
    Integer __fastcall LStrCmp(String, String);
	PChar __fastcall LStrToPChar(String);

	struct TObject
	{
        static VMT_ClassDefinition* Class;

		static PObject __fastcall Create(Pointer, Boolean);
		static void __fastcall Destroy(PObject, Boolean);
		static void __fastcall Free(PObject);
	};
    ASSERT_SIZE(TObject, 0x01);

	PObject __fastcall ClassCreate(Pointer, Boolean);
	void __fastcall ClassDestroy(Pointer);
	Pointer __fastcall AfterConstruction(PObject);
	void __fastcall BeforeDestruction(PObject, Boolean);

	Pointer __cdecl GetMemory(Integer);
	Integer __cdecl FreeMemory(Pointer);
	Pointer __cdecl ReallocMemory(Pointer, Integer);
};
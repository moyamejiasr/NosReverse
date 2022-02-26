#pragma once
#include "../Common.h"

typedef void* Pointer;
typedef unsigned char Byte;
typedef bool Boolean;
typedef unsigned short Word;
typedef signed char Shortint;
typedef short Smallint;
typedef int Integer;
typedef float Single;

typedef char AnsiChar;
typedef AnsiChar* PAnsiChar;
typedef PAnsiChar String;
typedef String* PString;

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
    Integer __fastcall ParamCount();
    void __fastcall ParamStr(Integer, PString);
    void __fastcall LStrCopy(String, Integer, Integer, PString);
    Integer __fastcall LStrCmp(String, String);

	typedef struct TObject
	{
		static void __fastcall Destroy(TObject*, Boolean);
		static void __fastcall Free(TObject*);
	} *PObject;

	PObject __fastcall ClassCreate(Pointer, Boolean);
	void __fastcall ClassDestroy(Pointer);
	void __fastcall AfterConstruction(PObject);
	void __fastcall BeforeDestruction(PObject, Boolean);
};
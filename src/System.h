#pragma once
#include "Common.h"

typedef int Integer;
typedef int Pointer;
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
    extern Integer(__fastcall* ParamCount)();
    extern void(__fastcall* ParamStr)(Integer, PString);
    extern void(__fastcall* LStrCopy)(String, Integer, Integer, PString);
    extern Integer(__fastcall* LStrCmp)(String, String);
};
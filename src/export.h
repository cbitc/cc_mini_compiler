#pragma once
#include<stdlib.h>
#include"Instructions.h"



typedef enum {
	OBJECT_TYPE_LONG,
	OBJECT_TYPE_BOOLEN,
	OBJECT_TYPE_STR,
	OBJECT_TYPE_NULL,
	OBJECT_TYPE_CODE
}Export_Object_Type;

typedef struct {
	const char* name;
}Export_Name_Type;

typedef struct {
	unsigned short len;
	Export_Name_Type names[1];
}Export_Names;

typedef struct {
	void* data;
	Export_Object_Type type;
}Export_Const_Type;

typedef struct {
	unsigned short len;
	Export_Const_Type consts[1];
}Export_Consts;

typedef struct {
	size_t len;
	int ins[1];
}Export_Instructions;

typedef struct {
	Export_Names* names;
	Export_Consts* consts;
	Export_Instructions* codes;
}Export_CodeObject;


#ifdef __cplusplus
extern "C" {
#endif __cplusplus
	__declspec(dllexport) Export_Names* create_Export_Names(unsigned short maxLen);
	__declspec(dllexport) void insert_Export_Names(Export_Names* names,const char* name);
	__declspec(dllexport) Export_Consts* create_Export_Consts(unsigned short maxLen);
	__declspec(dllexport) void insert_Export_Consts(Export_Consts* consts,void* data,Export_Object_Type type);
	__declspec(dllexport) Export_Instructions* create_Export_Instructions(size_t maxLen);
	__declspec(dllexport) void insert_Export_Instructions(Export_Instructions* instruction,int ins);
	__declspec(dllexport) Export_CodeObject* create_Export_CodeObject(Export_Names* names, Export_Consts* consts, Export_Instructions* codes);
	__declspec(dllexport) void init_environment();
	__declspec(dllexport) void run_with_Export_CodeObject(Export_CodeObject* codeObject);
#ifdef __cplusplus
}
#endif __cplusplus
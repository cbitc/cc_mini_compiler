#include"export.h"
#include<stdio.h>

Export_Names* create_Export_Names(unsigned short maxLen) {
	if (maxLen == 0)return malloc(sizeof(Export_Names));
	Export_Names* names = malloc(sizeof(Export_Names)+(maxLen-1)*sizeof(Export_Name_Type));
	names->len = 0;
	return names;
}


void insert_Export_Names(Export_Names* names, const char* name) {
	unsigned short len = names->len++;
	names->names[len].name = name;
}


Export_Consts* create_Export_Consts(unsigned short maxLen) {
	if (maxLen == 0)return malloc(sizeof(Export_Consts));
	Export_Consts* consts = malloc(sizeof(Export_Consts) + (maxLen - 1) * sizeof(Export_Const_Type));
	consts->len = 0;
	return consts;
}


void insert_Export_Consts(Export_Consts* consts, void* data, Export_Object_Type type) {
	unsigned short cur = consts->len++;
	consts->consts[cur].data = data;
	consts->consts[cur].type = type;

}

Export_Instructions* create_Export_Instructions(size_t maxLen) {
	if (maxLen == 0)return malloc(sizeof(Export_Instructions));
	Export_Instructions* instructions = malloc(sizeof(Export_Instructions)*(maxLen - 1));
	instructions->len = 0;
	return instructions;
}
void insert_Export_Instructions(Export_Instructions* instructions,int ins){
	size_t len = instructions->len++;
	instructions->ins[len] = ins;
}

Export_CodeObject* create_Export_CodeObject(Export_Names* names, Export_Consts* consts, Export_Instructions* codes) {
	Export_CodeObject* codeObject = malloc(sizeof(Export_CodeObject));
	codeObject->names = names;
	codeObject->consts = consts;
	codeObject->codes = codes;
	return codeObject;
}
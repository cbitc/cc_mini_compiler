#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<math.h>
#include"export.h"
#include"Instructions.h"

typedef struct _Object_Type CTypeObject;
typedef struct _Object CObject;
typedef struct _Object_Var CVarObject;

typedef struct _Object_Long CLongObject;
typedef struct _Object_NumberRange CNumberRangeObject;
typedef struct _Object_NumberRangeIterator CNumberRangeIteratorObject;

typedef struct _Object_Str CStrObject;
typedef struct _Object_StrIterator CStrIteratorObject;
typedef struct _Object_List CListObject;
typedef struct _Object_ListIterator CListIteratorObject;
typedef struct _Object_Tuple CTupleObject;
typedef struct _Object_Dict CDictObject;
typedef struct _Object_Set CSetObject;
typedef struct _Object_Code CCodeObject;
typedef struct _Object_Frame CFrameObject;
typedef struct _Object_Function CFunctionObject;


typedef void(*f_print)(CObject*);
typedef unsigned int (*f_hash)(CObject*);
typedef CObject* (*f_call)(CObject* function,CTupleObject* args);
typedef CObject* (*f_new)(CObject* type,CTupleObject* args);
typedef void (*f_dealloc)(CObject*);
typedef void (*f_init)(CObject*,CTupleObject*);
typedef void (*f_destruct)(CObject*);
typedef CObject* (*f_next)(CObject*);
typedef CObject* (*f_binary)(CObject*, CObject*);
typedef CLongObject* (*f_toInt)(CObject*);
typedef CStrObject* (*f_toStr)(CObject*);
typedef CObject* (*f_iterator)(CObject*);
typedef CObject* (*f_item_get)(CObject*, CObject*);
typedef void (*f_item_set)(CObject*, CObject*, CObject*);

void slot_print(CObject*);
CLongObject* slot_hash(CObject*);
CObject* slot_call(CObject*, CTupleObject*);
CObject* slot_new(CObject*, CTupleObject*);
void slot_dealloc(CObject*);
void slot_init(CObject*, CTupleObject*);
void slot_destruct(CObject*);
CLongObject* slot_toInt(CObject*);
CStrObject* slot_toStr(CObject*);
CObject* slot_next(CObject*);
CObject* slot_add(CObject*, CObject*);
CObject* slot_sub(CObject*, CObject*);
CObject* slot_mul(CObject*, CObject*);
CObject* slot_div(CObject*, CObject*);
CObject* slot_equal(CObject*, CObject*);
CObject* slot_gt(CObject*, CObject*);
CObject* slot_lt(CObject*, CObject*);


CDictObject* _buildIn_;

void print_ins(int);

void* CMem_malloc(size_t size) {
	return malloc(size);
}

void CMem_free(void* block) {
	free(block);
}


struct _Object {
	unsigned int ob_refcnt;
	CTypeObject* ob_type;
};

struct _Object_Var {
	struct _Object ob_base;
	unsigned int ob_len;
};

struct _Object_Type {
	CObject ob_base;                    //base
	const char* ob_name;				//name of type
	unsigned int ob_size, item_size;    //memory size of type and memory size of element in varObject
	f_print tp_print;					//function to print self
	f_hash tp_hash;						//function to calculate hash_value
	f_toInt tp_toInt;
	f_toStr tp_toStr;
	f_new tp_new;
	f_init tp_init;
	f_dealloc tp_dealloc;
	f_destruct tp_destruct;
	f_call tp_call;
	f_binary tp_nb_add;
	f_binary tp_nb_sub;
	f_binary tp_nb_mul;
	f_binary tp_nb_div;
	f_binary tp_nb_pow;
	f_binary tp_em_eq;
	f_binary tp_em_gt;
	f_binary tp_em_lt;
	f_iterator tp_iterator;
	f_next tp_em_next;
	f_item_get tp_item_get;
	f_item_set tp_item_set;
	CDictObject* ob_attrs;
};




//declare about virtual function of print
void print_long(CObject*);
void print_boolen(CObject*);
void print_str(CObject*);
void print_null(CObject*);
void print_list(CObject*);
void print_tuple(CObject*);
void print_dict(CObject*);
void print_set(CObject*);
void print_code(CObject*);
void print_frame(CObject*);
void print_function(CObject*);
void print_type(CObject*);

//declare about virtual function of hash
unsigned int hash_long(CObject*);
unsigned int hash_str(CObject*);

//declare about virtual function of add
CObject* binaryAdd_long(CObject*, CObject*);
CObject* binarySub_long(CObject*, CObject*);
CObject* binaryMul_long(CObject*, CObject*);
CObject* binaryDiv_long(CObject*, CObject*);
CObject* binaryPow_long(CObject*, CObject*);
CObject* binaryAdd_str(CObject*, CObject*);
CObject* binaryAdd_list(CObject*, CObject*);
CObject* binaryAdd_tuple(CObject*, CObject*);
CObject* binaryAdd_set(CObject*, CObject*);


//declare about virtual function of equal
CObject* equal_long(CObject*, CObject*);
CObject* equal_boolen(CObject*, CObject*);
CObject* equal_str(CObject*, CObject*);
CObject* equal_list(CObject*, CObject*);
CObject* equal_tuple(CObject*, CObject*);
CObject* equal_null(CObject*, CObject*);

//
CObject* item_get_Str(CObject*, CObject*);
CObject* item_get_List(CObject*, CObject*);
void item_set_List(CObject*, CObject*, CObject*);
CObject* item_get_Tuple(CObject*, CObject*);
CObject* item_get_Dict(CObject*, CObject*);
void item_set_Dict(CObject*, CObject*, CObject*);
CObject* item_get_Set(CObject*, CObject*);
 
//

//declare about virtual function of toInt
CLongObject* toInt_long(CObject*);
CLongObject* toInt_boolen(CObject*);
CLongObject* toInt_str(CObject*);
CLongObject* toInt_list(CObject*);
CLongObject* toInt_tuple(CObject*);

//declare about virtual function of toStr
CStrObject* toStr_long(CObject*);
CStrObject* toStr_str(CObject*);
CStrObject* toStr_boolen(CObject*);

//declare about virtual function of toBoolen



//declare about virtual function of compare
CLongObject* binary_gt_long(CObject*, CObject*);
CLongObject* binary_lt_long(CObject*, CObject*);


//declare about function groups about check
int check_long(CObject*);
int check_boolen(CObject*);
int check_str(CObject*);
int check_list(CObject*);
int check_dict(CObject*);
int check_tuple(CObject*);
int check_set(CObject*);
int check_code(CObject*);
int check_frame(CObject*);
int check_function(CObject*);


//declare about function groups about construction
CLongObject* CLongObject_new(long);
CLongObject* CBoolenObject_new(char);
CStrObject* CStrObject_new(const char*);
CListObject* CListObject_new(unsigned int);
CTupleObject* CTupleObject_new(CListObject*);
CDictObject* CDictObejct_new();
CSetObject* CSetObject_new();
CCodeObject* CCodeObject_new(CListObject*, CListObject*,int*,size_t);
CFrameObject* CFrameObject_new(CCodeObject*,CDictObject*);
CFunctionObject* CFunctionObject_new(CCodeObject*,CDictObject*);


CObject* type_new_long(CObject* type, CTupleObject* args);
CObject* type_new_str(CObject* type, CTupleObject* args);
CObject* type_new_list(CObject* type, CTupleObject* args);
CObject* type_new_tuple(CObject* type, CTupleObject* args);
CObject* type_new_dict(CObject* type, CTupleObject* args);
CObject* type_new_set(CObject* type, CTupleObject* args);


//declare about function 
CObject* CObject_binary_Arit(CObject*,CObject*,unsigned char);
CObject* CObject_binary_Compare(CObject*, CObject*, unsigned char);
CObject* CGetAttr(CObject*, CStrObject*);
void CSetAttr(CObject*, CStrObject*,CObject*);
CObject* judge_object(CObject* object);
void printObject(CObject*);

CObject* type_call_CAPI(CObject*, CTupleObject*);
CObject* type_call_function(CObject*, CTupleObject*);
CObject* type_call_new(CObject*, CTupleObject*);


CTypeObject* create_type(CStrObject*, CDictObject*);
CObject* type_new(CObject*, CTupleObject*);
void type_init(CObject*, CTupleObject*);
CObject* metaType_new(CObject*, CTupleObject*);
void fill_methods(CTypeObject*, CDictObject*);

//TypeObject


CTypeObject TypeObject_Type = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "type",
	.ob_size = sizeof(CTypeObject),
	.tp_print = print_type,
	.tp_new = metaType_new,
	.tp_call = type_call_new,
	.ob_attrs = NULL
};

//NullObject

typedef struct _Object_Null {
	CObject ob_base;
}CNullObject;




CTypeObject TypeObject_None = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "null",
	.ob_size = sizeof(CNullObject),
	.tp_print = print_null,
	.tp_em_eq = equal_null,
};

CNullObject None = {
	{1,&TypeObject_None}
};


//LongObject

typedef struct _Object_Long{
	CObject ob_base;
	long ob_value;
}CLongObject;



CTypeObject TypeObject_Long = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "int",
	.ob_size = sizeof(CLongObject),
	.tp_print = print_long,
	.tp_hash = hash_long,
	.tp_new = type_new_long,
	.tp_call = type_call_new,
	.tp_dealloc = NULL,
	.tp_init = type_init,
	.tp_destruct = NULL,
	.tp_nb_add = binaryAdd_long,
	.tp_nb_sub = binarySub_long,
	.tp_nb_mul = binaryMul_long,
	.tp_nb_div = binaryDiv_long,
	.tp_nb_pow = binaryPow_long,
	.tp_em_eq = equal_long,
	.tp_em_gt = binary_gt_long,
	.tp_em_lt = binary_lt_long,
	.tp_toInt = toInt_long,
	.tp_toStr = toStr_long,
	.ob_attrs = NULL,
};



CLongObject* CLongObject_new(long value) {
	CLongObject* res = CMem_malloc(sizeof(CLongObject));
	CTypeObject* type = &TypeObject_Long;
	CObject base = { 1,type };
	res->ob_base = base;
	res->ob_value = value;
	return res;
}


//..............



//CNumberRangeObject

CObject* CNumberRangeObject_getIter(CObject* this);
CNumberRangeIteratorObject* CNumberRangeIteratorObject_new(CNumberRangeObject* range);
CObject* CNumberRangeIteratorObject_next(CObject* this);


typedef struct _Object_NumberRange {
	CObject ob_base;
	long begin, end, step;
}CNumberRangeObject;

CTypeObject TypeObject_NumberRange = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "numberRange",
	.ob_size = sizeof(CNumberRangeObject),
	.tp_iterator = CNumberRangeObject_getIter
};

CNumberRangeObject* CNumberRangeObject_new(long begin, long end,long step) {
	CNumberRangeObject* range = CMem_malloc(sizeof(CNumberRangeObject));
	range->ob_base.ob_refcnt = 1;
	range->ob_base.ob_type = &TypeObject_NumberRange;
	range->begin = begin;
	range->end = end;
	range->step = step;
	return range;
}

CObject* CNumberRangeObject_getIter(CObject* this){
	CNumberRangeObject* range = (CNumberRangeObject*)this;
	return CNumberRangeIteratorObject_new(range);
}


typedef struct _Object_NumberRangeIterator {
	CObject ob_base;
	long curNumber;
	CNumberRangeObject* numberRange;
}CNumberRangeIteratorObject;


CTypeObject TypeObject_NumberRangeIterator = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "numerRangeIterator",
	.ob_size = sizeof(CNumberRangeObject),
	.tp_em_next = CNumberRangeIteratorObject_next,
};

CNumberRangeIteratorObject* CNumberRangeIteratorObject_new(CNumberRangeObject* range) {
	CNumberRangeIteratorObject* iter = CMem_malloc(sizeof(CNumberRangeIteratorObject));
	iter->ob_base.ob_refcnt = 1;
	iter->ob_base.ob_type = &TypeObject_NumberRangeIterator;
	iter->numberRange = range;
	iter->curNumber = range->begin;
	return iter;
}

CObject* CNumberRangeIteratorObject_next(CObject* this) {
	CNumberRangeIteratorObject* iterator = (CNumberRangeIteratorObject*)this;
	if (iterator->curNumber >= iterator->numberRange->end) { return &None; }
	CLongObject* value = CLongObject_new(iterator->curNumber);
	iterator->curNumber += iterator->numberRange->step;
	return value;
}

//.................


//boolen


CTypeObject TypeObject_Boolen = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "boolen",
	.ob_size = sizeof(CLongObject),
	.tp_print = print_boolen,
	.tp_dealloc = NULL,
	.tp_init = type_init,
	.tp_destruct = NULL,
	.tp_call = type_call_new,
	.tp_em_eq = equal_boolen,
	.tp_toInt = toInt_boolen,
	.tp_toStr = toStr_boolen,
	.ob_attrs = NULL
};

CLongObject True = {
	{1,&TypeObject_Boolen},
	1
};

CLongObject False = {
	{1,&TypeObject_Boolen},
	0
};

CLongObject* CBoolenObject_new(char value) {
	return value ? &True : &False;
}

//.....



//StrObject


CObject* CStrObject_getIter(CObject* this);
CObject* CStrIteratorObject_next(CObject* this);
CStrIteratorObject* CStrIteratorObject_new(CStrObject* string);


typedef struct _Object_Str{
	CVarObject ob_base;
	char ob_value[1];
}CStrObject;


CTypeObject TypeObject_Str = {
	.ob_base = {1,&TypeObject_Type},				
	.ob_name = "str",								
	.ob_size = sizeof(CStrObject),					
	.item_size = sizeof(char),						
	.tp_print = print_str,							
	.tp_hash = hash_str,							
	.tp_new = type_new_str,
	.tp_dealloc = NULL,
	.tp_init = type_init,
	.tp_destruct = NULL,
	.tp_call = type_call_new,
	.tp_nb_add = binaryAdd_str,
	.tp_em_eq = equal_str,
	.tp_iterator = CStrObject_getIter,
	.tp_item_get = item_get_Str,
	.tp_toInt = toInt_str,
	.tp_toStr = toStr_str,
	.ob_attrs = NULL
};

CStrObject* CStrObject_new(const char* str) {
	size_t len = strlen(str);
	CStrObject* res = (CStrObject*)CMem_malloc(sizeof(CStrObject) + len);
	memcpy(res->ob_value, str, len + 1);
	res->ob_base.ob_base.ob_refcnt = 1;
	res->ob_base.ob_base.ob_type = &TypeObject_Str;
	res->ob_base.ob_len = len;
	return res;
}

char* CStrObject_getCstr(CStrObject* object) {
	return object->ob_value;
}

char CStrObject_getItem(CStrObject* object,unsigned int index) {
	return object->ob_value[index];
}

CObject* CStrObject_getIter(CObject* this) {
	CStrObject* str = (CStrObject*)this;
	return CStrIteratorObject_new(str);
}


//...........

//CStrIteratorObject


typedef struct _Object_StrIterator {
	CObject ob_base;
	unsigned int index;
	CStrObject* string;
}CStrIteratorObject;

CTypeObject TypeObject_StrIterator = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "strIterator",
	.ob_size = sizeof(CStrIteratorObject),
	.tp_em_next = CStrIteratorObject_next,
};


CObject* CStrIteratorObject_next(CObject* this) {
	CStrIteratorObject* iter = (CStrIteratorObject*)this;
	if (iter->index == iter->string->ob_base.ob_len) { return &None; }
	char buffer[2];
	sprintf(buffer, "%c", CStrObject_getItem(iter->string, iter->index));
	return CStrObject_new(buffer);
}

CStrIteratorObject* CStrIteratorObject_new(CStrObject* string) {
	CStrIteratorObject* iter = CMem_malloc(sizeof(CStrIteratorObject));
	iter->ob_base.ob_refcnt = 1;
	iter->ob_base.ob_type = &TypeObject_StrIterator;
	iter->string = string;
	iter->index = 0;
	return iter;
}

//..................



//ListObject
CListIteratorObject* listIterator_new(CListObject* list);
CObject* listIterator_next(CObject* iterator);
CObject* CListObject_getIterator(CObject* list);

typedef struct _Object_List{
	CVarObject ob_base;
	CObject** ob_item;
	unsigned int allocate;
}CListObject;


CTypeObject TypeObject_List = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "list",
	.ob_size = sizeof(CListObject),
	.item_size = sizeof(CObject*),
	.tp_print = print_list,
	.tp_dealloc = NULL,
	.tp_destruct = NULL,
	.tp_nb_add = binaryAdd_list,
	.tp_iterator = CListObject_getIterator,
	.tp_item_get = item_get_List,
	.tp_item_set = item_set_List,
	.tp_toInt = toInt_list,
	.ob_attrs = NULL
};

CListObject* CListObject_new(unsigned int size) {
	CListObject* res = CMem_malloc(sizeof(CListObject));
	res->ob_base.ob_base.ob_refcnt = 1;
	res->ob_base.ob_base.ob_type = &TypeObject_List;
	res->ob_base.ob_len = size;
	res->allocate = size ? 2 * size : 1;
	res->ob_item = CMem_malloc(res->allocate * sizeof(CObject*));
	memset(res->ob_item, 0, res->allocate * sizeof(CObject*));
	return res;
}

void CListObject_realloc(CListObject* list) {
	unsigned int curSize = list->ob_base.ob_len;
	list->allocate = 2 * curSize;
	CObject** newItem = CMem_malloc(list->allocate * sizeof(CObject*));
	memset(newItem, 0, list->allocate * sizeof(CObject*));
	memcpy(newItem, list->ob_item, curSize * sizeof(CObject*));
	CMem_free(list->ob_item);
	list->ob_item = newItem;
}

void CListObject_append(CListObject* list, CObject* object) {
	if (list->ob_base.ob_len == list->allocate) {
		CListObject_realloc(list);
	}
	list->ob_item[list->ob_base.ob_len++] = object;
}

CObject* CListObject_pop(CListObject* list) {
	return list->ob_item[--list->ob_base.ob_len];
}

void CListObject_insert(CListObject* list, unsigned int index, CObject* object) {
	if (index >= list->ob_base.ob_len) {}
	if (list->ob_base.ob_len == list->allocate) {
		CListObject_realloc(list);
	}
	for (int i = list->ob_base.ob_len - 1; i >= index; i--) {
		list->ob_item[i + 1] = list->ob_item[i];
	}
	list->ob_item[index] = object;
	list->ob_base.ob_len++;
}

CObject* CListObject_erase(CListObject* list, unsigned int index) {
	CObject* target = list->ob_item[index];
	for (unsigned int i = index; i < list->ob_base.ob_len - 1; i++) {
		list->ob_item[i] = list->ob_item[i + 1];
	}
	list->ob_base.ob_len--;
	return target;
}

CObject* CListObject_getItem(CListObject* list, unsigned int index) {
	assert(index < list->ob_base.ob_len);
	return list->ob_item[index];
}

void CListObject_setItem(CListObject* list, unsigned int index,CObject* value) {
	assert(index < list->ob_base.ob_len);
	list->ob_item[index] = value;
	return;
}

CLongObject* CListObject_getSize(CListObject* list) {
	return CLongObject_new(list->ob_base.ob_len);
}

CObject* CListObject_getIterator(CObject* list) {
	CListObject* self = (CListObject*)list;
	return listIterator_new(self);
}

//.................


//CListIteratorObject


typedef struct _Object_ListIterator {
	CObject ob_base;
	unsigned int index;
	CListObject* list;
}CListIteratorObject;

CTypeObject TypeObject_ListIterator = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "iterator_list",
	.ob_size = sizeof(CListIteratorObject),
	.tp_em_next = listIterator_next,
	.ob_attrs = NULL
};

CListIteratorObject* listIterator_new(CListObject* list) {
	CListIteratorObject* iter = CMem_malloc(sizeof(CListIteratorObject));
	iter->ob_base.ob_refcnt = 1;
	iter->ob_base.ob_type = &TypeObject_ListIterator;
	iter->list = list;
	iter->index = 0;
	return iter;
}

CObject* listIterator_next(CObject* iterator) {
	CListIteratorObject* it = (CListIteratorObject*)iterator;
	if (it->index == it->list->ob_base.ob_len) { return &None; }
	CObject* cur = CListObject_getItem(it->list, it->index++);
	return cur;
}

//..............


//TupleObject

typedef struct _Object_Tuple{
	CVarObject ob_base;
	CObject* ob_item[1];

}CTupleObject;




CTypeObject TypeObject_Tuple = {
	.ob_base = {1,&TypeObject_Type},				
	.ob_name = "tuple",							
	.ob_size = sizeof(CTupleObject),				
	.item_size = sizeof(CObject*),					
	.tp_print = print_tuple,						
	.tp_new = type_new_tuple,
	.tp_dealloc = NULL,
	.tp_init = type_init,
	.tp_destruct = NULL,
	.tp_call = type_call_new,
	.tp_nb_add = binaryAdd_tuple,
	.tp_item_get = item_get_Tuple,
	.tp_toInt = toInt_tuple,
	.ob_attrs = NULL
};

CTupleObject* CTupleObject_new(CListObject* list) {
	if (list == NULL)return NULL;
	size_t len = list->ob_base.ob_len;
	CTupleObject* tuple = CMem_malloc(sizeof(CTupleObject) + (len - 1) * sizeof(CObject*));
	memset(tuple, 0, sizeof(CTupleObject) + (len - 1) * sizeof(CObject*));
	tuple->ob_base.ob_base.ob_refcnt = 1;
	tuple->ob_base.ob_base.ob_type = &TypeObject_Tuple;
	tuple->ob_base.ob_len = len;
	memcpy(tuple->ob_item, list->ob_item, len * sizeof(CObject*));
	return tuple;
}

CObject* CTupleObject_getItem(CTupleObject* tuple, unsigned int index) {
	if (index >= tuple->ob_base.ob_len) { assert(0); }
	return tuple->ob_item[index];
}


CLongObject* CTupleObject_getSize(CTupleObject* tuple) {
	return CLongObject_new(tuple->ob_base.ob_len);
}
//..............




//DictObject

#define SMALLTABLE_SIZE 8

typedef struct {
	CObject* key;
	CObject* value;
}CDictEntry;

void CDictEntry_construct(CDictEntry* this, CObject* key, CObject* value) {
	this->key = key;
	this->value = value;
}

typedef struct _Object_Dict {
	CVarObject ob_base;
	CDictEntry* table;
	unsigned int allocate;
	CDictEntry smallTable[SMALLTABLE_SIZE];
}CDictObject;



CTypeObject TypeObject_Dict = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "dict",
	.ob_size = sizeof(CDictObject),
	.item_size = sizeof(CDictEntry),
	.tp_print = print_dict,
	.tp_new = type_new_dict,
	.tp_dealloc = NULL,
	.tp_init = type_init,
	.tp_destruct = NULL,
	.tp_call = type_call_new,
	.tp_item_get = item_get_Dict,
	.tp_item_set = item_set_Dict,
	.ob_attrs = NULL
};

typedef struct {
	CObject ob_base;
}CDictDumy;

CTypeObject TypeObject_Dummy = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "dummy",
	.ob_size = sizeof(CDictDumy),
	.item_size = 0,
	.tp_print = NULL,
	.tp_hash = NULL,
	.tp_new = NULL,
	.tp_dealloc = NULL,
	.tp_init = NULL,
	.tp_destruct = NULL,
	.tp_call = NULL,
	.ob_attrs = NULL
};

CDictDumy Dummy = {
	1,
	&TypeObject_Dummy
};

CDictObject* CDictObejct_new() {
	CDictObject* dict = CMem_malloc(sizeof(CDictObject));
	dict->ob_base.ob_base.ob_refcnt = 1;
	dict->ob_base.ob_base.ob_type = &TypeObject_Dict;
	dict->ob_base.ob_len = 0;
	dict->allocate = SMALLTABLE_SIZE;
	memset(dict->smallTable, 0, SMALLTABLE_SIZE * sizeof(CDictEntry));
	dict->table = dict->smallTable;
	return dict;
}

void CDictObject_insert(CDictObject* this, CObject* key, CObject* value);

CDictEntry* CDictObject_find(CDictObject* this, CObject* key) {
	if (key->ob_type->tp_hash == NULL) { assert(0); }
	unsigned int hashcode = key->ob_type->tp_hash(key);
	unsigned int index = hashcode % this->allocate;
	for (int i = 0;i<this->allocate;i++,index++) {
		index = index % this->allocate;
		CObject* tableKey = this->table[index].key;
		if (tableKey == NULL) {
			break;
		}
		else if (tableKey->ob_type->tp_em_eq(tableKey, key) == &True) {
			return &(this->table[index]);
		}
	}
	return NULL;
}

void CDictObject_hasing(CDictEntry* table,unsigned int alloca,CObject* key,CObject* value) {
	if (key->ob_type->tp_hash == NULL) { assert(0); }
	unsigned int index = key->ob_type->tp_hash(key) % alloca;
	for (;; index++) {
		index = index % alloca;
		CObject* tableKey = table[index].key;
		if (tableKey == NULL || tableKey == &Dummy) {
			break;
		}
	}
	table[index].key = key;
	table[index].value = value;
}

void CDictObject_realloc(CDictObject* this) {
	unsigned int size = this->ob_base.ob_len;
	this->allocate = 2 * this->allocate;
	CDictEntry* newbuf = CMem_malloc(sizeof(CDictEntry) * this->allocate);
	memset(newbuf, 0,sizeof(CDictEntry) * this->allocate);
	for (int i = 0; i < size; i++) {
		if (this->table[i].key == NULL || this->table[i].key == &Dummy) {
			continue;
		}
		CObject* tkey = this->table[i].key;
		CObject* tvalue = this->table[i].value;
		CDictObject_hasing(newbuf,this->allocate,tkey, tvalue);
	}

	if (this->table != this->smallTable) {
		CMem_free(this->table);
	}
	this->table = newbuf;
}

void CDictObject_insert(CDictObject* this, CObject* key, CObject* value) {
	if (key->ob_type->tp_hash == NULL) { assert(0); }
	CDictEntry* entry = CDictObject_find(this, key);
	if (entry) {
		entry->value = value;
		return;
	}
	if (this->allocate == this->ob_base.ob_len) {
		CDictObject_realloc(this);
	}
	CDictObject_hasing(this->table, this->allocate, key, value);
	this->ob_base.ob_len++;
	return;
}

void CDictObject_erase(CDictObject* this, CObject* key) {
	CDictEntry* entry = CDictObject_find(this, key);
	if (entry == NULL) {
		return;
	}
	entry->key = &Dummy;
	entry->value = NULL;
	this->ob_base.ob_len--;
}

unsigned int DJBHash(char* str){
	unsigned int hash = 5381;

	while (*str)
	{
		hash += (hash << 5) + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

//.....................




//SetObject

typedef struct _Object_Set{
	CVarObject ob_base;
	unsigned int alloca;
	CObject** table;
}CSetObject;

CTypeObject TypeObject_Set = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "set",
	.ob_size = sizeof(CSetObject),
	.item_size = sizeof(CObject*),
	.tp_print = print_set,
	.tp_new = type_new_set,
	.tp_dealloc = NULL,
	.tp_init = type_init,
	.tp_destruct = NULL,
	.tp_call = type_call_new,
	.tp_nb_add = binaryAdd_set,
	.tp_item_get = item_get_Set,
	.ob_attrs = NULL
};

CSetObject* CSetObject_new() {
	CSetObject* set = CMem_malloc(sizeof(CSetObject));
	set->ob_base.ob_base.ob_refcnt = 1;
	set->ob_base.ob_base.ob_type = &TypeObject_Set;
	set->ob_base.ob_len = 0;
	set->alloca = 4;
	set->table = CMem_malloc(sizeof(CObject*) * set->alloca);
	memset(set->table, 0,sizeof(CObject*) * set->alloca);
	return set;
}

CObject** CSetObject_find(CSetObject* this, CObject* key) {
	if (key->ob_type->tp_hash == NULL) { assert(0); }
	unsigned int index = key->ob_type->tp_hash(key) % this->alloca;
	for (int i = 0; i < this->alloca; i++, index++) {
		index = index % this->alloca;
		CObject* tableKey = this->table[index];
		if (tableKey == NULL) {
			break;
		}
		else if (tableKey->ob_type->tp_em_eq(tableKey, key) == &True) {
			return &(this->table[index]);
		}
	}
	return NULL;
}

void CSetObject_hasing(CObject** table,unsigned int alloca ,CObject* value) {
	if (value->ob_type->tp_hash == NULL) { assert(0); }
	unsigned int index = value->ob_type->tp_hash(value) % alloca;
	for (;; index++) {
		index = index % alloca;
		if (table[index] == NULL || table[index] == &Dummy) {
			break;
		}
	}
	table[index] = value;
}

void CSetObject_realloc(CSetObject* this) {
	this->alloca = 2 * this->alloca;
	CObject** newbuf = CMem_malloc(sizeof(CObject*) * this->alloca);
	memset(newbuf, 0, sizeof(CObject*) * this->alloca);
	for (unsigned int i = 0; i < this->ob_base.ob_len; i++) {
		CSetObject_hasing(newbuf, this->alloca, this->table[i]);
	}
	CMem_free(this->table);
	this->table = newbuf;
}

int CSetObject_insert(CSetObject* this, CObject* value) {
	if (CSetObject_find(this, value)) { return 0; }

	if (this->alloca == this->ob_base.ob_len) {
		CSetObject_realloc(this);
	}
	CSetObject_hasing(this->table, this->alloca, value);
	this->ob_base.ob_len++;
	return 1;
}

void CSetObject_erase(CSetObject* this, CObject* key) {
	CObject** target = CSetObject_find(this, key);
	if (target == NULL) { return; }
	(*target) = &Dummy;
	this->ob_base.ob_len--;
}

//...............





//FunctionObject

typedef struct _Object_Function{
	CObject ob_base;
	CDictObject* f_global;
	CCodeObject* f_code;

}CFunctionObject;

CTypeObject TypeObject_Funciton = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "function",
	.ob_size = sizeof(CFunctionObject),
	.item_size = 0,
	.tp_print = print_function,
	.tp_hash = NULL,
	.tp_new = type_new,
	.tp_dealloc = NULL,
	.tp_init = NULL,
	.tp_destruct = NULL,
	.tp_call = type_call_function,
	.ob_attrs = NULL
};

CFunctionObject* CFunctionObject_new(CCodeObject* code, CDictObject* global) {
	CFunctionObject* function = CMem_malloc(sizeof(CFunctionObject));
	function->ob_base.ob_refcnt = 1;
	function->ob_base.ob_type = &TypeObject_Funciton;
	function->f_global = global;
	function->f_code = code;
	return function;
}


//...............






//CCodeObject

typedef struct _Object_Code{
	CVarObject ob_base;
	CTupleObject* co_consts;
	CTupleObject* co_names;
	int co_code[1];
}CCodeObject;

CTypeObject TypeObject_Code = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "code",
	.ob_size = sizeof(CCodeObject),
	.item_size = sizeof(int),
	.tp_print = print_code,
	.tp_hash = NULL,
	.tp_new = NULL,
	.tp_dealloc = NULL,
	.tp_init = NULL,
	.tp_destruct = NULL,
	.tp_call = NULL,
	.ob_attrs = NULL
};

CCodeObject* CCodeObject_new(CListObject* names, CListObject* consts,int* codes,size_t len) {
	CCodeObject* this = CMem_malloc(sizeof(CCodeObject) + sizeof(int) * (len - 1));
	this->ob_base.ob_base.ob_refcnt = 1;
	this->ob_base.ob_base.ob_type = &TypeObject_Code;
	this->ob_base.ob_len = len;
	this->co_names = CTupleObject_new(names);
	this->co_consts = CTupleObject_new(consts);
	memcpy(this->co_code, codes, sizeof(int) * len);
	return this;
}

//.............


//CCAPIObject

typedef CObject* (*f_CAPI)(CTupleObject*);

typedef struct {
	CObject ob_base;
	f_CAPI function;
}CCAPIObject;

CTypeObject TypeObject_CAPI = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "cAPI",
	.ob_size = sizeof(CCAPIObject),
	.item_size = 0,
	.tp_print = print_function,
	.tp_hash = NULL,
	.tp_new = NULL,
	.tp_dealloc = NULL,
	.tp_init = NULL,
	.tp_destruct = NULL,
	.tp_call = type_call_CAPI,
	.ob_attrs = NULL
};

CCAPIObject* CCAPIObject_new(f_CAPI function){
	CCAPIObject* result = CMem_malloc(sizeof(CCAPIObject));
	result->ob_base.ob_refcnt = 1;
	result->ob_base.ob_type = &TypeObject_CAPI;
	result->function = function;
	return result;
}

//...................

//
typedef struct _Object_Error_ {
	CObject ob_base;
	
}CErrorObject;

CTypeObject Typeobect_Error = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "error",
	.ob_size = sizeof(CErrorObject),
	.ob_attrs = NULL
};


//
//CFrameObject

#define DATASTACK_SIZE 64

typedef struct _Object_Frame {
	CObject ob_base;
	struct _Object_Frame* pre;
	CCodeObject* codes;
	CDictObject* local;
	CDictObject* global;
	CDictObject* buildin;
	CObject* dataStack_small[DATASTACK_SIZE];
	CObject** dataStack;
	int dataStack_top;
}CFrameObject;

CTypeObject CTypeObject_Frame = {
	.ob_base = {1,&TypeObject_Type},
	.ob_name = "frame",
	.ob_size = sizeof(CFrameObject),
	.item_size = 0,
	.tp_print = print_frame,
	.tp_hash = NULL,
	.tp_new = type_new,
	.tp_dealloc = NULL,
	.tp_init = NULL,
	.tp_destruct = NULL,
	.tp_call = NULL,
	.ob_attrs = NULL
};

CFrameObject* CFrameObject_new(CCodeObject* codes,CDictObject* global) {
	CFrameObject* frame = CMem_malloc(sizeof(CFrameObject));
	memset(frame, 0, sizeof(CFrameObject));
	frame->ob_base.ob_refcnt = 1;
	frame->ob_base.ob_type = &CTypeObject_Frame;
	frame->codes = codes;
	frame->global = global;
	frame->local = frame->global;
	frame->buildin = _buildIn_;
	frame->dataStack = frame->dataStack_small;
	frame->dataStack_top = -1;
	return frame;
}


CObject* CFrameObject_execute(CFrameObject* frame) {
	CCodeObject* codes = frame->codes;
	CObject* result = NULL;
	int cur = -1;
	int next = 0;
	int end = codes->ob_base.ob_len;
	CObject** dataStack = frame->dataStack;
	for (; next < end; ++next) {
		cur = next;
		int ins = codes->co_code[cur];
		unsigned short opCode = GET_OPCODE(ins);
		//print_ins(ins);
		switch (opCode)
		{
		case CCODE_END:
			break;
		case CCODE_NONE:
			break;
		case STACK_POP:
			--frame->dataStack_top;
			break;
		case LOAD_CONST:
		{
			unsigned short id = GET_OPNUM(ins);
			CObject* object = CTupleObject_getItem(codes->co_consts, id);
			++frame->dataStack_top;
			dataStack[frame->dataStack_top] = object;
			break;
		}
		case LOAD_NAME:
		{
			unsigned short id = GET_OPNUM(ins);
			CObject* key = CTupleObject_getItem(codes->co_names, id);
			CDictEntry* entry = CDictObject_find(frame->local, key);
			if (entry == NULL) {
				entry = CDictObject_find(frame->global, key);
				if (entry == NULL) {
					entry = CDictObject_find(frame->buildin, key);
					if (entry == NULL) { assert(0); }
				}
			}
			dataStack[++frame->dataStack_top] = entry->value;
			break;
		}
		case LOAD_LOCALS:
		{
			dataStack[++frame->dataStack_top] = frame->local;
			break;
		}
		case LOAD_ATTR:
		{
			unsigned short item = GET_OPNUM(ins);
			CObject* self = dataStack[frame->dataStack_top--];
			CStrObject* attr_name = CTupleObject_getItem(codes->co_names, item);
			CObject* attr = CGetAttr(self, attr_name);
			dataStack[++frame->dataStack_top] = attr;
			break;
		}

		case STORE_NAME:
		{
			unsigned short id = GET_OPNUM(ins);
			CObject* value = dataStack[frame->dataStack_top--];
			CObject* key = CTupleObject_getItem(codes->co_names, id);
			CDictObject_insert(frame->local, key, value);
			break;
		}
		case STORE_ATTR:
		{
			unsigned short item = GET_OPNUM(ins);
			CObject* self = dataStack[frame->dataStack_top--];
			CObject* value = dataStack[frame->dataStack_top--];
			CStrObject* attr_name = CTupleObject_getItem(codes->co_names, item);
			CSetAttr(self, attr_name, value);
			break;
		}
		case JUMP_IF_RELAIVE:
		{
			CObject* b = dataStack[frame->dataStack_top--];
			if (judge_object(b) == &False) {
				unsigned short dist = GET_OPNUM(ins);
				next += dist - 1;
			}
			break;
		}
		
		case JUMP_IF_ABSOLUTE:
		{
			CObject* b = dataStack[frame->dataStack_top--];
			if (judge_object(b) == &False) {
				unsigned short dist = GET_OPNUM(ins);
				next = dist - 1;
			}
			break;
		}
		case JUMP_RELATIVE:
		{
			unsigned short dist = GET_OPNUM(ins);
			next += dist - 1;
			break;
		}
		case JUMP_ABSOLUTE:
		{
			unsigned short dist = GET_OPNUM(ins);
			next = dist - 1;
			break;
		}
		case BINARY_COMP:
		{
			unsigned char id = GET_OPNUM(ins);
			CObject* right = dataStack[frame->dataStack_top--];
			CObject* left = dataStack[frame->dataStack_top];
			CObject* res = CObject_binary_Compare(left, right, id);
			assert(res);
			dataStack[frame->dataStack_top] = res;
			break;
		}
		case BINARY_ARIT:
		{
			unsigned char id = GET_OPNUM(ins);
			CObject* right = dataStack[frame->dataStack_top--];
			CObject* left = dataStack[frame->dataStack_top];
			CObject* res = CObject_binary_Arit(left, right, id);
			assert(res);
			dataStack[frame->dataStack_top] = res;
			break;
		}
		case LOGICAL_AND:
		{
			unsigned short dist = GET_OPNUM(ins);
			CObject* value = dataStack[frame->dataStack_top--];
			if (judge_object(value) == &False) {
				dataStack[++frame->dataStack_top] = &False;
				next += dist - 1;
			}
			break;
		}
		case LOGICAL_OR:
		{
			unsigned short dist = GET_OPNUM(ins);
			CObject* value = dataStack[frame->dataStack_top--];
			if (judge_object(value) == &True) {
				dataStack[++frame->dataStack_top] = &True;
				next += dist - 1;
			}
			break;
		}
		case LOGICAL_NOT: 
		{
			CObject* value = dataStack[frame->dataStack_top--];
			dataStack[++frame->dataStack_top] = judge_object(value) == &True ? &False : &True;
			break;
		}

		case GET_ITER:
		{
			CObject* object = dataStack[frame->dataStack_top--];
			CObject* iter = object->ob_type->tp_iterator(object);
			dataStack[++frame->dataStack_top] = iter;
			break;
		}
		case NEXT_ITER:
		{
			CObject* iter = dataStack[frame->dataStack_top];
			CObject* value = iter->ob_type->tp_em_next(iter);
			if (value == &None) {
				unsigned short dist = GET_OPNUM(ins);
				next += dist - 1;
			}
			else {
				dataStack[++frame->dataStack_top] = value;
			}
			break;
		}
		case ITEM_GET:
		{
			
			CObject* sub = dataStack[frame->dataStack_top--];
			CObject* object = dataStack[frame->dataStack_top];
			assert(object->ob_type->tp_item_get);
			CObject* value = object->ob_type->tp_item_get(object, sub);
			dataStack[frame->dataStack_top] = value;
			break;
		}
		case ITEM_SET:
		{
			CObject* sub = dataStack[frame->dataStack_top--];
			CObject* object = dataStack[frame->dataStack_top--];
			CObject* value = dataStack[frame->dataStack_top--];
			assert(object->ob_type->tp_item_set);
			object->ob_type->tp_item_set(object, sub, value);
			break;
		}
		case MAKE_FUNCTION:
		{
			CCodeObject* codes = (CCodeObject*)dataStack[frame->dataStack_top--];
			CFunctionObject* function = (CFunctionObject*)CFunctionObject_new(codes, frame->global);
			dataStack[++frame->dataStack_top] = function;
			break;
		}
		case CALL_FUNCTION:
		{
			unsigned short n = GET_OPNUM(ins);
			int curTop = frame->dataStack_top;
			CObject** pStack_top = frame->dataStack + frame->dataStack_top;
			CObject* caller = *(pStack_top - n);

			CListObject* args_list = CListObject_new(0);
			for (unsigned short i = 1; i <= n; i++) {
				CObject* value = *(pStack_top - n + i);
				CListObject_append(args_list, value);
			}
			CTupleObject* args_tuple = CTupleObject_new(args_list);

			CObject* res = caller->ob_type->tp_call(caller, args_tuple);

			frame->dataStack_top = curTop;
			frame->dataStack_top -= n + 1;
			if(res)frame->dataStack[++frame->dataStack_top] = res;
			break;
		}
		case MAKE_CLASS:
		{
			CDictObject* attrs = (CDictObject*)dataStack[frame->dataStack_top--];
			CStrObject* className = (CStrObject*)dataStack[frame->dataStack_top--];
			CTypeObject* type = create_type(className, attrs);
			dataStack[++frame->dataStack_top] = type;
			break;
		}
		case MAKE_LIST:
		{
			unsigned short n = GET_OPNUM(ins);
			CListObject* list = CListObject_new(0);
			for (unsigned short i = 1; i <= n; i++) {
				CObject* value = dataStack[frame->dataStack_top - n + i];
				CListObject_append(list, value);
			}
			frame->dataStack_top -= n;
			dataStack[++frame->dataStack_top] = list;
			break;
		}
		case RETURN_TOP:
		{
			result = dataStack[frame->dataStack_top--];
			next = end;
			break;
		}
		default:
			break;
		}
		/*
		printf("\n----------STACK---------\n");
		for (unsigned char i = 0; i < frame->dataStack_top + 1; i++) {
			CObject* object = dataStack[i];
			printObject(object); printf(" ");
		}
		printf("\n----------STACK---------\n\n");
		*/
		//printf("local: "); print_dict(frame->local);  printf("\n");
		//printf("global: "); print_dict(frame->global); printf("\n\n");
		
	}
	return result;
}


//......................


//slotFunction

typedef struct {
	char* name;
	size_t offset;
	void* slot_function;
}SlotFunction;

//..............



//implementation about virtual function of print


void print_long(CObject* ob_int) {
	printf("%d", ((CLongObject*)ob_int)->ob_value);
}

void print_boolen(CObject* object) {
	if (object == &True) {
		printf("True");
	}
	else if (object == &False) {
		printf("False");
	}
	else {
		assert(0);
	}
}

void print_str(CObject* str) {
	printf("%s", ((CStrObject*)str)->ob_value);
}

void print_null(CObject* object) {
	printf("none");
}

void print_list(CObject* object) {
	printf("[");
	CListObject* list = (CListObject*)object;
	for (unsigned int i = 0; i < list->ob_base.ob_len; i++) {
		CObject* obj = list->ob_item[i];
		if (obj == NULL) { printf("null,"); continue; }
		printObject(obj);
		printf(",");
	}
	printf("]");
}

void print_tuple(CObject* object) {
	printf("(");
	CTupleObject* tuple = (CTupleObject*)object;
	for (unsigned int i = 0; i < tuple->ob_base.ob_len; i++) {
		CObject* obj = tuple->ob_item[i];
		if (obj == NULL) { printf("null,"); continue; }
		printObject(obj);
		printf(",");
	}
	printf(")");
}

void print_dict(CObject* object) {
	printf("{");
	CDictObject* dict = (CDictObject*)object;
	for (unsigned int i = 0; i < dict->allocate; i++) {
		CDictEntry entry = dict->table[i];
		if (entry.value) {
			printObject(entry.key);
			printf(":");
			printObject(entry.value);
			printf(",");
		}
	}
	printf("}");
}

void print_set(CObject* object) {
	printf("{");
	CSetObject* set = (CSetObject*)object;
	for (unsigned int i = 0; i < set->alloca; i++) {
		CObject* elem = set->table[i];
		if (elem && elem!=&Dummy) {
			printObject(elem);
			printf(",");
		}
	}
	printf("}");
}

void print_code(CObject* object) {
	CCodeObject* this = (CCodeObject*)object;
	print_tuple(this->co_names);
	printf("\n");
	print_tuple(this->co_consts);
	printf("\n");
}

void print_frame(CObject* object) {
	CFrameObject* frame = (CFrameObject*)object;

	printf("codes\n-----------------\n"); print_code(frame->codes); printf("-----------------\n\n\n");
	printf("local\n-----------------\n"); print_dict(frame->local); printf("\n-----------------\n\n\n");
	printf("global\n-----------------\n"); print_dict(frame->global); printf("\n-----------------\n\n\n");
	printf("buildin\n-----------------\n"); print_dict(frame->buildin); printf("\n-----------------\n\n\n");
}

void print_function(CObject* object) {
	printf("function");
}

void print_type(CObject* object) {
	CTypeObject* type = (CTypeObject*)object;
	print_dict(type->ob_attrs);
	
}

//.............



//implementation about virtual function of add

CObject* binaryAdd_long(CObject* this, CObject* other) {
	CLongObject* left = (CLongObject*)this;
	CObject* res = NULL;
	if (check_long(other)) {
		long value = left->ob_value + ((CLongObject*)other)->ob_value;
		res = CLongObject_new(value);
	}
	else {
		assert(0);
	}
	return res;
}

CObject* binarySub_long(CObject* this, CObject* other) {
	CLongObject* left = (CLongObject*)this;
	CObject* res = NULL;
	if (check_long(other)) {
		long value = left->ob_value - ((CLongObject*)other)->ob_value;
		res = CLongObject_new(value);
	}
	else {
		assert(0);
	}
	return res;
}
CObject* binaryMul_long(CObject* this, CObject* other) {
	CLongObject* left = (CLongObject*)this;
	CObject* res = NULL;
	if (check_long(other)) {
		long value = left->ob_value * ((CLongObject*)other)->ob_value;
		res = CLongObject_new(value);
	}
	else {
		assert(0);
	}
	return res;
}
CObject* binaryDiv_long(CObject* this, CObject* other) {
	CLongObject* left = (CLongObject*)this;
	CObject* res = NULL;
	if (check_long(other)) {
		long value = left->ob_value / ((CLongObject*)other)->ob_value;
		res = CLongObject_new(value);
	}
	else {
		assert(0);
	}
	return res;
}
CObject* binaryPow_long(CObject* this, CObject* other) {
	CLongObject* left = (CLongObject*)this;
	CObject* res = NULL;
	if (check_long(other)) {
		long value = pow(left->ob_value, ((CLongObject*)other)->ob_value);
		res = CLongObject_new(value);
	}
	else {
		assert(0);
	}
	return res;
}

CObject* binaryAdd_str(CObject* this, CObject* other) {
	CStrObject* left = (CStrObject*)this;
	char* lstr = left->ob_value;
	CObject* res = NULL;
	if (check_str(other)) {
		CStrObject* right = (CStrObject*)other;
		char* cat = CMem_malloc(left->ob_base.ob_len + 1);
		strcpy(cat, left->ob_value);
		strcat(cat, right->ob_value);
		res = CStrObject_new(cat);
	}
	else {
		assert(0);
	}
	return res;
}

CObject* binaryAdd_list(CObject* this, CObject* other) {
	assert(check_list(other));
	CListObject* left = (CListObject*)this;
	CListObject* right = (CListObject*)other;
	CListObject* sum = CListObject_new(0);
	for (size_t i = 0; i < left->ob_base.ob_len; i++) {
		CListObject_append(sum, CListObject_getItem(left, i));
	}
	for (size_t i = 0; i < right->ob_base.ob_len; i++) {
		CListObject_append(sum, CListObject_getItem(right, i));
	}
	return sum;
}

CObject* binaryAdd_tuple(CObject* this, CObject* other) {
	assert(check_tuple(other));
	CTupleObject* left = (CTupleObject*)this;
	CTupleObject* right = (CTupleObject*)other;
	CListObject* sum_list = CListObject_new(0);
	for (size_t i = 0; i < left->ob_base.ob_len; i++) {
		CListObject_append(sum_list, CTupleObject_getItem(left, i));
	}
	for (size_t i = 0; i < right->ob_base.ob_len; i++) {
		CListObject_append(sum_list, CTupleObject_getItem(right, i));
	}
	CTupleObject* result = CTupleObject_new(sum_list);
	return result;
}

CObject* binaryAdd_set(CObject* this, CObject* other) {
	return NULL;
}


//..............



//implementation about virtual function of hash

unsigned int hash_long(CObject* object) {
	return 0;
}

unsigned int hash_str(CObject* object) {
	CStrObject* strObject = (CStrObject*)object;
	char* str = CStrObject_getCstr(strObject);
	unsigned int res = DJBHash(str);
	return res;
}

//.........





//implementation about virtual function of equal

CObject* equal_long(CObject* this, CObject* other) {
	if (this == other) {
		return &True;
	}
	else if(check_long(this) && check_long(other)){
		long v1 = ((CLongObject*)this)->ob_value;
		long v2 = ((CLongObject*)other)->ob_value;
		return v1 == v2 ? &True : &False;
	}
	return &False;
}

CObject* equal_boolen(CObject* this, CObject* other) {
	return this == other ? &True : &False;
}

CObject* equal_str(CObject* this, CObject* other) {
	if (this == other) {
		return &True;
	}
	else if (check_str(this) && check_str(other)) {
		char* v1 = ((CStrObject*)this)->ob_value;
		char* v2 = ((CStrObject*)other)->ob_value;
		CObject* res = strcmp(v1, v2) == 0 ? &True : &False;
		return res;
	}
	return &False;
}

CObject* equal_null(CObject* this, CObject* other) {
	return this == other ? &True : &False;
}

CObject* equal_list(CObject* this, CObject* other) {
	CListObject* left = (CListObject*)this;
	CListObject* right = (CListObject*)other;
	if (left->ob_base.ob_len != right->ob_base.ob_len)return &False;
	for (unsigned int i = 0; i < left->ob_base.ob_len; i++) {
		CObject* l = CListObject_getItem(left, i);
		CObject* r = CListObject_getItem(right, i);
		if (l->ob_type->tp_em_eq == NULL || r->ob_type->tp_em_eq == NULL || l->ob_type->tp_em_eq(l, r) == NULL) {
			return &False;
		}
	}
	return &True;
}

CObject* equal_tuple(CObject* this, CObject* other) {
	CTupleObject* left = (CTupleObject*)this;
	CTupleObject* right = (CTupleObject*)other;
	if (left->ob_base.ob_len != right->ob_base.ob_len)return &False;
	for (unsigned int i = 0; i < left->ob_base.ob_len; i++) {
		CObject* l = CTupleObject_getItem(left, i);
		CObject* r = CTupleObject_getItem(right, i);
		if (l->ob_type->tp_em_eq == NULL || r->ob_type->tp_em_eq == NULL || l->ob_type->tp_em_eq(l, r) == NULL) {
			return &False;
		}
	}
	return &True;
}

//...................


//implementation about virtual function of toInt
CLongObject* toInt_long(CObject* self) {
	CLongObject* object = (CLongObject*)self;
	return CLongObject_new(object->ob_value);
}

CLongObject* toInt_boolen(CObject* self) {
	char value = self->ob_type == &True ? 1 : 0;
	return CLongObject_new(value);
}

CLongObject* toInt_str(CObject* self) {
	CStrObject* object = (CStrObject*)self;
	int value = atoi(object->ob_value);
	return CLongObject_new(value);
}

CLongObject* toInt_list(CObject* self) {
	CListObject* list = (CListObject*)self;
	long value = 0;
	for (size_t i = 0; i < list->ob_base.ob_len; i++) {
		CObject* object = list->ob_item[i];
		if (object->ob_type->tp_toInt == NULL)continue;
		value += object->ob_type->tp_toInt(object)->ob_value;
	}
	return CLongObject_new(value);
}

CLongObject* toInt_tuple(CObject* self) {
	CTupleObject* tuple = (CTupleObject*)self;
	long value = 0;
	for (size_t i = 0; i < tuple->ob_base.ob_len; i++) {
		CObject* object = tuple->ob_item[i];
		if (object->ob_type->tp_toInt == NULL)continue;
		value += object->ob_type->tp_toInt(object)->ob_value;
	}
	return CLongObject_new(value);
}
//..........................


//implementation about virtual function of toStr
CStrObject* toStr_long(CObject* self) {
	long value = ((CLongObject*)self)->ob_value;
	char buffer[16];
	sprintf(buffer, "%d", value);
	return CStrObject_new(buffer);
}

CStrObject* toStr_str(CObject* self) {
	CStrObject* object = (CStrObject*)self;
	return CStrObject_new(object->ob_value);
}

CStrObject* toStr_boolen(CObject* self) {
	const char* value = (self == &True ? "true" : "false");
	return CStrObject_new(value);
}

//implementation about virtual function of compare




CLongObject* binary_gt_long(CObject* this, CObject* other) {
	assert(check_long(other));
	CLongObject* result = NULL;
	if (((CLongObject*)this)->ob_value > ((CLongObject*)other)->ob_value) {
		result = &True;
	}
	else {
		result = &False;
	}
	return result;
}

CLongObject* binary_lt_long(CObject* this, CObject* other) {
	assert(check_long(other));
	CLongObject* result = NULL;
	if (((CLongObject*)this)->ob_value < ((CLongObject*)other)->ob_value) {
		result = &True;
	}
	else {
		result = &False;
	}
	return result;
}

//

//
CObject* item_get_Str(CObject* this, CObject* sub) {
	return NULL;
}

CObject* item_get_List(CObject* this, CObject* sub) {
	assert(check_long(sub));
	long index = ((CLongObject*)sub)->ob_value;
	CObject* object = CListObject_getItem(this, index);
	return object;
}

void item_set_List(CObject* this, CObject* sub,CObject* value) {
	assert(check_long(sub));
	unsigned int index = (*(CLongObject*)sub).ob_value;
	CListObject_setItem(this, index, value);
}

CObject* item_get_Tuple(CObject* this, CObject* sub) {
	assert(check_long(sub));
	long index = ((CLongObject*)sub)->ob_value;
	CObject* object = CTupleObject_getItem(this, index);
	return object;
}

CObject* item_get_Dict(CObject* this, CObject* sub) {
	CDictEntry* entry = CDictObject_find(this, sub);
	assert(entry);
	return entry->value;
}

void item_set_Dict(CObject* this, CObject* sub, CObject* value) {
	CDictObject_insert(this, sub, value);
}

CObject* item_get_Set(CObject* this, CObject* sub) {
	
}

//



//implementation of function groups check

int check_long(CObject* object) {
	return object->ob_type == &TypeObject_Long;
}

int check_str(CObject* object) {
	return object->ob_type == &TypeObject_Str;
}

int check_list(CObject* object) {
	return object->ob_type == &TypeObject_List;
}

int check_dict(CObject* object) {
	return object->ob_type == &TypeObject_Dict;
}

int check_tuple(CObject* object) {
	return object->ob_type == &TypeObject_Tuple;
}

int check_function(CObject* object) {
	return object->ob_type == &TypeObject_Funciton;
}

//..................




//implementation of CObject_binary_Arit

CObject* CObject_binary_Arit(CObject* left,CObject* right,unsigned char opType) {
	assert(left && left->ob_type);
	CObject* result = NULL;
	switch (opType)
	{
	case BINARY_ARIT_ADD:
		assert(left->ob_type->tp_nb_add);
		result = left->ob_type->tp_nb_add(left, right);
		break;
	case BINARY_ARIT_SUB:
		assert(left->ob_type->tp_nb_sub);
		result = left->ob_type->tp_nb_sub(left, right);
		break;
	case BINARY_ARIT_MUL:
		assert(left->ob_type->tp_nb_mul);
		result = left->ob_type->tp_nb_mul(left, right);
		break;
	case BINARY_ARIT_DIV:
		assert(left->ob_type->tp_nb_div);
		result = left->ob_type->tp_nb_div(left, right);
		break;
	case BINARY_ARIT_POW:
		assert(left->ob_type->tp_nb_pow);
		result = left->ob_type->tp_nb_pow(left, right);
		break;
	default:
		break;
	}
	return result;
}

//....................................



//







//

//implementation of CObject_binary_Arit

CObject* CObject_binary_Compare(CObject* this, CObject* other, unsigned char opType) {
	assert(this && this->ob_type);
	CObject* result = NULL;
	switch (opType)
	{
	case BINARY_COMP_EQ:
	{
		CObject* condition = this->ob_type->tp_em_eq(this, other);
		if (condition == &True) {
			result = &True;
		}
		else {
			result = &False;
		}
		break;
	}
	case BINARY_COMP_NEQ:
	{
		CObject* condition = this->ob_type->tp_em_eq(this, other);
		if (condition == &False) {
			result = &True;
		}
		else {
			result = &False;
		}
		break;
	}
	case BINARY_COMP_GT:
	{
		CObject* condition = this->ob_type->tp_em_gt(this, other);
		result = (condition == &True) ? &True : &False;
		break;
	}
	case BINARY_COMP_GTE:
	{
		CObject* condition1 = this->ob_type->tp_em_eq(this, other);
		CObject* condition2 = this->ob_type->tp_em_gt(this, other);
		if (condition1 == &True || condition2 == &True) {
			result = &True;
		}
		else {
			result = &False;
		}
		break;
	}
	case BINARY_COMP_LT:
	{
		CObject* condition = this->ob_type->tp_em_lt(this, other);
		result = (condition == &True) ? &True : &False;
		break;
	}
	case BINARY_COMP_LTE:
	{
		CObject* condition1 = this->ob_type->tp_em_eq(this, other);
		CObject* condition2 = this->ob_type->tp_em_lt(this, other);
		if (condition1 == &True || condition2 == &True) {
			result = &True;
		}
		else {
			result = &False;
		}
		break;
	}
	default:
		break;
	}
	return result;
}


//.....................................



CObject* CGetAttr(CObject* this, CStrObject* attr_name) {
	CDictObject* attrs = this->ob_type->ob_attrs;
	CDictEntry* entry = CDictObject_find(attrs, attr_name);
	return entry->value;
}

void CSetAttr(CObject* self, CStrObject* attr_name, CObject* value) {
	CDictObject* attrs = self->ob_type->ob_attrs;
	CDictObject_insert(attrs, attr_name,value);
	return;
}

CObject* judge_object(CObject* object)
{
	if (object == &False || object == &None
		|| (object->ob_type == &TypeObject_Long && ((CLongObject*)object)->ob_value == 0)) {
		return &False;
	}
	return &True;
}





//implementation of printObject

void printObject(CObject* object) {
	//assert(object->ob_type->tp_print);
	if (!object->ob_type->tp_print) {
		printf("unknow");
		return;
	}
	object->ob_type->tp_print(object);
}

//.............................


void slot_print(CObject* this){
	CStrObject* key = CStrObject_new("__print__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CTupleObject* args = CTupleObject_new(args_list);
	function->ob_type->tp_call(function, args);
}

CLongObject* slot_hash(CObject* this){
	CStrObject* key = CStrObject_new("__hash__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CLongObject* slot_toInt(CObject* this) {
	CStrObject* key = CStrObject_new("__int__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CStrObject* slot_toStr(CObject* this) {
	CStrObject* key = CStrObject_new("__str__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}


CObject* slot_call(CObject* this, CTupleObject* args){
	CStrObject* key = CStrObject_new("__call__");
	CObject* function = CGetAttr(this, key);
	return function->ob_type->tp_call(function, args);
}


CObject* slot_new(CObject* this, CTupleObject* args){


}


void slot_dealloc(CObject* this){


}


void slot_init(CObject* this, CTupleObject* args){
	CStrObject* key = CStrObject_new("__init__");
	CObject* function = CGetAttr(this, key);
	CListObject* self_list = CListObject_new(0);
	CListObject_append(self_list, this);
	CTupleObject* self_tuple = CTupleObject_new(self_list);
	CTupleObject* args_new = binaryAdd_tuple(self_tuple, args);
	function->ob_type->tp_call(function, args_new);
}


void slot_destruct(CObject* this){


}


CObject* slot_add(CObject* this, CObject* other){
	CStrObject* key = CStrObject_new("__add__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CListObject_append(args_list, other);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CObject* slot_sub(CObject* this, CObject* other){
	CStrObject* key = CStrObject_new("__sub__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CListObject_append(args_list, other);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CObject* slot_mul(CObject* this, CObject* other){
	CStrObject* key = CStrObject_new("__mul__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CListObject_append(args_list, other);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CObject* slot_div(CObject* this, CObject* other){
	CStrObject* key = CStrObject_new("__div__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CListObject_append(args_list, other);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CObject* slot_pow(CObject* this, CObject* other){
	CStrObject* key = CStrObject_new("__pow__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CListObject_append(args_list, other);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}


CObject* slot_equal(CObject* this, CObject* other){
	CStrObject* key = CStrObject_new("__eq__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CListObject_append(args_list, other);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CObject* slot_gt(CObject* this, CObject* other){
	CStrObject* key = CStrObject_new("__gt__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CListObject_append(args_list, other);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CObject* slot_lt(CObject* this, CObject* other) {
	CStrObject* key = CStrObject_new("__lt__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CListObject_append(args_list, other);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CObject* slot_iterator(CObject* this) {
	CStrObject* key = CStrObject_new("__iter__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CObject* slot_next(CObject* this) {
	CStrObject* key = CStrObject_new("__next__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

CObject* slot_item_get(CObject* this, CObject* sub) {
	CStrObject* key = CStrObject_new("__item_get__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CTupleObject* args = CTupleObject_new(args_list);
	return function->ob_type->tp_call(function, args);
}

void slot_item_set(CObject* this, CObject* sub,CObject* value) {
	CStrObject* key = CStrObject_new("__item_set__");
	CObject* function = CGetAttr(this, key);
	CListObject* args_list = CListObject_new(0);
	CListObject_append(args_list, this);
	CListObject_append(args_list, sub);
	CListObject_append(args_list, value);
	CTupleObject* args = CTupleObject_new(args_list);
	function->ob_type->tp_call(function, args);
}

//.................................




//implementation of CAPI
CObject* CAPI_CListObject_new(CTupleObject* args) {
	CListObject* list = CListObject_new(0);
	if (args->ob_base.ob_len == 0) { return list; }
	CObject* object = CTupleObject_getItem(args, 0);
	assert(object->ob_type->tp_iterator);
	CObject* iter = object->ob_type->tp_iterator(object);
	for (CObject* value = iter->ob_type->tp_em_next(iter); value != &None; value = iter->ob_type->tp_em_next(iter)) {
		CListObject_append(list, value);
	}
	return list;
}

CObject* CAPI_CListObject_append(CTupleObject* args) {
	CListObject* list = (CListObject*)CTupleObject_getItem(args, 0);
	CObject* value = CTupleObject_getItem(args, 1);
	CListObject_append(list, value);
	return NULL;
}

CObject* CAPI_CListObject_pop(CTupleObject* args) {
	CListObject* list = (CListObject*)CTupleObject_getItem(args, 0);
	return CListObject_pop(list);
}

CObject* CAPI_CListObject_insert(CTupleObject* args) {
	CListObject* list = (CListObject*)CTupleObject_getItem(args, 0);
	CLongObject* index = CTupleObject_getItem(args, 1);
	CObject* value = CTupleObject_getItem(args, 2);
	CListObject_insert(list, index->ob_value, value);
	return NULL;
}

CObject* CAPI_CListObject_erase(CTupleObject* args) {
	CListObject* list = (CListObject*)CTupleObject_getItem(args, 0);
	CLongObject* index = CTupleObject_getItem(args, 1);
	CListObject_erase(list, index->ob_value);
	return NULL;
}

CObject* CAPI_CListObject_getItem(CTupleObject* args) {
	CListObject* list = (CListObject*)CTupleObject_getItem(args, 0);
	CLongObject* index = CTupleObject_getItem(args, 1);
	return CListObject_getItem(list, index->ob_value);
}

CObject* CAPI_CListObject_getSize(CTupleObject* args) {
	CListObject* list = (CListObject*)CTupleObject_getItem(args, 0);
	return CListObject_getSize(list);
}

CObject* CAPI_CTupleObject_new(CTupleObject* args) {
	CListObject* list = CAPI_CListObject_new(args);
	return CTupleObject_new(list);
}


CObject* CAPI_CTupleObject_getItem(CTupleObject* args) {
	CTupleObject* tuple = (CTupleObject*)CTupleObject_getItem(args, 0);
	CLongObject* index = CTupleObject_getItem(args, 1);
	return CTupleObject_getItem(tuple, index->ob_value);
}

CObject* CAPI_CTupleObject_getSize(CTupleObject* args) {
	CTupleObject* tuple = (CTupleObject*)CTupleObject_getItem(args, 0);
	return CTupleObject_getSize(tuple);
}

CObject* CAPI_CDictObejct_new(CTupleObject* args) {
	if (args->ob_base.ob_len == 0)return CDictObejct_new();

}

CObject* CAPI_CDictObject_find(CTupleObject* args) {
	CDictObject* dict = (CDictObject*)CTupleObject_getItem(args, 0);
	CObject* key = CTupleObject_getItem(args, 1);
	CDictEntry* entry =  CDictObject_find(dict, key);
	if (entry == NULL)return &None;
	return entry->value;
}

CObject* CAPI_CDictObject_insert(CTupleObject* args) {
	CDictObject* dict = (CDictObject*)CTupleObject_getItem(args, 0);
	CObject* key = CTupleObject_getItem(args, 1);
	CObject* value = CTupleObject_getItem(args, 2);
	CDictObject_insert(dict, key, value);
	printObject(dict);
	return NULL;
}

CObject* CAPI_CDictObject_erase(CTupleObject* args) {
	CDictObject* dict = (CDictObject*)CTupleObject_getItem(args, 0);
	CObject* key = CTupleObject_getItem(args, 1);
	CDictObject_erase(dict, key);
	return NULL;
}

CObject* CAPI_CDictObject_size(CTupleObject* args) {
	CDictObject* dict = (CDictObject*)CTupleObject_getItem(args, 0);
	unsigned int size = dict->ob_base.ob_len;
	return CLongObject_new(size);
}



CObject* CAPI_printObject(CTupleObject* args) {
	CObject* object = CTupleObject_getItem(args, 0);
	printObject(object);
	return NULL;
}

CObject* CAPI_printLine(CTupleObject* args) {
	CObject* object = CTupleObject_getItem(args, 0);
	printObject(object);
	printf("\n");
	return NULL;
}

CObject* CAPI_spawnRange(CTupleObject* args) {
	long begin = ((CLongObject*)CTupleObject_getItem(args, 0))->ob_value;
	long end = ((CLongObject*)CTupleObject_getItem(args, 1))->ob_value;
	long step = begin <= end ? 1 : -1;
	if (args->ob_base.ob_len == 3) {
		step = ((CLongObject*)CTupleObject_getItem(args, 2))->ob_value;
	}
	return CNumberRangeObject_new(begin, end, step);
}

CObject* CAPI_toInt(CTupleObject* args) {
	CObject* object = CTupleObject_getItem(args, 0);
	assert(object->ob_type->tp_toInt);
	return object->ob_type->tp_toInt(object);
}

CObject* CAPI_toStr(CTupleObject* args) {
	CObject* object = CTupleObject_getItem(args, 0);
	assert(object->ob_type->tp_toStr);
	return object->ob_type->tp_toStr(object);
}

CObject* CAPI_toBoolen(CTupleObject* args) {
	CObject* object = CTupleObject_getItem(args, 0);
	return judge_object(object);
}

//......................




//type_new function
CObject* type_new_long(CObject* type, CTupleObject* args) {
	CObject* value = CTupleObject_getItem(args, 0);
	assert(value->ob_type->tp_toInt);
	long v = value->ob_type->tp_toInt;
	return CLongObject_new(v);
}



CObject* type_new_str(CObject* type, CTupleObject* args) {
	CObject* value = CTupleObject_getItem(args, 0);
	assert(value->ob_type->tp_toInt);
	char* v = value->ob_type->tp_toInt;
	return CStrObject_new(v);
}

CObject* type_new_list(CObject* type, CTupleObject* args) {
	CListObject* list = CListObject_new(0);
	for (unsigned int i = 0; i < args->ob_base.ob_len; i++) {
		CObject* value = CTupleObject_getItem(args, i);
		CListObject_append(list, value);
	}
	return list;
}

CObject* type_new_tuple(CObject* type, CTupleObject* args) {
	CListObject* list = CTupleObject_getItem(args, 0);
	return CTupleObject_new(list);
}

CObject* type_new_dict(CObject* type, CTupleObject* args) {
	CDictObject* dict = CDictObejct_new();
	return dict;
}

CObject* type_new_set(CObject* type, CTupleObject* args) {
	CSetObject* set = CSetObject_new();
	return set;
}
//...................





CTypeObject* create_type(CStrObject* className, CDictObject* attrs) {
	CListObject* list = CListObject_new(0);
	CListObject_append(list, className);
	CListObject_append(list, attrs);
	CTupleObject* tuple = CTupleObject_new(list);
	CTypeObject* res = TypeObject_Type.tp_call(&TypeObject_Type, tuple);
	return res;
}


CObject* metaType_new(CObject* type_type,CTupleObject* args) {
	CTypeObject* meta = (CTypeObject*)type_type;
	CTypeObject* type = CMem_malloc(sizeof(CTypeObject));
	memset(type, 0, sizeof(CTypeObject));
	CStrObject* className = CTupleObject_getItem(args, 0);
	CDictObject* attrs = CTupleObject_getItem(args, 1);
	type->ob_base.ob_type = type_type;
	type->ob_name = className->ob_value;
	type->ob_size = sizeof(CObject);
	type->ob_attrs = attrs;
	type->tp_call = type_call_new;
	type->tp_new = type_new;
	type->tp_init = type_init;
	fill_methods(type, attrs);
	return type;
}


#define METHODS_NAMES_LEN 18
#define SLOT_DEFINED(method_name,tp_ptr,slot_func) {#method_name,offsetof(CTypeObject,tp_ptr),(void*)slot_func}

void fill_methods(CTypeObject* type, CDictObject* attrs) {

	static SlotFunction method_names[METHODS_NAMES_LEN] = {
		SLOT_DEFINED(__print__,tp_print,slot_print),
		SLOT_DEFINED(__hash__,tp_hash,slot_hash),
		SLOT_DEFINED(__int__,tp_toInt,slot_toInt),
		SLOT_DEFINED(__str__,tp_toStr,slot_toStr),
		SLOT_DEFINED(__init__,tp_init,slot_init),
		SLOT_DEFINED(__call__,tp_call,slot_call),
		SLOT_DEFINED(__add__,tp_nb_add,slot_add),
		SLOT_DEFINED(__sub__,tp_nb_sub,slot_sub),
		SLOT_DEFINED(__mul__,tp_nb_mul,slot_mul),
		SLOT_DEFINED(__div__,tp_nb_div,slot_div),
		SLOT_DEFINED(__pow__,tp_nb_pow,slot_pow),
		SLOT_DEFINED(__eq__,tp_em_eq,slot_equal),
		SLOT_DEFINED(__gt__,tp_em_gt,slot_gt),
		SLOT_DEFINED(__lt__,tp_em_lt,slot_lt),
		SLOT_DEFINED(__iter__,tp_iterator,slot_iterator),
		SLOT_DEFINED(__next__,tp_em_next,slot_next),
		SLOT_DEFINED(__item_get__,tp_item_get,slot_item_get),
		SLOT_DEFINED(__item_set__,tp_item_set,slot_item_set),
	};
	/*
	f_print tp_print;					
	f_hash tp_hash;						
	f_toInt tp_toInt;
	f_toStr tp_toStr;
	f_new tp_new;
	f_init tp_init;
	f_dealloc tp_dealloc;
	f_destruct tp_destruct;
	f_call tp_call;
	f_binary tp_nb_add;
	f_binary tp_nb_sub;
	f_binary tp_nb_mul;
	f_binary tp_nb_div;
	f_binary tp_nb_pow;
	f_binary tp_em_eq;
	f_binary tp_em_gt;
	f_binary tp_em_lt;
	f_iterator tp_iterator;
	f_next tp_em_next;
	f_item_get tp_item_get;
	f_item_set tp_item_set;
	*/
	for (unsigned short i = 0; i < METHODS_NAMES_LEN; i++) {
		CObject* key = CStrObject_new(method_names[i].name);
		CDictEntry* entry = CDictObject_find(attrs, key);
		if (entry == NULL)continue;
		void** head = (char*)type + method_names[i].offset;
		*head = method_names[i].slot_function;
	}

}

CObject* type_call_function(CObject* functionObject, CTupleObject* args) {
	CFunctionObject* function = (CFunctionObject*)functionObject;
	CTupleObject* names = function->f_code->co_names;
	CDictObject* local = CDictObejct_new();
	for (unsigned short i = 1; i <= args->ob_base.ob_len; i++) {
		CObject* key = CTupleObject_getItem(names, i - 1);
		CObject* value = CTupleObject_getItem(args, i - 1);
		CDictObject_insert(local, key, value);
	}

	//create new frame to execute function
	CFrameObject* frame = CFrameObject_new(function->f_code, function->f_global);
	frame->local = local;

	//execute function meanwhile receive r_value
	CObject* result = CFrameObject_execute(frame);

	return result;

}

CObject* type_call_new(CObject* typeObject, CTupleObject* args) {
	CTypeObject* type = (CTypeObject*)typeObject;
	CObject* result = type->tp_new(typeObject, args);
	if (result->ob_type != &TypeObject_Type) {
		type->tp_init(result, args);
	}
	return result;
}

CObject* type_call_CAPI(CObject* cAPIObject, CTupleObject* args) {
	CCAPIObject* cAPI = (CCAPIObject*)cAPIObject;
	return cAPI->function(args);
}

CObject* type_new(CObject* type, CTupleObject* args) {
	CObject* instance = CMem_malloc(sizeof(type->ob_type->ob_size));
	instance->ob_refcnt = 1;
	instance->ob_type = (CTypeObject*)type;
	return instance;
}

void type_init(CObject* self, CTupleObject* args) {
	

}



void init_buildIn() {
	if (_buildIn_)return;
	_buildIn_ = CDictObejct_new();
	CDictObject_insert(_buildIn_, CStrObject_new("print"), CCAPIObject_new(CAPI_printObject));
	CDictObject_insert(_buildIn_, CStrObject_new("printLine"), CCAPIObject_new(CAPI_printLine));
	CDictObject_insert(_buildIn_, CStrObject_new("range"), CCAPIObject_new(CAPI_spawnRange));
	CDictObject_insert(_buildIn_, CStrObject_new("int"), CCAPIObject_new(CAPI_toInt));
	CDictObject_insert(_buildIn_, CStrObject_new("str"), CCAPIObject_new(CAPI_toStr));
	CDictObject_insert(_buildIn_, CStrObject_new("bool"), CCAPIObject_new(CAPI_toBoolen));
	CDictObject_insert(_buildIn_, CStrObject_new("list"), CCAPIObject_new(CAPI_CListObject_new));
	CDictObject_insert(_buildIn_, CStrObject_new("tuple"), CCAPIObject_new(CAPI_CTupleObject_new));
	CDictObject_insert(_buildIn_, CStrObject_new("dict"), CCAPIObject_new(CAPI_CDictObejct_new));
	CDictObject_insert(_buildIn_, CStrObject_new("set"), &TypeObject_Set);
}

void init_list() {
	static CDictObject* _list_attrs_ = NULL;
	if (_list_attrs_)return;
	_list_attrs_ = CDictObejct_new();
	CDictObject_insert(_list_attrs_, CStrObject_new("append"), CCAPIObject_new(CAPI_CListObject_append));
	CDictObject_insert(_list_attrs_, CStrObject_new("pop"), CCAPIObject_new(CAPI_CListObject_pop));
	CDictObject_insert(_list_attrs_, CStrObject_new("insert"), CCAPIObject_new(CAPI_CListObject_insert));
	CDictObject_insert(_list_attrs_, CStrObject_new("erase"), CCAPIObject_new(CAPI_CListObject_erase));
	CDictObject_insert(_list_attrs_, CStrObject_new("get"), CCAPIObject_new(CAPI_CListObject_getItem));
	CDictObject_insert(_list_attrs_, CStrObject_new("size"), CCAPIObject_new(CAPI_CListObject_getSize));
	TypeObject_List.ob_attrs = _list_attrs_;
}

void init_tuple() {
	static CDictObject* _tuple_attrs_ = NULL;
	if (_tuple_attrs_)return;
	_tuple_attrs_ = CDictObejct_new();
	CDictObject_insert(_tuple_attrs_, CStrObject_new("get"), CCAPIObject_new(CAPI_CTupleObject_getItem));
	CDictObject_insert(_tuple_attrs_, CStrObject_new("size"), CCAPIObject_new(CAPI_CTupleObject_getSize));
	TypeObject_Tuple.ob_attrs = _tuple_attrs_;
}

void init_dict() {
	static CDictObject* _dict_attrs_ = NULL;
	if (_dict_attrs_)return;
	_dict_attrs_ = CDictObejct_new();
	CDictObject_insert(_dict_attrs_, CStrObject_new("insert"), CCAPIObject_new(CAPI_CDictObject_insert));
	CDictObject_insert(_dict_attrs_, CStrObject_new("find"), CCAPIObject_new(CAPI_CDictObject_find));
	CDictObject_insert(_dict_attrs_, CStrObject_new("erase"), CCAPIObject_new(CAPI_CDictObject_erase));
	CDictObject_insert(_dict_attrs_, CStrObject_new("size"), CCAPIObject_new(CAPI_CDictObject_size));
	TypeObject_Dict.ob_attrs = _dict_attrs_;
}

void init_environment() {
	init_buildIn();
	init_list();
	init_tuple();
	init_dict();
}


CCodeObject* CCodeObject_new_from_Export_CodeObject(Export_CodeObject* export_codeObject) {
	CListObject* names_list = CListObject_new(0);
	CListObject* consts_list = CListObject_new(0);

	Export_Name_Type* names = export_codeObject->names->names;
	unsigned short names_len = export_codeObject->names->len;

	Export_Const_Type* consts = export_codeObject->consts->consts;
	unsigned short consts_len = export_codeObject->consts->len;

	int* ins = export_codeObject->codes->ins;
	size_t ins_len = export_codeObject->codes->len;

	for (unsigned short i = 0; i < names_len; i++) {
		const char* name = names[i].name;
		CListObject_append(names_list, CStrObject_new(name));
	}

	for (unsigned short i = 0; i < consts_len; i++) {
		void* data = consts[i].data;
		Export_Object_Type type = consts[i].type;
		switch (type)
		{
		case OBJECT_TYPE_LONG:
		{
			long value = *((long*)data);
			CListObject_append(consts_list, CLongObject_new(value));
			break;
		}
		case OBJECT_TYPE_BOOLEN:
		{
			long value = *((long*)data);
			CListObject_append(consts_list, CBoolenObject_new(value));
			break;
		}
		case OBJECT_TYPE_STR:
		{
			const char* value = (const char*)data;
			CListObject_append(consts_list, CStrObject_new(value));
			break;
		}
		case OBJECT_TYPE_NULL:
		{
			CListObject_append(consts_list, &None);
			break;
		}
		case OBJECT_TYPE_CODE:
		{
			Export_CodeObject* codeObject = (Export_CodeObject*)data;
			CListObject_append(consts_list, CCodeObject_new_from_Export_CodeObject(codeObject));
			break;
		}
		default:
			break;
		}
	}


	CCodeObject* result = CCodeObject_new(names_list, consts_list,ins,ins_len);
	return result;
}

void run_with_Export_CodeObject(Export_CodeObject* codeObject) {
	CCodeObject* byteCode = CCodeObject_new_from_Export_CodeObject(codeObject);
	CDictObject* global = CDictObejct_new();
	CFrameObject* frame = CFrameObject_new(byteCode, global);
	CFrameObject_execute(frame);
}



void print_ins(int code) {
	unsigned char opCode = GET_OPCODE(code);
	unsigned short opNum = GET_OPNUM(code);
	switch (opCode)
	{
	case LOAD_CONST:
		printf("LOAD_CONST %d ", opNum);
		break;
	case LOAD_NAME:
		printf("LOAD_NAME %d ", opNum);
		break;
	case LOAD_ATTR:
		printf("LOAD_ATTR %d ", opNum);
		break;
	case LOAD_LOCALS:
		printf("LOAD_LOCALS %d ", opNum);
		break;
	case STORE_NAME:
		printf("STORE_NAME %d ", opNum);
		break;
	case STORE_ATTR:
		printf("STORE_ATTR %d ", opNum);
		break;
	case BINARY_ARIT:
		printf("BINARY_ARIT %d ", opNum);
		break;
	case BINARY_COMP:
		printf("BINARY_COMP %d ", opNum);
		break;
	case LOGICAL_AND:
		printf("LOGICAL_AND %d ", opNum);
		break;
	case LOGICAL_OR:
		printf("LOGICAL_OR %d ", opNum);
		break;
	case LOGICAL_NOT:
		printf("LOGICAL_NOT %d ", opNum);
		break;
	case JUMP_ABSOLUTE:
		printf("JUMP_ABSOLUTE %d ", opNum);
		break;
	case JUMP_RELATIVE:
		printf("JUMP_RELATIVE %d ", opNum);
		break;
	case JUMP_IF_ABSOLUTE:
		printf("JUMP_IF_ABSOLUTE %d ", opNum);
		break;
	case JUMP_IF_RELAIVE:
		printf("JUMP_IF_RELAIVE %d ", opNum);
		break;
	case GET_ITER:
		printf("GET_ITER %d ", opNum);
		break;
	case NEXT_ITER:
		printf("NEXT_ITER %d ", opNum);
		break;
	case ITEM_GET:
		printf("ITEM_GET %d ", opNum);
		break;
	case ITEM_SET:
		printf("ITEM_SET %d ", opNum);
		break;
	case RETURN_TOP:
		printf("RETURN_TOP %d ", opNum);
		break;
	case MAKE_FUNCTION:
		printf("MAKE_FUNCTION %d ", opNum);
		break;
	case MAKE_CLASS:
		printf("MAKE_CLASS %d ", opNum);
		break;
	case MAKE_LIST:
		printf("MAKE_LIST %d ", opNum);
		break;
	case CALL_FUNCTION:
		printf("CALL_FUNCTION %d ", opNum);
		break;
	case STACK_POP:
		printf("STACK_POP %d ", opNum);
		break;
	default:
		printf("UnKnow Code: %d ", code);
		break;
	}
	printf("\n");
}


#pragma once

#define CCODE_END 0x00
#define LOAD_CONST 0x01
#define LOAD_NAME 0x02
#define LOAD_LOCALS 0x03
#define LOAD_ATTR 0x04
#define STORE_NAME 0x05
#define STORE_ATTR 0x06
#define BINARY_ARIT 0x07
#define BINARY_COMP 0x08
#define LOGICAL_AND 0x0A
#define LOGICAL_OR 0x0B
#define LOGICAL_NOT 0x0C

#define JUMP_RELATIVE 0x11
#define JUMP_ABSOLUTE 0x12
#define JUMP_IF_RELAIVE 0x13
#define JUMP_IF_ABSOLUTE 0x14
#define FOR_LOOP 0x15
#define GET_ITER 0x16
#define NEXT_ITER 0x17
#define ITEM_GET 0x18
#define ITEM_SET 0x19

#define MAKE_CLASS 0x21
#define MAKE_FUNCTION 0x22
#define MAKE_LIST 0x23

#define CALL_FUNCTION 0x31
#define RETURN_TOP 0x32
#define STACK_POP 0x33


#define CCODE_NONE 0xF0

#define BINARY_ARIT_ADD 0
#define BINARY_ARIT_SUB 1
#define BINARY_ARIT_MUL 2
#define BINARY_ARIT_DIV 3
#define BINARY_ARIT_POW 4

#define BINARY_COMP_EQ 0
#define BINARY_COMP_NEQ 1
#define BINARY_COMP_GT 2
#define BINARY_COMP_GTE 3
#define BINARY_COMP_LT 4
#define BINARY_COMP_LTE 5



#define GET_OPCODE(x) (x >> 24)
#define GET_OPNUM(x) (x & 0x0000FFFF)
#define CAT_INS(opcode,opnum) ((opcode << 24)|( opnum ))



#include<iostream>
#include<vector>
#include<string>
#include<optional>
#include<variant>
#include<unordered_map>
#include<unordered_set>
#include<assert.h>
#include<stack>
#include<fstream>
#include<type_traits>
#include<functional>
#include<map>
#include<algorithm>
#include<functional>
#include<export.h>


using namespace std;

namespace UtilityFunction {
	bool isNum(char c) {
		return c >= '0' && c <= '9';
	}
	bool isAlpha(char c) {
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}
	
}
using UtilityFunction::isNum, UtilityFunction::isAlpha;



void printCode(int code) {
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


enum class TokenType {
	TOKEN_INT,
	TOKEN_STR,
	TOKEN_IDENTIFIER,
	TOKEN_EQ,
	TOKEN_NEQ,
	TOKEN_GT,
	TOKEN_GTE,
	TOKEN_LT,
	TOKEN_LTE,
	TOKEN_ADD,
	TOKEN_MIN,
	TOKEN_DIV,
	TOKEN_MUL,
	TOKEN_POW,
	TOKEN_INPLACE_ADD,
	TOKEN_INPLACE_SUB,
	TOKEN_INPLACE_MUL,
	TOKEN_INPLACE_DIV,
	TOKEN_INPLACE_POW,
	TOKEN_DOT,
	TOKEN_ASSIGN,
	TOKEN_LPAR,
	TOKEN_RPAR,
	TOKEN_LBRACKER,
	TOKEN_RBRACKER,
	TOKEN_LMBRACKER,
	TOKEN_RMBRACKER,
	TOKEN_COMMA,
	TOKEN_NULL,
	TOKEN_KEYWORD_NULL,
	TOKEN_KEYWORD_TRUE,
	TOKEN_KEYWORD_FALSE,
	TOKEN_KEYWORD_AND,
	TOKEN_KEYWORD_OR,
	TOKEN_KEYWORD_NOT,
	TOKEN_KEYWORD_IF,
	TOKEN_KEYWORD_ELIF,
	TOKEN_KEYWORD_ELSE,
	TOKEN_KEYWORD_WHILE,
	TOKEN_KEYWORD_RETURN,
	TOKEN_KEYWORD_BREAK,
	TOKEN_KEYWORD_CONTINUE,
	TOKEN_KEYWORD_VAR,
	TOKEN_KEYWORD_CLASS,
	TOKEN_KEYWORD_FOR,
	TOKEN_KEYWORD_IN,
	TOKEN_KEYWORD_DEF,

	TOKEN_EOF,
};




struct Error_Lexer {
	string info;
	size_t line, col;
	void what() const  {
		cout << "Lexer Error " << info; cout << " " << "line: " << line << " " << "col: " << col;
	}
};


struct Error_Parser {
	string info;
	size_t line, col;
	void what() const{
		cout << "Parser Error " <<"(" << "line: " << line << " " << "col: " << col << ")" << " ";
		cout << info;
	}
};




struct RuntimeError{ string info; };




using TokenValue = std::string;




struct Token {
	TokenType type;
	TokenValue value;
	size_t line, col;
};


unordered_map<string,Token> keywords{
	{"null",Token{TokenType::TOKEN_KEYWORD_NULL,"null"}},
	{"if",Token{TokenType::TOKEN_KEYWORD_IF,"if"}},
	{"elif",Token{TokenType::TOKEN_KEYWORD_ELIF,"elif"}},
	{"else",Token{TokenType::TOKEN_KEYWORD_ELSE,"else"}},
	{"return",Token{TokenType::TOKEN_KEYWORD_RETURN,"return"}},
	{"break",Token{TokenType::TOKEN_KEYWORD_BREAK,"break"}},
	{"continue",Token{TokenType::TOKEN_KEYWORD_CONTINUE,"continue"}},
	{"while",Token{TokenType::TOKEN_KEYWORD_WHILE,"while"}},
	{"true",Token{TokenType::TOKEN_KEYWORD_TRUE,"true"}},
	{"false",Token{TokenType::TOKEN_KEYWORD_FALSE,"false"}},
	{"and",Token{TokenType::TOKEN_KEYWORD_AND,"and"}},
	{"or",Token{TokenType::TOKEN_KEYWORD_OR,"or"}},
	{"not",Token{TokenType::TOKEN_KEYWORD_NOT,"not"}},
	{"class",Token{TokenType::TOKEN_KEYWORD_CLASS,"class"}},
	{"for",Token{TokenType::TOKEN_KEYWORD_FOR,"for"}},
	{"in",Token{TokenType::TOKEN_KEYWORD_IN,"in"}},
	{"def",Token{TokenType::TOKEN_KEYWORD_DEF,"def"}}
};




class Lexer {
	class TokenGetter {
	private:
		const string& text;
		int curPos;
		int nextPos;
		optional<char> curChar;
	public:
		TokenGetter(const string& text_) :text(text_), curPos(-1), nextPos(0), curChar(std::nullopt) { next(); }
		void next() {
			if (end()) {
				curPos = -1;
				curChar = nullopt;
				return;
			}
			curPos++;
			nextPos++;
			curChar = text[curPos];
		}
		optional<char> peekNext() const {
			if (end()) {
				return nullopt;
			}
			return text[nextPos];
		}
		optional<char> current() const { return text[curPos]; }
		bool transgression() const {
			return curChar == nullopt;
		}
		bool end() const {
			return nextPos == text.size();
		}
	};
private:
	string text;
	TokenGetter getter;
	size_t curLine, curCol;
private:
	void next() {
		return getter.next();
	}
	char current()const { return getter.current().value(); }
	char peekNext()const { return getter.peekNext().value(); }
	bool end()const {
		return getter.end();
	}
	bool transgression()const {
		return getter.transgression();
	}

public:
	Lexer(const string& text_) :text(text_), getter(TokenGetter(text)),curLine(1),curCol(1){}
	vector<Token> getTokens() {
		vector<Token> res{};
		while (!transgression()) {
			char curChar = current();
			Token token;
			if (isNum(curChar)) {
				string num = "";
				while (!transgression() && isNum(current())) {
					num += current();
					next();
				}
				token.type = TokenType::TOKEN_INT;
				token.value = num;
			}
			else if (isAlpha(curChar) || curChar == '_') {
				string id = "";
				while (!transgression() && (isNum(current()) || isAlpha(current()) || current() == '_')) {
					id += current();
					next();
				}
				if (auto it = keywords.find(id);it!=keywords.end()) {
					token = it->second;
				}
				else {
					token.type = TokenType::TOKEN_IDENTIFIER;
					token.value = id;
				}	
			}
			else if (curChar == '"') {
				string str = "";
				next();
				while (!transgression() && current() != '"') {
					str += current();
					next();
				}
				next();
				token.type = TokenType::TOKEN_STR;
				token.value = str;
			}
			else if (curChar == '.') {
				next();
				token.type = TokenType::TOKEN_DOT;
				token.value = ".";
			}
			else if (curChar == ',') {
				next();
				token.type = TokenType::TOKEN_COMMA;
				token.value = ",";
			}
			else if (curChar == '<') {
				next();
				if (!transgression() && current() == '=') {
					next();
					token.type = TokenType::TOKEN_LTE;
					token.value = "<=";
				}
				else {
					token.type = TokenType::TOKEN_LT;
					token.value = "<";
				}
			}
			else if (curChar == '>') {
				next();
				if (!transgression() && current() == '=') {
					token.type = TokenType::TOKEN_GTE;
					token.value = ">=";
					next();
				}
				else {
					token.type = TokenType::TOKEN_GT;
					token.value = ">";
				}
			}
			else if (curChar == '!') {
				next();
				if (!transgression() && current() == '=') {
					token.type = TokenType::TOKEN_NEQ;
					token.value = "!=";
					next();
				}
				else {
					throw Error_Lexer{ "unrecognize '!'" ,curLine,curCol};
				}
			}
			else if (curChar == '+') {
				next();
				if (!transgression() && current() == '=') {
					next();
					token.type = TokenType::TOKEN_INPLACE_ADD;
					token.value = "+=";
				}
				else {
					token.type = TokenType::TOKEN_ADD;
					token.value = "+";
				}
			}
			else if (curChar == '-') {
				next();
				if (!transgression() && current() == '=') {
					next();
					token.type = TokenType::TOKEN_INPLACE_SUB;
					token.value = "-=";
				}
				else {
					token.type = TokenType::TOKEN_MIN;
					token.value = "-";
				}
			}
			else if (curChar == '*') {
				next();
				if (!transgression() && current() == '=') {
					next();
					token.type = TokenType::TOKEN_INPLACE_MUL;
					token.value = "*=";
				}
				else {
					token.type = TokenType::TOKEN_MUL;
					token.value = "*";
				}
			}
			else if (curChar == '/') {
				next();
				if (!transgression() && current() == '=') {
					next();
					token.type = TokenType::TOKEN_INPLACE_DIV;
					token.value = "/=";
				}
				else {
					token.type = TokenType::TOKEN_DIV;
					token.value = "/";
				}
			}
			else if (curChar == '^') {
				next();
				if (!transgression() && current() == '=') {
					next();
					token.type = TokenType::TOKEN_INPLACE_POW;
					token.value = "^=";
				}
				else {
					token.type = TokenType::TOKEN_POW;
					token.value = "^";
				}
			}
			else if (curChar == '=') {
				string opt = "";
				opt += curChar;
				next();
				if (!transgression() && current() == '=') {
					next();
					token.type = TokenType::TOKEN_EQ;
					token.value = "==";
				}
				else {
					token.type = TokenType::TOKEN_ASSIGN;
					token.value = "=";
				}				
			}
			else if (curChar == '(') {
				next();
				token.type = TokenType::TOKEN_LPAR;
				token.value = "(";
			}
			else if (curChar == ')') {
				next();
				token.type = TokenType::TOKEN_RPAR;
				token.value = ")";
			}
			else if (curChar == '{') {
				next();
				token.type = TokenType::TOKEN_LBRACKER;
				token.value = "{";
			}
			else if (curChar == '}') {
				next();
				token.type = TokenType::TOKEN_RBRACKER;
				token.value = "}";
			}
			else if (curChar == '[') {
				next();
				token.type = TokenType::TOKEN_LMBRACKER;
				token.value = "[";
			}
			else if (curChar == ']') {
				next();
				token.type = TokenType::TOKEN_RMBRACKER;
				token.value = "]";
			}
			else if (curChar == ' ') {
				next();
				continue;
			}
			else if (curChar == '\n') {
				next();
				++curLine;
				curCol = 1;
				continue;
			}
			else {
				throw Error_Lexer{ "unrecognize charactor",curLine,curCol };
			}
			token.line = curLine;
			token.col = curCol++;
			res.push_back(token);
		}
		res.push_back(Token{ TokenType::TOKEN_EOF,"$",curCol,curLine});
		return res;
	}
	

	
};

void printTokens(const vector<Token>& tokens) {

	for (const Token& token : tokens) {
		cout << '[';
		cout << token.value;
		cout << ']' << " ";
	}
	cout << endl << "- - - - - - - - - - - - - - - - - - -" << endl;
}


struct Node;
struct Node_Expr_Var;

struct Null_Type{
	
};
Null_Type Null;
bool operator==(const Null_Type& left, const Null_Type& right) {
	return &left == &right;
}

class ByteCodes;
struct Const_Type_Variant;
using Name_Type = std::string;
using Const_Type = std::variant<long,const char*, bool,Null_Type*,ByteCodes*>;
using Instruction_Type = int;

using Names = std::vector<std::string>;
using Consts = std::vector<Const_Type>;
using Instructions = std::vector<Instruction_Type>;

struct Const_Type_Visitor_Print {
	void operator()(long value) {
		cout << value;
	}
	void operator()(const char* value) {
		printf("'%s'", value);
	}
	void operator()(bool value) {
		cout << (value ? "true" : "false");
	}
	void operator()(Null_Type* null) {
		cout << "null"; 
	}
	void operator()(ByteCodes*);

};


void* pos_bind(Instruction_Type* head, Instruction_Type* tail) {
	Instruction_Type** binder = new Instruction_Type* [2];
	binder[0] = head;
	binder[1] = tail;
	return binder;
}



class ByteCodes {

private:
	Names names;
	Consts consts;
	Instructions ins;
	std::string codeName;
	std::vector<pair<size_t, int*>> delays;
public:
	ByteCodes(const std::string& codeName_) :codeName(codeName_) { consts.push_back(&Null); }

	unsigned short insert(const Const_Type& con) {
		for (unsigned short i = 0; i < consts.size(); i++) {
			Const_Type& cur = consts[i];
			if (cur == con) {
				return i;
			}
		}
		consts.push_back(con);
		return consts.size() - 1;
	}

	unsigned short insert(const Name_Type& name) {
		for (unsigned short i = 0; i < names.size(); i++) {
			const Name_Type& cur = names[i];
			if (cur == name) {
				return i;
			}
		}
		names.push_back(name);
		return names.size() - 1;
	}


	size_t insert(Instruction_Type code) {
		ins.push_back(code);
		return ins.size() - 1;
	}

	void bind_delay(int* delayer) {
		size_t pos = insert(CAT_INS(CCODE_NONE, 0));
		delays.push_back(pair(pos, delayer));
	}

	void eval_delays() {
		for_each(delays.begin(), delays.end(),
			[this](pair<size_t, int*>& p) {
				Instruction_Type code = *p.second;
				this->setIns(code, p.first);	
		}
		);
	}

	void print() {
		cout << endl << "----------" << codeName << "----------" << endl;
		cout << "names: (";
		for_each(names.begin(), names.end(),[](const Name_Type& name) {cout << name << " "; });
		cout <<")"<< endl << "--------------------" << endl;
		cout << "consts: (" ;
		for_each(consts.begin(), consts.end(), [](const Const_Type& con) {std::visit(Const_Type_Visitor_Print(), con); cout << " "; });
		cout <<")" << endl << "--------------------" << endl;
		cout << "Ins: " << endl;
		for_each(ins.begin(), ins.end(), [](Instruction_Type code) {printCode(code); });
		cout << endl << "----------" << codeName << "----------" << endl;
	}

	size_t getInsSize() {
		return ins.size();
	}

	void setIns(int instruction, size_t index) {
		ins[index] = instruction;
	}

	Names& getNames() { return names; }
	Consts& getConsts() { return consts; }
	Instructions& getInstruction() { return ins; }
	string& getCodeName() { return codeName; }
};

std::vector<ByteCodes*> ByteCodes_Array{};


void Const_Type_Visitor_Print::operator()(ByteCodes* value) {
	cout << value->getCodeName();
}

struct Node {
	virtual void print() = 0;
	virtual void load(ByteCodes* byteCodes,void*) = 0;
};


struct Node_Expr :public Node {
	virtual void print() = 0;
	virtual void load(ByteCodes* byteCodes,void*) = 0;
};


struct Node_Expr_Literals :public Node_Expr {
	virtual void print() = 0;
	virtual void load(ByteCodes* byteCodes,void*) = 0;
};

struct Node_Expr_ALG :public Node_Expr {
	Node_Expr* left;
	Node_Expr* right;
	TokenType opType;
	Node_Expr_ALG(Node_Expr* left_, Node_Expr* right_,TokenType opType_):left(left_),right(right_),opType(opType_){}
	virtual void print() {
		left->print(); 
		cout << " ALG "; right->print();
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		left->load(byteCodes, msg);
		right->load(byteCodes, msg);
		switch (opType){
		case TokenType::TOKEN_ADD:
			byteCodes->insert(CAT_INS(BINARY_ARIT, BINARY_ARIT_ADD));
			break;
		case TokenType::TOKEN_MIN:
			byteCodes->insert(CAT_INS(BINARY_ARIT, BINARY_ARIT_SUB));
			break;
		case TokenType::TOKEN_MUL:
			byteCodes->insert(CAT_INS(BINARY_ARIT, BINARY_ARIT_MUL));
			break;
		case TokenType::TOKEN_DIV:
			byteCodes->insert(CAT_INS(BINARY_ARIT, BINARY_ARIT_DIV));
			break;
		case TokenType::TOKEN_POW:
			byteCodes->insert(CAT_INS(BINARY_ARIT, BINARY_ARIT_POW));
			break;
		default:
			break;
		}
		return;
	}
};

struct Node_Expr_Compare :public Node_Expr {
	Node_Expr* left;
	Node_Expr* right;
	TokenType opType;
	Node_Expr_Compare(Node_Expr* left_,Node_Expr* right_,TokenType opType_):left(left_),right(right_),opType(opType_){}
	virtual void print() {
		left->print(); cout << " COMPARE "; right->print();
	}
	virtual void load(ByteCodes* byteCodes, void* msg) {
		left->load(byteCodes, msg);
		right->load(byteCodes, msg);
		switch (opType)
		{
		case TokenType::TOKEN_EQ:
			byteCodes->insert(CAT_INS(BINARY_COMP, BINARY_COMP_EQ));
			break;
		case TokenType::TOKEN_LT:
			byteCodes->insert(CAT_INS(BINARY_COMP, BINARY_COMP_LT));
			break;
		case TokenType::TOKEN_LTE:
			byteCodes->insert(CAT_INS(BINARY_COMP, BINARY_COMP_LTE));
			break;
		case TokenType::TOKEN_GT:
			byteCodes->insert(CAT_INS(BINARY_COMP, BINARY_COMP_GT));
			break;
		case TokenType::TOKEN_GTE:
			byteCodes->insert(CAT_INS(BINARY_COMP, BINARY_COMP_GTE));
			break;
		case TokenType::TOKEN_NEQ:
			byteCodes->insert(CAT_INS(BINARY_COMP, BINARY_COMP_NEQ));
			break;
		default:
			break;
		}
	}
};



struct Node_Expr_Logical :public Node_Expr {
	Node_Expr* left;
	Node_Expr* right;
	TokenType opType;
	Node_Expr_Logical(Node_Expr* left_, Node_Expr* right_,TokenType opType_):left(left_), right(right_),opType(opType_) {}
	virtual void print() {
		left->print(); 
		cout << " Logic "; right->print();
	}
	virtual void load(ByteCodes* byteCodes, void* msg) {
		left->load(byteCodes, msg);
		if (opType == TokenType::TOKEN_KEYWORD_AND) {
			size_t sign = byteCodes->insert(CAT_INS(LOGICAL_AND, 0));
			right->load(byteCodes, msg);
			unsigned short dist = byteCodes->getInsSize() - sign;
			byteCodes->setIns(CAT_INS(LOGICAL_AND, dist),sign);
		}
		else if (opType == TokenType::TOKEN_KEYWORD_OR){
			size_t sign = byteCodes->insert(CAT_INS(LOGICAL_OR, 0));
			right->load(byteCodes, msg);
			unsigned short dist = byteCodes->getInsSize() - sign;
			byteCodes->setIns(CAT_INS(LOGICAL_OR, dist), sign);
		}
	}
	
};

struct Node_Expr_Unary :public Node_Expr {
	TokenType opType;
	Node_Expr_Unary(TokenType opType_):opType(opType_){}
	virtual void print() = 0;
	virtual void load(ByteCodes*,void*) = 0;
};

struct Node_Expr_Unary_Not :public Node_Expr_Unary {
	Node_Expr* expr;
	Node_Expr_Unary_Not(Node_Expr* expr_):Node_Expr_Unary(TokenType::TOKEN_KEYWORD_NOT),expr(expr_){}
	virtual void print(){
		cout << "not ";
		expr->print();
	}
	virtual void load(ByteCodes* byteCodes,void* msg){
		expr->load(byteCodes,nullptr);
		byteCodes->insert(CAT_INS(LOGICAL_NOT, 0));
	}
};

struct Node_Expr_Int :public Node_Expr_Literals {
	long value;
	Node_Expr_Int(long value_):value(value_){}
	virtual void print() {
		cout << value;
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		Const_Type con = value;
		unsigned short id = byteCodes->insert(con);
		byteCodes->insert(CAT_INS(LOAD_CONST, id));
	}
};

struct Node_Expr_Str :public Node_Expr_Literals {
	std::string value;
	Node_Expr_Str(const std::string value_) :value(value_){}
	virtual void print() {
		printf("'%s'", value.c_str());
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		Const_Type con = value.c_str();
		unsigned short id = byteCodes->insert(con);
		byteCodes->insert(CAT_INS(LOAD_CONST, id));
	}
};

struct Node_Expr_Bool :public Node_Expr_Literals {
	bool value;
	Node_Expr_Bool(bool value_) :value(value_) {}
	virtual void print() {
		cout << (value ? "true" : "false");
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		Const_Type con = value;
		unsigned short id = byteCodes->insert(con);
		byteCodes->insert(CAT_INS(LOAD_CONST, id));
	}
};

struct Node_Expr_Null :public Node_Expr_Literals {
	virtual void print(){
		cout << "null";
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		unsigned short id = byteCodes->insert(&Null);
		byteCodes->insert(CAT_INS(LOAD_CONST, id));
	}
};

struct Node_Expr_List :public Node_Expr_Literals {
	std::vector<Node_Expr*> list;
	Node_Expr_List(const std::vector<Node_Expr*>& list_):list(list_){}
	virtual void print() {
		cout << "[";
		unsigned short len = list.size();
		for (unsigned short i = 0; i < len; i++) {
			Node_Expr* expr = list[i];
			expr->print();
			if (i == len - 1)break;
			cout << ",";
		}
		cout << "]";
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		unsigned short len = list.size();
		for_each(list.begin(), list.end(), [byteCodes, msg](Node_Expr* expr) {expr->load(byteCodes, msg); });
		byteCodes->insert(CAT_INS(MAKE_LIST, len));
	}
};




struct Node_Expr_Var :public Node_Expr {
	virtual void print() = 0;
	virtual void load(ByteCodes* byteCodes,void*) = 0;
	virtual void store(ByteCodes* byteCodes) = 0;
};

struct Node_Expr_Var_Var :public Node_Expr_Var {
	std::string var_name;
	Node_Expr_Var_Var(const std::string& name):var_name(name){}
	virtual void print() {
		cout << var_name;
	}
	virtual void load(ByteCodes* byteCodes,void*) {
		Name_Type name = var_name.c_str();
		unsigned short id = byteCodes->insert(name);
		byteCodes->insert(CAT_INS(LOAD_NAME, id));
	}
	virtual void store(ByteCodes* byteCodes) {
		Name_Type name = var_name.c_str();
		unsigned short id = byteCodes->insert(name);
		byteCodes->insert(CAT_INS(STORE_NAME, id));
	}
};

struct Node_Expr_Var_Attr :public Node_Expr_Var {
	Node_Expr_Var* left;
	Node_Expr_Var_Var* right;
	Node_Expr_Var_Attr(Node_Expr_Var* left_,Node_Expr_Var_Var* right_):left(left_),right(right_){}
	virtual void print() {
		left->print(); cout << "."; right->print();
	}
	virtual void load(ByteCodes* byteCodes, void* msg) {
		left->load(byteCodes, msg);
		Name_Type name = right->var_name.c_str();
		unsigned short id = byteCodes->insert(name);
		byteCodes->insert(CAT_INS(LOAD_ATTR, id));
	}
	virtual void store(ByteCodes* byteCodes) {
		left->load(byteCodes,nullptr);
		Name_Type name = right->var_name.c_str();
		unsigned short id = byteCodes->insert(name);
		byteCodes->insert(CAT_INS(STORE_ATTR, id));
	}
};

struct Node_Expr_Var_SubAccess :public Node_Expr_Var {
	Node_Expr_Var* left;
	Node_Expr* sub;
	Node_Expr_Var_SubAccess(Node_Expr_Var* left_,Node_Expr* sub_):left(left_),sub(sub_){}
	virtual void print() {
		left->print(); cout << "["; sub->print(); cout << "]";
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		left->load(byteCodes, msg);
		sub->load(byteCodes, msg);
		byteCodes->insert(CAT_INS(ITEM_GET,0));
	}
	virtual void store(ByteCodes* byteCodes) {
		left->load(byteCodes,nullptr);
		sub->load(byteCodes,nullptr);
		byteCodes->insert(CAT_INS(ITEM_SET, 0));
	}
};

struct Node_Expr_Call :public Node_Expr {
	Node_Expr_Var* caller;
	std::vector<Node_Expr*> args;
	Node_Expr_Call(Node_Expr_Var* caller_, const std::vector<Node_Expr*>& args_) :caller(caller_), args(args_) {}
	virtual void print() {
		caller->print();
		cout << "(";
		unsigned short len = args.size();
		for (unsigned short i = 0; i < len ; i++) {
			Node_Expr* arg = args[i];
			arg->print();
			if (i == len - 1)break;
			cout << ",";
		}
		cout << ")";
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		unsigned short arg_num = args.size();
		caller->load(byteCodes, msg);
		if (Node_Expr_Var_Attr* attr = dynamic_cast<Node_Expr_Var_Attr*>(caller); attr) {
			attr->left->load(byteCodes, msg);
			++arg_num;
		}
		for (Node_Expr* arg : args) {
			arg->load(byteCodes, msg);
		}
		byteCodes->insert(CAT_INS(CALL_FUNCTION, arg_num));
	}
};

struct Node_Assign :public Node {
	Node_Expr_Var* var;
	Node_Expr* expr;
	Node_Assign(Node_Expr_Var* variant_,Node_Expr* expr_):var(variant_),expr(expr_){}
	virtual void print() {
		var->print(); cout << " = "; expr->print();
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		expr->load(byteCodes, msg);
		var->store(byteCodes);
	}
};

struct Node_Inplace :public Node {
	Node_Expr_Var* left;
	Node_Expr* right;
	TokenType opType;

	Node_Inplace(Node_Expr_Var* left_,Node_Expr* right_,TokenType opType_):
	left(left_),right(right_),opType(opType_){}

	virtual void print() {
		left->print();
		string op = "";
		switch (opType)
		{
		case TokenType::TOKEN_INPLACE_ADD:
			op = "+=";
			break;
		case TokenType::TOKEN_INPLACE_SUB:
			op = "-=";
			break;
		case TokenType::TOKEN_INPLACE_MUL:
			op = "*=";
			break;
		case TokenType::TOKEN_INPLACE_DIV:
			op = "/=";
			break;
		case TokenType::TOKEN_INPLACE_POW:
			op = "^=";
			break;
		default:
			assert(0);
			break;
		}
		cout << " " << op << " ";
		right->print();
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		left->load(byteCodes, msg);
		right->load(byteCodes, msg);
		unsigned short type;
		switch (opType)
		{
		case TokenType::TOKEN_INPLACE_ADD:
			type = BINARY_ARIT_ADD;
			break;
		case TokenType::TOKEN_INPLACE_SUB:
			type = BINARY_ARIT_SUB;
			break;
		case TokenType::TOKEN_INPLACE_MUL:
			type = BINARY_ARIT_MUL;
			break;
		case TokenType::TOKEN_INPLACE_DIV:
			type = BINARY_ARIT_DIV;
			break;
		case TokenType::TOKEN_INPLACE_POW:
			type = BINARY_ARIT_POW;
			break;
		default:
			assert(0);
			break;
		}
		byteCodes->insert(CAT_INS(BINARY_ARIT, type));
		left->store(byteCodes);
	}
};


struct Node_Program :public Node {
	
	std::vector<Node*> statements;
	Node_Program(const std::vector<Node*> statements_):statements(statements_){}
	virtual void print() {
		for_each(statements.begin(), statements.end(),
			[](Node* statement) {
				statement->print(); cout << endl;
			}
		);
	}
	virtual void load(ByteCodes* byteCodes,void*) = 0;
};

struct Node_Program_Modules :public Node_Program {
	
	Node_Program_Modules(const std::vector<Node*>& statements_):Node_Program(statements_){}
	ByteCodes* spawn() {
		ByteCodes* byteCodes = new ByteCodes("Modules");
		for (Node* statement : statements) {
			statement->load(byteCodes,nullptr);
		}
		ByteCodes_Array.push_back(byteCodes);
		return byteCodes;
	}
	virtual void load(ByteCodes* byteCodes,void*) {

	}
};

struct Node_Program_Function :public Node_Program {
	Node_Program_Function(const std::vector<Node*>& statements_):
	Node_Program(statements_){}

	ByteCodes* spawn(Node_Expr_Var_Var* funcName,const vector<Node_Expr_Var_Var*>& args) {
		ByteCodes* byteCodes = new ByteCodes(funcName->var_name);
		for_each(args.begin(), args.end(), [byteCodes](Node_Expr_Var_Var* arg) {byteCodes->insert(arg->var_name); });
		for_each(statements.begin(), statements.end(),
			[byteCodes](Node* statement) {
				statement->load(byteCodes,nullptr);
			}
		);
		ByteCodes_Array.push_back(byteCodes);
		return byteCodes;
	}
	void load_Program_Function(ByteCodes* byteCodes,Node_Expr_Var_Var* funcName,const vector<Node_Expr_Var_Var*>& args) {
		ByteCodes* funCode = spawn(funcName,args);
		unsigned short id = byteCodes->insert(funCode);
		byteCodes->insert(CAT_INS(LOAD_CONST, id));
	}

	virtual void load(ByteCodes* byteCodes,void* msg) {
		
	}
};

struct Node_Program_Class :public Node_Program {
	Node_Program_Class(const std::vector<Node*>& statements_):Node_Program(statements_){}

	ByteCodes* spawn(Node_Expr_Var_Var* className) {
		ByteCodes* classCodes = new ByteCodes(className->var_name);
		for_each(statements.begin(), statements.end(),
			[classCodes](Node* statement) {
				statement->load(classCodes,nullptr);
			}
		);
		classCodes->insert(CAT_INS(LOAD_LOCALS, 0));
		classCodes->insert(CAT_INS(RETURN_TOP,0));
		ByteCodes_Array.push_back(classCodes);
		return classCodes;
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {

	}
};

struct Node_Program_Loop :public Node_Program {
	Node_Program_Loop(const std::vector<Node*>& statements_) :Node_Program(statements_) {}

	virtual void load(ByteCodes* byteCodes,void* msg) {
		for_each(statements.begin(), statements.end(),
			[byteCodes,msg](Node* statement) {
				statement->load(byteCodes,msg);
			}
		);
	}
};

struct Node_Program_If :public Node_Program {
	Node_Program_If(const std::vector<Node*>& statements_):Node_Program(statements_){}

	virtual void load(ByteCodes* byteCodes,void* msg) {
		for_each(statements.begin(), statements.end(),
			[byteCodes,msg](Node* statement) {
				statement->load(byteCodes, msg);
			}
		);
	}
};

struct Node_MakeClass :public Node {
	Node_Expr_Var_Var* className;
	Node_Program_Class* classProgram;
	Node_MakeClass(Node_Expr_Var_Var* className_,Node_Program_Class* classProgam_):
	className(className_),classProgram(classProgam_){}

	virtual void print() {
		cout << "class " << className->var_name << "{" << endl;
		classProgram->print(); cout << "}" << endl;
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		Const_Type name = className->var_name.c_str();
		unsigned short id = byteCodes->insert(name);
		byteCodes->insert(CAT_INS(LOAD_CONST, id));
		ByteCodes* classCode = classProgram->spawn(className);
		id = byteCodes->insert(classCode);
		byteCodes->insert(CAT_INS(LOAD_CONST, id));
		byteCodes->insert(CAT_INS(MAKE_FUNCTION,0));
		byteCodes->insert(CAT_INS(CALL_FUNCTION,0));
		byteCodes->insert(CAT_INS(MAKE_CLASS, 0));
		className->store(byteCodes);
	}
};

struct Node_MakeFunction :public Node {
	Node_Expr_Var_Var* functionName;
	std::vector<Node_Expr_Var_Var*> args;
	Node_Program_Function* functionProgram;
	Node_MakeFunction(Node_Expr_Var_Var* funcName, Node_Program_Function* funcProgram,const vector<Node_Expr_Var_Var*>& args_):
	functionName(funcName), functionProgram(funcProgram),args(args_){}
	virtual void print() {
		cout << "def "; functionName->print(); cout << "(";
		for (unsigned short i = 0; i < args.size(); i++) {
			Node_Expr_Var_Var* arg = args[i];
			arg->print();
			if (i == args.size() - 1)break;
			cout << ",";
		}
		cout << ")"; cout << "{" << endl;
		functionProgram->print(); cout << "}" << endl;
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		functionProgram->load_Program_Function(byteCodes,functionName,args);
		byteCodes->insert(CAT_INS(MAKE_FUNCTION, 0));
		functionName->store(byteCodes);
	}
};



struct Node_ForLoop :public Node {
	Node_Expr_Var* loop_var;
	Node_Expr* loop_iter;
	Node_Program_Loop* loop_body;

	Node_ForLoop(Node_Expr_Var* loop_var_,Node_Expr* loop_iter_,Node_Program_Loop* loop_body_):
	loop_var(loop_var_),loop_iter(loop_iter_),loop_body(loop_body_){}

	virtual void print() {
		cout << "for "; loop_var->print(); cout << " in "; loop_iter->print(); cout << "{" << endl;
		loop_body->print(); cout << "}" << endl;
	}

	virtual void load(ByteCodes* byteCodes,void* msg) {
		loop_iter->load(byteCodes, msg);
		byteCodes->insert(CAT_INS(GET_ITER, 0));
		unsigned short sign = byteCodes->insert(CAT_INS(NEXT_ITER, 0));
		loop_var->store(byteCodes);
		loop_body->load(byteCodes, msg);
		byteCodes->insert(CAT_INS(JUMP_ABSOLUTE, sign));
		unsigned short dist = byteCodes->getInsSize() - sign;
		byteCodes->setIns(CAT_INS(NEXT_ITER, dist),sign);
		byteCodes->insert(CAT_INS(STACK_POP, 0));
	}
};

struct Node_WhileLoop :public Node {
	Node_Expr* loop_condition;
	Node_Program_Loop* loop_body;

	Node_WhileLoop(Node_Expr* condition_,Node_Program_Loop* loop_body_):
	loop_condition(condition_),loop_body(loop_body_){}

	virtual void print() {
		cout << "while "; loop_condition->print(); cout << "{" << endl;
		loop_body->print(); cout << "}" << endl;
	}

	virtual void load(ByteCodes* byteCodes,void* msg) {
		Instruction_Type head, tail;
		void* binder = pos_bind(&head,&tail);
		unsigned short pos_head = byteCodes->getInsSize();
		loop_condition->load(byteCodes, msg);
		unsigned short sign = byteCodes->insert(CAT_INS(JUMP_IF_RELAIVE,0));
		loop_body->load(byteCodes, binder);
		byteCodes->insert(CAT_INS(JUMP_ABSOLUTE, pos_head));
		unsigned short pos_tail = byteCodes->getInsSize();
		unsigned short dist = byteCodes->getInsSize() - sign;
		byteCodes->setIns(CAT_INS(JUMP_IF_RELAIVE, dist), sign);
		head = CAT_INS(JUMP_ABSOLUTE, pos_head);
		tail = CAT_INS(JUMP_ABSOLUTE, pos_tail);
		byteCodes->eval_delays();
	}
};

struct Node_If :public Node {
	pair<Node_Expr*, Node_Program_If*> statement_if;
	vector<pair<Node_Expr*, Node_Program_If*>> statements_elif;
	Node_Program_If* statement_else;

	Node_If(pair<Node_Expr*, Node_Program_If*> statement_if_,
	const vector<pair<Node_Expr*, Node_Program_If*>>& statements_elif_,Node_Program_If* statement_else_):
	statement_if(statement_if_),statements_elif(statements_elif_),statement_else(statement_else_){}

	virtual void print() {
		cout << "if "; statement_if.first->print(); cout << "{" << endl; 
		statement_if.second->print(); cout << "}" << endl;

		for_each(statements_elif.begin(), statements_elif.end(),
		[](pair<Node_Expr*, Node_Program_If*> statement) {
			cout << "else if ";
			statement.first->print(); cout << "{" << endl;
			statement.second->print(); cout << "}" << endl;
		}
		);
		if (statement_else) {
			cout << "else " << "{" << endl; statement_else->print(); cout << "}" << endl;
		}
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {

		auto func = [byteCodes,msg](pair<Node_Expr*, Node_Program_If*> statement) {
			statement.first->load(byteCodes, msg);
			size_t sign = byteCodes->insert(CAT_INS(JUMP_IF_RELAIVE, 0));
			statement.second->load(byteCodes, msg);
			unsigned short dist = byteCodes->getInsSize() - sign;
			byteCodes->setIns(CAT_INS(JUMP_IF_RELAIVE, dist), sign);
		};
		func(statement_if);

		for_each(statements_elif.begin(), statements_elif.end(),func);
		if (statement_else) {
			statement_else->load(byteCodes,msg);
		}
	}
};

struct Node_Break :public Node {
	virtual void print() {
		cout << "break" ;
	}
	virtual void load(ByteCodes* byteCodes,void* binder) {
		assert(binder);
		Instruction_Type** arr = static_cast<Instruction_Type**>(binder);
		Instruction_Type* tail = arr[1];
		byteCodes->bind_delay(tail);
	}
};

struct Node_Continue :public Node {
	virtual void print() {
		cout << "continue" ;
	}
	virtual void load(ByteCodes* byteCodes,void* binder) {
		assert(binder);
		Instruction_Type** arr = static_cast<Instruction_Type**>(binder);
		Instruction_Type* head = arr[0];
		byteCodes->bind_delay(head);
	}
};

struct Node_Return :public Node {
	Node_Expr* value;
	Node_Return(Node_Expr* value_):value(value_){}
	virtual void print() {
		cout << "return "; value->print();
	}
	virtual void load(ByteCodes* byteCodes,void* msg) {
		value->load(byteCodes,msg);
		byteCodes->insert(CAT_INS(RETURN_TOP, 0));
	}
};




class Parser {
	class Getter {
	private:
		const vector<Token>& tokens;
		int curPos;
	public:
		Getter(const vector<Token>& tokens_) :tokens(tokens_), curPos(0){}
		Getter& operator=(const Getter& other) {
			this->curPos = other.curPos;
			return *this;
		}

		Token next() {
			Token cur = tokens[curPos++];
			return cur;
		}

		Token current()const { 
			return tokens[curPos];
		}

		Token last()const {
			return tokens[curPos - 1];
		}
		Token peek(size_t i)const {
			size_t index = i + curPos;
			if (index > (tokens.size() - 1)) {
				return Token{ TokenType::TOKEN_EOF,"#" };
			}
			return tokens[index];
		}
		bool isEnd()const { return tokens[curPos].type == TokenType::TOKEN_EOF; }

	};
private:
	vector<Token> tokens;
	Getter getter;
	stack<Getter> records;
private:
	void recording() {
		records.push(getter);
	}
	void rollback() {
		if (records.empty())return;
		getter = records.top();
		records.pop();
	}
	void eraseRecord() {
		if (records.empty())return;
		records.pop();
	}
	Token next() {
		return getter.next();
	}
	Token current()const { return getter.current(); }
	Token last()const { return getter.last(); }
	Token peek(size_t i) { return getter.peek(i); }
	bool isEnd()const {
		return getter.isEnd();
	}
private:
	

	Node_Program_Modules* create_Node_Program_Modules() {
		std::vector<Node*> statements = {};
		while (!isEnd()) {
			Node* result = nullptr;
			if (Node* node = try_create(&Parser::create_Node_MakeClass); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_MakeFunction);node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_ForLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_WhileLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_If); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Operator); node) {
				result = node;
			}
			statements.push_back(result);
		}
		return new Node_Program_Modules(statements);
	}

	Node_Program_Function* create_Node_Program_Function() {
		std::vector<Node*> statements = {};
		while (current().type != TokenType::TOKEN_RBRACKER) {
			Node* result = nullptr;
			if (Node* node = try_create(&Parser::create_Node_ForLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_WhileLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_If); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Operator); node) {
				result = node;
			}
			statements.push_back(result);
		}
		return new Node_Program_Function(statements);
	}

	Node_MakeClass* create_Node_MakeClass() {
		Node_MakeClass* result = nullptr;
		if (!match(TokenType::TOKEN_KEYWORD_CLASS))return result;
		Node_Expr_Var_Var* className = try_create(&Parser::create_Node_Expr_Var_Var);
		if (className == nullptr) throw Error_Parser{ "Mising ClassName after 'class'",current().line,current().col };
		if(!match(TokenType::TOKEN_LBRACKER)) throw Error_Parser{ "Expected '{' before body of class",current().line,current().col };
		Node_Program_Class* classProgram = try_create(&Parser::create_Node_Program_Class);
		if(!match(TokenType::TOKEN_RBRACKER)) throw Error_Parser{ "Expected '}' after body of function",current().line,current().col };
		result = new Node_MakeClass(className,classProgram);
		return result;
	}

	Node_Program_Class* create_Node_Program_Class() {
		std::vector<Node*> statements = {};
		while (current().type != TokenType::TOKEN_RBRACKER) {
			Node* result = nullptr;
			if (Node* node = try_create(&Parser::create_Node_MakeFunction); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_ForLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_WhileLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_If); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Operator); node) {
				result = node;
			}
			statements.push_back(result);
		}
		return new Node_Program_Class(statements);
	}

	Node_MakeFunction* create_Node_MakeFunction() {
		Node_MakeFunction* result = nullptr;
		if (!match(TokenType::TOKEN_KEYWORD_DEF))return result;
		Node_Expr_Var_Var* funcName = try_create(&Parser::create_Node_Expr_Var_Var);
		if(!match(TokenType::TOKEN_LPAR)) throw Error_Parser{ "Expected '(' after name of function",current().line,current().col };
		std::vector<Node_Expr_Var_Var*> args{};
		for (Node_Expr_Var_Var* arg = try_create(&Parser::create_Node_Expr_Var_Var); arg; arg = try_create(&Parser::create_Node_Expr_Var_Var)) {
			args.push_back(arg);
			if (!match(TokenType::TOKEN_COMMA))break;
		}
		if(!match(TokenType::TOKEN_RPAR)) throw Error_Parser{ "Expected ')' after list of arguments",current().line,current().col };
		if(!match(TokenType::TOKEN_LBRACKER)) throw Error_Parser{ "Expected '{' before body of function",current().line,current().col };
		Node_Program_Function* funcProgram = try_create(&Parser::create_Node_Program_Function);
		if(!match(TokenType::TOKEN_RBRACKER)) throw Error_Parser{ "Expected '}' after body of function",current().line,current().col };
		result = new Node_MakeFunction(funcName, funcProgram, args);
		return result;
	}

	Node_WhileLoop* create_Node_WhileLoop() {
		Node_WhileLoop* result = nullptr;
		if (!match(TokenType::TOKEN_KEYWORD_WHILE))return result;
		Node_Expr* condition = try_create(&Parser::create_Expr);
		if(condition == nullptr) throw Error_Parser{ "Missing expresstion in the parens",current().line,current().col };
		if(!match(TokenType::TOKEN_LBRACKER)) throw Error_Parser{ "Expected '{' before body of loop",current().line,current().col };
		Node_Program_Loop* loop_body = try_create(&Parser::create_Node_Program_Loop);
		if(!match(TokenType::TOKEN_RBRACKER)) throw Error_Parser{ "Expected '}' after body of function",current().line,current().col };
		result = new Node_WhileLoop(condition, loop_body);
		return result;
	}

	Node_Program_Loop* create_Node_Program_Loop() {
		std::vector<Node*> statements = {};
		while (current().type != TokenType::TOKEN_RBRACKER) {
			Node* result = nullptr;
			if (Node* node = try_create(&Parser::create_Node_ForLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_WhileLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_If); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Operator); node) {
				result = node;
			}
			statements.push_back(result);
		}
		return new Node_Program_Loop(statements);
	}

	Node_ForLoop* create_Node_ForLoop() {
		Node_ForLoop* result = nullptr;
		if (!match(TokenType::TOKEN_KEYWORD_FOR))return result;
		Node_Expr_Var* loop_var = try_create(&Parser::create_Node_Expr_Var);
		if(loop_var == nullptr) throw Error_Parser{ "Missing expression after 'for'",current().line,current().col };
		if(!match(TokenType::TOKEN_KEYWORD_IN)) throw Error_Parser{ "Missing keyword('in') after expreesion",current().line,current().col };
		Node_Expr* loop_iter = try_create(&Parser::create_Expr);
		if(loop_iter == nullptr)throw Error_Parser{ "Missing expression after 'in'",current().line,current().col };
		if(!match(TokenType::TOKEN_LBRACKER)) throw Error_Parser{ "Expected '{' before body of loop",current().line,current().col };
		Node_Program_Loop* loop_body = try_create(&Parser::create_Node_Program_Loop);
		if(!match(TokenType::TOKEN_RBRACKER)) throw Error_Parser{ "Expected '}' after body of loop",current().line,current().col };
		result = new Node_ForLoop(loop_var,loop_iter,loop_body);
		return result;
	}

	Node_If* create_Node_If() {
		Node_If* result = nullptr;
		if (!match(TokenType::TOKEN_KEYWORD_IF))return nullptr;
		if (Node_Expr* condition_if = try_create(&Parser::create_Expr); condition_if) {
			if(!match(TokenType::TOKEN_LBRACKER)) throw Error_Parser{ "Expected '{' before body of if",current().line,current().col };
			Node_Program_If* statement_if = try_create(&Parser::create_Node_Program_If);
			if(!match(TokenType::TOKEN_RBRACKER))throw Error_Parser{ "Expected '}' after body of if",current().line,current().col };
			std::vector<pair<Node_Expr*, Node_Program_If*>> statements_elif{};
			while (match(TokenType::TOKEN_KEYWORD_ELIF)) {
				Node_Expr* condition = try_create(&Parser::create_Expr);
				if(condition == nullptr) throw Error_Parser{ "Missing expression after 'elif'",current().line,current().col };
				if(!match(TokenType::TOKEN_LBRACKER)) throw Error_Parser{ "Expected '{' before body of elif",current().line,current().col };
				Node_Program_If* statement = try_create(&Parser::create_Node_Program_If);
				if(!match(TokenType::TOKEN_RBRACKER)) throw Error_Parser{ "Expected '}' after body of elif",current().line,current().col };
				statements_elif.push_back(pair(condition, statement));
			}
			Node_Program_If* statement_else = nullptr;
			if (match(TokenType::TOKEN_KEYWORD_ELSE)) {
				if(!match(TokenType::TOKEN_LBRACKER)) throw Error_Parser{ "Expected '{' before body of else",current().line,current().col };
				statement_else = try_create(&Parser::create_Node_Program_If);
				if(!match(TokenType::TOKEN_RBRACKER)) throw Error_Parser{ "Expected '}' after body of else",current().line,current().col };
			}
			result = new Node_If(pair(condition_if,statement_if),statements_elif,statement_else);
		}
		else {
			throw Error_Parser{ "Missing expression after 'if'",current().line,current().col };
		}
		return result;
	}

	Node_Program_If* create_Node_Program_If() {
		std::vector<Node*> statements = {};
		while (current().type != TokenType::TOKEN_RBRACKER) {
			Node* result = nullptr;
			if (Node* node = try_create(&Parser::create_Node_ForLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_WhileLoop); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Node_If); node) {
				result = node;
			}
			else if (Node* node = try_create(&Parser::create_Operator); node) {
				result = node;
			}
			statements.push_back(result);
		}
		return new Node_Program_If(statements);
	}

	Node* create_Operator() {
		Node* res = nullptr;
		if (Node* node = try_create(&Parser::create_Node_Break); node) {
			res = node;
		}
		else if (Node* node = try_create(&Parser::create_Node_Continue); node) {
			res = node;
		}
		else if (Node* node = try_create(&Parser::create_Node_Return); node) {
			res = node;
		}
		else if (Node* node = try_create(&Parser::create_Node_Assign); node) {
			res = node;
		}
		else if (Node* node = try_create(&Parser::create_Node_Inplace); node) {
			res = node;
		}
		else if (Node* node = try_create(&Parser::create_Expr); node) {
			res = node;
		}
		return res;
	}

	Node_Inplace* create_Node_Inplace() {
		Node_Expr_Var* left = try_create(&Parser::create_Node_Expr_Var);
		Node_Inplace* result = nullptr;
		if (left == nullptr)return nullptr;
		if (match({ TokenType::TOKEN_INPLACE_ADD,TokenType::TOKEN_INPLACE_SUB,
		TokenType::TOKEN_INPLACE_MUL,TokenType::TOKEN_INPLACE_DIV,TokenType::TOKEN_INPLACE_POW })) {
			TokenType opType = last().type;
			Node_Expr* right = try_create(&Parser::create_Expr);
			if(right == nullptr)throw Error_Parser{ "unmatch expression after operator",current().line,current().col };
			result = new Node_Inplace(left, right, opType);
		}
		return result;
	}

	Node_Break* create_Node_Break() {
		Node_Break* result = nullptr;
		if (match(TokenType::TOKEN_KEYWORD_BREAK)) {
			result = new Node_Break();
		}
		return result;
	}

	Node_Continue* create_Node_Continue() {
		Node_Continue* result = nullptr;
		if (match(TokenType::TOKEN_KEYWORD_CONTINUE)) {
			result = new Node_Continue();
		}
		return result;
	}

	Node_Return* create_Node_Return() {
		Node_Return* result = nullptr;
		if (match(TokenType::TOKEN_KEYWORD_RETURN)) {
			Node_Expr* value = try_create(&Parser::create_Expr);
			result = new Node_Return(value);
		}
		return result;
	}

	Node_Assign* create_Node_Assign() {
		Node_Assign* result = nullptr;
		if (Node_Expr_Var* var = try_create(&Parser::create_Node_Expr_Var); var && match(TokenType::TOKEN_ASSIGN)) {
			Node_Expr* expr = try_create(&Parser::create_Expr);
			if(expr == nullptr)throw Error_Parser{ "unmatch expression after operator('=')",current().line,current().col };
			result =  new Node_Assign(var, expr);
		}
		return result;
	}


	Node_Expr* create_Expr() {
		Node_Expr* expr = try_create(&Parser::create_Expr_0);
		return expr;
	}


	Node_Expr* create_Expr_0() {
		Node_Expr* left = try_create(&Parser::create_Expr_1);
		if (left == nullptr)return nullptr;
		if (match({ TokenType::TOKEN_KEYWORD_AND,TokenType::TOKEN_KEYWORD_OR })) {
			TokenType opType = last().type;
			Node_Expr* right = try_create(&Parser::create_Expr_0);
			if(right == nullptr)throw Error_Parser{ "unmatch expression after operator",current().line,current().col };
			left = new Node_Expr_Logical(left, right, opType);
		}
		return left;
	}


	Node_Expr* create_Expr_1() {
		Node_Expr* left = try_create(&Parser::create_Expr_2);
		if (left == nullptr)return nullptr;
		if (match({ TokenType::TOKEN_EQ,TokenType::TOKEN_NEQ,TokenType::TOKEN_LT,
			TokenType::TOKEN_LTE,TokenType::TOKEN_GT,TokenType::TOKEN_GTE })) {
			TokenType opType = last().type;
			Node_Expr* right = try_create(&Parser::create_Expr_2);
			if (right == nullptr) throw Error_Parser{ "unmatch expression after operator",current().line,current().col };
			return new Node_Expr_Compare(left, right, opType);
		}
		return left;
	}

	Node_Expr* create_Expr_2() {
		Node_Expr* left = try_create(&Parser::create_Expr_3);
		if (left == nullptr)return nullptr;
		Node_Expr* right = nullptr;
		while (match({ TokenType::TOKEN_ADD,TokenType::TOKEN_MIN })) {
			TokenType opType = last().type;
			right = try_create(&Parser::create_Expr_3);
			if (right == nullptr) throw Error_Parser{ "unmatch expression after operator",current().line,current().col };
			left = new Node_Expr_ALG(left, right, opType);
		}
		return left;
	}

	Node_Expr* create_Expr_3() {
		Node_Expr* left = try_create(&Parser::create_Expr_4);
		if (left == nullptr)return nullptr;
		Node_Expr* right = nullptr;
		while (match({ TokenType::TOKEN_MUL,TokenType::TOKEN_DIV,TokenType::TOKEN_POW })) {
			TokenType opType = last().type;
			right = try_create(&Parser::create_Expr_4);
			if(right == nullptr) throw Error_Parser{ "unmatch expression after operator",current().line,current().col };
			left = new Node_Expr_ALG(left, right, opType);
		}
		return left;
	}

	Node_Expr* create_Expr_4() {
		Node_Expr* result = nullptr;
		if (match(TokenType::TOKEN_LPAR)) {
			result = try_create(&Parser::create_Expr_0);
			if(result == nullptr)throw Error_Parser{ "unmatch expression in the parents",current().line,current().col };
			if(!match(TokenType::TOKEN_RPAR))throw Error_Parser{ "Missing ')' after expression",current().line,current().col };
		}
		else if (match(TokenType::TOKEN_KEYWORD_NOT)) {
			Node_Expr* expr = try_create(&Parser::create_Expr_0);
			if(expr == nullptr)throw Error_Parser{ "Missing expression after 'not'",current().line,current().col };
			result = new Node_Expr_Unary_Not(expr);
		}
		else if (Node_Expr* expr = try_create(&Parser::create_Value); expr) {
			result = expr;
		}
		return result;
	}


	Node_Expr* create_Value() {
		Node_Expr* result = nullptr;
		if (Node_Expr* value = try_create(&Parser::create_Node_Expr_Int); value) {
			result = value;
		}
		else if (Node_Expr* value = try_create(&Parser::create_Node_Expr_Bool); value) {
			result = value;
		}
		else if (Node_Expr* value = try_create(&Parser::create_Node_Expr_Null); value) {
			result = value;
		}
		else if (Node_Expr* value = try_create(&Parser::create_Node_Expr_Str); value) {
			result = value;
		}
		else if (Node_Expr* value = try_create(&Parser::create_Node_Expr_List); value) {
			result = value;
		}
		else if (Node_Expr* value = try_create(&Parser::create_Node_Expr_Call); value) {
			result = value;
		}
		else if (Node_Expr* value = try_create(&Parser::create_Node_Expr_Var); value) {
			result = value;
		}
		return result;
	}

	

	Node_Expr_Var* create_Node_Expr_Var() {
		Node_Expr_Var* left = try_create(&Parser::create_Node_Expr_Var_Var);
		if (left == nullptr)return nullptr;
		Node_Expr_Var_Var* right = nullptr;
		while (match({TokenType::TOKEN_DOT,TokenType::TOKEN_LMBRACKER})) {
			if (last().type == TokenType::TOKEN_DOT) {
				if(!match(TokenType::TOKEN_IDENTIFIER))throw Error_Parser{ "must be identifier after '.'",current().line,current().col };
				right = new Node_Expr_Var_Var(last().value);
				left = new Node_Expr_Var_Attr(left, right);
			}
			else if (last().type == TokenType::TOKEN_LMBRACKER) {
				Node_Expr* sub = try_create(&Parser::create_Expr);
				if(sub == nullptr)throw Error_Parser{ "unmatch expression in the '[]'",current().line,current().col };
				left = new Node_Expr_Var_SubAccess(left,sub);
				if(!match(TokenType::TOKEN_RMBRACKER))throw Error_Parser{ "Missing ']' after expression",current().line,current().col };
			}
		}
		return left;
	}

	Node_Expr_Var_Var* create_Node_Expr_Var_Var() {
		Node_Expr_Var_Var* result = nullptr;
		if (match(TokenType::TOKEN_IDENTIFIER)) {
			result = new Node_Expr_Var_Var(last().value);
		}
		return result;
	}

	Node_Expr_Call* create_Node_Expr_Call() {
		Node_Expr_Call* result = nullptr;
		if (Node_Expr_Var* caller = try_create(&Parser::create_Node_Expr_Var); caller) {
			if (match(TokenType::TOKEN_LPAR)) {
				std::vector<Node_Expr*> args{};
				for (Node_Expr* arg = try_create(&Parser::create_Expr); arg; arg = try_create(&Parser::create_Expr)) {
					args.push_back(arg);
					if (!match(TokenType::TOKEN_COMMA))break;
				}
				if(!match(TokenType::TOKEN_RPAR))throw Error_Parser{ "Missing ')' after list of arguments",current().line,current().col };
				result = new Node_Expr_Call(caller, args);
			}
		}
		return result;
	}

	Node_Expr_Int* create_Node_Expr_Int() {
		Node_Expr_Int* result = nullptr;
		if (match(TokenType::TOKEN_INT)) {
			result = new Node_Expr_Int(atoi(last().value.c_str()));
		}
		return result;
	}

	Node_Expr_Bool* create_Node_Expr_Bool() {
		Node_Expr_Bool* result = nullptr;
		if (match({ TokenType::TOKEN_KEYWORD_TRUE,TokenType::TOKEN_KEYWORD_FALSE })) {
			TokenType type = last().type;
			result = new Node_Expr_Bool(type == TokenType::TOKEN_KEYWORD_TRUE ? true : false);
		}
		return result;
	}

	Node_Expr_Str* create_Node_Expr_Str() {
		Node_Expr_Str* result = nullptr;
		if (match(TokenType::TOKEN_STR)) {
			result = new Node_Expr_Str(last().value);
		}
		return result;
	}

	Node_Expr_Null* create_Node_Expr_Null() {
		Node_Expr_Null* result = nullptr;
		if (match(TokenType::TOKEN_KEYWORD_NULL)) {
			result = new Node_Expr_Null();
		}
		return result;
	}

	Node_Expr_List* create_Node_Expr_List() {
		Node_Expr_List* result = nullptr;
		if (match(TokenType::TOKEN_LMBRACKER)) {
			std::vector<Node_Expr*> args{};
			for (Node_Expr* arg = try_create(&Parser::create_Expr); arg; arg = try_create(&Parser::create_Expr)) {
				args.push_back(arg);
				if (!match(TokenType::TOKEN_COMMA))break;
			}
			if(!match(TokenType::TOKEN_RMBRACKER))throw Error_Parser{ "Missing ']' match whit '['",current().line,current().col };
			
			result = new Node_Expr_List(args);
		}
		return result;
	}


	



















private:
	bool match(const vector<TokenType>& types) {
		if (isEnd()) { return false; }
		TokenType currentType = current().type;
		for (TokenType type : types) {
			if (currentType == type) {
				next();
				return true;
			}
		}
		return false;
	}
	bool match(TokenType tokenType) {
		if (isEnd()) { return false; }
		Token currentToken = current();
		if (currentToken.type == tokenType) {
			next();
			return true;
		}
		else {
			return false;
		}
	}


private:
	template<typename F,typename...Args>
	auto try_create(F function,Args&&...args)->decltype((this->*function)(args...)){
		if (isEnd())return nullptr;
		using ResType = decltype((this->*function)(args...));
		recording();
		if (ResType expr =(this->*function)(args...); expr) {
			eraseRecord();
			return expr;
		}
		rollback();
		return nullptr;
	}

public:
	Parser(const vector<Token>& tokens_):tokens(tokens_),getter(tokens){}
	Node_Program_Modules* create_AST() {
		return create_Node_Program_Modules();
	}
};







Export_CodeObject* to_Export_CodeObject(ByteCodes* byteCodes);

struct To_Export_Const_Type_Visitor {
	Export_Consts* exportConsts;
	To_Export_Const_Type_Visitor(Export_Consts* consts_):exportConsts(consts_){}
	void operator()(long value) {
		long* data = new long(value);
		insert_Export_Consts(exportConsts, data, OBJECT_TYPE_LONG);
	}
	void operator()(bool value) {
		long* data = new long(value);
		insert_Export_Consts(exportConsts, data, OBJECT_TYPE_BOOLEN);
	}
	void operator()(const char* value) {
		void* data = const_cast<char*>(value);
		insert_Export_Consts(exportConsts, data, OBJECT_TYPE_STR);
	}
	void operator()(Null_Type* value) {
		insert_Export_Consts(exportConsts, 0, OBJECT_TYPE_NULL);
	}
	void operator()(ByteCodes* byteCodes) {
		Export_CodeObject* data = to_Export_CodeObject(byteCodes);
		insert_Export_Consts(exportConsts, data, OBJECT_TYPE_CODE);
	}
};



Export_CodeObject* to_Export_CodeObject(ByteCodes* byteCodes) {
	const Names& names = byteCodes->getNames();
	const Consts& consts = byteCodes->getConsts();
	const Instructions& instructions = byteCodes->getInstruction();
	Export_Names* exportNames = create_Export_Names(names.size());
	Export_Consts* exportConsts = create_Export_Consts(consts.size());
	Export_Instructions* exportIns = create_Export_Instructions(instructions.size());
	for_each(names.begin(), names.end(), 
		[names, exportNames](const Name_Type& name) {
			insert_Export_Names(exportNames, name.c_str()); 
		});
	for_each(consts.begin(), consts.end(),
		[consts, exportConsts](const Const_Type& con) {
			std::visit(To_Export_Const_Type_Visitor(exportConsts),con);
		});
	for_each(instructions.begin(), instructions.end(),
		[instructions, exportIns](const Instruction_Type& ins) {
			insert_Export_Instructions(exportIns, ins);
		});
	Export_CodeObject* codeObject = create_Export_CodeObject(exportNames, exportConsts, exportIns);
	return codeObject;
}

class CMDLine {
	struct CompilingUnit {
		string text;
		vector<Token> tokens;
		Node_Program_Modules* ASTree;
		ByteCodes* mainModulesCodes;
		CompilingUnit():ASTree(nullptr),mainModulesCodes(nullptr){}
	};
private:
	CompilingUnit* result;
	bool isQuit;
private:
	string getInput() {
		cout << ">> ";
		string str = "";
		getline(cin, str);
		return str;
	}

	bool compiling(const string& path) {
		if (result) { delete result; }
		ByteCodes_Array.clear();
		result = new CompilingUnit();
		try {
			result->text = loadfile(path);
			result->tokens = getTokens(result->text);
			result->ASTree = getASTree(result->tokens);
			result->mainModulesCodes = getByteCodes(result->ASTree);
		}
		catch (const Error_Parser& error) {
			cout << "Error: "; error.what();
			return false;
		}
		catch (const Error_Lexer& error) {
			cout << "Error: "; error.what();
			return false;
		}
		catch (const char* mes) {
			cout << mes;
			return false;
		}
		return true;
	}

	string loadfile(const string& path) {
		fstream stream;
		stream.open(path);
		if (!stream.is_open())throw "failed to open file";
		string text = "";
		string str = "";
		while (getline(stream, str)) {
			if (str.empty())continue;
			text += str;
			text += '\n';
		}
		stream.close();
		return text;
	}

	vector<Token> getTokens(const string& text) {
		Lexer* lexer = new Lexer(text);
		auto tokens = lexer->getTokens();
		return tokens;
	}

	Node_Program_Modules* getASTree(const vector<Token>& tokens) {
		Parser* parser = new Parser(tokens);
		auto ASTree = parser->create_AST();
		return ASTree;
	}

	ByteCodes* getByteCodes(Node_Program_Modules* ast) {
		return ast->spawn();
	}

	void look(const string& name) {
		if (name == "TEXT") {
			cout << "text: " << result->text;
		}
		else if (name == "TOKEN") {
			cout << "tokens: "; printTokens(result->tokens); 
		}
		else if (name == "AST") {
			cout << "ASTree: "; result->ASTree->print(); 
		}
		else if (name == "CODE") {
			cout << "byteCodes: "; 
			for_each(ByteCodes_Array.begin(), ByteCodes_Array.end(),
				[](ByteCodes* code) {code->print(); cout << endl; });
		}
		else {
			cout << "no targetName: " << name;
		}
	}

	void help() {
		cout << "these for instruction: "; cout << endl;
		cout << "(-c pathName) "; cout << "compiling target file and leaving compilation results,pathName is the path of file" << endl;
		cout << "(-e) "; cout << "execute the compilation results" << endl;
		cout << "(-l targetName) "; cout << "observe the compilation results,targetName include TEXT,TOKEN,AST,CODE"<< endl;
		cout << "(-s sys) "; cout << "use cmd instruction" << endl;
		cout << "(-q) "; cout << "quit";
	}

	
	void execute_VM(ByteCodes* byteCodes) {
		Export_CodeObject* exportCodes = to_Export_CodeObject(byteCodes);
		init_environment();
		run_with_Export_CodeObject(exportCodes);
	}


	void execute_ViewInstruction(const string& ins) {
		if (ins.empty())return;
		if (ins[0] != '-')cout << "Unknown instruction";
		if(ins.size()<2)cout << "Unknown instruction";
		char c = ins[1];
		if (c == 'c') {
			string path = string(ins.begin() + 2, ins.end());
			for (size_t pos = path.find(' '); pos != string::npos; pos = path.find(' ')) { path.erase(pos, 1);}
			if (compiling(path))cout << "Compilation completed";
		}
		else if (c == 'e') {
			if (result == nullptr) { cout << "No compiling results at present" << endl; return; }
			execute_VM(result->mainModulesCodes);
		}
		else if (c == 'l') {
			if (result == nullptr) { cout << "No compiling results at present" << endl; return; }
			string name = string(ins.begin() + 2, ins.end());
			for (size_t pos = name.find(' '); pos != string::npos; pos = name.find(' ')) { name.erase(pos, 1); }
			look(name);
		}
		else if (c == 's') {
			string name = string(ins.begin() + 2, ins.end());
			for (size_t pos = name.find(' '); pos != string::npos; pos = name.find(' ')) { name.erase(pos, 1); }
			system(name.c_str());
		}
		else if (c == 'q') {
			isQuit = true;
		}
		else if (c == 'h') {
			help();
		}
		else {
			cout << "Unknown instruction";
		}
		cout << endl;
	}
public:
	CMDLine():isQuit(false),result(nullptr){}

	void run() {
		cout << "welcome,if have any doubt,please enter -h for help"<<endl;
		while (!isQuit) {
			string ins = getInput();
			execute_ViewInstruction(ins);
		}
	}
};


int main() {
	CMDLine* cmd = new CMDLine();
	cmd->run();
}

/*
int main() {
	fstream stream;
	stream.open("text.txt");
	string text = "";
	string str = "";
	while (getline(stream, str)) {
		if (str.empty())continue;
		text += str;
		text += '\n';
	}
	stream.close();
	Lexer* lexer = new Lexer(text);
	vector<Token> tokens;
	try {
		tokens = lexer->getTokens();
	}
	catch (const Error_Lexer& error) {
		error.what();
		return -1;
	}
	lexer->print(tokens);
	Parser* parser = new Parser(tokens);
	Node_Program_Modules* AST = nullptr;
	try {
		AST = parser->create_AST();
	}
	catch (const Error_Parser& error) {
		cout << "Error: "; error.what();
		return -1;
	}
	AST->print();
	ByteCodes* byteCodes = AST->spawn();
	for_each(ByteCodes_Array.begin(), ByteCodes_Array.end(),
		[](ByteCodes* code) {code->print(); cout << endl; });

	

	Export_CodeObject* exportCodes = to_Export_CodeObject(byteCodes);
	init_environment();
	run_with_Export_CodeObject(exportCodes);
}*/


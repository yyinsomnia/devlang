#ifndef PRIVATE_CROWBAR_H_INCLUDED
#define PRIVATE_CROWBAR_H_INCLUDED
#include <stdio.h>
#include "MEM.h"
#include "CRB.h"
#include "CRB_dev.h"

#define smaller(a, b) ((a) < (b) ? (a) : (b))
#define larger(a, b) ((a) > (b) ? (a) : (b))

#define MESSAGE_ARGUMENT_MAX	(256)
#define LINE_BUF_SIZE			(1024)

typedef enum {
	PARSE_ERR = 1,
	CHARACTER_INVALID_ERR,
	FUNCTION_NULTIPLE_DEFINE_ERR,
	COMPILE_ERROR_COUNT_PLUS_1
} CompileError;

typedef enum {
	VARIABLE_NOT_FOUND_ERR = 1, /* 假如忘记进行初始化时，变量中被置入0的概率是非常高的，那么枚举类型如果从1开始的话，可以更早地发现异常状态*/
	FUNCTION_NOT_FOUND_ERR,
	ARGUMENT_TOO_MANY_ERR,
	ARGUMENT_TOO_FEW_ERR,
	NOT_BOOLEAN_TYPE_ERR,
	MINUS_OPERAND_TYPE_ERR,
	BAD_OPERAND_TYPE_ERR,
	NOT_BOOLEAN_OPERATOR_ERR,
	FOPEN_ARGUMENT_TYPE_ERR,
	FCLOSE_ARGUMENT_TYPE_ERR,
	FGETS_ARGUMENT_TYPE_ERR,
	FPUTS_ARGUMENT_TYPE_ERR,
	NOT_NULL_OPERATOR_ERR,
	DIVISION_BY_ZERO_ERR,
	GLOBAL_VARIABLE_NOT_FOUND_ERR,
	GLOBAL_STATEMENT_IN_TOPLEVEL_ERR,
	BAD_OPERATOR_FOR_STRING_ERR,
	RUNTIME_ERROR_COUNT_PLUS_1 /* 有了 COMPILE_ERROR_COUNT_PLUS_1 这个可变元素，就可以借助其遍历所有枚举元素，并在后续程序中利用这一特性进行更丰富的处理 */
} RuntimeError;

typedef enum {
	INT_MESSAGE_ARGUMENT = 1,
	DOUBLE_MESSAGE_ARGUMENT,
	STRING_MESSAGE_ARGUMENT,
	CHARACTER_MESSAGE_ARGUMENT,
	POINTER_MESSAGE_ARGUMENT,
	MESSAGE_ARGUMENT_END
} MessageArgumentType;

typedef struct {
	char *format;
} MessageFormat;

typedef struct Expression_tag Expression;

typedef enum {
	BOOLEAN_EXPRESSION = 1, 	/* 布尔型常量 */
	INT_EXPRESSION,				/* 整数型常量 */
	DOUBLE_EXPRESSION,			/* 实数型常量 */
	STRING_EXPRESSION,			/* 字符串型常量 */
	IDENTIFIER_EXPRESSION,		/* 变量 */
	ASSIGN_EXPRESION,			/* 赋值表达式 */
	ADD_EXPRESSION,				/* 加法表达式 */
	SUB_EXPRESSION,				/* 减法表达式 */
	MUL_EXPRESSION,				/* 乘法表达式 */
	DIV_EXPRESSION,				/* 除法表达式 */
	MOD_EXPRESSION,				/* 求余表达式 */
	EQ_EXPRESSION,				/* == */
	NE_EXPRESSION,				/* != */
	GT_EXPRESSION,				/* > */
	GE_EXPRESSION,				/* >= */
	LT_EXPRESSION,				/* < */　
	LE_EXPRESSION,				/* <= */　
	LOGICAL_AND_EXPRESSION,		/* && */　
	LOGICAL_OR_EXPRESSION,		/* || */　
	MINUS_EXPRESSION,			/* 单目取负 */　
	FUNCTION_CALL_EXPRESSION,	/* 函数调用表达式 */　
	NULL_EXPRESSION,			/* null 表达式 */　
	EXPRESSION_TYPE_COUNT_PLUS_1
} ExpressionType;

#define dkc_is_math_operator(operator) \
  ((operator) == ADD_EXPRESSION || (operator) == SUB_EXPRESSION\
   || (operator) == MUL_EXPRESSION || (operator) == DIV_EXPRESSION\
   || (operator) == MOD_EXPRESSION)
   
typedef struct {
	Expression *left;
	Expression *right;
} BinaryExpression;

















struct Expression_tag {
	ExpressionType type;
	int line_num;
	union {
		CRB_Boolean				boolean_value;
		int						int_value;
		double					double_value;
		char					*string_value;
		AssignExpression		assign_expression;
		BinaryExpression		binary_expression;
		Expression 				*minus_expression;
		FunctionCallExpression	function_call_expression;
	} u;
};

typedef struct Statement_tag Statement;

typedef struct StatementList_tag {
	Statement	*statement;
	struct StatementList_tag	*next;
} StatementList;

typedef struct {
	StatementList		*statement_list;
} Block;

typedef struct {
	Expression		*condition;		/* 条件表达式 */
	Block			*block;			/* 可执行块 */
} WhileStatement;


typedef enum {
	EXPRESSION_STATEMENT = 1;
	GLOBAL_STATEMENT,
	IF_STATEMENT,
	WHILE_STATEMENT,
	FOR_STATEMENT,
	RETURN_STATEMENT,
	BREAK_STATEMENT,
	CONTINUE_STATEMENT,
	STATEMENT_TYPE_COUNT_PLUS_1
} StatementType;

struct Statement_tag {
	StatementType		type;
	int					line_number;
	union {
		Expression		*expression_s;
		GlobalStatement global_s;
		IfStatement		if_s;
		WhileStatement	while_s;
		ForStatement	for_s;
		ReturnStatement	return_s;
	} u;
};

typedef struct ParameterList_tag {
	char		*name;
	struct ParameterList_tag *next;
} ParameterList;

typedef enum {
	CROWBAR_FUNCTION_DEFINITION = 1;
	NATIVE_FUNCTION_DEFINITION
} FunctionDefinitionType;

typedef struct FunctionDefinition_tag {
	char				*name;
	FunctionDefinitionType		type;
	union {
		struct {
			ParameterList		*parameter;
			Block				*block;
		} crowbar_f;
		struct {
			CRB_NativeFunctionProc		*proc;
		} native_f;
	} u;
	struct FunctionDefinition_tag		*next;
} FunctionDefinition;

typedef struct Variable_tag {
	char		*name;
	CRB_Value	value;
	struct Variable_tag *next;
} Variable;

struct CRB_Interpreter_tag {
	MEM_Storage			interpreter_storage;
	MEM_Storage			execute_storage;
	Variable			*variable;
	FunctionDefinition	*function_list;
	StatementList		*statement_list;
	int 				current_line_number;
};
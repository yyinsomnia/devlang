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
	VARIABLE_NOT_FOUND_ERR = 1,
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
	RUNTIME_ERROR_COUNT_PLUS_1
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
	BOOLEAN_EXPRESSION = 1,
	INT_EXPRESSION,
	DOUBLE_EXPRESSION,
	STRING_EXPRESSION,
	IDENTIFIER_EXPRESSION,
	ASSIGN_EXPRESION,
	ADD_EXPRESSION,
	SUB_EXPRESSION,
	MUL_EXPRESSION,
	DIV_EXPRESSION,
	MOD_EXPRESSION,
	EQ_EXPRESSION,
	NE_EXPRESSION,
	GT_EXPRESSION,
	GE_EXPRESSION,
	LT_EXPRESSION,
	LE_EXPRESSION,
	LOGICAL_AND_EXPRESSION,
	LOGICAL_OR_EXPRESSION,
	MINUS_EXPRESSION,
	FUNCTION_CALL_EXPRESSION,
	NULL_EXPRESSION,
	EXPRESSION_TYPE_COUNT_PLUS_1
} ExpressionType;

#define dkc_is_math_operator(operator) \
  ((operator) == ADD_EXPRESSION || (operator) == SUB_EXPRESSION\
   || (operator) == MUL_EXPRESSION || (operator) == DIV_EXPRESSION\
   || (operator) == MOD_EXPRESSION)
   

















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
Expression *
crb_create_binary_expression(ExpressionType operator,
							 Expression *left, Expression *right)
{
	Expression *exp;
	exp = crb_alloc_expression(operator);
	exp->u.binary_expression.left = left;
	exp->u.binary_expression.right = right;
	return exp;
}

Expression *
crb_alloc_expression(ExpressionType type)
{
	Expression *exp;
	
	exp = crb_malloc(sizeof(Expression));
	exp->type = type;
	exp->line_num = crb_get_current_interpreter()->current_line_number;
	
	return exp;
}


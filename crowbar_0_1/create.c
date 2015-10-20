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
#include "semantics.hpp"

stmt* Semantics::new_block_stmt(std::vector<stmt*> stmt_seq)
{
	return new block_stmt(stmt_seq);
}

stmt* Semantics::new_if_stmt(expr* condition, stmt* if_true, stmt* if_false)
{
	return new if_stmt(condition, if_true, if_false);
}

stmt* Semantics::new_while_stmt(expr* condition, stmt* statement)
{
	return new while_stmt(condition, statement);
}

stmt* Semantics::new_break_stmt()
{
	return new break_stmt();
}

stmt* Semantics::new_continue_stmt()
{
	return new continue_stmt();
}

stmt* Semantics::new_return_stmt(expr* expression)
{
	return new return_stmt(expression);
}

stmt* Semantics::new_decl_stmt(decl* declaration)
{
	return new decl_stmt(declaration);
}

stmt* Semantics::new_expr_stmt(expr* expression)
{
	return new expr_stmt(expression);
}


type* Semantics::new_void_type()
{
	return new void_type(void_t);
}

type* Semantics::new_bool_type()
{
	return new bool_type(bool_t);
}

type* Semantics::new_int_type()
{
	return new int_type(int_t);
}

type* Semantics::new_float_type()
{
	return new float_type(mfloat_t);
}

type* Semantics::new_char_type()
{
	return new char_type(char_t);
}

type* Semantics::new_func_type(std::vector<type*> params, type_t ret_type)
{
	return new function_type(params, ret_type);
}

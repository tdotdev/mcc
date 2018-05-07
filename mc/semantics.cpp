#include "semantics.hpp"

decl* Semantics::new_program(std::vector<decl*> dec_seq)
{
	return nullptr;
}

decl* Semantics::new_var_decl(token* tok, type* t)
{
	return nullptr;
}

decl* Semantics::new_var_def(decl* var_decl, expr* e)
{
	return nullptr;
}

decl* Semantics::new_const_decl(token* tok, type* t)
{
	return nullptr;
}

decl* Semantics::new_const_def(decl* var_decl, expr* e)
{
	return nullptr;
}

decl* Semantics::new_val_decl(token* tok, type* t)
{
	return nullptr;
}

decl* Semantics::new_val_def(decl* var_decl, expr* e)
{
	return nullptr;
}

decl* Semantics::new_func_decl(token* tok, std::vector<decl*> params, type* t)
{
	return nullptr;
}
decl* Semantics::new_func_def(decl* func_decl, stmt* func_body)
{
	return nullptr;
}

decl* Semantics::new_param(token* param, type* t)
{
	return nullptr;
}



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

expr* Semantics::new_boolean_literal(token* tok)
{
	return nullptr;
}

expr* Semantics::new_integer_literal(token* tok)
{
	return nullptr;
}

expr* Semantics::new_float_literal(token* tok)
{
	return nullptr;
}

expr* Semantics::new_char_literal(token* tok)
{
	return nullptr;
}

expr* Semantics::new_string_literal(token* tok)
{
	return nullptr;
}

expr* Semantics::new_identifier(token* tok)
{
	return nullptr;
}

expr* Semantics::new_postfix_expr(expr* expression, std::vector<expr*> args)
{
	return nullptr;
}

expr* Semantics::new_unary_expr(token_name unary_op, expr* expression)
{
	return nullptr;
}

expr* Semantics::new_cast_expr(expr* cast_expr, type* ts)
{
	return nullptr;
}

expr* Semantics::new_mul_expr(token_name mul_op, expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_add_expr(token_name ad_op, expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_shift_expr(token_name shift_op, expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_rel_expr(token_name rel_op, expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_eq_expr(token_name eq_op, expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_bw_and_expr(expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_bw_xor_expr(expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_bw_or_expr(expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_log_and_expr(expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_log_or_expr(expr* lhs, expr* rhs)
{
	return nullptr;
}

expr* Semantics::new_cond_expr(expr* expr1, expr* expr2, expr* expr3)
{
	return nullptr;
}

expr* Semantics::new_assign_expr(expr* lhs, expr* rhs)
{
	return nullptr;
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

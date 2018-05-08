#include "semantics.hpp"

bool Semantics::is_arithmetic(expr* e)
{
	type* t = e->expr_type;

	switch(t->type_type)
	{
		case int_t:
		case mfloat_t:
			return true;
	}

	return false;
}

bool Semantics::is_type(expr* e, type* t)
{
	if (e->expr_type->type_type == t->type_type)
		return true;

	return false;
}

bool Semantics::is_reference(expr* e)
{
	if (e->expr_type->type_type == ref_t)
		return true;

	return false;
}

bool Semantics::is_same_type(expr* e1, expr* e2)
{
	if (!(e1->expr_type->type_type == e2->expr_type->type_type))
		return true;

	return false;
}

void Semantics::assert_type(expr* e, type_t t)
{
	if (!(e->expr_type->type_type == t))
		throw std::runtime_error("Expr e is not of type t");
}

void Semantics::assert_reference(expr* e)
{
	if (!(is_reference(e)))
		throw std::runtime_error("Reference type required");
}

void Semantics::assert_same_type(expr* e1, expr* e2)
{
	if (!(e1->expr_type->type_type == e2->expr_type->type_type))
		throw std::runtime_error("Expr e1 and e2 not same type");
}

void Semantics::assert_arithmetic(expr* e)
{
	if(!is_arithmetic(e))
		throw std::runtime_error("Arithmetics type required");
}


type* Semantics::common_type_of(expr* e1, expr* e2)
{
	if (is_same_type(e1, e2))
		return e1->expr_type;

	if (is_reference(e1))
		return e2->expr_type;

	if (is_reference(e2))
		return e1->expr_type;

	throw std::runtime_error("Undefined common type");
}

expr* Semantics::basic_to_bool(expr* e)
{
	type* t = e->expr_type;
	bool val = true;

	switch (t->type_type)
	{
		case bool_t:
			bool_literal* b = static_cast<bool_literal*>(e);
			val = b->value;
			break;
		case int_t:
			int_literal* i = static_cast<int_literal*>(e);
			if (i->value == 0)
				val = false;
			break;
		case mfloat_t:
			float_literal* f = static_cast<float_literal*>(e);
			if (f->value == 0)
				val = false;
			break;
		case char_t:
			char_literal* c = static_cast<char_literal*>(e);
			if (c->value == '\0')
				val = false;
			break;
		default:
			throw std::runtime_error("Not convertable to bool");
	}

	return new bool_literal(val, new_bool_type());
}

expr* Semantics::to_int(expr* e)
{
	int val;
	type* t = e->expr_type;

	switch (t->type_type)
	{
		case bool_t:
			bool_literal* b = static_cast<bool_literal*>(e);
			val = b->value;
		case char_t:
			char_literal* c = static_cast<char_literal*>(e);
			val = c->value;
		case mfloat_t:
			float_literal* f = static_cast<float_literal*>(e);
			val = f->value;
		default:
			throw std::runtime_error("Not convertable to int");
	}

	return new int_literal(val, new_int_type());
}

expr* Semantics::to_float(expr* e)
{
	float val;
	type* t = e->expr_type;
	if (t->type_type == int_t)
	{
		int_literal* i = static_cast<int_literal*>(e);
		val = i->value;
		return new float_literal(val, new_float_type());
	}

	throw std::runtime_error("Not convertable to float");
}

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
	boolean* bool_tok = static_cast<boolean*>(tok);

	return new bool_literal(bool_tok->val, new_bool_type());
}

expr* Semantics::new_integer_literal(token* tok)
{
	integer* int_tok = static_cast<integer*>(tok);

	return new int_literal(int_tok->val, new_int_type());
}

expr* Semantics::new_float_literal(token* tok)
{
	floating_point* float_tok = static_cast<floating_point*>(tok);

	return new float_literal(float_tok->val, new_float_type());
}

expr* Semantics::new_char_literal(token* tok)
{
	character* char_tok = static_cast<character*>(tok);

	return new char_literal(char_tok->val, new_char_type());
}

expr* Semantics::new_string_literal(token* tok)
{
	string* str_tok = static_cast<string*>(tok);

	return new string_literal(str_tok->val, new_string_type());
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
	assert_type(expr1, bool_t);
	assert_same_type(expr2, expr3);

	return new cond_expr(expr1, expr2, expr3);
}

expr* Semantics::new_assign_expr(expr* lhs, expr* rhs)
{
	assert_reference(lhs);
	assert_same_type(lhs, rhs);

	return new assign_expr(lhs, rhs);
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

type* Semantics::new_string_type()
{
	return new string_type(string_t);
}

type* Semantics::new_func_type(std::vector<type*> params, type_t ret_type)
{
	return new function_type(params, ret_type);
}

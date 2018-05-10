#include "semantics.hpp"

/*	HELPER FUNCTIONS	*/


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

type* Semantics::val_conv(expr* e)
{
	ref_type* r = dynamic_cast<ref_type*>(e->expr_type);
	if (r != nullptr)
		return r;
	

	throw std::runtime_error("Expected reference type");
}

bool Semantics::val_conv_is(expr* e, type* t)
{
	if (val_conv(e)->type_type == t->type_type)
		return true;
	
	return false;
}

bool Semantics::is_scalar(expr* e)
{
	type* t = e->expr_type;

	switch (t->type_type)
	{
		case func_t:
		case ref_t:
			return false;
		default:
			return true;
	}
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

bool Semantics::is_int(expr* e)
{
	if (e->expr_type->type_type == int_t)
		return true;

	return false;
}

expr* Semantics::basic_to_bool(expr* e)
{
	type* t = e->expr_type;
	bool val = true;

	switch (t->type_type)
	{
		case bool_t:
		{
			bool_literal* b = static_cast<bool_literal*>(e);
			val = b->value;
			break;
		}
		case int_t:
		{
			int_literal* i = static_cast<int_literal*>(e);
			if (i->value == 0)
				val = false;
			break;
		}
		case mfloat_t:
		{
			float_literal* f = static_cast<float_literal*>(e);
			if (f->value == 0)
				val = false;
			break;
		}
		case char_t:
		{
			char_literal* c = static_cast<char_literal*>(e);
			if (c->value == '\0')
				val = false;
			break;
		}
		default:
			throw std::runtime_error("Not convertable to bool");
	}

	return new bool_literal(val, new_bool_type());
}

bool Semantics::is_same_type(expr* e1, expr* e2)
{
	if (e1->expr_type->type_type == ref_t)
	{
		id_expr* e = static_cast<id_expr*>(e1);
		var_decl* v = static_cast<var_decl*>(e->ref_to);
		if (v->var_type->type_type == e2->expr_type->type_type)
			return true;
	}

	if (e1->expr_type->type_type == e2->expr_type->type_type)
		return true;

	return false;
}

void Semantics::assert_scalar(expr* e)
{
	if (!(is_scalar(e)))
		throw std::runtime_error("Expected scalar type");
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

void Semantics::assert_int(expr* e)
{
	if (!(is_int(e)))
		throw std::runtime_error("Integer type required");
}

void Semantics::assert_same_type(expr* e1, expr* e2)
{
	if (!(is_same_type(e1, e2)))
		throw std::runtime_error("Expr e1 and e2 not same type");
}

void Semantics::assert_arithmetic(expr* e)
{
	if(!is_arithmetic(e))
		throw std::runtime_error("Arithmetics type required");
}

type* Semantics::verify_conversion(expr* e, type* dest_type)
{
	type* expr_t = e->expr_type;

	switch (expr_t->type_type)
	{
		case bool_t:
		{
			switch (dest_type->type_type)
			{
				case bool_t:
				case int_t:
					return new_bool_type();
				default:
					return nullptr;
			}
		}
		case char_t:
		{
			switch (dest_type->type_type)
			{
				case char_t:
					return new_char_type();
				case int_t:
					return new_char_type();
				case bool_t:
					return new_bool_type();
				default:
					return nullptr;

			}
		}
		case int_t:
		{
			switch (dest_type->type_type)
			{
				case bool_t:
					return new_bool_type();
				case char_t:
					return new_char_type();
				case int_t:
					return new_int_type();
				case mfloat_t:
					return new_int_type();
				default:
					return nullptr;
			}
		}
		case mfloat_t:
		{
			switch (dest_type->type_type)
			{

				case int_t:
					return new_int_type();
				case mfloat_t:
					return new_float_type();
				case bool_t:
					return new_bool_type();
				default:
					return nullptr;
			}
		}
		case ptr_t:
		{
			switch (dest_type->type_type)
			{
				case ptr_t:
					return nullptr;
				case bool_t:
					return new_bool_type();
				default:
					return nullptr;
			}
		}
		case ref_t:
		{
			switch (dest_type->type_type)
			{
				case ref_t:
					return nullptr;
				default:
					return nullptr;
			}
		}
		default:
			throw std::runtime_error("Unsupported type provided");
	}

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



expr* Semantics::to_int(expr* e)
{
	int val;
	type* t = e->expr_type;

	switch (t->type_type)
	{
		case bool_t:
		{
			bool_literal* b = static_cast<bool_literal*>(e);
			val = b->value;
			break;
		}
		case char_t:
		{
			char_literal* c = static_cast<char_literal*>(e);
			val = c->value;
			break;
		}
		case mfloat_t:
		{
			float_literal* f = static_cast<float_literal*>(e);
			val = f->value;
			break;
		}
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

/*	DECLARATION SEMANTICS	*/

decl* Semantics::new_program(std::vector<decl*> decl_seq)
{
	return new program_decl(decl_seq);
}

decl* Semantics::new_var_decl(token* tok, type* t)
{
	identifier* id = static_cast<identifier*>(tok);
	decl* var = new var_decl(id->id, t, nullptr);

	sem_scope->add_decl(id->id, var);

	return var;
}

decl* Semantics::new_var_def(decl* d, expr* e)
{
	var_decl* declaration = static_cast<var_decl*>(d);
	decl* definition = new var_decl(declaration->id, declaration->var_type, e);

	return definition;
}

decl* Semantics::new_const_decl(token* tok, type* t)
{
	identifier* id = static_cast<identifier*>(tok);
	decl* cons = new const_decl(id->id, t, nullptr);

	sem_scope->add_decl(id->id, cons);

	return cons;
}

decl* Semantics::new_const_def(decl* d, expr* e)
{
	const_decl* declaration = static_cast<const_decl*>(d);
	decl* definition = new const_decl(declaration->id, declaration->const_type, e);

	return definition;
}

decl* Semantics::new_val_decl(token* tok, type* t)
{
	identifier* id = static_cast<identifier*>(tok);
	decl* val = new val_decl(id->id, t, nullptr);

	sem_scope->add_decl(id->id, val);

	return val;
}

decl* Semantics::new_val_def(decl* d, expr* e)
{
	val_decl* declaration = static_cast<val_decl*>(d);
	decl* definition = new val_decl(declaration->id, declaration->val_type, e);

	return definition;
}

decl* Semantics::new_func_decl(token* tok, std::vector<decl*> params, type* t)
{
	identifier* id = static_cast<identifier*>(tok);
	decl* declaration = new func_decl(id->id, params, t, nullptr);

	sem_scope->add_decl(id->id, declaration);

	return declaration;
}
decl* Semantics::new_func_def(decl* fd, stmt* func_body)
{
	func_decl* declaration = static_cast<func_decl*>(fd);
	decl* definition = new func_decl(declaration->id, declaration->params, declaration->ret_type, func_body);
	// scope it
	return definition;
}

decl* Semantics::new_param(token* param, type* t)
{
	identifier* id = static_cast<identifier*>(param);
	decl* parameter = new param_decl(id->id, t);

	sem_scope->add_decl(id->id, parameter);

	return parameter;
}

/*	STATEMENT SEMANTICS	*/

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

/*	EXPRESSION SEMANTICS	*/

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

decl* Semantics::lookup(std::string id)
{
	scope* s = sem_scope;

	while (s != nullptr)
	{
		 decl* d = s->find_decl(id);
		 if (d != nullptr)
			 return d;
		 s = s->parent_scope;
	}

	throw std::runtime_error("Undefined reference");
}

expr* Semantics::new_identifier(token* tok)
{
	identifier* id_tok = static_cast<identifier*>(tok);

	decl* d = lookup(id_tok->id);
	
	var_decl* v = static_cast<var_decl*>(d);

	return new id_expr(d, new_ref_type(v->var_type));
}

expr* Semantics::new_postfix_expr(expr* e, std::vector<expr*> args)
{
	//assert_type(e, func_t);

	ref_type* r = static_cast<ref_type*>(e->expr_type);

	//identifier* id_tok = static_cast<identifier*>(tok);
	//decl* function_declaration = lookup(id_tok->id);

	function_type* func = static_cast<function_type*>(e->expr_type);
	std::vector<type*> params = func->params;

	if (args.size() == params.size())
	{
		for (auto i = 0; i < params.size(); i++)
		{
			if (params[i]->type_type != args[i]->expr_type->type_type)
				throw std::runtime_error("Type error in arguments");
		}

		return new func_expr(e->expr_type, e, args);
	}

	throw std::runtime_error("Invalid number of arguments");
}

unary_op tok_to_op(token_name n)
{
	switch (n)
	{
		case tok_add:
			return u_add;
		case tok_sub:
			return u_sub;
		case tok_bitw_not:
			return u_sub;
		case tok_logical_not:
			return u_not;
		case tok_bitw_and:
			return u_ref;
		case tok_mul:
			return u_deref;
	default:
		throw std::runtime_error("Expected unary op token");
	}
}

expr* Semantics::new_unary_expr(token_name unary_op, expr* e)
{
	switch (unary_op)
	{
		case tok_add:
		case tok_sub:
		{
			assert_arithmetic(e);
			return new unary_expr(tok_to_op(unary_op), e, e->expr_type);
		}
		case tok_bitw_not:
		{
			assert_type(e, int_t);
			return new unary_expr(tok_to_op(unary_op), e, new_int_type());
		}
		case tok_logical_not:
		{
			assert_type(e, bool_t);
			return new unary_expr(tok_to_op(unary_op), e, new_bool_type());
		}
		case tok_bitw_and:
		{
			assert_type(e, ref_t);
			return new unary_expr(tok_to_op(unary_op), e, new_ptr_type(e->expr_type));
		}
		case tok_mul:
		{
			assert_type(e, ptr_t);
			return new unary_expr(tok_to_op(unary_op), e, new_ref_type(e->expr_type));
		}
	}

	throw std::runtime_error("Expected unary expression");
}

expr* Semantics::new_cast_expr(expr* expr, type* ts)
{
	type* t = verify_conversion(expr, ts);

	if (t == nullptr)
		throw std::runtime_error("Invalid cast expression");

	return new cast_expr(expr, ts);
}

expr* Semantics::new_mul_expr(token_name mul_op, expr* lhs, expr* rhs)
{
	assert_arithmetic(lhs);
	assert_arithmetic(rhs);

	type* t = common_type_of(lhs, rhs);

	binary_op op;

	switch (mul_op)
	{
		case tok_mul:
			op = bop_mul;
			break;
		case tok_div:
			op = bop_div;
			break;
		case tok_rem:
			op = bop_rem;
			break;
		default:
			throw std::runtime_error("Expected multiplicative operation");
	}

	return new binary_expr(op, lhs, rhs, t);
}

expr* Semantics::new_add_expr(token_name add_op, expr* lhs, expr* rhs)
{
	assert_arithmetic(lhs);
	assert_arithmetic(rhs);

	type* t = common_type_of(lhs, rhs);

	binary_op op;

	switch (add_op)
	{
		case tok_add:
			op = bop_add;
			break;
		case tok_sub:
			op = bop_sub;
			break;
		default:
			throw std::runtime_error("Expected additive operation");
	}

	return new binary_expr(op, lhs, rhs, t);
}

expr* Semantics::new_shift_expr(token_name shift_op, expr* lhs, expr* rhs)
{
	assert_int(lhs);
	assert_int(rhs);

	binary_op op;

	switch (shift_op)
	{
	case tok_shift_left:
		op = bop_lshift;
		break;
	case tok_shift_right:
		op = bop_rshift;
		break;
	default:
		throw std::runtime_error("Expected shift operation");
	}

	return new binary_expr(op, lhs, rhs, new_int_type());
}

expr* Semantics::new_rel_expr(token_name rel_op, expr* lhs, expr* rhs)
{
	assert_scalar(lhs);
	assert_scalar(rhs);

	binary_op op;

	switch (rel_op)
	{
		case tok_rel_gt:
			op = bop_gt;
			break;
		case tok_rel_lt:
			op = bop_lt;
			break;
		case tok_rel_ge:
			op = bop_gte;
			break;
		case tok_rel_le:
			op = bop_lte;
			break;
	default:
		throw std::runtime_error("Expected shift operation");
	}

	return new binary_expr(op, lhs, rhs, new_bool_type());
}

expr* Semantics::new_eq_expr(token_name eq_op, expr* lhs, expr* rhs)
{
	assert_scalar(lhs);
	assert_scalar(rhs);

	binary_op op;

	switch (eq_op)
	{
	case tok_rel_eq:
		op = bop_eq;
		break;
	case tok_rel_neq:
		op = bop_neq;
		break;
	default:
		throw std::runtime_error("Expected equality operation");
	}

	return new binary_expr(op, lhs, rhs, new_bool_type());
}

expr* Semantics::new_bw_and_expr(expr* lhs, expr* rhs)
{
	assert_int(lhs);
	assert_int(rhs);

	return new binary_expr(bop_bwand, lhs, rhs, new_int_type());
}

expr* Semantics::new_bw_xor_expr(expr* lhs, expr* rhs)
{
	assert_int(lhs);
	assert_int(rhs);

	return new binary_expr(bop_bwxor, lhs, rhs, new_int_type());
}

expr* Semantics::new_bw_or_expr(expr* lhs, expr* rhs)
{
	assert_int(lhs);
	assert_int(rhs);

	return new binary_expr(bop_bwor, lhs, rhs, new_int_type());
}

expr* Semantics::new_log_and_expr(expr* lhs, expr* rhs)
{
	assert_scalar(lhs);
	assert_scalar(rhs);

	return new binary_expr(bop_land, lhs, rhs, new_bool_type());
}

expr* Semantics::new_log_or_expr(expr* lhs, expr* rhs)
{
	assert_scalar(lhs);
	assert_scalar(rhs);

	return new binary_expr(bop_lor, lhs, rhs, new_bool_type());
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

type* Semantics::new_ptr_type(type* t)
{
	return new ptr_type(t, ptr_t);
}

type* Semantics::new_ref_type(type* t)
{
	return new ref_type(t, ref_t);
}

type* Semantics::new_string_type()
{
	return new string_type(string_t);
}

type* Semantics::new_func_type(std::vector<type*> params, type_t ret_type)
{
	return new function_type(params, ret_type);
}

void Semantics::new_global_scope()
{
	sem_scope = new scope(global);
}

void Semantics::new_param_scope()
{
	scope* new_scope = new scope(parameter);
	new_scope->parent_scope = sem_scope;
	sem_scope = new_scope;

}

void Semantics::new_block_scope()
{
	scope* new_scope = new scope(block);
	new_scope->parent_scope = sem_scope;
	sem_scope = new_scope;
}

void Semantics::exit_current_scope()
{
	sem_scope = sem_scope->parent_scope;
}

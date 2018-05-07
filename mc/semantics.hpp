#pragma once

#include <vector>
#include "expression.hpp"
#include "statement.hpp"
#include "declaration.hpp"
#include "type.hpp"
#include "token.hpp"


struct Semantics {

	decl* new_program(std::vector<decl*> dec_seq);
	decl* new_var_decl(token* tok, type* t);
	decl* new_var_def(decl* var_decl, expr* e);
	decl* new_const_decl(token* tok, type* t);
	decl* new_const_def(decl* var_decl, expr* e);
	decl* new_val_decl(token* tok, type* t);
	decl* new_val_def(decl* var_decl, expr* e);
	decl* new_func_decl(token* tok, std::vector<decl*> params, type* t);
	decl* new_func_def(decl* func_decl, stmt* func_body);
	decl* new_param(token* param, type* t);

	stmt* new_block_stmt(std::vector<stmt*> stmt_seq);
	stmt* new_if_stmt(expr* condition, stmt* if_true, stmt* if_false);
	stmt* new_while_stmt(expr* condition, stmt* statement);
	stmt* new_break_stmt();
	stmt* new_continue_stmt();
	stmt* new_return_stmt(expr* expression);
	stmt* new_decl_stmt(decl* declaration);
	stmt* new_expr_stmt(expr* expression);

	expr* new_boolean_literal(token* tok);
	expr* new_integer_literal(token* tok);
	expr* new_float_literal(token* tok);
	expr* new_char_literal(token* tok);
	expr* new_string_literal(token* tok);
	expr* new_identifier(token* tok);
	expr* new_postfix_expr(expr* expression, std::vector<expr*> args);
	expr* new_unary_expr(token_name unary_op, expr* expression);
	expr* new_cast_expr(expr* cast_expr, type* ts);
	expr* new_mul_expr(token_name mul_op, expr* lhs, expr* rhs);
	expr* new_add_expr(token_name ad_op, expr* lhs, expr* rhs);
	expr* new_shift_expr(token_name shift_op, expr* lhs, expr* rhs);
	expr* new_rel_expr(token_name rel_op, expr* lhs, expr* rhs);
	expr* new_eq_expr(token_name eq_op, expr* lhs, expr* rhs);
	expr* new_bw_and_expr(expr* lhs, expr* rhs);
	expr* new_bw_xor_expr(expr* lhs, expr* rhs);
	expr* new_bw_or_expr(expr* lhs, expr* rhs);
	expr* new_log_and_expr(expr* lhs, expr* rhs);
	expr* new_log_or_expr(expr* lhs, expr* rhs);
	expr* new_cond_expr(expr* expr1, expr* expr2, expr* expr3);
	expr* new_assign_expr(expr* lhs, expr* rhs);

	type* new_void_type();
	type* new_bool_type();
	type* new_int_type();
	type* new_float_type();
	type* new_char_type();
	type* new_func_type(std::vector<type*> params, type_t ret_type);

};
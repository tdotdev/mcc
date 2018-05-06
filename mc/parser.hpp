#pragma once

#include "token.hpp"
#include "location.hpp"

#include "semantics.hpp"
#include "expression.hpp"
#include "declaration.hpp"
#include "type.hpp"
#include "statement.hpp"

#include <vector>
#include <cassert>
#include <iostream>

struct Parser 
{
	Parser(const std::vector<token*>& token_stream);	

	Semantics semantics;

	std::vector<token*> tokens;
	std::vector<token*>::const_iterator first, last;

	token_name lookahead();
	token_name lookahead(int n);

	token* accept();

	void match(token_name tok);
	void match_if(token_name tok);

	// Types
	type* parse_basic_type();
	type* parse_postfix_type();
	type* parse_reference_type();
	type* parse_type();

	// Expressions
	expr* parse_primary_expr();
	expr* parse_postfix_expr();
	std::vector<expr*> parse_arg_list();
	expr* parse_arg();
	expr* parse_unary_expr();
	expr* parse_cast_expr();
	expr* parse_mul_expr();
	expr* parse_add_expr();
	expr* parse_shift_expr();
	expr* parse_rel_expr();
	expr* parse_eq_expr();
	expr* parse_bw_and_expr();
	expr* parse_bw_xor_expr();
	expr* parse_bw_or_expr();
	expr* parse_logical_and_expr();
	expr* parse_logical_or_expr();
	expr* parse_conditional_expr();
	expr* parse_assign_expr();
	expr* parse_expr();
	expr* parse_const_expr();
	token* match_if_postfix_expr();
	token* match_if_arg_list();
	token* match_if_mul_expr();
	token* match_if_add_expr();
	token* match_if_shift_expr();
	token* match_if_rel_expr();
	token* match_if_eq_expr();
	token* match_if_bw_and_expr();
	token* match_if_bw_xor_expr();
	token* match_if_bw_or_expr();
	token* match_if_logical_and_expr();
	token* match_if_logical_or_expr();

	// Statements
	stmt* parse_stmt();
	stmt* parse_block_stmt();
	std::vector<stmt*> parse_stmt_seq();
	stmt* parse_if_stmt();
	stmt* parse_while_stmt();
	stmt* parse_break_stmt();
	stmt* parse_continue_stmt();
	stmt* parse_return_stmt();
	stmt* parse_decl_stmt();
	stmt* parse_expr_stmt();
	token* is_stmt();

	// Declarations
	decl* parse_program();
	std::vector<decl*> parse_decl_seq();
	decl* parse_decl();
	decl* parse_local_decl();
	decl* parse_obj_def();
	decl* parse_var_def();
	decl* parse_const_def();
	decl* parse_val_def();
	decl* parse_func_def();
	std::vector<decl*> parse_param_list();
	decl* parse_param();
	token* match_if_param_list();
};
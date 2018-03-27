#pragma once

#include "token.hpp"
#include "location.hpp"
#include <vector>
#include <cassert>
#include <iostream>



struct Parser {

	std::vector<token*> tokens;

	std::vector<token*>::const_iterator first;
	std::vector<token*>::const_iterator last;

	Parser(const std::vector<token*>& token_stream);

	token_name lookahead();
	token_name lookahead(int n);
	
	void parse();
	void match(token_name tok);
	void accept();
	void accept(int n);


	// Types
	void parse_basic_type();
	void parse_type_list();
	void parse_postfix_type();
	void parse_reference_type();
	void parse_type();

	// Expressions
	void parse_primary_expr();
	void parse_postfix_expr();
	void parse_arg_list();
	void parse_arg();
	void parse_unary_expr();
	void parse_cast_expr();
	void parse_mul_expr();
	void parse_add_expr();
	void parse_shift_expr();
	void parse_rel_expr();
	void parse_eq_expr();
	void parse_bw_and_expr();
	void parse_bw_xor_expr();
	void parse_bw_or_expr();
	void parse_logical_and_expr();
	void parse_logical_or_expr();
	void parse_conditional_expr();
	void parse_assign_expr();
	void parse_expr();
	void parse_const_expr();

	// Statements
	void parse_stmt();
	void parse_block_stmt();
	void parse_stmt_seq();
	void parse_if_stmt();
	void parse_while_stmt();
	void parse_break_stmt();
	void parse_continue_stmt();
	void parse_return_stmt();
	void parse_decl_stmt();
	void parse_expr_stmt();

	// Declarations

	void parse_program();
	void parse_decl_seq();
	void parse_decl();
	void parse_local_decl();
	void parse_obj_def();
	void parse_var_def();
	void parse_const_def();
	void parse_val_def();
	void parse_func_def();
	void parse_param_list();
	void parse_param();



};




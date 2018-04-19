#include "parser.hpp"

Parser::Parser(const std::vector<token*>& token_stream)
{
	std::vector<token*>::const_iterator it;

	it = token_stream.begin();

	while (it != token_stream.end())
	{
		tokens.push_back(*it);
		it++;
	}

	first = tokens.begin();
	last = tokens.end();
	
}

token_name Parser::lookahead() {

	if(first != last)
		return (*first)->getType();

	return tok_eof;
}

token_name Parser::lookahead(int n)
{
	std::vector<token*>::const_iterator it{ first };

	for (it; it != first + n; ++it);

	return (*it)->getType();
}

void Parser::accept()
{
		assert(first != last);
		++first;
}

void Parser::accept(int n)
{
	for (int i = 0; i < n; i++)
	{
		assert(first != last);
		++first;
	}
}

void Parser::match(token_name tok)
{
	if ((*first)->getType() == tok)
	{
		accept();
		return;
	}
	throw std::runtime_error("Invalid match");
}

void Parser::match_if(token_name tok)
{
	if ((*first)->getType() == tok)
	{
		accept();
	}

}

void Parser::parse_basic_type()
{

	switch (lookahead())
	{
		case tok_ts_void:
		case tok_ts_bool:
		case tok_ts_int:
		case tok_ts_float:
		case tok_ts_char:
			return accept();
	}

	throw std::runtime_error("Expected basic-type");
}
void Parser::parse_type_list()
{}

void Parser::parse_postfix_type()
{
	switch (lookahead())
	{
		case tok_mul:
		case tok_kw_const:
		case tok_kw_volatile:
			return accept();

		case tok_left_bracket:
			match(tok_left_bracket);
			if (lookahead() != tok_right_brace)
				parse_expr();
			return match(tok_right_brace);

		default:
			return parse_basic_type();
	}

	throw std::runtime_error("Expected postfix type");
}


void Parser::parse_reference_type()
{
	parse_postfix_type();
	match_if(tok_bitw_and);
}

void Parser::parse_type()
{
	parse_reference_type();
}

void Parser::parse_primary_expr()
{
	switch(lookahead())
	{
		case tok_binary_integer:
		case tok_decimal_integer:
		case tok_hexadecimal_integer:
		case tok_boolean:
		case tok_floating_point:
		case tok_character:
		case tok_string:
		case tok_identifier:
			return accept();

		case tok_left_paren:
			match(tok_left_paren);
			parse_expr();
			return match(tok_right_paren);
	}

	throw std::runtime_error("Expected primary expression");
}

bool Parser::match_if_postfix_expr()
{
	switch (lookahead()) 
	{
		case tok_left_paren:
		case tok_left_bracket:
			accept();
			return true;
	}

	return false;
}

void Parser::parse_postfix_expr()
{
	parse_primary_expr();

	while (match_if_postfix_expr())
	{
		parse_arg_list();
		accept();
	}
}

bool Parser::match_if_arg_list()
{
	if (lookahead() == tok_comma)
	{
		accept();
		return true;
	}

	return false;
}

void Parser::parse_arg_list()
{
	parse_arg();
	while (match_if_arg_list())
		parse_arg();
}


void Parser::parse_arg()
{
	parse_expr();
}

void Parser::parse_unary_expr()
{
	switch (lookahead())
	{
		case tok_add:
		case tok_sub:
		case tok_bitw_not:
		case tok_logical_not:
		case tok_logical_and:
		case tok_mul:
			accept();
			parse_unary_expr();
		default:
			parse_postfix_expr();
	}
}


// fix me!!
void Parser::parse_cast_expr()
{
	parse_unary_expr();
}

bool Parser::match_if_mul_expr()
{
	switch (lookahead()) 
	{
		case tok_mul:
		case tok_div:
		case tok_rem:
			accept();
			return true;
	}

	return false;
}

void Parser::parse_mul_expr()
{
	parse_cast_expr();

	while (match_if_mul_expr())
		parse_cast_expr();
}

bool Parser::match_if_add_expr()
{
	switch (lookahead()) {
		case tok_add:
		case tok_sub:
			accept();
			return true;
		default:
			return false;
	}
}

void Parser::parse_add_expr()
{
	parse_mul_expr();

	while (match_if_add_expr())
		parse_mul_expr();
}

bool Parser::match_if_shift_expr()
{
	switch (lookahead()) 
	{
		case tok_shift_left:
		case tok_shift_right:
			accept();
			return true;
	}

	return false;
}

void Parser::parse_shift_expr()
{
	parse_add_expr();
	while (match_if_shift_expr())
	{
		parse_add_expr();
	}
}

bool Parser::match_if_rel_expr()
{
	switch (lookahead()) 
	{
		case tok_rel_lt:
		case tok_rel_gt:
		case tok_rel_le:
		case tok_rel_ge:
			accept();
			return true;
	}

	return false;
}

void Parser::parse_rel_expr()
{
	parse_shift_expr();

	while (match_if_rel_expr())
		parse_shift_expr();
}

bool Parser::match_if_eq_expr()
{
	switch (lookahead()) 
	{
		case tok_rel_eq:
		case tok_rel_neq:
			accept();
			return true;
	}

	return false;
}

void Parser::parse_eq_expr()
{
	parse_rel_expr();

	while (match_if_eq_expr())
		parse_rel_expr();
}

bool Parser::match_if_bw_and_expr()
{
	if (lookahead() == tok_bitw_and)
	{
		accept();
		return true;
	}

	return false;
}

void Parser::parse_bw_and_expr()
{
	parse_eq_expr();

	while (match_if_bw_and_expr())
		parse_eq_expr();
}


bool Parser::match_if_bw_xor_expr()
{
	if (lookahead() == tok_bitw_xor) 
	{
		accept();
		return true;
	}

	return false;
}

void Parser::parse_bw_xor_expr()
{
	parse_bw_and_expr();

	while (match_if_bw_xor_expr())
		parse_bw_and_expr();
}

bool Parser::match_if_bw_or_expr()
{
	if (lookahead() == tok_bitw_or) 
	{
		accept();
		return true;
	}

	return false;
}

void Parser::parse_bw_or_expr()
{
	parse_bw_xor_expr();

	while (match_if_bw_or_expr())
		parse_bw_xor_expr();
}

bool Parser::match_if_logical_and_expr()
{
	if (lookahead() == tok_logical_and) 
	{
		accept();
		return true;
	}

	return false;
}

void Parser::parse_logical_and_expr()
{
	parse_bw_or_expr();

	while (match_if_logical_and_expr())
		parse_bw_or_expr();
}

bool Parser::match_if_logical_or_expr()
{
	if (lookahead() == tok_logical_or) 
	{
		accept();
		return true;
	}

	return false;
}

void Parser::parse_logical_or_expr()
{
	parse_logical_and_expr();

	while (match_if_logical_or_expr())
		parse_logical_and_expr();
}

void Parser::parse_conditional_expr()
{
	parse_logical_or_expr();

	if (lookahead() == tok_conditional_operator)
	{
		accept();
		parse_expr();
		match(tok_colon);
		parse_conditional_expr();

	}
}

void Parser::parse_assign_expr()
{
	parse_conditional_expr();

	if (lookahead() == tok_assignment_operator)
	{
		accept();
		parse_assign_expr(); 
		return;
	}

}

void Parser::parse_expr()
{
	parse_assign_expr();
}

void Parser::parse_const_expr()
{
	parse_conditional_expr();
}

void Parser::parse_stmt()
{
	switch (lookahead()) 
	{
		case tok_left_brace:
			return parse_block_stmt();
		case tok_kw_if:
			return parse_if_stmt();
		case tok_kw_while:
			return parse_while_stmt();
		case tok_kw_break:
			return parse_break_stmt();
		case tok_kw_continue:
			return parse_continue_stmt();
		case tok_kw_return:
			return parse_return_stmt();
		case tok_kw_def:
		case tok_kw_let:
		case tok_kw_var:
			return parse_decl_stmt();	
	}

	parse_expr_stmt();
}

void Parser::parse_block_stmt()
{
	match(tok_left_brace);
	parse_stmt_seq();
	match(tok_right_brace);
}

bool Parser::match_if_stmt_seq()
{
	switch (lookahead())
	{
		case tok_kw_if:
		case tok_left_bracket:
		case tok_kw_while:
		case tok_kw_break:
		case tok_kw_continue:
		case tok_kw_return:
		case tok_kw_def:
		case tok_kw_let:
		case tok_kw_var:
		case tok_identifier:
			return true;
	}

	return false;
}

void Parser::parse_stmt_seq()
{
	parse_stmt();
	while (match_if_stmt_seq())
		parse_stmt();
}

void Parser::parse_if_stmt()
{
	match(tok_kw_if);
	match(tok_left_paren);
	parse_expr();
	match(tok_right_paren);
	parse_stmt();
	if (lookahead() == tok_kw_else) 
	{
		match(tok_kw_else);
		parse_stmt();
	}
	
}

void Parser::parse_while_stmt()
{
	match(tok_kw_while);
	match(tok_left_paren);
	parse_expr();
	match(tok_right_paren);
	parse_stmt();
}

void Parser::parse_break_stmt()
{
	match(tok_kw_break);
	match(tok_semicolon);
}

void Parser::parse_continue_stmt()
{
	match(tok_kw_continue);
	match(tok_semicolon);
}

void Parser::parse_return_stmt()
{
	match(tok_kw_return);
	if (lookahead() == tok_semicolon)
		return accept();
	parse_expr();
	match(tok_semicolon);
}

void Parser::parse_decl_stmt()
{
	parse_local_decl();
}

void Parser::parse_expr_stmt()
{
	parse_expr();
	match(tok_semicolon);
}

void Parser::parse_program()
{
	parse_decl_seq();
}

bool Parser::match_if_decl_seq()
{
	return false;
}

void Parser::parse_decl_seq()
{
	while(first != last)
		parse_decl();
}

void Parser::parse_decl()
{
	switch (lookahead()) 
	{
		case tok_kw_def: 
		{
			token_name la = lookahead(2);
			if (la == tok_colon)
				return parse_obj_def();
			else if (la == tok_left_paren)
				return parse_func_def();
		}
		case tok_kw_let:
		case tok_kw_var:
			return parse_obj_def();
	}

	throw std::runtime_error("Expected declaration");
}

void Parser::parse_local_decl()
{
	parse_obj_def();
}

void Parser::parse_obj_def()
{
	switch (lookahead())
	{
		case tok_kw_def:
			return parse_val_def();
		case tok_kw_let:
			return parse_const_def();
		case tok_kw_var:
			return parse_var_def();
	}

	throw std::runtime_error("Expected onject definition");
}

void Parser::parse_var_def()
{
	match(tok_kw_var);
	match(tok_identifier);
	match(tok_colon);
	parse_type();

	switch (lookahead()) 
	{
		case tok_semicolon:
			return match(tok_semicolon);
		case tok_assignment_operator:
			match(tok_assignment_operator);
			parse_expr();
			return match(tok_semicolon);
	}

	throw std::runtime_error("Expected variable definition");
}

void Parser::parse_const_def()
{
	match(tok_kw_let);
	match(tok_identifier);
	match(tok_colon);
	parse_type();
	match(tok_assignment_operator);
	parse_expr();
	match(tok_semicolon);
}

void Parser::parse_val_def()
{
	match(tok_kw_def);
	match(tok_identifier);
	match(tok_colon);
	parse_type();
	match(tok_assignment_operator);
	parse_expr();
	match(tok_semicolon);
}

void Parser::parse_func_def()
{
	match(tok_kw_def);
	match(tok_identifier);
	match(tok_left_paren);
	parse_param_list();
	match(tok_right_paren);
	match(tok_sub);
	match(tok_rel_gt);
	parse_type();
	parse_block_stmt();
}

bool Parser::match_if_param_list()
{
	if (lookahead() == tok_comma) 
	{
		accept();
		return true;
	}

	return false;
}

void Parser::parse_param_list()
{
	parse_param();

	while (match_if_param_list())
		parse_param();
}

void Parser::parse_param()
{
	match(tok_identifier);
	match(tok_colon);
	parse_type();
}
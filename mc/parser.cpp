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
	return (*first)->getType();
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


void Parser::parse()
{
	
}

void Parser::match(token_name tok)
{
	if ((*first)->getType() == tok)
	{
		++first;
		return;
	}
	throw std::runtime_error("Invalid match");
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
{}
void Parser::parse_type()
{
	parse_postfix_type();
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
void Parser::parse_postfix_expr()
{}
void Parser::parse_arg_list()
{}
void Parser::parse_arg()
{}
void Parser::parse_unary_expr()
{}
void Parser::parse_cast_expr()
{}
void Parser::parse_mul_expr()
{}
void Parser::parse_add_expr()
{}
void Parser::parse_shift_expr()
{}
void Parser::parse_rel_expr()
{}
void Parser::parse_eq_expr()
{}
void Parser::parse_bw_and_expr()
{}
void Parser::parse_bw_xor_expr()
{}
void Parser::parse_bw_or_expr()
{}
void Parser::parse_logical_and_expr()
{}
void Parser::parse_logical_or_expr()
{}
void Parser::parse_conditional_expr()
{}
void Parser::parse_assign_expr()
{
	parse_conditional_expr();
	match(tok_assignment_operator);
	
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
{}
void Parser::parse_block_stmt()
{}
void Parser::parse_stmt_seq()
{}
void Parser::parse_if_stmt()
{}
void Parser::parse_while_stmt()
{}
void Parser::parse_break_stmt()
{}
void Parser::parse_continue_stmt()
{}
void Parser::parse_return_stmt()
{}
void Parser::parse_decl_stmt()
{}
void Parser::parse_expr_stmt()
{}



void Parser::parse_program()
{
	parse_decl_seq();
}
void Parser::parse_decl_seq()
{

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
		{
			return parse_obj_def();
		}
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

	switch (lookahead()) {
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
	match(tok_sub);
	match(tok_rel_gt);
	parse_type();
	parse_block_stmt();
}
void Parser::parse_param_list()
{}
void Parser::parse_param()
{
	match(tok_identifier);
	match(tok_colon);
	parse_type();
}
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

token_name Parser::lookahead(int n)
{

	std::vector<token*>::const_iterator it{ first };
	//it = first;

	for (int i = 0; i < n; i++)
	{

		++it;
	}


	return (*it)->getType();
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
	parse_var_def();

}

void Parser::match(token_name tok)
{
	if ((*first)->getType() == tok)
	{
		++first;
		return;
	}
	throw std::runtime_error("Syntax error");
}

void Parser::parse_basic_type()
{
	const std::vector<token_name> types{ tok_ts_void, tok_ts_bool, tok_ts_int, tok_ts_float, tok_ts_char };

	std::vector<token_name>::const_iterator it{ std::find(types.begin(), types.end(), lookahead(0)) };

	if (it != types.end())
	{
		accept(1);
		return;
	}

	throw std::runtime_error("Syntax error");
}
void Parser::parse_type_list()
{}
void Parser::parse_postfix_type()
{}
void Parser::parse_reference_type()
{}
void Parser::parse_type()
{}

void Parser::parse_primary_expr()
{}
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
{}
void Parser::parse_expr()
{}
void Parser::parse_const_expr()
{}

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
{}
void Parser::parse_decl_seq()
{}
void Parser::parse_decl()
{}
void Parser::parse_local_decl()
{}
void Parser::parse_obj_def()
{}

void Parser::parse_var_def()
{
	match(tok_kw_var);
	match(tok_identifier);
	match(tok_colon);
	parse_basic_type();

	switch (lookahead(0)) {
		case tok_semicolon:
			match(tok_semicolon);
			return;
		case tok_assignment_operator:
			match(tok_assignment_operator);
			parse_expr();
			match(tok_semicolon);
			return;
	}
	throw std::runtime_error("Syntax error");
}

void Parser::parse_const_def()
{}
void Parser::parse_val_def()
{}
void Parser::parse_func_def()
{}
void Parser::parse_param_list()
{}
void Parser::parse_param()
{}
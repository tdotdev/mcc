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

inline token_name Parser::lookahead() {

	if(first != last)
		return (*first)->getType();

	return tok_eof;
}

inline token_name Parser::lookahead(int n)
{
	std::vector<token*>::const_iterator it{ first };

	for (it; it != first + n; ++it);

	return (*it)->getType();
}

inline token* Parser::accept()
{
		assert(first != last);
		token* current = *first;
		++first;
		return current;
}

inline void Parser::match(token_name tok)
{
	if ((*first)->getType() == tok)
	{
		accept();
		return;
	}
	throw std::runtime_error("Invalid match");
}

inline void Parser::match_if(token_name tok)
{
	if ((*first)->getType() == tok)
	{
		accept();
	}
	throw std::runtime_error("Invalid match");
}

type* Parser::parse_basic_type()
{

	switch (lookahead())
	{
		case tok_ts_void:
		case tok_ts_bool:
		case tok_ts_int:
		case tok_ts_float:
		case tok_ts_char: 
			accept();
			return new type;
	}

	throw std::runtime_error("Expected basic-type");
}

type* Parser::parse_postfix_type()
{
	switch (lookahead())
	{
		case tok_mul:
		case tok_kw_const:
		case tok_kw_volatile:
			accept();
			return new type;

		case tok_left_bracket:
			match(tok_left_bracket);
			if (lookahead() != tok_right_brace)
			{
				expr* e = parse_expr();
			}
			match(tok_right_brace);
			return new type;

		default:
			type* basic_type = parse_basic_type();
			return new type;
	}

	throw std::runtime_error("Expected postfix type");
}


type* Parser::parse_reference_type()
{
	type* post_type = parse_postfix_type();
	while (lookahead() == tok_bitw_and)
	{
		accept();
	}

	return new type;
}

type* Parser::parse_type()
{
	type* ref_type = parse_reference_type();

	return new type;
}

expr* Parser::parse_primary_expr()
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
			accept();
			return new expr;

		case tok_left_paren:
			match(tok_left_paren);
			expr* e = parse_expr();
			match(tok_right_paren);
			return new expr;
	}

	throw std::runtime_error("Expected primary expression");
}

token*Parser::match_if_postfix_expr()
{
	switch (lookahead()) 
	{
		case tok_left_paren:
		case tok_left_bracket:
			return accept();
	}

	return nullptr;
}

expr* Parser::parse_postfix_expr()
{
	expr* primary_expr = parse_primary_expr();

	while (match_if_postfix_expr())
	{
		std::vector<expr*> arg_list = parse_arg_list();
		accept();
	}

	return new expr;
}

token*Parser::match_if_arg_list()
{
	if (lookahead() == tok_comma)
	{
		return accept();
	}

	return nullptr;
}

std::vector<expr*> Parser::parse_arg_list()
{
	std::vector<expr*> arg_list;
	expr* arg = parse_arg();
	arg_list.push_back(arg);

	while (match_if_arg_list())
	{
		expr* arg_more = parse_arg();
		arg_list.push_back(arg_more);
	}

	return arg_list;
}


expr* Parser::parse_arg()
{
	expr* e = parse_expr();

	return new expr;
}

expr* Parser::parse_unary_expr()
{
	switch (lookahead())
	{
		case tok_add:
		case tok_sub:
		case tok_bitw_not:
		case tok_logical_not:
		case tok_logical_and:
		case tok_mul:
		{
			accept();
			expr* unary_expr = parse_unary_expr();
			return new expr;
		}
		default:
		{
			expr* post_expr = parse_postfix_expr();
			return new expr;
		}
	}
}

expr* Parser::parse_cast_expr()
{
	expr* unary_expr = parse_unary_expr();
	while (lookahead() == tok_kw_as) {
		accept();
		type* t = parse_type();
	}

	return new expr;
}

token*Parser::match_if_mul_expr()
{
	switch (lookahead()) 
	{
		case tok_mul:
		case tok_div:
		case tok_rem:
			return accept();
	}

	return nullptr;
}

expr* Parser::parse_mul_expr()
{
	expr* cast_expr = parse_cast_expr();

	while (match_if_mul_expr())
	{
		expr* cast_expr_more = parse_cast_expr();
	}

	return new expr;
}

token*Parser::match_if_add_expr()
{
	switch (lookahead()) {
		case tok_add:
		case tok_sub:
			return accept();
		default:
			return nullptr;
	}
}

expr* Parser::parse_add_expr()
{
	expr* mul_expr = parse_mul_expr();

	while (match_if_add_expr())
	{
		expr* mul_expr_more = parse_mul_expr();
	}

	return new expr;
}

token*Parser::match_if_shift_expr()
{
	switch (lookahead()) 
	{
		case tok_shift_left:
		case tok_shift_right:
			return accept();
	}

	return nullptr;
}

expr* Parser::parse_shift_expr()
{
	expr* add_expr = parse_add_expr();
	while (match_if_shift_expr())
	{
		expr* add_expr_more = parse_add_expr();
	}

	return new expr;
}

token*Parser::match_if_rel_expr()
{
	switch (lookahead()) 
	{
		case tok_rel_lt:
		case tok_rel_gt:
		case tok_rel_le:
		case tok_rel_ge:
			return accept();
	}

	return nullptr;
}

expr* Parser::parse_rel_expr()
{
	expr* shift_expr = parse_shift_expr();

	while (match_if_rel_expr())
	{
		expr* shift_expr_more = parse_shift_expr();
	}

	return new expr;
}

token*Parser::match_if_eq_expr()
{
	switch (lookahead()) 
	{
		case tok_rel_eq:
		case tok_rel_neq:
			return accept();
	}

	return nullptr;
}

expr* Parser::parse_eq_expr()
{
	expr* rel_expr = parse_rel_expr();

	while (match_if_eq_expr())
	{
		expr* rel_expr_more = parse_rel_expr();
	}

	return new expr;
}

token*Parser::match_if_bw_and_expr()
{
	if (lookahead() == tok_bitw_and)
	{
		return accept();
	}

	return nullptr;
}

expr* Parser::parse_bw_and_expr()
{
	expr* eq_expr = parse_eq_expr();

	while (match_if_bw_and_expr())
	{
		expr* eq_expr_more = parse_eq_expr();
	}

	return new expr;
}


token*Parser::match_if_bw_xor_expr()
{
	if (lookahead() == tok_bitw_xor) 
	{
		return accept();
	}

	return nullptr;
}

expr* Parser::parse_bw_xor_expr()
{
	expr* bw_and_expr = parse_bw_and_expr();

	while (match_if_bw_xor_expr())
	{
		expr* bw_and_expr_more = parse_bw_and_expr();
	}

	return new expr;
}

token*Parser::match_if_bw_or_expr()
{
	if (lookahead() == tok_bitw_or) 
	{
		return accept();
	}

	return nullptr;
}

expr* Parser::parse_bw_or_expr()
{
	expr* bw_xor_expr = parse_bw_xor_expr();

	while (match_if_bw_or_expr())
	{
		expr* bw_xor_expr_more = parse_bw_xor_expr();
	}

	return new expr;
}

token*Parser::match_if_logical_and_expr()
{
	if (lookahead() == tok_logical_and) 
	{
		return accept();
	}

	return nullptr;
}

expr* Parser::parse_logical_and_expr()
{
	expr* bw_or_expr = parse_bw_or_expr();

	while (match_if_logical_and_expr())
	{
		expr* bw_or_expr_more = parse_bw_or_expr();
	}

	return new expr;
}

token*Parser::match_if_logical_or_expr()
{
	if (lookahead() == tok_logical_or) 
	{
		return accept();
	}

	return nullptr;
}

expr* Parser::parse_logical_or_expr()
{
	expr* log_and_expr = parse_logical_and_expr();

	while (match_if_logical_or_expr())
	{
		expr* log_and_expr_more = parse_logical_and_expr();
	}


	return new expr;
}

/*%%%%%%%%%%%%%%%%%%%*/
expr* Parser::parse_conditional_expr()
{
	expr* log_or_expr1 = parse_logical_or_expr();

	if (lookahead() == tok_conditional_operator)
	{
		accept();
		expr* e = parse_expr();
		match(tok_colon);
		expr* cond_expr = parse_conditional_expr();

		return new expr;
	}

	return new expr;
}

expr* Parser::parse_assign_expr()
{
	expr* cond_expr = parse_conditional_expr();

	if (lookahead() == tok_assignment_operator)
	{
		accept();
		expr* assign_expr = parse_assign_expr(); 

		return new expr;
	}

	return new expr;
}

expr* Parser::parse_expr()
{
	expr* assign_expr = parse_assign_expr();

	return new expr;
}

expr* Parser::parse_const_expr()
{
	expr* cond_expr = parse_conditional_expr();

	return new expr;
}

stmt* Parser::parse_stmt()
{
	switch (lookahead()) 
	{
		case tok_left_brace:
		{
			stmt* block_stmt = parse_block_stmt();
			return new stmt;
		}
		case tok_kw_if:
		{
			stmt* if_stmt = parse_if_stmt();
			return new stmt;
		}
		case tok_kw_while:
		{
			stmt* while_stmt = parse_while_stmt();
			return new stmt;
		}
		case tok_kw_break:
		{
			stmt* break_stmt = parse_break_stmt();
			return new stmt;
		}
		case tok_kw_continue:
		{
			stmt* cont_stmt = parse_continue_stmt();
			return new stmt;
		}
		case tok_kw_return:
		{
			stmt* return_stmt = parse_return_stmt();
			return new stmt;
		}
		case tok_kw_def:
		case tok_kw_let:
		case tok_kw_var:
		{
			stmt* decl_stmt = parse_decl_stmt();
			return new stmt;
		}
	}

	stmt* expr_stmt = parse_expr_stmt();

	return new stmt;
}

stmt* Parser::parse_block_stmt()
{
	match(tok_left_brace);
	std::vector<stmt*> stmt_seq = parse_stmt_seq();
	match(tok_right_brace);

	return new stmt;
}


/* This may be buggy vvvv*/
token*Parser::is_stmt()
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
		case tok_decimal_integer:
		case tok_binary_integer:
		case tok_hexadecimal_integer:
		case tok_character:
		case tok_boolean:
			return *first;
	}

	return nullptr;
}

std::vector<stmt*> Parser::parse_stmt_seq()
{
	std::vector<stmt*> stmt_seq;

	stmt* s = parse_stmt();
	stmt_seq.push_back(s);

	while (is_stmt())
	{
		stmt* s_more = parse_stmt();
		stmt_seq.push_back(s_more);
	}

	return stmt_seq;
}

stmt* Parser::parse_if_stmt()
{
	match(tok_kw_if);
	match(tok_left_paren);

	expr* e = parse_expr();

	match(tok_right_paren);

	stmt* s = parse_stmt();

	stmt* s_more = nullptr;
	if (lookahead() == tok_kw_else) 
	{
		match(tok_kw_else);
		s_more = parse_stmt();
	}


	return semantics.new_if_stmt(e, s, s_more);
}

stmt* Parser::parse_while_stmt()
{
	match(tok_kw_while);
	match(tok_left_paren);

	expr* e = parse_expr();

	match(tok_right_paren);

	stmt* s = parse_stmt();

	return semantics.new_while_stmt(e, s);
}

stmt* Parser::parse_break_stmt()
{
	match(tok_kw_break);
	match(tok_semicolon);

	return semantics.new_break_stmt();
}

stmt* Parser::parse_continue_stmt()
{
	match(tok_kw_continue);
	match(tok_semicolon);

	return semantics.new_continue_stmt();
}

stmt* Parser::parse_return_stmt()
{
	match(tok_kw_return);
	if (lookahead() == tok_semicolon)
	{
		accept();
		return new stmt;
	}
	expr* e = parse_expr();
	match(tok_semicolon);

	return semantics.new_return_stmt(e);
}

stmt* Parser::parse_decl_stmt()
{
	decl* local_dec = parse_local_decl();

	return semantics.new_decl_stmt(local_dec);
}

stmt* Parser::parse_expr_stmt()
{
	expr* e = parse_expr();
	match(tok_semicolon);

	return semantics.new_expr_stmt(e);
}

decl* Parser::parse_program()
{
	std::vector<decl*> decl_seq = parse_decl_seq();

	return new decl;
}

std::vector<decl*> Parser::parse_decl_seq()
{
	std::vector<decl*> decl_list;

	while(first < last)
	{ 
		decl* d = parse_decl();
		decl_list.push_back(d);
	}

	return decl_list;
}

decl* Parser::parse_decl()
{
	switch (lookahead()) 
	{
		case tok_kw_def: 
		{
			token_name la = lookahead(2);
			if (la == tok_colon)
			{
				decl* obj_def = parse_obj_def();

				return new decl;
			}
			else if (la == tok_left_paren)
			{
				decl* func_def = parse_func_def();

				return new decl;
			}
		}
		case tok_kw_let:
		case tok_kw_var:
			decl* obj_def = parse_obj_def();

			return new decl;
	}

	throw std::runtime_error("Expected declaration");
}

decl* Parser::parse_local_decl()
{
	decl* obj = parse_obj_def();

	return new decl;
}

decl* Parser::parse_obj_def()
{
	switch (lookahead())
	{
		case tok_kw_def:
		{
			decl* def = parse_val_def();
			return new decl;
		}
		case tok_kw_let:
		{
			decl* let = parse_const_def();
			return new decl;
		}
		case tok_kw_var:
		{
			decl* var = parse_var_def();
			return new decl;
		}
	}

	throw std::runtime_error("Expected onject definition");
}

decl* Parser::parse_var_def()
{
	match(tok_kw_var);
	match(tok_identifier);
	match(tok_colon);
	type* t = parse_type();

	switch (lookahead()) 
	{
		case tok_semicolon:
		{
			match(tok_semicolon);

			return new decl;
		}
		case tok_assignment_operator:
		{
			match(tok_assignment_operator);
			expr* e = parse_expr();
			match(tok_semicolon);

			return new decl;
		}
	}

	throw std::runtime_error("Expected variable definition");
}

decl* Parser::parse_const_def()
{
	match(tok_kw_let);
	match(tok_identifier);
	match(tok_colon);
	type* t = parse_type();
	match(tok_assignment_operator);
	expr* e = parse_expr();
	match(tok_semicolon);

	return new decl;
}

decl* Parser::parse_val_def()
{
	match(tok_kw_def);
	match(tok_identifier);
	match(tok_colon);
	type* t = parse_type();
	match(tok_assignment_operator);
	expr* e = parse_expr();
	match(tok_semicolon);

	return new decl;
}

decl* Parser::parse_func_def()
{
	match(tok_kw_def);
	match(tok_identifier);
	match(tok_left_paren);
	if(lookahead() != tok_right_paren)
		std::vector<decl*> param_list = parse_param_list();
	match(tok_right_paren);
	match(tok_sub);
	match(tok_rel_gt);
	type* t = parse_type();
	stmt* block_stmt = parse_block_stmt();

	return new decl;
}

token* Parser::match_if_param_list()
{
	if (lookahead() == tok_comma) 
	{
		return accept();
	}

	return nullptr;
}

std::vector<decl*> Parser::parse_param_list()
{
	std::vector<decl*> param_list;

	decl* param = parse_param();
	param_list.push_back(param);

	while (match_if_param_list())
	{
		decl* param_more = parse_param();
		param_list.push_back(param_more);
	}

	return param_list;
}

decl* Parser::parse_param()
{
	match(tok_identifier);
	match(tok_colon);
	type* t = parse_type();

	return new decl;
}
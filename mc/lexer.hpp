#pragma once

#include "token.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <cctype>
#include <map>



struct lexer {

	std::map<std::string, token> kw_table =
	{
		{"and", logical_and},
		{ "bool", ts_bool },
		{ "char", ts_char },
		{ "def", kw_def },
		{ "float", ts_float },
		{ "if", kw_if },
		{ "int",ts_int },
		{ "let", kw_let },
		{ "not", logical_not },
		{ "or", logical_or },
		{ "false", false},
		{ "true", true },
		{ "var", kw_var },
	};

	

	const char* first;
	const char* last;

	lexer(std::string& source);
	token scan();

	bool eof();
	const char peek(int n);	

	bool is_space(const char c);
	bool is_newline(const char c);
	bool is_digit(const char c);
	bool is_alpha(const char c);

	void skip_whitespace();
	void skip_comment();
	void skip_newline();

	token lex_word();
	token lex_num();
	token lex_puncuator(token_name);
	token lex_relational_operator(relational_op);
	token lex_arithmetic_operator(arithmetic_op);
	token lex_bitwise_operator(bitwise_op);
	token lex_logical_operator(logical_op);
	token lex_conditional_operator();
	token lex_assignment_operator();
	token lex_keyword();
	token lex_identifier();
	token lex_binary_integer();
	token lex_decimal_integer();
	token lex_floating_point();
	token lex_character();
	token lex_escape_sequence();
	token lex_string();
	token lex_type_specifier(type_spec);

	
	


};
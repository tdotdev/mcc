#pragma once

#include "token.hpp"
#include "location.hpp"
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>
#include <cctype>
#include <unordered_map>

struct lexer {

	std::unordered_map<std::string, token_name> reserved{
		{"and", tok_logical_and},
		{"const", tok_kw_const},
		{"volatile", tok_kw_volatile},
		{ "while", tok_kw_while },
		{ "break", tok_kw_break },
		{ "continue", tok_kw_continue },
		{ "return", tok_kw_return },
		{ "bool", tok_ts_bool},
		{"void", tok_ts_void},
		{ "char", tok_ts_char},
		{ "def", tok_kw_def},
		{ "else", tok_kw_else},
		{ "false", tok_false},
		{ "float", tok_ts_float},
		{ "if", tok_kw_if},
		{ "int", tok_ts_int},
		{ "let", tok_kw_let},
		{ "not", tok_logical_not},
		{ "or", tok_logical_or},
		{ "true", tok_true},
		{ "var", tok_kw_var},
		{ "as", tok_kw_as },
	};

	const char* first;
	const char* last;
	location current;

	lexer(std::string& source);

	token* scan();
	const char peek(int n);
	bool eof();
	bool search(char);
	char match_escape_sequence(const char escape);

	bool is_space(const char c);
	bool is_newline(const char c);
	bool is_digit(const char c);
	bool is_alpha(const char c);

	void skip_whitespace();
	void skip_comment();
	void skip_newline();
	void accept(int n);

	token* lex_word();
	token* lex_num();
	token* lex_puncuator(token_name);
	token* lex_relational_operator(token_name);
	token* lex_arithmetic_operator(token_name);
	token* lex_shift_operator(token_name);
	token* lex_bitwise_operator(token_name);
	token* lex_logical_operator(token_name);
	token* lex_conditional_operator();
	token* lex_assignment_operator();
	token* lex_binary_integer();
	token* lex_hexadecimal_integer();
	token* lex_decimal_integer();
	token* lex_floating_point();
	token* lex_character();
	token* lex_string();
};
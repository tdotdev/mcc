#pragma once

#include <iostream>
#include <cassert>
#include <string>

enum token_name
{
	// Punctuators
	tok_left_brace,
	tok_right_brace,
	tok_left_paren,
	tok_right_paren,
	tok_left_bracket,
	tok_right_bracket,
	tok_comma,
	tok_semicolon,
	tok_colon,

	// Keywords
	tok_kw_def,
	tok_kw_else,
	tok_kw_if,
	tok_kw_let,
	tok_kw_var,

	tok_identifier,
	tok_binary_integer,
	tok_decimal_integer,
	tok_hexadecimal_integer,
	tok_boolean,
	tok_floating_point,
	tok_character,
	tok_string,

	tok_conditional_operator,
	tok_assignment_operator,

	// rel ops
	tok_rel_eq,
	tok_rel_neq,
	tok_rel_lt,
	tok_rel_gt,
	tok_rel_le,
	tok_rel_ge,

	// math ops
	tok_add,
	tok_sub,
	tok_mul,
	tok_div,
	tok_rem,

	// bitwise ops
	tok_bitw_and,
	tok_bitw_or,
	tok_bitw_xor,
	tok_bitw_not,

	// logical ops
	tok_logical_and,
	tok_logical_or,
	tok_logical_not,

	// types
	tok_ts_char,
	tok_ts_bool,
	tok_ts_int,
	tok_ts_float,

	// boolean values
	tok_false,
	tok_true,

	// other
	tok_eof,
	tok_tok,
};

enum radix
{
	binary = 2,
	decimal = 10,
	hexadecimal = 16,
};

std::string token_name_to_string(token_name);
std::string radix_to_string(radix);

struct token {
	token_name name;

	token() = default;
	token(token_name n) {
		name = n;
	}

	virtual std::string to_string() {
		return "<" + token_name_to_string(name) + ">";
	}
};

struct integer : token {
	long long val;
	radix rad;

	integer(token_name n, long long v, radix r) {
		val = v;
		rad = r;
		name = n;
	}

	std::string to_string() {
		return "<" + token_name_to_string(name) + ": " + std::to_string(val) + ">";
	}
};

struct floating_point : token {
	double val;

	floating_point(double num) {
		name = tok_floating_point;
		val = num;
	}

	std::string to_string() {
		return "<" + token_name_to_string(name) + ": " + std::to_string(val) + ">";
	}
};

struct boolean : token {
	bool val;

	boolean(bool tf) {
		name = tok_boolean;
		val = tf;
	}

	std::string to_string() {
		return "<" + token_name_to_string(name) + ": " + std::to_string(val) + ">";
	}
};

struct character : token {
	char val;

	character(char c) {
		name = tok_character;
		val = c;
	}	
	
	std::string to_string() {
		return "<" + token_name_to_string(name) + ": " + val + ">";
	}
};

struct string : token {
	std::string val;

	string(std::string str) {
		name = tok_string;
		val = str;
	}

	std::string to_string() {
		return "<" + token_name_to_string(name) + ": " + val + ">";
	}
};

struct identifier : token {
	std::string id;

	identifier(std::string str) {
		name = tok_identifier;
		id = str;
	}

	std::string to_string() {
		return "<" + token_name_to_string(name) + ": " + id + ">";
	}
};
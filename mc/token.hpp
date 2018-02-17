#pragma once

#include "symbol.hpp"
#include "location.hpp"
#include <cassert>
#include <string>

enum token_name
{
	// Miscellaneous
	tok_eof,

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

	// Operators
	tok_relational_operator, // ==, !=, <, >, <=, >=
	tok_arithmetic_operator, // +, -, *, /, %
	tok_bitwise_operator, // &, |, ^, ~
	tok_logical_operator, // and, or, not
	tok_conditional_operator, // ?
	tok_assignment_operator, // =

// Keywords
	kw_def,
	kw_else,
	kw_if,
	kw_let,
	kw_var,

	tok_identifier,
	tok_binary_integer,
	tok_decimal_integer,
	tok_hexadecimal_integer,
	tok_boolean,
	tok_floating_point,
	tok_character,
	tok_string,
	tok_type_specifier,
};

const char* to_string(token_name n);


enum relational_op
{
	op_eq,
	op_ne,
	op_lt,
	op_gt,
	op_le,
	op_ge,
};

enum arithmetic_op
{
	op_add,
	op_sub,
	op_mul,
	op_div,
	op_rem,
};

enum bitwise_op
{
	op_and,
	op_or,
	op_xor,
	op_not,
};

enum logical_op
{
	logical_and,
	logical_or,
	logical_not,
};

enum type_spec
{
	ts_char,
	ts_bool,
	ts_int,
	ts_float,
};

const char* to_string(relational_op op);
const char* to_string(arithmetic_op op);
const char* to_string(bitwise_op op);
const char* to_string(logical_op op);
const char* to_string(type_spec ts);

enum radix
{
	binary = 2,
	decimal = 10,
	hexadecimal = 16,
};

/// Stored information about integer values.
struct integer_attr
{
	radix rad;
	long long value;
};

/// Stored information about strings. Note that string literals are stored in 
/// the symbol table so we can avoid copying. This class primarily lets us
/// different identifiers (also symbols) from strings when constructing tokens.
///
/// \todo Is there anything else we might want to put in here? Encoding?
struct string_attr
{
	symbol sym;
};


/// The union of all token attributes. The actual value is discriminated the
/// token name.
///
/// Note that 
union token_attr
{
	token_attr() = default;
	token_attr(symbol sym) : sym(sym) { }
	token_attr(relational_op op) : rel_op(op) { }
	token_attr(arithmetic_op op) : arith_op(op) { }
	token_attr(bitwise_op op) : bit_op(op) { }
	token_attr(logical_op op) : logic_op(op) { }
	token_attr(integer_attr val) : int_val(val) { }
	token_attr(double val) : fp_val(val) { }
	token_attr(bool b) : bool_val(b) { }
	token_attr(char c) : char_val(c) { }
	token_attr(string_attr s) : string_val(s) { }
	token_attr(type_spec ts) : ts(ts) { }

	symbol sym;
	relational_op rel_op;
	arithmetic_op arith_op;
	bitwise_op bit_op;
	logical_op logic_op;
	integer_attr int_val;
	double fp_val;
	bool bool_val;
	char char_val;
	string_attr string_val;
	type_spec ts;

};


/// A token is the name of a symbol and optional attribute. The kind
/// of attribute is determined by the name of the symbol.
class token
{
public:
	token() = default;
	token(token_name n)
		: name(n) {}
	token(token_name n, token_attr attr)
		: name(n), attr(attr) {}
	token(symbol sym)
		: name(tok_identifier), attr(sym){}
	token(relational_op op)
		: name(tok_relational_operator), attr(op) {}
	token(arithmetic_op op)
		: name(tok_arithmetic_operator), attr(op) {}
	token(bitwise_op op)
		: name(tok_bitwise_operator), attr(op) {}
	token(logical_op op)
		: name(tok_logical_operator), attr(op) {}
	token(radix rad, long long val) {
		switch (rad) {
		case binary:
			name = tok_binary_integer;
		case decimal:
			name = tok_decimal_integer;
		case hexadecimal:
			name = tok_hexadecimal_integer;
		}
		integer_attr ia{ rad, val };
		attr = ia;
	}
	token(token_name n, radix rad, long long val) {
		name = n;
		integer_attr ia{ rad, val };
		attr = ia;
	}
	token(double val)
		: name(tok_floating_point), attr(val) {}
	token(bool tf)
		: name(tok_boolean), attr(tf) {}
	token(char c)
		: name(tok_character), attr(c) {}
	token(string_attr s)
		: name(tok_identifier), attr(s) {}
	token(type_spec ts)
		: name(tok_type_specifier), attr(ts) {}


private:
	token_name name;
	token_attr attr;
};
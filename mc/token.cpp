#include "token.hpp"

#include <cassert>
#include <iostream>
#include <iomanip>

const char*
to_string(token_name n)
{
	switch (n) {
	case tok_eof:
		return "eof";

	case tok_left_brace:
		return "left-brace";
	case tok_right_brace:
		return "right-brace";
	case tok_left_paren:
		return "left-paren";
	case tok_right_paren:
		return "right-paren";
	case tok_left_bracket:
		return "left-bracket";
	case tok_right_bracket:
		return "right-bracket";
	case tok_comma:
		return "comma";
	case tok_semicolon:
		return "semicolon";
	case tok_colon:
		return "colon";

	case tok_relational_operator:
		return "relational-operator";
	case tok_arithmetic_operator:
		return "arithmetic-operator";
	case tok_bitwise_operator:
		return "bitwise-operator";
	case tok_logical_operator:
		return "logical-operator";
	case tok_conditional_operator:
		return "conditional-operator";
	case tok_assignment_operator:
		return "assignment-operator";

	case kw_def:
		return "def";
	case kw_else:
		return "else";
	case kw_if:
		return "if";
	case kw_let:
		return "let";
	case kw_var:
		return "var";

	case tok_identifier:
		return "identifier";
	case tok_binary_integer:
		return "binary-integer";
	case tok_decimal_integer:
		return "decimal-integer";
	case tok_hexadecimal_integer:
		return "hexadecimal-integer";
	case tok_boolean:
		return "boolean";
	case tok_floating_point:
		return "floating-point";
	case tok_character:
		return "character";
	case tok_string:
		return "string";
	case tok_type_specifier:
		return "type-specifier";
	}
}

// Kinds of relational operator
const char*
to_string(relational_op op)
{
	switch (op) {
	case op_eq:
		return "eq";
	case op_ne:
		return "ne";
	case op_lt:
		return "lt";
	case op_gt:
		return "gt";
	case op_le:
		return "le";
	case op_ge:
		return "ge";
	}
};

const char*
to_string(arithmetic_op op)
{
	switch (op) {
	case op_add:
		return "add";
	case op_sub:
		return "sub";
	case op_mul:
		return "mul";
	case op_div:
		return "quo";
	case op_rem:
		return "rem";
	}
};

const char*
to_string(bitwise_op op)
{
	switch (op) {
	case op_and:
		return "and";
	case op_or:
		return "ior";
	case op_xor:
		return "xor";
	case op_not:
		return "not";
	}
};

const char*
to_string(logical_op op)
{
	switch (op) {
	case logical_and:
		return "and";
	case logical_or:
		return "or";
	case logical_not:
		return "not";
	}
};

const char*
to_string(type_spec ts)
{
	switch (ts) {
	case ts_bool:
		return "char";
	case ts_int:
		return "int";
	case ts_char:
		return "char";
	case ts_float:
		return "float";
	}
};

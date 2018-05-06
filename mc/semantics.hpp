#pragma once

#include <vector>
#include "expression.hpp"
#include "statement.hpp"
#include "declaration.hpp"
#include "type.hpp"


struct Semantics {

	stmt* new_block_stmt(std::vector<stmt*> stmt_seq);
	stmt* new_if_stmt(expr* condition, stmt* if_true, stmt* if_false);
	stmt* new_while_stmt(expr* condition, stmt* statement);
	stmt* new_break_stmt();
	stmt* new_continue_stmt();
	stmt* new_return_stmt(expr* expression);
	stmt* new_decl_stmt(decl* declaration);
	stmt* new_expr_stmt(expr* expression);

	type* new_void_type();
	type* new_bool_type();
	type* new_int_type();
	type* new_float_type();
	type* new_char_type();

	type* new_func_type(std::vector<type*> params, type_t ret_type);

};
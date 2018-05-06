#pragma once

#include <vector>
#include "expression.hpp"
#include "statement.hpp"
#include "declaration.hpp"

enum stmt_t {
	block_t,
	if_t,
	while_t,
	break_t,
	continue_t,
	return_t,
	decl_t,
	expr_t,
	default_t
};

struct stmt {
	stmt(stmt_t stmt_type)
		: stmt_type(stmt_type)
	{}

	stmt() = default;

	stmt_t stmt_type;
};

struct block_stmt : stmt {

	block_stmt(std::vector<stmt*> seq)
		: stmt_seq(seq)
		, stmt(block_t)
	{}

	std::vector<stmt*> stmt_seq;
};

struct if_stmt : stmt {

	if_stmt(expr* e, stmt* t, stmt* f)
		: expression(e)
		, if_true(t)
		, if_false(f)
		, stmt(if_t)
	{}

	expr* expression;
	stmt* if_true;
	stmt* if_false;
};

struct while_stmt : stmt {

	while_stmt(expr* e, stmt* s)
		: expression(e)
		, statement(s)
		, stmt(while_t)
	{}

	expr* expression;
	stmt* statement;
};

struct break_stmt : stmt {
	
	break_stmt()
		: stmt(break_t)
	{}
};

struct continue_stmt : stmt {

	continue_stmt()
		: stmt(continue_t)
	{}
};

struct return_stmt : stmt {

	return_stmt(expr* e)
		: expression(e)
		, stmt(return_t)
	{}

	expr* expression;
};

struct decl_stmt : stmt {

	decl_stmt(decl* d)
		: declaration(d)
		, stmt(decl_t)
	{}

	decl* declaration;
};

struct expr_stmt : stmt {

	expr_stmt(expr* e)
		: expression(e)
		, stmt(expr_t)
	{}

	expr* expression;
};
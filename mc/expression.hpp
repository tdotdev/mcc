#pragma once

#include "type.hpp"

struct decl;

struct expr {

	expr() = default;

	expr(type* t)
		: expr_type(t)
	{}

	type* expr_type;
};



struct bool_literal : expr {

	bool_literal(bool val, type* t)
		: value(val)
		, expr(t) // bool_t
	{}
	
	bool value;
};

struct int_literal : expr {

	int_literal(int val, type* t)
		: value(val)
		, expr(t) // int_t
	{}

	int value;
};

struct float_literal : expr {

	float_literal(double val, type* t)
		: value(val)
		, expr(t) // ffloat_t
	{}

	double value;
};

struct char_literal : expr {

	char_literal(char val, type* t)
		: value(val)
		, expr(t) // char_t
	{}

	char value;
};

struct string_literal : expr {

	string_literal(std::string val, type* t)
		: value(val)
		, expr(t)
	{}

	std::string value;
};

enum binary_op {
	bop_mul,
	bop_div,
	bop_rem,
	bop_add,
	bop_sub,

	bop_lshift,
	bop_rshift,

	bop_lt,
	bop_gt,
	bop_lte,
	bop_gte,
	bop_eq,
	bop_neq,

	bop_bwand,
	bop_bwxor,
	bop_bwor,

	bop_land,
	bop_lor,
};

enum unary_op {
	u_add,
	u_sub,
	u_bwnot,
	u_not,
	u_ref,
	u_deref
};

struct unary_expr : expr {

	unary_expr(unary_op u, expr* e, type* t)
		: u_op(u)
		, e(e)
		, expr(t)
	{}

	unary_op u_op;
	expr* e;
};

struct binary_expr : expr {

	binary_expr(binary_op op, expr* lhs, expr* rhs, type* t) 
		: b_op(op)
		, lhs(lhs)
		, rhs(rhs)
		, expr(t)
	{}

	binary_op b_op;
	expr* lhs;
	expr* rhs;
};

struct assign_expr : expr {

	assign_expr(expr* r, expr* v)
		: ref(r)
		, val(v)
	{}

	expr* ref;
	expr* val;
};

struct func_expr : expr {

	func_expr(type* ret, expr* e, std::vector<expr*> args)
		: e(e)
		, expr(ret)
		, args(args)
	{}

	expr* e;
	std::vector<expr*> args;
};

struct cast_expr : expr {

	cast_expr(expr* e, type* t)
		: cast(e)
		, t(t)
		, expr(t)
	{}

	expr* cast;
	type* t;
};

struct cond_expr : expr {

	cond_expr(expr* e1, expr* e2, expr* e3)
		: expr1(e1)
		, expr2(e2)
		, expr3(e3)
		, expr(e3->expr_type)
	{}

	expr* expr1;
	expr* expr2;
	expr* expr3;
};

struct call_expr : expr {
	call_expr()
	{
		throw std::runtime_error("not yet impl");
	}
};

struct id_expr : expr {
	id_expr(decl* d, type* t)
		: ref_to(d)
		, expr(t) // id_t
	{}

	decl* ref_to;
};

struct conv_expr : expr {
	conv_expr()
	{
		throw std::runtime_error("not yet impl");
	}
};
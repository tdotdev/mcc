#pragma once

struct expr {
	virtual void to_string() = 0;
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

	bop_band,
	bop_bwxor,
	bop_bwor,

	bop_land,
	bop_lor,

};

struct binary_expr : expr {

	binary_expr(binary_op op, expr* lhs, expr* rhs) :
		m_op(op), m_lhs(lhs), m_rhs(rhs)
	{}

	binary_op m_op;
	expr* m_lhs;
	expr* m_rhs;
};
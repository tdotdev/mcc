#pragma once


enum decl_t {
	var_t,
	const_t,
	value_t,
	param_t,
	function_t,
	program_t
};

struct decl {

	decl(std::string id, decl_t t)
		: id(id)
		, decl_type(t)
	{}

	std::string id;
	decl_t decl_type;
};

struct func_decl : decl {

	func_decl(std::string id, std::vector<decl*> params, type* ret_t, stmt* s)
		: decl(id, function_t)
		, params(params)
		, body(s)
		, ret_type(ret_t)
	{}

	std::vector<decl*> params;
	stmt* body;
	type* ret_type;
};


struct var_decl : decl {

	var_decl(std::string id, type* t, expr* value)
		: decl(id, var_t)
		, init(value)
		, var_type(t)
	{}
	
	type* var_type;
	expr* init;
};

struct val_decl : decl {

	val_decl(std::string id, type* t, expr* value)
		: decl(id, value_t)
		, init(value)
		, val_type(t)
	{}

	type* val_type;
	expr* init;
};

struct const_decl : decl {

	const_decl(std::string id, type* t, expr* value)
		: decl(id, const_t)
		, init(value)
		, const_type(t)
	{}

	type* const_type;
	expr* init;
};

struct param_decl : decl {

	param_decl(std::string id, type* t)
		: decl(id, param_t)
		, param_type(t)
	{}

	type* param_type;
};

/*
struct program_decl : decl {

	program_decl(std::vector<decl*> decl_seq)
		: decl_seq(decl_seq)
		, decl(program_t)
	{}

	std::vector<decl*> decl_seq;
};

*/
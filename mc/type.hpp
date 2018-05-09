#pragma once

/* TODO, Implement postfix types... how to represent multiple indirection??? */

#include <vector>

enum type_t {
	void_t,
	bool_t,
	int_t,
	mfloat_t,
	char_t,
	string_t,
	ref_t,
	ptr_t,
	func_t,
	scalar_t
};

struct type {
	type(type_t t)
		: type_type(t)
	{}

	type_t type_type;
	virtual ~type() = default;
};

struct ptr_type : type {
	ptr_type(type* r, type_t t)
		: type(t)
		, ptr_to_type(r)
	{}

	type* ptr_to_type;
};

struct void_type : type {
	void_type(type_t t)
		: type(t)
	{}
};

struct bool_type : type {
	bool_type(type_t t)
		: type(t)
	{}
};


struct int_type : type {
	int_type(type_t t)
		: type(t)
	{}
};

struct float_type : type {
	float_type(type_t t)
		: type(t)
	{}
};

struct char_type : type {
	char_type(type_t t)
		: type(t)
	{}
};

struct string_type : type {
	string_type(type_t t)
		: type(t)
	{}
};

struct ref_type : type {
	ref_type(type* r, type_t t)
		: type(t)
		, ref_to_type(r)
	{}

	type* ref_to_type;
};

struct function_type : type {
	function_type(std::vector<type*> params, type_t ret_type)
		: params(params)
		, ret_type(ret_type)
		, type(func_t)
	{}

	std::vector<type*> params;
	type_t ret_type;
};
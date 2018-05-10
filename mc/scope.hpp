#pragma once

#include <unordered_map>

struct decl;

enum scope_level {
	global,
	parameter,
	block
};

struct scope {

	scope(scope_level l)
		: level(l)
	{
		parent_scope = nullptr;
		scope_content = {};
	}

	std::unordered_map<std::string, decl*> scope_content;
	scope_level level;
	scope* parent_scope;

	void add_decl(std::string id, decl* d)
	{

		std::unordered_map<std::string, decl*>::const_iterator it = scope_content.find(id);
			
		if (it != scope_content.end())
			throw std::runtime_error("Redeclaration");

		scope_content.emplace(id, d);
	}

	decl* find_decl(std::string id)
	{
		std::unordered_map<std::string, decl*>::const_iterator it;

		it = scope_content.find(id);

		if (it != scope_content.end())
			return it->second;

		return nullptr;
	}
};
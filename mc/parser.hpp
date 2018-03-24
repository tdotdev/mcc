#pragma once

#include "token.hpp"
#include "location.hpp"
#include <vector>
#include <cassert>
#include <iostream>



struct Parser {

	std::vector<token*> tokens;

	std::vector<token*>::const_iterator first;
	std::vector<token*>::const_iterator last;

	Parser(const std::vector<token*>& token_stream);

	token* lookahead(int n);
	
	void parse();
	void accept(int n);
};




#include "parser.hpp"

Parser::Parser(const std::vector<token*>& token_stream)
{
	std::vector<token*>::const_iterator it;

	it = token_stream.begin();

	while (it != token_stream.end())
	{
		tokens.push_back(*it);
		it++;
	}

	first = tokens.begin();
	last = tokens.end();
	
}

token* Parser::lookahead(int n)
{
	assert(first < last - 1);
	std::vector<token*>::const_iterator it;
	it = first;

	for (int i = 0; i < n; i++)
	{
		assert(it < last - 1);
		++it;
	}

	return *it;
}



void Parser::accept(int n)
{
	for (int i = 0; i < n; i++)
	{
		assert(first != last);
		++first;
	}
}

void Parser::parse()
{
	

}
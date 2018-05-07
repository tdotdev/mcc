#include <iostream>
#include <string>
#include "lexer.hpp"
#include "token.hpp"
#include "parser.hpp"
#include <fstream>
#include <vector>

void print_token_stream(std::vector<token*>&);
std::string init_source(std::string);

int main()
{
	std::string source{ init_source("stmts_t.mc") };

	lexer lexer(source);
	std::vector<token*> tokens;

	while(!lexer.eof()){

		token* tok = lexer.scan();
		if(tok != nullptr)
			tokens.push_back(tok);
	}

	print_token_stream(tokens);

	Parser parser(tokens);
	parser.parse_program();

	std::cout << "\n>>> Nice.\n";
	char a;
	std::cin >> a;

	return 0;
}

std::string init_source(std::string fname)
{
	std::string source;

	std::ifstream source_file(fname);

	while (!source_file.eof()) {
		source += source_file.get();
	}

	return source;
}

void print_token_stream(std::vector<token*>& tokens)
{
	for (const auto tok : tokens)
	{
		std::cout << tok->to_string() << "\n";
	}
}
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
	std::string source{ init_source("parser_t.mc") };

	lexer lex(source);
	std::vector<token*> tokens;

	while(!lex.eof()){
		tokens.push_back(lex.scan());
	}

	print_token_stream(tokens);
	std::cout << "PARSING\n";

	Parser parse(tokens);
	
	parse.parse_program();


	std::cout << "GREAT SUCCESS!";

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
	for (auto it = tokens.begin(); it != tokens.end(); ++it)
	{
		std::cout << (*it)->to_string() << "\n";
	}
}
#include <iostream>
#include <string>
#include "lexer.hpp"
#include "token.hpp"
#include "parser.hpp"
#include <fstream>
#include <vector>

int main()
{
	

	std::ifstream source_file("parser_t.mc");
	std::string source;

	while (!source_file.eof()) {
		source += source_file.get();
	}

	lexer lex(source);

	std::vector<token*> tokens;

	while(!lex.eof()){
		tokens.push_back(lex.scan());
	}

	
	for (int i = 0; i < tokens.size(); ++i) {
		std::cout << tokens[i]->to_string() << "\n";
	}
	
	std::cout << "PARSING\n";

	Parser parse(tokens);

	parse.parse();
	
	char a;
	std::cin >> a;

	return 0;
}
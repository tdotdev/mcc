#include "lexer.hpp"

lexer::lexer(std::string &source) 
{
	first = &source[0];
	last = &source[source.length() - 1];
	current = 0;
}

void lexer::accept(int n)
{
	for (int i = 0; i < n; ++i)
	{
		assert(!eof());
		++first;
		++current;
	}
}

const char lexer::peek(int n) 
{
	assert(!eof());
	const char* c = first;
	for (int i = 0; i < n; ++i)
		++c;
	return *c;
}

bool lexer::search(char c)
{
	assert(!eof());
	const char* check = first;
	
	while (is_digit(*check) || *check == c) {
		if (*check == c)
			return true;
		++check;
	}

	return false;
}

bool lexer::eof() 
{
	return first == last;
}

bool lexer::is_space(const char c) 
{
	assert(!eof());
	return c == ' ';
}

bool lexer::is_digit(const char c) 
{
	assert(!eof());
	return std::isdigit(c);
}

bool lexer::is_alpha(const char c) 
{
	assert(!eof());
	return std::isalpha(c);
}

bool lexer::is_newline(const char c) 
{
	assert(!eof());
	return c == '\n';
}

void lexer::skip_whitespace() 
{
	assert(!eof());

	while (!eof() && is_space(*first))
		accept(1);
}

void lexer::skip_newline() 
{
	assert(!eof());

	while (!eof() && is_newline(*first))
		accept(1);
}

void lexer::skip_comment() 
{
	assert(!eof());
	assert(*first == '#');

	while (!is_newline(*first))
		accept(1);
}

token* lexer::lex_puncuator(token_name name) 
{
	accept(1);
	return new token(name, current);
}

token* lexer::lex_relational_operator(token_name op) 
{
	if (op == tok_rel_le || op == tok_rel_ge)
		accept(2);
	else
		accept(1);

	return new token(op, current);
}

token* lexer::lex_arithmetic_operator(token_name op)
{
	accept(1);
	return new token(op, current);
}
token* lexer::lex_bitwise_operator(token_name op) 
{
	accept(1);
	return new token(op, current);
}

token* lexer::lex_logical_operator(token_name op) 
{
	accept(1);
	return new token(op, current);
}

token* lexer::lex_conditional_operator()
{ 
	accept(1);
	return new token(tok_conditional_operator, current);
}

token* lexer::lex_assignment_operator()
{ 
	accept(1);
	return new token(tok_assignment_operator, current);
}

token* lexer::lex_num() 
{
	if (*first == '0') 
	{
		if (tolower(peek(1)) == 'b')
			return lex_binary_integer();

		else if (tolower(peek(1)) == 'x')
			return lex_hexadecimal_integer();
	}
	else {
		if (search('.'))
			return lex_floating_point();
		else
			return lex_decimal_integer();
	}
}

token* lexer::lex_binary_integer()
{
	std::string num;

	accept(2);
	while (*first == '0' || *first == '1') 
	{
		num += *first;
		accept(1);
	}

	return new integer(tok_binary_integer, std::strtoll(num.c_str(), nullptr, 2), binary, current);
}

token* lexer::lex_decimal_integer()
{
	std::string num;
	int value;

	while (is_digit(*first)) 
	{
		num += *first;
		accept(1);
	}

	std::istringstream buffer(num);
	buffer >> value;

	return new integer(tok_decimal_integer, value, decimal, current);
}

token* lexer::lex_hexadecimal_integer() 
{
	std::string num;

	accept(2);
	while (std::isxdigit(*first)) 
	{
		num += *first;
		accept(1);
	}

	return new integer(tok_hexadecimal_integer, std::strtoll(num.c_str(), nullptr, 16), hexadecimal, current);
}

token* lexer::lex_floating_point()
{ 
	std::string num;
	double val;

	while (is_digit(*first) || *first == '.') {
		num += *first;
		accept(1);
	}

	val = std::stod(num);

	return new floating_point(val, current);
}

token* lexer::lex_character()
{ 
	accept(1);
	char c;
	if (*first == '\\')
	{
		accept(1);
		switch (*first) {
			case '"':
				c = '\"';
				break;
			case '\'':
				c = '\'';
				break;
			case '\\':
				c = '\\';
				break;
			case 'a':
				c = '\a';
				break;
			case 'b':
				c = '\b';
				break;
			case 'f':
				c = '\f';
				break;
			case 'n':
				c = '\n';
				break;
			case 'r':
				c = '\r';
				break;
			case 't':
				c = '\t';
				break;
			case 'v':
				c = '\v';
				break;
		}
	}
	else
	{
		c = *first;
	}
	accept(2);
	return new character(c, current);
}


token* lexer::lex_string()
{ 
	std::string word{ "" };

	accept(1); 
	while (*first != '"')
	{
		word += *first;
		accept(1);
	}
	accept(1);

	return new string(word, current);
}

token* lexer::lex_word() {
	
	std::string word{ "" };

	while (!is_space(*first) && !eof() && is_alpha(*first)) 
	{
		word += *first;
		accept(1);
	}

	std::map<std::string, token_name>::const_iterator got = reserved.find(word);

	// symbol not found in table, add it!
	if (got == reserved.end()) {
		reserved.insert(std::make_pair(word, tok_identifier));
		return new identifier(word, current);;
	}
	// a reserved word or identifier
	else 
	{
		if (reserved.at(word) == tok_true)
			return new boolean(true, current);

		else if (reserved.at(word) == tok_false)
			return new boolean(false, current);

		else 
			return new token(reserved.at(word), current);
	}
}

token* lexer::scan() {
	while (!eof()) {
		switch (*first) {
			case ' ':
				skip_whitespace();
				continue;

			case '\n':
				skip_newline();
				continue;

			case '\t':
				accept(1);
				continue;

			case '#':
				skip_comment();
				continue;

			case '{':
				return lex_puncuator(tok_left_brace);

			case '}':
				return lex_puncuator(tok_right_brace);

			case '(':
				return lex_puncuator(tok_left_paren);

			case ')':
				return lex_puncuator(tok_right_paren);

			case '[':
				return lex_puncuator(tok_left_brace);

			case ']':
				return lex_puncuator(tok_right_brace);

			case ',':
				return lex_puncuator(tok_comma);

			case ';':
				return lex_puncuator(tok_semicolon);

			case ':':
				return lex_puncuator(tok_colon);

			case '=':
				if (peek(1) == '=') 
					return lex_relational_operator(tok_rel_eq);
				else 
					return lex_assignment_operator();

			case '!':
				if(peek(1) == '=')
					return lex_relational_operator(tok_rel_neq);
				else
					return lex_bitwise_operator(tok_bitw_not);

			case '<':
				if (peek(1) == '=') 
					return lex_relational_operator(tok_rel_le);
				else 
					return lex_relational_operator(tok_rel_lt);

			case '>':
				if (peek(1) == '=') 
					return lex_relational_operator(tok_rel_ge);
				else 
					return lex_relational_operator(tok_rel_gt);

			case '+':
				return lex_arithmetic_operator(tok_add);

			case '-':
				return lex_arithmetic_operator(tok_sub);

			case '*':
				return lex_arithmetic_operator(tok_mul);

			case '/':
				return lex_arithmetic_operator(tok_div);

			case '%':
				return lex_arithmetic_operator(tok_rem);

			case '&':
				return lex_bitwise_operator(tok_bitw_and);

			case '|':
				return lex_bitwise_operator(tok_bitw_or);

			case '^':
				return lex_bitwise_operator(tok_bitw_xor);

			case '~': 
				return lex_bitwise_operator(tok_bitw_not);

			case '?':
				return lex_conditional_operator();

			case '\'':
					return lex_character();

			case '"':
				return lex_string();


			default:
				if (is_alpha(*first)) 
					return lex_word();
				
				else if(is_digit(*first))
					return lex_num();
				
				std::cout << "INVALID";
				accept(1);
		}
	}
}
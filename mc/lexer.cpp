#include "lexer.hpp"

lexer::lexer(std::string &source) {

	first = &source[0];
	last = &source[source.length() - 1];
}

const char lexer::peek(int n) {
	assert(!eof());
	const char* c = first;
	for (int i = 0; i < n; ++i)
		++c;
	return *c;
}

bool lexer::eof() {
	return first == last;
}

bool lexer::is_space(const char c) {
	assert(!eof());
	return c == ' ';
}

bool lexer::is_digit(const char c) {
	assert(!eof());
	return std::isdigit(c);
}

bool lexer::is_alpha(const char c) {
	assert(!eof());
	return std::isalpha(c);
}

bool lexer::is_newline(const char c) {
	assert(!eof());
	return c == '\n';
}

void lexer::skip_whitespace() {
	assert(!eof());

	while (!eof() && is_space(*first))
		++first;
}

void lexer::skip_newline() {
	assert(!eof());

	while (!eof() && is_newline(*first))
		++first;
}

void lexer::skip_comment() {
	assert(!eof());
	assert(*first == '#');

	while (!is_newline(*first))
		++first;
}

token lexer::lex_puncuator(token_name name) {
	++first;
	return token{ name };
}


token lexer::lex_relational_operator(relational_op op) {
	if (op == op_le || op == op_ge) {
		++first;
		++first;
	}
	else {
		++first;
	}
	return token(op); 
}

token lexer::lex_arithmetic_operator(arithmetic_op op){
	++first;
	return token(op); 
}
token lexer::lex_bitwise_operator(bitwise_op op) {
	++first;
	return token(op);
}

token lexer::lex_logical_operator(logical_op op) {
	++first;
	return token(op);
}

token lexer::lex_conditional_operator(){ return token(tok_conditional_operator); }
token lexer::lex_assignment_operator(){ return token(tok_assignment_operator); }

token lexer::lex_identifier(){ return token(); }

token lexer::lex_binary_integer(){ return token(); }
token lexer::lex_decimal_integer(){ return token(); }
token lexer::lex_floating_point(){ return token(); }
token lexer::lex_character(){ return token(); }
token lexer::lex_escape_sequence(){ return token(); }
token lexer::lex_string(){ return token(); }





token lexer::lex_word() {
	std::string word{ "" };

	while (!is_space(*first) && !eof() && is_alpha(*first)) {
		word += *first;
		++first;
	}

	std::map<std::string, token>::const_iterator got = kw_table.find(word);

	// not a keyword, new id
	if (got == kw_table.end()) {
		kw_table.insert(std::make_pair(word, tok_identifier));
		symbol s = &word;
		token t(s);
		return t;
	}
	// is a keyword or previous id
	else {
		token t(kw_table.at(word));
		return t;
	}
	
	

}

token lexer::lex_num() {
	std::string word{ "" };

	if (*first == 0) {
		if (tolower(peek(1)) == 'b')
		{
			
		}
		else if (tolower(peek(1)) == 'x')
		{

		}
	}
	else {
		return token();
	}

	return token();
}
 
token lexer::scan() {
	while (!eof()) {
		std::cout << *first;
		switch (*first) {
			case ' ':
				skip_whitespace();
				continue;
			case '\n':
				skip_newline();
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
				if (peek(1) == '=') {
					return lex_relational_operator(op_eq);
				}
				else {
					return lex_assignment_operator();
				}
			case '!':
				if(peek(1) == '=')
					return lex_relational_operator(op_ne);
				else
					return lex_bitwise_operator(op_not);
			case '<':
				if (peek(1) == '=') {
					return lex_relational_operator(op_le);
				}
				else {
					return lex_relational_operator(op_lt);
				}
			case '>':
				if (peek(1) == '=') {
					return lex_relational_operator(op_ge);
				}
				else {
					return lex_relational_operator(op_gt);
				}
			case '+':
				return lex_arithmetic_operator(op_add);
			case '-':
				return lex_arithmetic_operator(op_sub);
			case '*':
				return lex_arithmetic_operator(op_mul);
			case '/':
				return lex_arithmetic_operator(op_div);
			case '%':
				return lex_arithmetic_operator(op_rem);
			case '&':
				return lex_bitwise_operator(op_and);
			case '|':
				return lex_bitwise_operator(op_or);
			case '^':
				return lex_bitwise_operator(op_xor);
			case '~':
				return lex_bitwise_operator(op_not);
			case '?':
				return lex_conditional_operator();
			case '\'':
				if (peek(1) == '\\')
					return lex_escape_sequence();
				else
					return lex_character();
			case '"':
				return lex_string();
			default:
				if (is_alpha(*first)) {
					return lex_word();
				}
				else if(is_digit(*first)){
					return lex_num();
				}

				std::cout << "If you made it this far... there is an error\n";
				continue;

				return token();
		}
	}

	return token();
}
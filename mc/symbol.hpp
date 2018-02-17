#pragma once

#include <string>
#include <unordered_set>

/// Represents a symbol in the language. Because all symbols have unique
/// values, the value of a symbol is its identity.
using symbol = const std::string*;


/// Ensures that all symbols having the same spelling are unique.
///
/// Many compilers associate information with symbols (e.g., token 
/// attributes), but that's fallen out of fashion. Attributes are simply
/// part of a token object.
class symbol_table
{
public:
	symbol get(const char* str);
	symbol get(const std::string& str);

private:
	std::unordered_set<std::string> m_syms;
};

/// Returns the symbol corresponding to string.
inline symbol
symbol_table::get(const char* str)
{
	return &*m_syms.insert(str).first;
}

/// Returns the symbol corresponding to string.
inline symbol
symbol_table::get(const std::string& str)
{
	return &*m_syms.insert(str).first;
}

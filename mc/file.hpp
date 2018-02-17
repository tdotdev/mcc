#pragma once

#include <string>

/// A source file.
class file
{
public:
	file(const std::string& path);

	const std::string& get_path() const;
	const std::string& get_text() const;

private:
	std::string m_path;
	std::string m_text;
};

inline const std::string&
file::get_path() const
{
	return m_path;
}

inline const std::string&
file::get_text() const
{
	return m_text;
}

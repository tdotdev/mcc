#pragma once

#include <iosfwd>

class file;

/// Represents a location in the input file. Note that these are based at
/// 0 and need to be adjusted prior to display.
///
/// \todo Actually store or refer to the path of the file.
class location
{
public:
	location()
		: source(nullptr), line(-1), column(-1)
	{ }

	location(const file& f, int l, int c)
		: source(&f), line(l), column(c)
	{ }

	explicit operator bool() const
	{
		return line >= 0;
	}

	const file* source;
	int line;
	int column;
};

std::ostream& operator<<(std::ostream& os, location loc);

#include <iostream>
#include <sstream>

#include "parser.hpp"
#include "hash_cache.hpp"
#include "cse.hpp"

int main()
{
	size_t count;
	std::cin >> count;

	for(size_t i = 0; i < count; i++)
	{
		if(std::cin.get() != '\n') // Read newline
			throw std::runtime_error("Expected newline in input");

		std::string str;
		std::cin >> str; // First writing to a string is faster
		std::stringstream sstr(str);

		const expr_ptr e(parser::read_expr(sstr));

		{
			cse c;
			c.print(e, std::cout); // Print Common Subexpression Eliminated variant
		}

		std::cout << std::endl; // Finish with newline
	}

	return 0;
}

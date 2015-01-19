#include <iostream>
#include <sstream>

#include "parser.hpp"
#include "hash_cache.hpp"
#include "cse.hpp"

int main(int argc, char** argv)
{
	size_t count;
	std::cin >> count;

	for(size_t i = 0; i < count; i++)
	{
		std::cin.get();

		std::string str;
		std::cin >> str; // Writing to a string first is faster

		std::stringstream sstr(str);
		parser p(sstr);

		auto e(p.read_expr());

		cse c;
		c.print(e, std::cout);
		std::cout << std::endl;
	}

	return 0;
}

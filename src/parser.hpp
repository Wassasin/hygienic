#pragma once

#include <istream>

#include "expr.hpp"

class parser
{
	parser() = delete; // Private constructor

	static bool is_alpha(char c)
	{
		return (
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z')
		);
	}

	static void assume(bool b)
	{
		if(!b)
			throw std::runtime_error("Assumption failure");
	}

	static bool read_term(std::istream& is, char c)
	{
		if(is.eof() || is.peek() != c)
			return false;

		is.get();
		return true;
	}

	static std::string read_var(std::istream& is)
	{
		std::string result;

		while(true)
		{
			auto c = is.peek();

			if(!is_alpha(c) || is.eof())
				return result;

			result.push_back(c);
			is.get();
		}
	}

public:
	static expr_ptr read_expr(std::istream& is)
	{
		std::string name = read_var(is);

		if(!read_term(is, '('))
			return std::make_shared<expr>(name);

		std::vector<expr_ptr> subexprs;
		bool first = true;
		while(!read_term(is, ')'))
		{
			if(first)
				first = false;
			else
				assume(read_term(is, ','));

			subexprs.emplace_back(read_expr(is));
		}

		expr* ptr = new expr(std::move(name), std::move(subexprs));
		return std::shared_ptr<expr>(ptr);
	}
};

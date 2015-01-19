#pragma once

#include <istream>

#include "expr.hpp"

class parser
{
	std::istream& is;

	bool is_alpha(char c)
	{
		return (
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z')
		);
	}

	bool eof()
	{
		return is.eof();
	}

	void assume(bool b)
	{
		if(!b)
			throw std::runtime_error("Assumption failure");
	}

	bool read_term(char c)
	{
		if(eof() || is.peek() != c)
			return false;

		is.get();
		return true;
	}

	std::string read_var()
	{
		std::string result;

		while(true)
		{
			auto c = is.peek();

			if(!is_alpha(c) || eof())
				return result;

			result.push_back(c);
			is.get();
		}
	}

public:
	parser(std::istream& is)
		: is(is)
	{}

	expr_ptr read_expr()
	{
		std::string name = read_var();

		if(!read_term('('))
			return std::make_shared<expr>(name);

		std::vector<expr_ptr> subexprs;
		bool first = true;
		while(!read_term(')'))
		{
			if(first)
				first = false;
			else
				assume(read_term(','));

			subexprs.emplace_back(read_expr());
		}

		expr* ptr = new expr(std::move(name), std::move(subexprs));
		return std::shared_ptr<expr>(ptr);
	}
};

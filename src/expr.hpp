#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ostream>

struct expr;

typedef std::shared_ptr<expr> expr_ptr;

struct expr
{
	enum class expr_type_t
	{
		ET_VAR,
		ET_FUNCALL
	};

	expr_type_t type;
	std::string name;

	std::vector<expr_ptr> subexprs;

	expr(std::string name)
		: type(expr_type_t::ET_VAR)
		, name(name)
		, subexprs()
	{}

	expr(std::string name, std::vector<expr_ptr> subexprs)
		: type(expr_type_t::ET_FUNCALL)
		, name(name)
		, subexprs(subexprs)
	{}
};

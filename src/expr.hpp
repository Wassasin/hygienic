#pragma once

#include <string>
#include <vector>
#include <memory>

struct expr;

typedef std::shared_ptr<expr> expr_ptr;

/* An immutable expression, either a variable or a function call.
 * Variable: "a"
 * Funtion call: "f(a,b)"
 */
struct expr
{
	enum class expr_type_t
	{
		ET_VAR,
		ET_FUNCALL
	};

	const expr_type_t type;
	const std::string name;

	const std::vector<expr_ptr> subexprs;

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

#pragma once

#include <functional>

#include "expr.hpp"

template<>
struct std::hash<expr::expr_type_t>
{
	size_t operator()(expr::expr_type_t& t) const
	{
		switch(t)
		{
		case expr::expr_type_t::ET_VAR:
			return 1;
		case expr::expr_type_t::ET_FUNCALL:
			return 2;
		}
	}
};

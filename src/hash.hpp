#pragma once

#include <functional>

#include "expr.hpp"

namespace std
{

template<>
struct hash<expr::expr_type_t>
{
	size_t operator()(const expr::expr_type_t& t) const
	{
		switch(t)
		{
		case expr::expr_type_t::ET_VAR:
			return 1;
		case expr::expr_type_t::ET_FUNCALL:
			return 2;
		}

		return 0; // GCC does not have reachability analysis
	}
};

}

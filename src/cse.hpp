#pragma once

#include <unordered_map>

#include "expr.hpp"
#include "hash_cache.hpp"

struct cse
{
	std::unordered_map<size_t, size_t> id_map;
	hash_cache hashes;
	size_t i;

	cse()
		: id_map()
		, hashes()
		, i(1)
	{}

	void print(expr_ptr e, std::ostream& os)
	{
		size_t h = hashes.fetch_add(e);
		auto it = id_map.find(h);

		if(it != id_map.end())
		{
			os << it->second;
			return;
		}

		size_t current_i = i++;
		os << e->name;

		switch(e->type)
		{
		case expr::expr_type_t::ET_VAR:
			break;
		case expr::expr_type_t::ET_FUNCALL:
			os << '(';
			bool first = true;
			for(const expr_ptr se : e->subexprs)
			{
				if(first)
					first = false;
				else
					os << ',';

				print(se, os);
			}
			os << ')';
			break;
		}

		id_map.emplace(std::make_pair(h, current_i));
	}
};

#pragma once

#include <unordered_map>
#include <tuple>

#include "expr.hpp"
#include "hash.hpp"

/* Remembers for each expression visited it's hash.
 * By pointer of expression. */
class hash_cache
{
	std::unordered_map<expr*, size_t> map;

	static size_t combine(size_t h1, size_t h2)
	{
		return h1 * 101 + h2;
	}

public:
	hash_cache()
		: map()
	{}

	/* Look up hash of expr.
	 * If expr is not yet in cache, add it and all the subnodes to the cache.
	 * Assumes expr to be immutable.
	 * O(n), walks through tree once. */
	size_t fetch_add(expr_ptr e)
	{
		auto it = map.find(e.get());
		if(it != map.end())
			return it->second;

		size_t h1 = std::hash<expr::expr_type_t>()(e->type);
		size_t h2 = std::hash<std::string>()(e->name);

		size_t h3 = 0;

		for(auto se : e->subexprs)
			h3 = combine(fetch_add(se), h3);

		size_t h = combine(h1, combine(h2, h3));
		map.emplace(std::make_pair(e.get(), h));
		return h;
	}
};

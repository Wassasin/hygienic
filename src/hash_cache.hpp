#pragma once

#include <unordered_map>
#include <tuple>
#include <boost/functional/hash.hpp>

#include "expr.hpp"

/* Remembers for each expression visited it's hash.
 * By pointer of expression. */
class hash_cache
{
	std::unordered_map<expr*, size_t> map;

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

		size_t h = 0;
		boost::hash_combine(h, boost::hash_value(e->type));
		boost::hash_combine(h, boost::hash_value(e->name));

		for(auto se : e->subexprs)
			boost::hash_combine(h, fetch_add(se));

		map.emplace(std::make_pair(e.get(), h));
		return h;
	}
};

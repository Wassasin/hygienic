#pragma once

#include <unordered_map>
#include <tuple>

#include "expr.hpp"
#include "hash.hpp"

class hash_cache
{
	std::unordered_map<expr*, size_t> map;

public:
	hash_cache()
		: map()
	{
		map.reserve(1024);
	}

	size_t fetch_add(expr_ptr e);
};

size_t hash_cache::fetch_add(expr_ptr e)
{
	auto it = map.find(e.get());
	if(it != map.end())
		return it->second;

	size_t h1 = std::hash<expr::expr_type_t>()(e->type);
	size_t h2 = std::hash<std::string>()(e->name);

	size_t h3 = 0;

	for(auto se : e->subexprs)
		h3 = fetch_add(se) ^ (h3 << 1);

	size_t h = h1 ^ ((h2 ^ (h3 << 1)) << 1);

	map.emplace(std::make_pair(e.get(), h));
	return h;
}

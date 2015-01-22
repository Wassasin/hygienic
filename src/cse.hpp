#pragma once

#include <unordered_map>

#include "expr.hpp"
#include "hash_cache.hpp"

/* Remembers expression printed before,
 * and replaces these subexpressions with predetermined id's. */
class cse
{
	class expr_hash
	{
		const hash_cache& cache;

	public:
		expr_hash(const hash_cache& cache)
			: cache(cache)
		{}

		size_t operator()(expr_ptr e) const
		{
			return cache.fetch(e);
		}
	};

	class expr_eq
	{
		const hash_cache& cache;

		bool eq(const expr_ptr& lhs, const expr_ptr& rhs) const
		{
			if(
					lhs->name != rhs->name ||
					lhs->type != rhs->type ||
					lhs->subexprs.size() != rhs->subexprs.size()
			)
				return false;

			for(size_t i = 0; i < lhs->subexprs.size(); i++)
				if(!this->operator ()(lhs->subexprs[i], rhs->subexprs[i]))
					return false;

			return true;
		}

	public:
		expr_eq(const hash_cache& cache)
			: cache(cache)
		{}

		bool operator()(const expr_ptr& lhs, const expr_ptr& rhs) const
		{
			if(cache.fetch(lhs) != cache.fetch(rhs))
				return false;

			if(eq(lhs, rhs))
				return true;

			return false;
		}
	};

	const hash_cache hashes;
	std::unordered_map<expr_ptr, size_t, expr_hash, expr_eq> id_map;
	size_t i;

	static hash_cache create_hash_cache(const expr_ptr& e)
	{
		hash_cache cache;
		cache.fetch_add(e);
		return cache;
	}

	cse(const expr_ptr& e)
		: hashes(create_hash_cache(e))
		, id_map({}, 1024, expr_hash(hashes), expr_eq(hashes))
		, i(1) // Stated by assignment (1-indexed)
	{}

	void print_expr(expr_ptr e, std::ostream& os)
	{
		{
			auto it = id_map.find(e);
			if(it != id_map.end())
			{
				os << it->second;
				return;
			}
		}

		// Remember the id given to the current node
		id_map.emplace(std::make_pair(e, i++));
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

				print_expr(se, os);
			}
			os << ')';
			break;
		}
	}

public:
	static void print(expr_ptr e, std::ostream& os)
	{
		cse c(e);
		c.print_expr(e, os);
	}
};

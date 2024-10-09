#pragma once

#include <functional>
#include <vector>
#include "shared.h"

namespace overdrive {
namespace vector {
	using namespace shared;

	template <typename A>
	auto filter(
		const std::vector<A>& vector,
		const std::function<bool_t(const A& value, size_t index)> predicate
	) -> std::vector<A> {
		auto result = std::vector<A>();
		for (auto index = size_t(0); index < vector.size(); index += 1) {
			auto& value = vector.at(index);
			if (predicate(value, index)) {
				result.push_back(value);
			}
		}
		return result;
	}

	template <typename A, typename B>
	auto map(
		const std::vector<A>& vector,
		const std::function<B(const A& value, size_t index)> mapper
	) -> std::vector<B> {
		auto result = std::vector<B>();
		for (auto index = size_t(0); index < vector.size(); index += 1) {
			auto& value = vector.at(index);
			result.push_back(mapper(value, index));
		}
		return result;
	}
}
}

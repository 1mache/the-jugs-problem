#pragma once
#include <utility>
#include <cstddef>
#include <cstdint>

class Config
{
public:
	using NodeType = std::pair<size_t, size_t>;

	static constexpr size_t INF = SIZE_MAX;
	static constexpr size_t NULL_ID = SIZE_MAX;
};
#pragma once
#include <utility>

class Node
{
    std::pair<size_t, size_t> m_state;
    size_t m_id;

public:
    Node(const std::pair<size_t, size_t>& state, size_t id) : m_state(state), m_id(id) {}
    
	// needed for std::sort
    bool operator <(const Node& other) const
    {
		// uses compare of std::pair
        return m_state < other.m_state;
    }

    const std::pair<size_t, size_t>& getState() const { return m_state; }
    size_t getId() const { return m_id; }
    
    void setState(const std::pair<size_t, size_t>& state) { m_state = state; }
};
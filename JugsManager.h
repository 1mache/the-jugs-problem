#pragma once
#include "Graph.h"

class JugsManager
{
	size_t m_smallJug, m_largeJug, m_targetJug;
	Graph m_graph;

public:
	JugsManager(size_t L, size_t S, size_t W):
		m_smallJug(S), m_largeJug(L), m_targetJug(W), m_graph(L, S)
	{}
};
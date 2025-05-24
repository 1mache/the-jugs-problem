#include "Graph.h"

void Graph::MakeEmptyGraph(size_t n)
{
	m_adjList.reserve(n);
	
	for (size_t i = 0; i < L; ++i) {
		for (size_t j = 0; j < S; ++j)
		{
			// add node (pair) into the adjacency list with empty neightbors list
			m_adjList[nodeId({ i, j })] = Neighbors();
		}
	}
}

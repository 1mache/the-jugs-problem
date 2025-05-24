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

std::list<Graph::Action> Graph::GetPath(Node goal)
{
	std::list<Action> path;
	Node current = goal;

	while (current != startNode)
	{
		size_t cid = nodeId(current);
		if (m_distances[cid] == static_cast<size_t>(-1)) 
		{
			return std::list<Action>(); // unreachable
		}

		std::pair<Node, Action> parentAction = m_parents[cid];
		Node parent = parentAction.first;
		Action action = parentAction.second;

		path.push_front(action);
		current = parent;
	}

	return path;
}


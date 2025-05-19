#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include "Node.h"

class Graph
{
	using AdjacencyList = std::vector<std::list<Node>>;
	AdjacencyList m_adjList;

public:
	Graph(size_t nodeCount)
	{
		MakeEmptyGraph(nodeCount);
	} 

	Graph(Graph&) = delete;
	Graph& operator=(Graph&) = delete;

	void MakeEmptyGraph(size_t n)
	{
		m_adjList.clear();
		m_adjList.reserve(n);
	}

	std::list<Node> GetAdjList(Node u)
	{
		return m_adjList[u.getId()];
	}	

	void AddEdge(Node u, Node v)
	{
		m_adjList[u.getId()].push_back(v);
		// sort lexicographically (see: Node operator < )
		m_adjList[u.getId()].sort(); 
	}
};
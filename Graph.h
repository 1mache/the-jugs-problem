#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <list>

class Graph
{
	using Node = std::pair<size_t, size_t>; 
	using AdjacencyList = std::vector<std::list<Node>>;
	AdjacencyList m_adjList;

	const size_t c_maxFirst, c_maxSecond;

public:
	Graph(size_t L, size_t S) : c_maxFirst(L), c_maxSecond(S)
	{
		MakeEmptyGraph((L+1) * (S+1));
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
		return m_adjList[nodeId(u)];
	}

	size_t nodeId(const Node& node)
	{
		return node.first * c_maxSecond + node.second;
	}	

	void AddEdge(Node u, Node v)
	{
		m_adjList[nodeId(u)].push_back(v);
		// sort lexicographically (with pair comparison)
		m_adjList[nodeId(u)].sort();
	}
};
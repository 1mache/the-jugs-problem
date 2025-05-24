#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <queue>

class Graph
{
public:
	enum Action {
		FillL,
		FillS,
		EmptyL,
		EmptyS,
		PourLtoS,
		PourStoL
	};

	using Node = std::pair<size_t, size_t>; 
	using Neighbors = std::list<Node>;
private:

	using AdjacencyList = std::vector<std::list<Node>>;
	const size_t L, S;

	AdjacencyList m_adjList;
	
	// BFS related
	const Node startNode = { 0, 0 };
	std::vector<std::pair<Node, Action>> m_parents;
	std::vector<size_t>					 m_distances;

public:
	Graph(size_t L, size_t S) : L(L), S(S)
	{
		MakeEmptyGraph((L+1) * (S+1));
	}

	Graph(Graph&) = delete;
	Graph& operator=(Graph&) = delete;

	void MakeEmptyGraph(size_t n);

	Neighbors GetAdjList(Node u)
	{
		return m_adjList[nodeId(u)];
	}

	void AddEdge(Node u, Node v)
	{
		m_adjList[nodeId(u)].push_back(v);
		// sort lexicographically (with pair comparison)
		m_adjList[nodeId(u)].sort();
	}

	std::list<Action> GetPath(Node goal);

private:
	// Convert a node to a unique index in the adjacency list
	size_t nodeId(Node u) const
	{
		return u.first * (S + 1) + u.second;
	}
};
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <queue>

class Graph
{
public:
	enum class Action 
	{
		FillL,
		FillS,
		EmptyL,
		EmptyS,
		PourLtoS,
		PourStoL, 
		None
	};

	using Node = std::pair<size_t, size_t>;
	using NeighborList = std::list<Node>;
	using AdjList = std::vector<NeighborList>;

public:
	Graph(size_t L, size_t S) : m_L(L), m_S(S), m_NodesCount((L + 1)* (S + 1))
	{
		MakeEmptyGraph(m_NodesCount);
	}
	Graph(Graph&) = delete;
	Graph& operator=(Graph&) = delete;

	void Graph::MakeEmptyGraph(size_t n)
	{
		m_adjList.resize(n);
	}

	NeighborList GetAdjList(Node u) { return m_adjList[nodeId(u)]; }

	void AddEdge(Node u, Node v)
	{
		// push v into the adjacency list of u
		m_adjList[nodeId(u)].push_back(v);
		// sort lexicographically (with pair comparison)
		m_adjList[nodeId(u)].sort();
	}

	void BFS();
	std::list<Action> GetActionPath(Node target);

private:
	// definintion of infinity for bfs
	static constexpr size_t INF = SIZE_MAX;

	const size_t m_L, m_S;
	const size_t m_NodesCount;

	AdjList m_adjList;

	// ======= BFS related =========
	const Node m_bfsStartNode = { 0, 0 };
	// parents hold the previous node and the action taken to reach the current node
	std::vector<std::pair<Node*, Action>> m_parents;
	std::vector<size_t>					  m_distances;

private:
	// convert a node to a unique index in the adjacency list
	size_t nodeId(Node u) const
	{
		return u.first * (m_S + 1) + u.second;
	}

	// determine the action taken to go from one node to another
	Graph::Action getAction(const Node& from, const Node& to);
};
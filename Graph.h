#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <queue>

#include "Config.h"
#include "Action.h"

class Graph
{
public:
	using Node = Config::NodeType;
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

	NeighborList GetAdjList(Node u) { return m_adjList[nodeToId(u)]; }

	void AddEdge(Node u, Node v)
	{
		// push v into the adjacency list of u
		m_adjList[nodeToId(u)].push_back(v);
		// sort lexicographically (with pair comparison)
		m_adjList[nodeToId(u)].sort();
	}

	void BFS(const Node& startNode);
	std::list<Action> GetActionPath(const Node& target);

private:
	const size_t m_L, m_S;
	const size_t m_NodesCount;

	AdjList m_adjList;

	// ======= BFS related =========
	size_t m_bfsStartNodeId = Config::NULL_ID; // which node is the start node for BFS
	// parents hold the previous node id and the action taken to reach the current node
	std::vector<std::pair<size_t, Action>> m_parents;
	std::vector<size_t>					   m_distances;

private:
	// convert a node to a unique index in the adjacency list
	size_t nodeToId(const Node& u) const
	{
		return u.first * (m_S + 1) + u.second;
	}

	// TODO: remove later if not used
	Node idToNode(size_t id) const 
	{
		return Node{ id / (m_S + 1), id % (m_S + 1) };
	}

	// determine the action taken to go from one node to another
	Action getAction(const Node& from, const Node& to);
};
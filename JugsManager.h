#pragma once
#include <unordered_map>
#include <queue>
#include "Graph.h"

class JugsManager
{
	using Node = Config::NodeType;
	using Transition = std::pair<Node, Action>;

	const size_t m_L, m_S, m_W;
	const Node m_startState = { 0, 0 }; // initial state of the jugs
	const Node m_goalState =  { m_W, 0 }; // goal state of the jugs

	// map that stores the actions taken to reach each node
	// (if node was processed), each node is represented by a unique index
	std::unordered_map<size_t, Action> m_visited;
public:
	JugsManager(size_t L, size_t S, size_t W):
		m_S(S), m_L(L), m_W(W)
	{}
	// Graph solution (implementation 1)
	void SolveWithGraph();
	// Hash table solution (implementation 2)
	void SolveWithHashTable();
	// calculate unvisited neighbors of a node
	std::list<Transition> CalculateAdjList(const Node& u); 
private:
	std::list<Action> calcActionPath(const std::unordered_map<size_t, size_t> parentMap) const;

	// helper functio to print the actions taken to reach solutions
	void printSolution(const std::list<Action>& actionPath) const;
	
	// convert a node to a unique index
	size_t nodeToId(const Node& u) const
	{
		return u.first * (m_S + 1) + u.second;
	}

	// checks if the node has been visited
	bool isVisited(size_t u_id) const
	{
		return m_visited.find(u_id) != m_visited.end();
	}
};
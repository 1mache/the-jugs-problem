#include "Graph.h"

void Graph::BFS()
{
	std::queue<Node> q;
	q.push(m_bfsStartNode);
	// initialize distances and parents
	m_distances.resize(m_NodesCount, INF);
	m_distances[nodeId(m_bfsStartNode)] = 0;
	// for now, should be null or similar
	m_parents.resize(m_NodesCount, { nullptr, Action::None });

	while (!q.empty())
	{
		Node v = q.front();
		q.pop();

		for (const Node& u : GetAdjList(v))
		{
			size_t uId = nodeId(u);

			if (m_distances[uId] == INF) // not visited
			{
				// update distance 
				m_distances[uId] = m_distances[nodeId(v)] + 1;
				// update parent and action
				m_parents[uId] = { &v, getAction(v, u) };
				q.push(u);
			}
		}
	}
}

std::list<Graph::Action> Graph::GetActionPath(Node target)
{
	// BFS should be called before this, this relies on
	// the parents list
	if (m_parents.empty())
		throw std::logic_error("Shortest path tree is empty.");

	std::list<Action> actionPath;

	size_t currId  = nodeId(target);
	size_t startId = nodeId(m_bfsStartNode);

	// if the target node is unreachable from the start node
	if(m_parents[currId].first == nullptr)
		return actionPath; // return empty path

	while (currId != nodeId(m_bfsStartNode))
	{
		auto action = m_parents[currId].second;
		// should never happen
		if (action == Action::None)
			throw std::logic_error("\"None\" action was found in shortest path tree.");

		// push the action to front because we are going backwards
		actionPath.push_front(m_parents[currId].second);
		// update current id to its parent id
		currId = nodeId(*(m_parents[currId].first));
	}
}

Graph::Action Graph::getAction(const Node& from, const Node& to)
{
	if (to.first > from.first && to.second == from.second) return Action::FillL;
	if (to.second > from.second && to.first == from.first) return Action::FillS;
	if (to.first == 0 && to.second == from.second) return Action::EmptyL;
	if (to.second == 0 && to.first == from.first) return Action::EmptyS;
	if (to.first < from.first && to.second > from.second) return Action::PourLtoS;
	if (to.first > from.first && to.second < from.second) return Action::PourStoL;

	// should never reach here if the graph is constructed correctly
	return Action::None;
}
#include "JugsManager.h"

void JugsManager::SolveWithGraph()
{
	Graph graph(m_L, m_S);

	// Add all possible state transitions to the graph
	for (size_t i = 0; i < m_L + 1; ++i) {
		for (size_t j = 0; j < m_S + 1; ++j)
		{
			Node currentState = { i, j };

			// Precalculate more complex state transitions:
			// min between how much large has and how much small can take
			size_t transferAmount = std::min(i, m_S - j);
			Node largeToSmall = { i - transferAmount, j + transferAmount };

			// min between how much small has and how much large can take
			transferAmount = std::min(j, m_L - i);
			Node smallToLarge = { i + transferAmount, j - transferAmount };

			std::vector<Node> possibleNeighbors
			{
				Node(m_L, j),    // Fill large jug
				Node(i, m_S),    // Fill small jug
				Node(0, j),      // Empty large jug
				Node(i, 0),      // Empty small jug
				largeToSmall,    // From large jug to small jug
				smallToLarge     // From small jug to large jug
			};

			for (const auto& neighbor : possibleNeighbors)
			{
				// we dont want edges to the same state
				if (currentState != neighbor)
					graph.AddEdge(currentState, neighbor);
			}
		}
	}

	graph.BFS(m_startState);
	std::list<Action> path = graph.GetActionPath(m_goalState);
	printSolution(path);
}

void JugsManager::SolveWithHashTable()
{
	m_visited.clear();

	// parents map (by indecies)
	std::unordered_map<size_t, size_t> parents;
	std::queue<Node> q;

	q.push(m_startState);
	// initialize start's parent to NULL
	parents[nodeToId(m_startState)] = Config::NULL_ID;

	while(!q.empty())
	{
		auto node   = q.front();
		auto nodeId = nodeToId(node);
		q.pop();

		auto adjList = CalculateAdjList(node);

		for(const auto& neighbor : adjList)
		{
			auto neighborId = nodeToId(neighbor.first);
			auto actionTaken = neighbor.second;

			// store the action leading to this node under nodes id
			m_visited[neighborId] = actionTaken;
			// assign the current node to be this one's parent
			parents[neighborId] = nodeId;

			q.push(neighbor.first);
		}
	}

	printSolution(calcActionPath(parents));
}

std::list<JugsManager::Transition> JugsManager::CalculateAdjList(const Node& u)
{
	std::list<Transition> adjList;

	size_t i = u.first, j = u.second;

	// Precalculate more complex state transitions:
	// min between how much large has and how much small can take
	size_t transferAmount = std::min(i, m_S - j);
	Node largeToSmall = { i - transferAmount, j + transferAmount };

	// min between how much small has and how much large can take
	transferAmount = std::min(j, m_L - i);
	Node smallToLarge = { i + transferAmount, j - transferAmount };

	std::vector<Transition> possibleNeighbors
	{
		{ Node(m_L, j),  Action::FillL    }, // Fill large jug
		{ Node(i, m_S),  Action::FillS    }, // Fill small jug
		{ Node(0, j),    Action::EmptyL   }, // Empty large jug
		{ Node(i, 0),    Action::EmptyS   }, // Empty small jug
		{ largeToSmall,  Action::PourLtoS }, // From large jug to small jug
		{ smallToLarge,  Action::PourStoL }  // From small jug to large jug
	};

	for (const auto& neighbor : possibleNeighbors)
	{
		auto neighborId = nodeToId(neighbor.first);
		// if the transition is not to the same state 
		// and the neighbor has not been visited yet
		if (u != neighbor.first && !isVisited(neighborId))
			adjList.push_back(neighbor); // add to adjacency list
	}

	return adjList;
}

std::list<Action> JugsManager::calcActionPath(const std::unordered_map<size_t, size_t> parentMap) const
{
	std::list<Action> actionPath;
	// needs to recieve valid parentMap
	if (parentMap.empty())
		return actionPath; // return empty list

	size_t currId = nodeToId(m_goalState);
	size_t startId = nodeToId(m_startState);

	// if the target node is unreachable from the start node
	if (parentMap.at(currId) == Config::NULL_ID)
		return actionPath; // return empty path

	while (currId != startId)
	{
		auto action = m_visited.at(currId);
		// should never happen
		if (action == Action::None)
			throw std::logic_error("\"None\" action was found among jugs actions.");

		// push the action to front because we are going backwards
		actionPath.push_front(action);
		// update current id to its parent id
		currId = parentMap.at(currId);
	}

	return actionPath;
}

void JugsManager::printSolution(const std::list<Action>& actionPath) const
{
	if (actionPath.empty())
	{
		std::cout << "No solution." << std::endl;
		return;
	}

	std::cout << "Number of operations: " << actionPath.size() << std::endl;
	std::cout << "Operations:\n";

	size_t stepCount = 1;

	for (auto action : actionPath)
	{
		std::cout << stepCount << ". ";
		stepCount++;

		switch (action)
		{
		case Action::FillL:
			std::cout << "Fill large jug\n";
			break;
		case Action::FillS:
			std::cout << "Fill small jug\n";
			break;
		case Action::EmptyL:
			std::cout << "Empty large jug\n";
			break;
		case Action::EmptyS:
			std::cout << "Empty small jug\n";
			break;
		case Action::PourLtoS:
			std::cout << "Transfer from large jug to small jug\n";
			break;
		case Action::PourStoL:
			std::cout << "Transfer from small jug to large jug\n";
			break;
		}
	}
}
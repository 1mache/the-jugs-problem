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

}

std::list<JugsManager::Node> JugsManager::CalculateAdjList(const Node& u)
{
	std::list<Node> adjList;

	// check all possible state transitions from the current Node u
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

			std::vector<std::pair<Node, Action>> possibleNeighbors
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
				if (currentState != neighbor.first && !isVisited(neighborId)) 
				{
					adjList.push_back(neighbor.first);
					// store the action leading to this state
					m_visited[neighborId] = neighbor.second; 
				}
			}
		}
	}

	return adjList;
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
#include "JugsManager.h"

void JugsManager::solveWithGraph()
{
	Graph graph(L, S);
	// TODO: is this ok?
	//graph.MakeEmptyGraph((L+1)*(S+1));

	// Add all possible state transitions to the graph
	for (size_t i = 0; i < L+1; ++i) {
		for (size_t j = 0; j < S+1; ++j)
		{
			// TODO: can we change AddEdge to pass Action
			
			// Fill large jug:
			if (i < L) // if the large jug is not full
				graph.AddEdge({ i, j }, { L, j });

			// Fill small jug:
			if(j < S) // if the small jug is not full
				graph.AddEdge({ i, j }, { i, S });

			// Empty large jug:
			if (i > 0) // if the large jug is not empty
				graph.AddEdge({ i, j }, { 0, j });

			// Empty small jug
			if (j > 0) // if the large jug is not empty
				graph.AddEdge({ i, j }, { i, 0 });

			// From large jug to small jug:
			
			// min between how much large has and how much small can take
			size_t transferAmount = std::min(i, S - j);
			std::pair<size_t, size_t> newState = { i - transferAmount, j + transferAmount};
			if (newState != newState)
				graph.AddEdge({ i, j }, newState);

			// From small jug to large jug:
			
			// min between how much small has and how much large can take
			transferAmount = std::min(j, L - i);
			newState = { i + transferAmount, j - transferAmount };
			if (newState != newState)
				graph.AddEdge({ i, j }, newState);
		}
	}

	graph.BFS();
	std::list<Graph::Action> path = graph.GetActionPath({ W, 0 });

	std::cout << "Number of operations: " << path.size() << std::endl;
	std::cout << "Operations:\n";

	size_t stepCount = 1;

	for (auto action : path)
	{
		std::cout << stepCount << ". ";
		stepCount++;

		switch (action)
		{
		case Graph::Action::FillL:
			std::cout << "Fill large jug\n";
			break;
		case Graph::Action::FillS:
			std::cout << "Fill small jug\n";
			break;
		case Graph::Action::EmptyL:
			std::cout << "Empty large jug\n";
			break;
		case Graph::Action::EmptyS:
			std::cout << "Empty small jug\n";
			break;
		case Graph::Action::PourLtoS:
			std::cout << "Transfer from large jug to small jug\n";
			break;
		case Graph::Action::PourStoL:
			std::cout << "Transfer from small jug to large jug\n";
			break;
		}
	}
}
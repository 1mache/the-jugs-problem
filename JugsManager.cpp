#include "JugsManager.h"

void JugsManager::solveWithGraph()
{
	Graph graph(L, S);
	// TODO: is this ok?
	//graph.MakeEmptyGraph((L+1)*(S+1));

	graph.BFS();
	std::list<Graph::Action> path = graph.GetActionPath({ W, 0 });

	std::cout << "Number of operations: " << path.size() << std::endl;
	std::cout << "Operations:\n";

	for(auto action : path)
	{
		switch(action)
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
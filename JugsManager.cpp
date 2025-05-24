#include "JugsManager.h"

void JugsManager::solveWithGraph()
{
	Graph graph(L, S);
	// TODO: is this ok?
	//graph.MakeEmptyGraph((L+1)*(S+1));

	graph.BFS();
	std::list<Graph::Action> path = graph.GetActionPath({ W, 0 });

	for(auto action : path)
	{
		switch(action)
		{
			case Graph::Action::FillL:
				std::cout << "Fill L jug\n";
				break;
			case Graph::Action::FillS:
				std::cout << "Fill S jug\n";
				break;
			case Graph::Action::EmptyL:
				std::cout << "Empty L jug\n";
				break;
			case Graph::Action::EmptyS:
				std::cout << "Empty S jug\n";
				break;
			case Graph::Action::PourLtoS:
				std::cout << "Pour L jug to S jug\n";
				break;
			case Graph::Action::PourStoL:
				std::cout << "Pour S jug to L jug\n";
				break;
		}
	}
}
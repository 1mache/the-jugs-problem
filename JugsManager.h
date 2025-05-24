#pragma once
#include "Graph.h"

class JugsManager
{
	const size_t L, S, W;
public:
	JugsManager(size_t L, size_t S, size_t W):
		S(S), L(L), W(W)
	{}
	
	void solveWithGraph();

};
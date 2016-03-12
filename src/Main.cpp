//
//
//
//
//

#include <iostream>
#include "GraphManager.h"
#include "Planet.h"

uint GetRandom(uint min, uint max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint> uni(min, max);
	return uni(rng);
}

int main(int argc, const char** argv)
{
	GraphManager GraphManager;
	GraphManager.CreateGraph(50, { 200, 200 });
	GraphManager.FormEdges();

	std::vector<Planet> PlanetList;

	for (uint i = 0; i < GraphManager.NumNodes(); ++i)
		PlanetList.emplace_back(GraphManager.TakeNode());



	return 0;
}

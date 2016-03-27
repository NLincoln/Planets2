//
//
//
//
//

#include <iostream>
#include "GraphManager.h"
#include "Planet.h"
#include "Ship.h"

uint GetRandom(uint min, uint max)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<uint> uni(min, max);
    return uni(rng);
}

int main(int argc, const char** argv)
{
    const uint NUM_SHIPS = 50;
    const uint NUM_PLANETS = 500;
    const uint FIELD_DIMS = 500;
    GraphManager GraphManager;
    GraphManager.CreateGraph(NUM_PLANETS, { FIELD_DIMS, FIELD_DIMS });
    GraphManager.FormEdges();
    
    std::vector<Planet*> PlanetList;

    for (uint i = 0; i < GraphManager.NumNodes(); ++i)
    {
        Planet* p = new Planet(i, GraphManager.TakeNode());
        PlanetList.push_back(p);
    }
    std::vector<Ship> ShipList;
    for (uint i = 0; i < NUM_SHIPS; ++i)
    {
        ShipList.emplace_back(PlanetList[GetRandom(0, NUM_PLANETS)], [&] (GraphNode* Start, GraphNode* End)
        {
            auto GraphList = GraphManager.FindPath(Start, End);
            std::vector<Planet*> Result;
            for(auto Node : GraphList)
                for (Planet* Planet : PlanetList)
                    if (Planet->GetGraphNode() == Node)
                        Result.push_back(Planet);
            return Result;
        });
    }

    for (auto& Ship : ShipList)
        Ship.Tick();

    return 0;
}

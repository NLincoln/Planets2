//
// Created by nate on 3/4/16.
//

#ifndef PLANETS2_PLANET_H
#define PLANETS2_PLANET_H

#include <vector>
#include <iostream>
#include "Ore.h"

class GraphNode;

class Planet
{
    uint m_id;
    GraphNode* m_GraphNode;
    OreMap m_OrePrices;

public:
    GraphNode* GetGraphNode() const;

    uint GetOrePrice(Ore ore) const;
    OreMap GetOrePrices() const;


    Planet(uint id, GraphNode *Node);
    friend std::ostream& operator<<(std::ostream&, Planet&);
};

#endif //PLANETS2_PLANET_H

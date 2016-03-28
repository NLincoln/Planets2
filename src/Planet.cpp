//
// Created by nate on 3/4/16.
//

#include "Planet.h"
#include "Common.h"


Planet::Planet(uint id, GraphNode* Node)
{
    m_id = id;
    m_GraphNode = Node;
    m_OrePrices = OreMapFactory();

    for (auto& ore : m_OrePrices)
    {
        ore.second = GetRandom(0, 100);
    }
}

GraphNode* Planet::GetGraphNode() const
{
    return m_GraphNode;
}

std::ostream& operator<<(std::ostream& out, Planet& p)
{
    return out << p.m_id;
}

uint Planet::GetOrePrice(Ore ore) const
{
    return m_OrePrices.at(ore);
}

OreMap Planet::GetOrePrices() const
{
    return m_OrePrices;
}



//
// Created by nate on 3/4/16.
//

#include "Planet.h"


Planet::Planet(uint id, GraphNode* Node)
{
	m_id = id;
	m_GraphNode = Node;
}

GraphNode* Planet::GetGraphNode() const
{
	return m_GraphNode;
}

std::ostream& operator<<(std::ostream& out, Planet& p)
{
	return out << p.m_id;
}

//
// Created by nate on 3/4/16.
//

#include "Planet.h"


Planet::Planet(GraphNode* Node)
{
	m_GraphNode = Node;
}

GraphNode* Planet::GetGraphNode() const
{
	return m_GraphNode;
}

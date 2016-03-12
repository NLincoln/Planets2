//
// Created by nate on 3/4/16.
//

#ifndef PLANETS2_PLANET_H
#define PLANETS2_PLANET_H


#include "GraphManager.h"

class GraphNode;

class Planet
{
	GraphNode* m_GraphNode;
public:
	GraphNode* GetGraphNode() const;

	Planet(GraphNode *Node);
};


#endif //PLANETS2_PLANET_H

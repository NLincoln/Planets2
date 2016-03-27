//
// Created by nate on 3/12/16.
//

#ifndef PLANETS_SHIP_H
#define PLANETS_SHIP_H


#include <queue>
#include "Planet.h"

class Ship
{
    std::vector<Planet*> m_Path;
    double m_TimeToTarget;
    std::function<std::vector<Planet*>(GraphNode*, GraphNode*)> m_PathCallback;

public:
    void Tick();

    void SetDestination(Planet *Destination);
    Ship(Planet* Start, std::function<std::vector<Planet*>(GraphNode*, GraphNode*)>  Callback);
};


#endif //PLANETS_SHIP_H

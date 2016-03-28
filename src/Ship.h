//
// Created by nate on 3/12/16.
//

#ifndef PLANETS_SHIP_H
#define PLANETS_SHIP_H


#include <queue>
#include <functional>
#include "Planet.h"

class Ship
{
    uint m_id;

    std::vector<Planet*> m_Path;
    double m_TimeToTarget;
    std::function<std::vector<Planet*>(GraphNode*, GraphNode*)> m_PathCallback;

    OreMap m_CargoHold;

public:
    void Tick(std::vector<Planet*> PlanetList);

    void SetDestination(Planet *Destination);
    Ship(uint id, Planet* Start, std::function<std::vector<Planet*>(GraphNode*, GraphNode*)>  Callback);
};


#endif //PLANETS_SHIP_H

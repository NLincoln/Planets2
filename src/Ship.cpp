//
// Created by nate on 3/12/16.
//

#include "Ship.h"
#include "GraphManager.h"
void Ship::SetDestination(Planet *Destination)
{
    m_Path = m_PathCallback(m_Path.front()->GetGraphNode(), Destination->GetGraphNode());
    std::cout << "Setting destination to Planet " << *Destination << std::endl;
    m_TimeToTarget = m_Path[0]->GetGraphNode()->DistanceTo(m_Path[1]->GetGraphNode());

    std::cout << "Time to target = " << m_TimeToTarget << std::endl;
}

Ship::Ship(uint id, Planet* Start, std::function<std::vector<Planet*>(GraphNode*, GraphNode*)>  Callback)
{
    m_id = id;
    m_PathCallback = Callback;
    m_Path.push_back(Start);
    m_CargoHold = OreMapFactory();

    for (auto& Ore : m_CargoHold)
        Ore.second = GetRandom(0, 50);

}

void Ship::Tick(std::vector<Planet*> PlanetList)
{
    --m_TimeToTarget;
    if (m_TimeToTarget < 0) // Done with this one
    {
        if (m_Path.size() > 1)
        {
            m_Path.erase(m_Path.begin());
            std::cout << "Going to next planet " << *m_Path.front() << std::endl;
            m_TimeToTarget = m_Path[0]->GetGraphNode()->DistanceTo(m_Path[1]->GetGraphNode());
        }
    }
    Planet* Dest = FindBestPlanet(PlanetList, m_CargoHold);

    SetDestination(Dest);
    std::cout << "Ship " << m_id << " Traveling to planet " << *Dest << std::endl;
}





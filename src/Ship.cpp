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

Ship::Ship(Planet* Start, std::function<std::vector<Planet*>(GraphNode*, GraphNode*)>  Callback)
{
    m_PathCallback = Callback;
    m_Path.push_back(Start);
}

void Ship::Tick()
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
}





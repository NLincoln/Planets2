//
// Created by nate on 3/5/16.
//

#include <vector>
#include "Ore.h"
#include "Planet.h"
OreMap OreMapFactory()
{
    OreMap Result;
    for (int i = 0; i < static_cast<int>(ORE::ORE_MAX); ++i)
        Result.insert(std::make_pair(static_cast<ORE>(i), 0));
    return Result;
}

Planet* FindBestPlanet(std::vector<Planet*> PlanetList, const OreMap& Cargo)
{
    Planet* BestPlanet = PlanetList[0];
    uint BestPrice = 0;

    auto SumPrice = [Cargo] (const Planet* Planet, const OreMap& Ores)
    {
        auto PriceMap = Planet->GetOrePrices();
        uint Price = 0;
        for (auto CargoOre : Cargo)
            Price += CargoOre.second * PriceMap[CargoOre.first];
        return Price;
    };

    for (auto Planet : PlanetList)
    {
        uint P = SumPrice(Planet, Cargo);
        if (P > BestPrice)
        {
            BestPlanet = Planet;
            BestPrice = P;
        }
    }

    return BestPlanet;
}

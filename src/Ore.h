//
// Created by nate on 3/5/16.
//

#ifndef PLANETS_ORE_H
#define PLANETS_ORE_H

#include <map>
#include <string>


enum class ORE
{
    Adamantium = 0,
    Actuatite,
    Argon,
    Cobalt,
    Nickel,
    Crogidon,
    Deoroxium,
    Deontistribos,
    Pludomititetium,
    Yttrium,
    Deontostrybiomium,
    Langonite,
    Bestrominite,
    Ironite,
    Orongondium,
    Chronomium,
    Aceron,
    Ukalite,
    Zornomeite,
    Aulite,
    Yytrillite,
    Mythrillite,

    ORE_MAX,
};
using Ore = ORE;
using OreMap = std::map<Ore, uint>;

OreMap OreMapFactory();

class Planet;

Planet* FindBestPlanet(std::vector<Planet*> PlanetList, const OreMap& Cargo);

#endif //PLANETS_ORE_H

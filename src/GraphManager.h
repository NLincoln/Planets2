//
//
//
//
//

#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include "Common.h"
#include "Planet.h"
#include "Ore.h"

#include <vector>
#include <map>
#include <functional>
#include <algorithm>


template <typename T>
struct Vector2
{
    T x;
    T y;
};

template <typename T>
bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs);

using Vector2u = Vector2<uint>;

class GraphNode;

struct PathInfo
{
    double Cost;
    bool isKnown;
    GraphNode* PrevNode;
};

struct GraphEdge
{
    double Cost;
    GraphNode* Destination;
};

template <typename T>
double distance(Vector2<T> a, Vector2<T> b);

class GraphNode
{   
    std::vector<GraphEdge> m_Neighbors;
    Vector2u m_Position;
public:
    void AddNeighbor(GraphEdge node);
    void AddNeighbor(GraphNode* node, double distance);
    void AddNeighbor(GraphNode* node);

    double DistanceTo(GraphNode* Node);

    Vector2u GetPosition() const;

    GraphNode(Vector2u Pos);

    friend class GraphManager;
};

using PathCallback = std::function<std::vector<GraphNode*>(GraphNode*, GraphNode*)>;

class GraphManager
{
    uint NumTaken;
    std::vector<GraphNode*> m_GraphList;
public:
    std::vector<GraphNode*> FindPath(GraphNode* Start, GraphNode* End) const;

    GraphManager& CreateGraph(const uint NumNodes, const Vector2u Field);
    GraphManager& FormEdges();

    PathCallback GetPathCallback();

    uint NumNodes();
    uint NumNodesNotTaken();
    GraphNode* TakeNode();

    GraphNode* operator[](uint index) const;

    GraphManager();
    ~GraphManager();
};

#endif

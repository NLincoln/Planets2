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
bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}

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
double distance(Vector2<T> a, Vector2<T> b)
{
	auto square = [](T x) { return x * x; };
	double d = square(a.x - b.x) + square(a.y - b.y);
	return std::sqrt(d);
}

class GraphNode
{	
	std::vector<GraphEdge> m_Neighbors;
	Vector2u m_Position;
public:
	void AddNeighbor(GraphEdge node)
	{
		m_Neighbors.push_back(node);
	}
	
	void AddNeighbor(GraphNode* node, double distance)
	{
		GraphEdge Edge;
		Edge.Cost = distance;
		Edge.Destination = node;
		AddNeighbor(Edge);
	}
	
	void AddNeighbor(GraphNode* node)
	{
		if (this != node)
		{
			double cost = distance(m_Position, node->m_Position);
			AddNeighbor(node, cost);
		}
	}

	double DistanceTo(GraphNode* Node)
	{
		for (auto Neighbor : m_Neighbors)
			if (Node == Neighbor.Destination)
				return Neighbor.Cost;

		return 0;
	}

	Vector2u GetPosition() const
	{
		return m_Position;
	}

	GraphNode(Vector2u Pos)
	{
		m_Position = Pos;
	}

	friend class GraphManager;
};

using PathCallback = std::function<std::vector<GraphNode*>(GraphNode*, GraphNode*)>;


class GraphManager
{
	uint NumTaken;
	std::vector<GraphNode*> m_GraphList;
public:
	std::vector<GraphNode*> FindPath(GraphNode* Start, GraphNode* End) const
	{
		const uint BIG_NUMBER = 0xfffffff; // Not the actual value, but who cares?
		std::map<GraphNode*, PathInfo> PathData;
		for (GraphNode* Node : m_GraphList)
		{
			PathInfo info;
			info.Cost = BIG_NUMBER;
			info.isKnown = false;
			info.PrevNode = nullptr;
			PathData[Node] = info;
		}
		std::vector<GraphNode*> UnvisitedNodes = m_GraphList;
		GraphNode* CurrentNode = Start;
		PathData[CurrentNode].Cost = 0;
		while (CurrentNode != End)
		{
			CurrentNode = [] (std::map<GraphNode*, PathInfo> Nodes, std::vector<GraphNode*> Unvisited)
			{
				GraphNode* Current = Unvisited[0];
				for (auto Node : Unvisited)
					if (Nodes[Node].Cost < Nodes[Current].Cost)
						Current = Node;
				return Current;
			}(PathData, UnvisitedNodes);
			PathData[CurrentNode].isKnown = true;
			for (auto Edge : CurrentNode->m_Neighbors)
			{
				GraphNode* Neighbor = Edge.Destination;
				if (!PathData[Neighbor].isKnown)
				{
					double dist = Edge.Cost;
					if (PathData[CurrentNode].Cost + dist < PathData[Neighbor].Cost)
					{
						PathData[Neighbor].Cost = PathData[CurrentNode].Cost + dist;
						PathData[Neighbor].PrevNode = CurrentNode;
					}
				}
			}
			UnvisitedNodes.erase(std::find(UnvisitedNodes.begin(), UnvisitedNodes.end(), CurrentNode));
		}
		std::function<std::vector<GraphNode*>(GraphNode*)> GetPath = [&](GraphNode* Current)
		{
			std::vector<GraphNode*> Result;
			if (PathData[Current].PrevNode != nullptr)
			{
				auto Other = GetPath(PathData[Current].PrevNode);
				Result.insert(Result.end(), Other.begin(), Other.end());
			}
			Result.push_back(Current);
			return Result;
		};
		return GetPath(End);
	}

	GraphManager& CreateGraph(const uint NumNodes, const Vector2u Field)
	{
		if (!m_GraphList.empty())
			m_GraphList.clear();
		m_GraphList.reserve(NumNodes);
		std::vector<Vector2u> PositionList;
		PositionList.reserve(NumNodes);
		while (PositionList.size() < NumNodes)
		{
			uint x = GetRandom(0, Field.x);
			uint y = GetRandom(0, Field.y);
			Vector2u Position = { x, y };
			if (std::find(PositionList.begin(), PositionList.end(), Position) == PositionList.end())
				PositionList.push_back(Position);
		}
		for (auto Position : PositionList)
		{
			GraphNode* Node = new GraphNode(Position);
			m_GraphList.push_back(Node);
		}
		return *this;
	}

	GraphManager& FormEdges()
	{
		using K = CGAL::Exact_predicates_inexact_constructions_kernel;
		using Delauney = CGAL::Delaunay_triangulation_2 <K>;
		using Circulator = Delauney::Vertex_circulator;
		using CGALPoint = Delauney::Point;

		std::vector<CGALPoint> points = [&] ()
		{
			std::vector<CGALPoint> result;
			for (auto Node : m_GraphList)
			{
				auto Loc = Node->GetPosition();
				CGALPoint point(Loc.x, Loc.y);
				result.push_back(point);
			}
			return result;
		}();

		Delauney dt;
		dt.insert(points.begin(), points.end());

		Circulator vc = dt.incident_vertices(dt.infinite_vertex()), done(vc);

		for (auto it = dt.finite_edges_begin(); it != dt.finite_edges_end(); ++it)
		{
			Delauney::Edge e = *it;
			auto CGALPointA = e.first->vertex((e.second + 1) % 3)->point();
			auto CGALPointB = e.first->vertex((e.second + 2) % 3)->point();

			// Now the chore is finding where in the world Point a and b are....
			auto FindNodeIndexFromCoords = [] (std::vector<GraphNode*> List, Vector2u Coord)
			{
				for (int i = 0; i < List.size(); ++i)
				{
					if (List[i]->m_Position == Coord)
						return i;
				}
				return -1;
			};

			Vector2u PointA;
			PointA.x = CGALPointA.x();
			PointA.y = CGALPointA.y();

			Vector2u PointB;
			PointB.x = CGALPointB.x();
			PointB.y = CGALPointB.y();

			int indexA = FindNodeIndexFromCoords(m_GraphList, PointA);
			int indexB = FindNodeIndexFromCoords(m_GraphList, PointB);

			if (indexA >= 0 && indexB >= 0)
			{
				m_GraphList[indexA]->AddNeighbor(m_GraphList[indexB]);
				m_GraphList[indexB]->AddNeighbor(m_GraphList[indexB]);
			}
		}
		return *this;
	}

	PathCallback GetPathCallback()
	{
		return [this] (GraphNode* Start, GraphNode* End)
		{
			return FindPath(Start, End);
		};
	}

	uint NumNodes()
	{
		return static_cast<uint>(m_GraphList.size());
	}

	uint NumNodesNotTaken()
	{
		return NumNodes() - NumTaken;
	}

	GraphNode* TakeNode()
	{
		if (NumTaken < m_GraphList.size())
			return m_GraphList[NumTaken++];
		else exit(3);
	}

	GraphNode* operator[](uint index) const
	{
		return m_GraphList[index];
	}

	GraphManager()
	{
		NumTaken = 0;
	}

	~GraphManager()
	{
	}
};

#endif

#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
// 
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//                               ...
//                  Copyright (C) 2024 Rohan Bharatia

#pragma endregion LICENSE

#pragma once

#ifndef _ALGORITHM_A_STAR_cpp_
    #define _ALGORITHM_A_STAR_cpp_

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <functional>

#include "prerequisites.c"
#include "control.c"
#include "maps.c"
#include "base.c"

struct Node
{
    PointD p;
    double gCost = INT_MAX;
    double hCost = 0.0;
    Node* parent = nullptr;

    double fCost(void) const
    {
        return gCost + hCost;
    }
};

struct NodeComparator
{
    double operator (void) (Node* a, Node* b)
    {
        return a->fCost(void) > b->fCost(void);
    }
};

struct NodeHasher
{
    uint8_t operator (void) (const PointD& p) const
    {
        uint8_t h1 = std::hash<double>{}(p.x);
        uint8_t h2 = std::hash<double>{}(p.y);
        uint8_t h3 = std::hash<double>{}(p.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class AStar
{
public:
    AStar(void) = default;
    AStar(std::vector<std::vector<PointD>> map = emptyMap(50)) : width(map.size(void)), height(map[0].size(void))
    {
        for (int i = 0; i < map.size(void); ++i)
        {
            for(int j = 0; j < map[i].size(void); ++j)
                blockedPoints.insert(map[i][j]);
        }
        return;
    }

    std::vector<Node*> findPath(Node* start, Node* goal)
    {
        if(start.p < PointD::ZERO)
            start.p = PointD::ZERO;
        if(start.p > PointD((double)width, (double)height))
            start.p = PointD((double)width, (double)height);

        if(goal.p < PointD::ZERO)
            goal.p = PointD::ZERO;
        if(goal.p > PointD((double)width, (double)height))
            goal.p = PointD((double)width, (double)height);
        
        std::priority_queue<Node*, std::vector<Node*>, NodeComparator> openSet;
        std::unordered_map<std::string, Node*> allNodes;

        start->gCost = 0.0;
        start->hCost = heuristic(start, goal);
        openSet.push(start);

        while(!openSet.empty(void))
        {
            Node* current = openSet.top(void);
            openSet.pop(void);

            if(current == goal)
            {
            #define DEBUG_A_STAR
                printTimestamp(void);
                std::cout << "Path between: " << start << " and: " << goal << " is " << reconstructPath(goal) << "\n";
            #endif // DEBUG_A_STAR
                return reconstructPath(goal);
            }

            for(auto& neighbor : getNeighbors(current))
            {
                double newGCost = current->gCost + 1;

                if(newGCost < neighbor->gCost)
                {
                    neighbor->parent = current;
                    neighbor->gCost  = newGCost;
                    neighbor->hCost  = heuristic(neighbor, goal);
                    openSet.push(neighbor);
                }
            }
        }
    #define DEBUG_A_STAR
        printTimestamp(void);
        std::cout << "No path found\n";
    #endif // DEBUG_A_STAR
        return { /* empty list */ };
    }

private:
    const uint8_t width;
    const uint8_t height;
    std::unordered_set<PointD, NodeHasher> blockedPoints;

    int isBlocked(const PointD& p)
    {
        return blockedPoints.find(p) != blockedPoints.end(void);
    }

    std::vector<Node*> getNeighbors(Node* current)
    {
        std::vector<Node*> neighbors;
        const std::vector<std::pair<int, int>> directions = {
                                                                 { -1, -1 }, // up & left
                                                                 { -1,  0 }, // up
                                                                 { -1,  1 }, // up & right
                                                                 {  0,  1 }, // right
                                                                 { -1,  1 }, // down & right
                                                                 { -1,  0 }, // down
                                                                 { -1, -1 }, // down & left
                                                                 {  0, -1 }  // left
                                                            };
        
        for (auto& dir : directions)
        {
            PointD point(current->x + dir.first, current->y + dir.second);
            
            if (point >= 0 && point < PointD((double)width, (double)height) && !isBlocked(point))
            {
                Node* neighbor = { p, current->gCost, current->hCost, current->parent };
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }

    double heuristic(Node* a, Node* b)
    {
        return abs(a->p.x - b->p.x) + abs(a->p.y - b->p.y);
    }

    std::vector<Node*> reconstructPath(Node* goal)
    {
        std::vector<Node*> path;
        Node* current = goal;
        while (current)
        {
            path.push_back(current);
            current = current->parent;
        }
        std::reverse(path.begin(void), path.end(void));
        return path;
    }
};

#endif // _ALGORITHM_A_STAR_cpp_
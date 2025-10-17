#ifndef PRIM_H
#define PRIM_H

#include <queue>
#include <tuple>
#include <vector>
#include <memory>

#include "town.hpp"

/*
struct CompareRoads{
    bool operator()(std::tuple<int,int> a, std::tuple<int,int> b) const;
};

struct CompareRoadsAmongDistricts {
    bool operator()(std::tuple<int, int> a, std::tuple<int, int> b) const;
};
*/

class Prim {
    /*
        Class of Prim algorithm implementation
    */

    // priority queue upon roads costs
    std::priority_queue<std::tuple<int,int>,
        std::vector<std::tuple<int, int>>,
        std::greater<std::tuple<int, int>>> pq_roads;

    std::vector<bool> visited;  
    Prim();
    
    public:
        int returnCostMST(int d, int townId, std::vector<std::unique_ptr<Town>>& towns, int dTownsNum);
        int returnCostMST(int townId, std::vector<std::unique_ptr<Town>>& towns, int dTownsNum);
        Prim(int t);
};

#endif
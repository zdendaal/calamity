#include "prim.hpp"
#include <iostream>

/*
bool CompareRoads::operator()(std::tuple<int,int> a, std::tuple<int,int> b) const {
        return std::get<1>(a) > std::get<1>(b);
}

bool CompareRoadsAmongDistricts::operator()(std::tuple<int, int> a, std::tuple<int, int> b) const {
    if (std::get<1>(a) > std::get<1>(b))
        return true;
    else if ()
}
*/

Prim::Prim() {
}

Prim::Prim(int t) {
    visited.resize(t);
    std::fill(visited.begin(), visited.end(), false);  // set visited to number of all towns
}

int Prim::returnCostMST(int d, int townId, std::vector<std::unique_ptr<Town>>& towns, int dTownsNum){ // returns MST cost of district d
    int cost = 0;
    using PQ = std::priority_queue<std::tuple<int,int>, 
        std::vector<std::tuple<int,int>>, 
        std::greater<std::tuple<int, int>>>;

    std::tuple<int,int> cheapest;

    pq_roads.push(std::make_tuple(0, townId));

    while (!pq_roads.empty()) {
        cheapest = pq_roads.top();
        pq_roads.pop();

        if (visited[std::get<1>(cheapest)]) 
            continue;

        cost += std::get<0>(cheapest);
        townId = std::get<1>(cheapest);

        visited[townId] = true;

        for (std::pair<Town*, int>& r : towns[townId]->roads)
        {
            if (!visited[r.first->id])
                pq_roads.push(std::make_tuple(r.second, r.first->id));
        }
    }

    // smazani prioritni fronty daneho distriktu
    PQ().swap(pq_roads);

    return cost;
}

int Prim::returnCostMST(int townId, std::vector<std::unique_ptr<Town>>& towns, int dTownsNum){ // returns MST cost of all nodes in graph
    int cost = 0;
    using PQ = std::priority_queue<std::tuple<int, int>,    // priority queue for swap delete
        std::vector<std::tuple<int, int>>,
        std::greater<std::tuple<int, int>>>;

    std::tuple<int, int> cheapest;

    // Prim algorithm
    pq_roads.push(std::make_tuple(0, townId));

    while (!pq_roads.empty()) {
        cheapest = pq_roads.top();
        pq_roads.pop();

        if (visited[std::get<1>(cheapest)]) 
            continue;

        cost += std::get<0>(cheapest);
        townId = std::get<1>(cheapest);

        visited[townId] = true;

        for (std::pair<Town*, int>& r : towns[townId]->roads)
        {
            if (!visited[r.first->id])
                pq_roads.push(std::make_tuple(r.second, r.first->id));
        }
    }

    // smazani prioritni fronty daneho distriktu
    PQ().swap(pq_roads);

    return cost;
}

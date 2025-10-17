#ifndef BFS_H
#define BFS_H

#include <vector>
#include <memory>

#include "town.hpp"


class BFS{
    public:
        bool coverNextDistrictLayer(std::vector<std::unique_ptr<Town>>& towns);    // searches through new level, return cost of spanning tree of part of that depth
        int district;

        std::vector<std::pair<int, int>> intersect_roads;   // (target town, road cost)
        std::vector<int> districtTowns; // indexes of towns

        BFS(int startTown);

    private:
        int layerOffset = 0;
};

#endif
#include <vector>
#include <memory>

#include "bfs.hpp"
#include "town.hpp"


BFS::BFS(int startTown){
    districtTowns.push_back(startTown);
    district = startTown;
}

bool BFS::coverNextDistrictLayer(std::vector<std::unique_ptr<Town>>& towns){ // přiřadí městům distrikty
    int size = districtTowns.size();
    int id;
    for(int i = layerOffset; i < size; i++){
        id = districtTowns[i];
        for(int j = 0; j < towns[id]->roads.size(); j++){

            if(towns[id]->roads[j].first->district == Town::NODISTRICT){
                districtTowns.push_back(towns[id]->roads[j].first->id);
                towns[id]->roads[j].first->district = district;
            }
            else if(district < towns[id]->roads[j].first->district)
                intersect_roads.push_back(std::make_pair(towns[id]->roads[j].first->district, towns[id]->roads[j].second));    // push road connecting two different districts
        }
    }
    if(layerOffset == size)
        return true;     // if district has reached all its towns

    layerOffset = size;
    return false;   // district hasnt reached all its towns
}
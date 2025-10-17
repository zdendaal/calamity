#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <functional>
#include <list>

#include "town.hpp"
#include "prim.hpp"
#include "bfs.hpp"


int search(std::vector<std::unique_ptr<BFS>>& ls_bfs, std::list<int> bfsLinkedList);


int t, d, r;    // towns, disctricts, roads
std::vector<std::unique_ptr<Town>> towns;

// Loads data from stdin
int main(int argc, char **argv){
    scanf("%d %d %d\n", &t, &d, &r);    // loads first row

    towns.resize(t);     // prepare size

    std::vector<std::unique_ptr<BFS>> ls_bfs;
    std::list<int> bfsLinkedList;

    for(int i = 0; i < d; i++){    // district towns
        towns[i] = std::make_unique<Town>(i, i);
        ls_bfs.push_back(std::make_unique<BFS>(i));
        bfsLinkedList.push_back(i);
    }

    for(int i = d; i < t; i++){  // casual towns
        towns[i] = std::make_unique<Town>(i, Town::NODISTRICT);
    }

    int t1;
    int t2;
    int c;
    for(int i = 0; i < r; i++){     // loads roads
        scanf("%d %d %d", &t1, &t2, &c);
        towns[t1-1]->roads.push_back(std::make_pair(towns[t2-1].get(), c));
        towns[t2-1]->roads.push_back(std::make_pair(towns[t1-1].get(), c));
    }
    
    int cost = search(ls_bfs, bfsLinkedList);
    printf("%d\n", cost);
}

int search(std::vector<std::unique_ptr<BFS>>& ls_bfs, std::list<int> bfsLinkedList){    // Calculates cost of all roads
    auto bfsIt = bfsLinkedList.begin();
    int counter = 0;

    while(counter != ls_bfs.size()) {
        if (ls_bfs[*bfsIt]->coverNextDistrictLayer(towns)) {
            bfsIt = bfsLinkedList.erase(bfsIt);
            counter++;
        }
        else if (bfsIt != bfsLinkedList.end())
            bfsIt++;

        if(bfsIt == bfsLinkedList.end())
            bfsIt = bfsLinkedList.begin();
    }

    // caluclating MST for each district
    int cost = 0;
    Prim prim = Prim(t);
    for(int i = 0; i < d; i++){
        cost += prim.returnCostMST(i, i, towns, ls_bfs[i]->districtTowns.size());
    }

    // collapsing towns in each district into one town
    std::vector<std::unique_ptr<Town>> collapsed;
    for (int i = 0; i < d; i++) {
        collapsed.push_back(std::make_unique<Town>(i, i));
    }

    int targetTown;
    for(int i = 0; i < d; i++){
        towns[i] = std::make_unique<Town>(i, i);
        for(int r = 0; r < ls_bfs[i]->intersect_roads.size(); r++){
            targetTown = ls_bfs[i]->intersect_roads[r].first;

            collapsed[i]->roads.emplace_back(
                collapsed[targetTown].get(),     // index of town
                ls_bfs[i]->intersect_roads[r].second    // road cost
            );

            collapsed[targetTown]->roads.emplace_back(
                collapsed[i].get(),     // index of town
                ls_bfs[i]->intersect_roads[r].second    // road cost
            );
        }
    }

    // calculating inter district part of MST
    Prim primCollapsed = Prim(d);
    cost += primCollapsed.returnCostMST(0, collapsed, d);

    return cost;
}
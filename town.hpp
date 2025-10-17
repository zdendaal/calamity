#ifndef TOWN_H
#define TOWN_H

#include <vector>


// node
class Town {
    public:
        int id;
        int district;
        std::vector<std::pair<Town*, int>> roads; // roads connecting town
        static const int NODISTRICT;

        Town(int id, int district);
};

#endif
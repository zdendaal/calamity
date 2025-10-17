#include "town.hpp"


const int Town::NODISTRICT = -1;

Town::Town(int id, int district){
            this->id = id;
            this->district = district;
}
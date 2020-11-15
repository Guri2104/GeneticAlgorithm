//
// Created by Gurden Angi on 2020-11-15.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#include <string>

using namespace std;

class City {
    string name;
    int x_coord;
    int y_coord;

public:
    City(string name, int x, int y) : name(name), x_coord(x), y_coord(y){}

    string getName(){return name;}
    int getX(){return x_coord;}
    int getY(){return y_coord;}

};


#endif //GENETICALGORITHM_CITY_HPP

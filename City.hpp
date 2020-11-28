//
// Created by Gurden Angi on 2020-11-15.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#include <string>
#include <cmath>

using namespace std;

/** Class representing a City in a tour */
class City {
    /** name of the city */
    string name;
    /** x coordinate of the city */
    int x_coord;
    /** y coordinate of the city */
    int y_coord;

public:
    /** 3-parameter constructor with name, and coordinates of the city */
    City(string name, int x, int y) : name(name), x_coord(x), y_coord(y){}
    /** method to retrieve name of the city */
    string getName(){return name;}
    /** method to retrieve x coordinate of the city */
    int getX(){return x_coord;}
    /** method to retrieve y coordinate of the city */
    int getY(){return y_coord;}
    /** method to calculate distance between two cities */
    double getDistance(City* city) const{
        return sqrt(pow(city->x_coord - x_coord, 2) + pow(city->y_coord - y_coord, 2));
    }

};


#endif //GENETICALGORITHM_CITY_HPP

//
// Created by Gurden Angi on 2020-11-15.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include <vector>
#include <algorithm>
#include "City.hpp"

using namespace std;
/** Class to manage tours to visit the cities in a certain order. */
class Tour {
private:
    /** list of pointers to cities in a certain order */
    vector<City*> tour_list;
    /** total distance to be travelled to complete tour */
    double distance;
    /** fitness of tour */
    double fitness;
    /** method to calculate tour distance */
    void calc_distance();
    /** method to calculate tour fitness */
    void calc_fitness();

public:
    /** default constructor */
    Tour() : distance(0), fitness(1000){}
    /** single parameter constructor with city pointer */
    Tour(City* city);
    /** single parameter constructor with city list vector */
    Tour(vector<City*> city_list);
    /** method to add city to tour */
    void addCity(City* city);
    /** check if tour contains the city */
    bool contains_city(City* city);
    /** shuffle cities order in the tour list */
    void shuffle_cities();
    /** retrieve total distance of tour */
    double get_tour_distance() const {return distance;}
    /** retrieve tour fitness */
    double get_fitness() const {return fitness;}
    /** retrieve list and order of cities in tour list. */
    vector<City*> getList() const {return tour_list;}
    /** set the tour list */
    void setList(vector<City*> list) {tour_list = list;}
    /** overloaded comparison operator */
    bool operator<(const Tour &a) const {return distance <  a.distance;}
};


#endif //GENETICALGORITHM_TOUR_HPP

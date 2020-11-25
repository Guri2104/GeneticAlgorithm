//
// Created by Gurden Angi on 2020-11-15.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include <vector>
#include <algorithm>
#include "City.hpp"

using namespace std;

class Tour {
private:
    vector<City*> tour_list;
    double distance;
    double fitness;
    void calc_distance();
    void calc_fitness();

public:
    Tour() : distance(0), fitness(1000){}
    Tour(City* city);
    Tour(vector<City*> city_list);

    void addCity(City* city);
    bool contains_city(City* city);
    void shuffle_cities();
    double get_tour_distance() const {return distance;}
    double get_fitness() const {return fitness;}
    vector<City*> getList() const {return tour_list;}
    void setList(vector<City*> list) {tour_list = list;}
    bool operator<(const Tour &a) const {return distance <  a.distance;}
};


#endif //GENETICALGORITHM_TOUR_HPP

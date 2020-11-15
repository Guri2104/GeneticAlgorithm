//
// Created by Gurden Angi on 2020-11-15.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include <vector>
#include "City.hpp"
using namespace std;
class Tour {
private:
    vector<City*> tour_list;
    double fitness;
    void calc_fitness();

public:
    Tour() : fitness(0){}
    Tour(City* city);
    Tour(vector<City*> city_list);

    double get_fitness(){return fitness;}
    vector<City*> getList(){return tour_list;}
    bool operator<(const Tour &a) const {return fitness <  a.fitness;}
    void addCity(City* city);
};


#endif //GENETICALGORITHM_TOUR_HPP

//
// Created by Gurden Angi on 2020-11-15.
//

#include "Tour.hpp"

Tour::Tour(City *city)  {
    tour_list.push_back(city);
    calc_fitness();
}

Tour::Tour(vector<City *> city_list) {
    for (int i=0; i < city_list.size(); i++)
        tour_list.push_back(city_list[i]);

    calc_fitness();
}

void Tour::calc_fitness() {
    fitness = 0;
    vector<City*>::iterator it1 = tour_list.begin();
    vector<City*>::iterator it2 = tour_list.end();
    vector<City*>::iterator it3;
    for (it3 = it1; it3 != it2; ++it3){
        fitness += (*it3)->getDistance(*(it3+1));
    }
    it3 = it1;
    it3 += tour_list.size()-1;
    fitness += (*it3)->getDistance(*it1);
}

void Tour::addCity(City* city){
    tour_list.push_back(city);
    calc_fitness();
}

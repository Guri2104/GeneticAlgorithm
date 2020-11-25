//
// Created by Gurden Angi on 2020-11-15.
//

#include "Tour.hpp"
#include <iostream>

Tour::Tour(City *city)  {
    addCity(city);
}

Tour::Tour(vector<City *> city_list) {
    for (int i=0; i < city_list.size(); i++)
        tour_list.push_back(city_list[i]);

    calc_distance();
}

void Tour::calc_distance() {
    distance = 0;
    vector<City*>::iterator it1 = tour_list.begin();
    vector<City*>::iterator it2 = tour_list.end();
    vector<City*>::iterator it3;
    for (it3 = it1; it3 != it2-1; ++it3){
        distance += (*it3)->getDistance(*(it3+1));
    }
    it3 = it1;
    it3 += tour_list.size()-1;
    distance += (*it3)->getDistance(*it1);
    calc_fitness();
}

void Tour::calc_fitness() {
    if (distance == 0)
        fitness = 1000;
    else fitness = (1/distance) * 1000;
}

void Tour::addCity(City* city){
    tour_list.push_back(city);
    calc_distance();
}

bool Tour::contains_city(City *city)  {
    vector<City*>::iterator it1 = tour_list.begin();
    vector<City*>::iterator it2 = tour_list.end();
    vector<City*>::iterator it3;
    for (it3 = it1; it3 != it2; ++it3){
        if (*it3 == city)
            return true;
    }
    return false;
}

void Tour::shuffle_cities() {
    random_shuffle(tour_list.begin(), tour_list.end());
    calc_distance();
}


#include <iostream>
#include <algorithm>
#include <set>
#include <random>
#include "City.hpp"
#include "Tour.hpp"

multiset<Tour> getCross(multiset<Tour> &population);

multiset<Tour> getCross(multiset<Tour> &population, vector<int> &used);

multiset<Tour> non_elite(multiset<Tour> population);

Tour crossover(multiset<Tour> cross1, multiset <Tour> cross2);

Tour crossover(multiset<Tour> &population);

int random_num_generator(int upperbound);

multiset<Tour> mutate(multiset<Tour> &population);

struct RNG {
    int operator() (int n) {
        return rand() / (1.0 + RAND_MAX) * n;
    }
};

using namespace std;
int main() {
    srand(unsigned(time(0)));

    vector<City*> city_list;
    multiset<Tour> population1;
    for (int i = 0; i < 20; ++i) {
        string name = "a" + to_string(i);
        City* a = new City(name, random_num_generator(999), random_num_generator(999));
        city_list.push_back(a);
    }

    for (int i = 0; i < 30; ++i) {
        random_shuffle(city_list.begin(), city_list.end(), RNG());
        Tour t1{city_list};
        population1.insert(t1);
    }

    multiset<Tour>::iterator it1 = population1.begin();
    multiset<Tour>::iterator it2 = population1.end();
    multiset<Tour>::iterator it3;

    for (it3 = it1; it3 != it2 ; ++it3) {
        cout << endl << (*it3).get_tour_distance();
//        cout << endl << (*it3).get_fitness();
    }
        cout << endl;
    double base_distance = (*it1).get_tour_distance();
    double best_distance = base_distance;
    double improvement_factor = 0.66;
    int num_iter = 0;

    while (best_distance/base_distance > improvement_factor && num_iter < 2000){
        Tour elite = *(population1.begin());
        multiset<Tour>new_population;
        new_population.insert(elite);

        multiset<Tour> population2 = non_elite(population1);

        for (int i = 0; i < population2.size(); ++i) {
            multiset<Tour> cross1 = getCross(population2);

            multiset<Tour> cross2 = getCross(population2);

            Tour child = crossover(cross1, cross2);
//            Tour child = crossover(population2);
            new_population.insert(child);
        }

        new_population = mutate(new_population);

//        multiset<Tour>::iterator it = new_population.begin();
//        for (int k = 0; k < new_population.size(); ++k) {
//            vector<City*> list = it->getList();
//            for (int l = 0; l < list.size(); ++l) {
//                cout << list[l]->getName() << " ";
//            }
//            cout << it->get_tour_distance();
//            cout << endl;
//            it++;
//        }
        cout << endl;

        best_distance = (new_population.begin())->get_tour_distance();
        population1 = new_population;
        num_iter++;

        cout << best_distance << endl;
        cout << base_distance <<endl;
        cout << best_distance/base_distance <<endl;
        cout << num_iter <<endl;
    }



    for (City* city : city_list) {
        delete city;
    }

    return 0;
}

multiset<Tour> mutate(multiset<Tour> &population) {
    Tour elite = *(population.begin());
    multiset<Tour> pop = non_elite(population);
    int size = pop.size();
    int num_mutated = 0.33 * size;
    for (int i = 0; i < num_mutated; ++i) {
        int tour_no = random_num_generator(size - 1);
        multiset<Tour>::iterator it = pop.begin();
        for (int j = 0; j < tour_no; ++j) {
            it++;
        }

        vector<City*>cities = it->getList();

        vector<City*>::iterator it1 = cities.begin();
        vector<City*>::iterator it2 = cities.end();
        vector<City*>::iterator it3;
        City* tmp;
        for (it3 = it1; it3 != it2-1; ++it3) {
            int mutate_risk = random_num_generator(100);
            if (mutate_risk < 25){
                tmp = *it3;
                *it3 = *(it3+1);
                *(it3+1) = tmp;
            }
        }
        it1 = cities.begin();
        it3 = it2-1;
        int mutate_risk = random_num_generator(100);
        if (mutate_risk < 25){
            tmp = *it3;
            *it3 = *it1;
            *it1 = tmp;
        }
        Tour t{cities};
        pop.erase(it);
        pop.insert(t);

    }
    pop.insert(elite);
    return pop;
}

Tour crossover(multiset<Tour> cross1, multiset <Tour> cross2) {
    Tour parent1 = *(cross1.begin());
    Tour parent2 = *(cross2.begin());
    Tour child;
    int upperbound= 20;
    int my_int= random_num_generator(upperbound - 1);
    vector<City*>list1 = parent1.getList();
    vector<City*>list2 = parent2.getList();

    for (int i = 0; i <= my_int; i++){
        child.addCity(list1[i]);
    }

    for (int j = 0; j < list2.size(); ++j) {

        if (!child.contains_city(list2[j])) {
            child.addCity(list2[j]);
        }
    }
    return child;
}

multiset<Tour> non_elite(multiset<Tour> population) {
    multiset<Tour> others = population;
    others.erase(others.begin());
    return others;
}

multiset<Tour> getCross(multiset<Tour> &population) {
    multiset<Tour> cross;
    int upperbound= population.size() - 1;
    for(int i = 0; i < 5; i++){
        int my_int= random_num_generator(upperbound);
        multiset<Tour>::iterator it = population.begin();
        for (int j = 0; j < my_int; ++j) {
            it++;
        }
        cross.insert(*it);
    }

    return cross;
}

int random_num_generator(int upperbound){
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<>distribution(0, upperbound);
    int my_int = distribution(generator);
    for (int i = 0; i < 63; ++i) {
        my_int = distribution(generator);
    }
    return my_int;
}

Tour crossover(multiset<Tour> &population) {
    vector<int> used_tours;
    multiset<Tour> cross1 = getCross(population, used_tours);
//    cout << "cross1" << endl;
//    multiset<Tour>::iterator it = cross1.begin();
//    for (int k = 0; k < cross1.size(); ++k) {
//        vector<City*> list = it->getList();
//        for (int l = 0; l < list.size(); ++l) {
//            cout << list[l]->getName() << " ";
//        }
//        cout << it->get_tour_distance();
//        cout << endl;
//        it++;
//    }
//    cout << endl;
    multiset<Tour> cross2 = getCross(population, used_tours);
//    cout << "cross2" << endl;
//    it = cross2.begin();
//    for (int k = 0; k < cross2.size(); ++k) {
//        vector<City*> list = it->getList();
//        for (int l = 0; l < list.size(); ++l) {
//            cout << list[l]->getName() << " ";
//        }
//        cout << it->get_tour_distance();
//        cout << endl;
//        it++;
//    }
//    cout << endl;
    Tour parent1 = *(cross1.begin());
    Tour parent2 = *(cross2.begin());
    Tour child;
    int upperbound= 20;
    int my_int= random_num_generator(upperbound - 1);
    vector<City*>list1 = parent1.getList();
    vector<City*>list2 = parent2.getList();

    for (int i = 0; i <= my_int; i++){
        child.addCity(list1[i]);
    }

    for (int j = 0; j < list2.size(); ++j) {

        if (!child.contains_city(list2[j])) {
            child.addCity(list2[j]);
        }
    }
    return child;
}

multiset<Tour> getCross(multiset<Tour> &population, vector<int> &used) {
    multiset<Tour> cross;
    int upperbound= population.size() - 1;
    for(int i = 0; i < 5; i++){
        int my_int = random_num_generator(upperbound);;
        while (find(used.begin(), used.end(), my_int) != used.end()){
            my_int = random_num_generator(upperbound);
        }
        used.push_back(my_int);
        multiset<Tour>::iterator it = population.begin();
        for (int j = 0; j < my_int; ++j) {
            it++;
        }
        cross.insert(*it);
    }

    return cross;
}




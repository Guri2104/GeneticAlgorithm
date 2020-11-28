#include <iostream>
#include <algorithm>
#include <set>
#include <random>
#include "City.hpp"
#include "Tour.hpp"

#define CITIES_IN_TOUR 32
#define POPULATION_SIZE 32
#define MIN_ITERATIONS 1000
#define MAP_BOUNDARY 1000
#define PARENT_POOL_SIZE 5
#define MUTATION_RATE 0.33
#define MUTATION_RISK 25
#define IMPROVEMENT_FACTOR 0.8
#define HUNDRED 100

/** method to get a cross of 5 tours from the population */
multiset<Tour> getCross(multiset<Tour> &population);
/** method to get all the non-elite tours in a population */
multiset<Tour> non_elite(multiset<Tour> population);
/** method to crossover two crosses to get a child tour */
Tour crossover(multiset<Tour> cross1, multiset <Tour> cross2);
/** method to get a random number within the given upperbound */
int random_num_generator(int upperbound);
/** method to mutate tours within a given population */
multiset<Tour> mutate(multiset<Tour> &population);
/** RNG functor for random_shuffle algorithm  */
struct RNG {
    int operator() (int n) {
        return rand() / (1.0 + RAND_MAX) * n;
    }
};


using namespace std;
/** main driver function */
int main() {
    // seed for random number generators
    srand(unsigned(time(0)));

    // list of all the cities
    vector<City*> city_list;
    // base population
    multiset<Tour> population1;

    // create Cities with random coordinates within bounds
    // and add cities to the city_list
    for (int i = 0; i < CITIES_IN_TOUR; ++i) {
        string name = "c" + to_string(i);
        City* a = new City(name, random_num_generator(MAP_BOUNDARY), random_num_generator(MAP_BOUNDARY));
        city_list.push_back(a);
    }

    // random_shuffle city_list and create tours with each random ordered list
    // insert tours to base population
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        random_shuffle(city_list.begin(), city_list.end(), RNG());
        Tour t1{city_list};
        population1.insert(t1);
    }

    // base distance
    double base_distance = (*population1.begin()).get_tour_distance();
    // best distance
    double best_distance = base_distance;
    // improvement factor for the genetic algorithm
    double improvement_factor = IMPROVEMENT_FACTOR;
    // number of iterations done
    int num_iter = 0;
    double base_improvement = 0;
    // base tour
    Tour base_tour = *(population1.begin());
    // best tour
    Tour best_tour;

    // keep improving the tour fitness until we reach the required improvement factor or max iterations
    while (best_distance/base_distance > improvement_factor || num_iter < MIN_ITERATIONS){
        // get elite tour
        Tour elite = *(population1.begin());
        // declare new population of tours to be achieved
        multiset<Tour>new_population;
        // initialize new population with current elite tour
        new_population.insert(elite);
        // get all non elite population to be crossover and mutated
        multiset<Tour> population2 = non_elite(population1);

        // crossover non-elite tours to get new child tours
        // add child tours to new_population
        for (int i = 0; i < population2.size(); ++i) {
            // get cross 1
            multiset<Tour> cross1 = getCross(population2);
            // get cross 2
            multiset<Tour> cross2 = getCross(population2);
            // crossover
            Tour child = crossover(cross1, cross2);
            // insert
            new_population.insert(child);
        }

        // mutate new population
        new_population = mutate(new_population);


        // get the best distance in new population
        best_distance = (new_population.begin())->get_tour_distance();
        // set the base population to new population for next iteration
        population1 = new_population;
        // increment iteration
        num_iter++;
        // improvement in this iteration
        int new_improvement = elite.get_tour_distance() - best_distance;
        best_tour = *(new_population.begin());

        // generate report
        cout << "Iteration#: " << num_iter <<endl;
        cout << "Best Distance: " <<  best_distance << endl;
        cout << "Improvement in this iteration: " << new_improvement << endl;
        cout << "Improvement percent so far: " << (base_distance-best_distance)/base_distance << endl;
        cout << endl;
    }

    cout << "-----------------------------------------------------------------------" << endl;
    cout << " ---------------------------- Final Report ----------------------------" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Total Iterations: " << num_iter << endl;
    cout << "Base Distance: " <<  base_distance << endl;
    cout << "Best Distance: " <<  best_distance << endl;
    cout << "Improvement Factor achieved: " << boolalpha << (best_distance/base_distance <= improvement_factor) << endl;
    cout << "Improvement percent: " << (base_distance-best_distance)/base_distance << endl;
    cout << "Base Route: ";
    vector<City*> list = base_tour.getList();
    for (int l = 0; l < list.size(); ++l) {
        cout << list[l]->getName() << " ";
    }
    cout << endl << "Best Route: ";
    vector<City*> list2 = best_tour.getList();
    for (int l = 0; l < list2.size(); ++l) {
        cout << list2[l]->getName() << " ";
    }

    // free dynamic memory
    for (City* city : city_list) {
        delete city;
    }

    return 0;
}


// -----------------------------------------------------------------------
// ------------------- Definitions of helper functions -------------------
// -----------------------------------------------------------------------


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


multiset<Tour> non_elite(multiset<Tour> population) {
    multiset<Tour> others = population;
    others.erase(others.begin());
    return others;
}


multiset<Tour> getCross(multiset<Tour> &population) {
    multiset<Tour> cross;
    int upperbound= population.size() - 1;
    for(int i = 0; i < PARENT_POOL_SIZE; i++){
        int my_int= random_num_generator(upperbound);
        multiset<Tour>::iterator it = population.begin();
        for (int j = 0; j < my_int; ++j) {
            it++;
        }
        cross.insert(*it);
    }

    return cross;
}


Tour crossover(multiset<Tour> cross1, multiset <Tour> cross2) {
    Tour parent1 = *(cross1.begin());
    Tour parent2 = *(cross2.begin());
    Tour child;
    int upperbound= CITIES_IN_TOUR - 1;
    int my_int = random_num_generator(upperbound);

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


multiset<Tour> mutate(multiset<Tour> &population) {
    Tour elite = *(population.begin());
    // get all non elite tours
    multiset<Tour> pop = non_elite(population);
    int size = pop.size();
    int num_mutated = (size * MUTATION_RATE);
    for (int i = 0; i < num_mutated; ++i) {
        // generate random tour number to mutate
        int tour_no = random_num_generator(size - 1);

        // traverse to the tour
        multiset<Tour>::iterator it = pop.begin();
        for (int j = 0; j < tour_no; ++j) {
            it++;
        }

        // get tour list
        vector<City*>cities = it->getList();

        vector<City*>::iterator it1 = cities.begin();
        int size = cities.size();
        vector<City*>::iterator it2 = cities.end();
        vector<City*>::iterator it3;
        City* tmp;
        for (it3 = it1; it3 != it2-1; ++it3) {
            // generate random number to check if to mutate or not
            int mutate_risk = random_num_generator(HUNDRED);
            if (mutate_risk < MUTATION_RISK){
                tmp = *it3;
                *it3 = *(it3+1);
                *(it3+1) = tmp;
            }
        }
        // handle case for last city
        it1 = cities.begin();
        it3 = it2-1;
        int mutate_risk = random_num_generator(HUNDRED);
        if (mutate_risk < MUTATION_RISK){
            tmp = *it3;
            *it3 = *it1;
            *it1 = tmp;
        }
        //create mutated tour
        Tour t{cities};
        // remove previous tour
        pop.erase(it);
        // insert mutated tour
        pop.insert(t);

    }
    // insert non-mutated elite tour from original population
    pop.insert(elite);
    return pop;
}

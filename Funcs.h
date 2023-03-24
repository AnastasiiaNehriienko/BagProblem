#pragma once
#include "MyClasses.h"
#include <fstream>

int find_max_person(Person** pop);
int find_min_person(Person** pop);
void mix_parents(Person* parent_1, Person* parent_2, bool* child_things);
void write_things_to_file(std::ofstream& things_file);
void write_first_population(std::ofstream& pop1_file, Person** population);
void write_last_population(std::ofstream& pop1_file, Person** population);
void genetic_algorithm(std::ofstream& max_file, Person** population);
void find_local_improve();

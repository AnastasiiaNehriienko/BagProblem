#include <iostream>
#include "MyClasses.h"
#include "externs.h"
#include "Funcs.h"
#include <fstream>
Thing* things[100];
int P = 250;
int min_from_max, max_from_min;

int main() {
	srand(time(NULL));
	for (int i = 0; i < 100; ++i) {
		Thing* n = new Thing();
		things[i] = n;
	}
	find_local_improve();
	//std::cout << min_from_max << " " << max_from_min<<std::endl;
	std::ofstream things_file("Things.txt");
	write_things_to_file(things_file);
	Person* population[100];
	for (int i = 0; i < 100; ++i) {
		Person* p = new Person();
		population[i] = p;
	}
	things_file.close();
	std::ofstream pop1_file("Population1.txt");
	std::ofstream pop2_file("Population2.txt");
	std::ofstream max_file("Max_through_iterations.txt");
	write_first_population(pop1_file, population);
	genetic_algorithm(max_file, population);
	write_last_population(pop2_file, population);
	pop1_file.close();
	pop2_file.close();
	max_file.close();

	for (int i = 0; i < 100; ++i) {
		delete population[i];
	}
	for (int i = 0; i < 100; ++i) {
		delete things[i];
	}
	return 0;
}
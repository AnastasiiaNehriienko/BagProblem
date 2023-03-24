#include "MyClasses.h"
#include "Funcs.h"
#include <iostream>
#include <fstream>
#include "externs.h"
int find_max_person(Person** pop) {
	int max = 0;
	for (int i = 1; i < 100; ++i) {
		if (pop[i]->get_total_price() > pop[max]->get_total_price()) {
			max = i;
		}
	}
	return max;
}
int find_min_person(Person** pop) {
	int min = 0;
	for (int i = 1; i < 100; ++i) {
		if (pop[i]->get_total_price() < pop[min]->get_total_price()) {
			min = i;
		}
	}
	return min;
}
void mix_parents(Person* parent_1, Person* parent_2, bool* child_things) {
	bool* p1 = parent_1->get_person_things();
	bool* p2 = parent_2->get_person_things();
	for (int j = 0; j < 25; ++j) {
		child_things[j] = p1[j];
	}
	for (int j = 25; j < 50; ++j) {
		child_things[j] = p2[j];
	}
	for (int j = 50; j < 75; ++j) {
		child_things[j] = p1[j];
	}
	for (int j = 75; j < 100; ++j) {
		child_things[j] = p2[j];
	}
}
void write_things_to_file(std::ofstream& things_file) {
	things_file << "___Things___\n";
	//std::cout << "___Things___\n";
	for (int i = 0; i < 100; ++i) {
		//printf("%d: weight %d, price %d\n", i+1, things[i]->get_weight(), things[i]->get_price());
		things_file << i + 1 << ": weight " << things[i]->get_weight() << ", price " << things[i]->get_price() << "\n";
	}
}
void write_first_population(std::ofstream& pop1_file, Person** population) {
	//std::cout << "___First Population___\n";
	pop1_file << "___First Population___\n";
	for (int i = 0; i < 100; ++i) {
		//printf("%d: weight %d, price %d\n", i+1, population[i]->get_total_weight(), population[i]->get_total_price());
		pop1_file << i + 1 << ": total_weight " << population[i]->get_total_weight() << ", total_price " << population[i]->get_total_price() << "\n";
	}
}
void write_last_population(std::ofstream& pop2_file, Person** population) {
	//std::cout << "___Last Population___\n";
	pop2_file << "___Last Population___\n";
	for (int i = 0; i < 100; ++i) {
		//printf("%d: weight %d, price %d\n", i+1, population[i]->get_total_weight(), population[i]->get_total_price());
		pop2_file << i + 1 << ": total_weight " << population[i]->get_total_weight() << ", total_price " << population[i]->get_total_price() << "\n";
	}
}
void genetic_algorithm(std::ofstream& max_file, Person** population) {
	int max_person_num;
	int min_person_num;
	bool* max_now;
	std::ofstream diagram_data("Diagram_data.csv");
	for (int j = 0; j < 50; ++j) {
		for (int i = 0; i < 20; ++i) {
			max_person_num = find_max_person(population);
			min_person_num = find_min_person(population);
			if (j == 0 && i == 0) {
				max_now = population[max_person_num]->get_person_things();
				//std::cout << "Beginning. Max: "<< max_person_num+1;
				max_file << "Beginning. Max: " << max_person_num + 1;
				//std::cout <<" weight: "<< population[max_person_num]->get_total_weight() << " price: " << population[max_person_num]->get_total_price() << std::endl;
				max_file << " weight: " << population[max_person_num]->get_total_weight() << " price: " << population[max_person_num]->get_total_price() << std::endl;
			}
			int rand_int = rand() % 100;
			while (rand_int == max_person_num)
				rand_int = rand() % 100;
			Person* parent_1 = population[max_person_num];
			Person* parent_2 = population[rand_int];
			bool child_things[100] = { 0 };
			mix_parents(parent_1, parent_2, child_things);
			int total_w = 0;
			for (int i = 0; i < 100; ++i) {
				if (child_things[i])
					total_w += things[i]->get_weight();
			}
			if (total_w <= P) {
				total_w = 0;
				int is_mutation = rand() % 20;
				if (is_mutation == 0) {
					int gen = rand() % 100;
					if (child_things[gen])
						child_things[gen] = 0;
					else child_things[gen] = 1;
				}
				for (int i = 0; i < 100; ++i) {
					if (child_things[i])
						total_w += things[i]->get_weight();
				}
				if (total_w <= P) {
					if (child_things[min_from_max] == 0 && total_w + things[min_from_max]->get_weight() <= P)
						child_things[min_from_max] = 1;
					else if (child_things[max_from_min] == 0 && total_w + things[max_from_min]->get_weight() <= P)
						child_things[max_from_min] = 1;
					Person* p = new Person(child_things);
					delete population[min_person_num];
					population[min_person_num] = p;
				}
			}
		}
		max_now = population[max_person_num]->get_person_things();
		//std::cout << "Max: " << max_person_num + 1;
		max_file << "Max: " << max_person_num + 1;
		//std::cout << " weight: " << population[max_person_num]->get_total_weight() << " price: " << population[max_person_num]->get_total_price() << std::endl;
		max_file << " weight: " << population[max_person_num]->get_total_weight() << " price: " << population[max_person_num]->get_total_price() << std::endl;
		diagram_data << j + 1 << "," << population[max_person_num]->get_total_price() << "\n";
	}
	std::cout << "Max: " << max_person_num + 1;
	std::cout << " weight: " << population[max_person_num]->get_total_weight() << " price: " << population[max_person_num]->get_total_price() << std::endl;
	diagram_data.close();
}
void find_local_improve() {
	int one = 0, two = 0;
	for (int i = 1; i < 100; ++i) {
		if (things[i]->get_price() > things[one]->get_price() || (things[i]->get_price() == things[one]->get_price() && things[i]->get_weight() < things[one]->get_weight()))
			one = i;
	}
	for (int i = 1; i < 100; ++i) {
		if (things[i]->get_weight() < things[two]->get_weight() || (things[i]->get_weight() == things[two]->get_weight() && things[i]->get_price() > things[two]->get_price()))
			two = i;
	}
	min_from_max = one;
	max_from_min = two;
}
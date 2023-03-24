#include "MyClasses.h"
#include "externs.h"
#include <random>
Thing::Thing() {
	weight = rand() % 25 + 1;
	price = rand() % 29 + 2;
}
Person::Person() {
	int chosen_thing = rand() % 99;
	for (int i = 0; i < 100; ++i) {
		if (i == chosen_thing) {
			person_things[i] = 1;
			total_price = things[i]->get_price();
			total_weight = things[i]->get_weight();
		}
		else person_things[i] = 0;
	}
	//needed = chosen_thing;

}
Person::Person(bool p_things[100]) {
	total_price = 0;
	total_weight = 0;
	for (int i = 0; i < 100; ++i) {
		person_things[i] = p_things[i];
		if (p_things[i] == 1) {
			total_price += things[i]->get_price();
			total_weight += things[i]->get_weight();
		}
	}
}
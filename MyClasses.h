#pragma once
class Thing {
	int weight;
	int price;
public:
	Thing();
	int get_weight() { return weight; }
	int get_price() { return price; }
};

class Person {
	bool person_things[100];
	int total_weight;
	int total_price;
	//int needed;
public:
	Person();
	Person(bool[100]);
	bool* get_person_things() { return person_things; }
	int get_total_weight() { return total_weight; }
	int get_total_price() { return total_price; }
};

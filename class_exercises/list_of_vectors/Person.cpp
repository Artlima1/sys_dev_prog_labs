//
// Created by arthur on 3/16/26.
//

#include "Person.h"

#include <iostream>


Person::Person(std::string name) {
    this->name = name;
}

void Person::add_number(const int number) {
    this->numbers.push_back(number);
}

std::string Person::get_name() {
    return this->name;
}

void Person::print_data() {
    std::cout << this->name << " ";
    for (auto number : this->numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}
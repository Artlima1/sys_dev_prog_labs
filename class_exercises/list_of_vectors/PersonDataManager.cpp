//
// Created by arthur on 3/16/26.
//

#include <sstream>
#include "PersonDataManager.h"

#include <iostream>


void PersonDataManager::add_person(const std::string &data) {
    std::stringstream ssdata(data);

    std::string name;
    int number;
    int n_numbers;

    ssdata >> name >> n_numbers;

    int found = false;
    for (auto &p : this->person_list) {
        if (p.get_name() == name) {
            for (int i = 0; i < n_numbers; i++) {
                ssdata >> number;
                p.add_number(number);
            }
            found = true;
        }
    }

    if (!found) {
        Person p(name);
        for (int i = 0; i < n_numbers; i++) {
            ssdata >> number;
            p.add_number(number);
        }

        if (std::islower(name[0])) {
            this->person_list.push_front(p);
        }
        else {
            this->person_list.push_back(p);
        }
    }

}

void PersonDataManager::print_data() {
    for (auto p : this->person_list) {
        p.print_data();
    }

}

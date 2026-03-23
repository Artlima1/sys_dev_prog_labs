//
// Created by arthur on 3/16/26.
//

#ifndef UNTITLED_PERSONDATAMANAGER_H
#define UNTITLED_PERSONDATAMANAGER_H
#include <list>

#include "Person.h"


class PersonDataManager {
private:
    std::pmr::list<Person> person_list;

    public:
    void add_person(const std::string &data);
    void print_data();
};


#endif //UNTITLED_PERSONDATAMANAGER_H
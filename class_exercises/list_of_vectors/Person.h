//
// Created by arthur on 3/16/26.
//

#ifndef UNTITLED_PERSON_H
#define UNTITLED_PERSON_H

#include <string>
#include <vector>



class Person {
private:
    std::string name;
    std::vector <int> numbers;
public:
    Person(std::string name);
    void add_number(int number);
    std::string get_name();
    void print_data();

};


#endif //UNTITLED_PERSON_H
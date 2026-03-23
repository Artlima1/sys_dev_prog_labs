#include <iostream>
#include <list>
#include <vector>

#include "PersonDataManager.h"
#include <fstream>

#define FILENAME "../list_of_vectors/my_file.txt"

int main() {

    PersonDataManager manager;

    std::ifstream infile(FILENAME);
    if (!infile.is_open()) {
        std::cerr << "Error opening " << FILENAME << std::endl;
        return EXIT_FAILURE;
    }

    std::string s;
    while (getline(infile,s)) {
        manager.add_person(s);
    }

    manager.print_data();

    infile.close();
    return EXIT_SUCCESS;
}
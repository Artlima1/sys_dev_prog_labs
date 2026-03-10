#include <iostream>
#include <stdlib.h>

#include "my_lib.hpp"

int main(int argc, char *argv[]){

    int N = std::stoi(argv[1]);

    int * my_array = allocate_and_read(N);
    sort_inplace(my_array, N);
    print_array(my_array, N);
    
    return 0;
}
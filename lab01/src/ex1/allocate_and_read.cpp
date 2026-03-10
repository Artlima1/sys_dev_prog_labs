#include "my_lib.hpp"

#include <iostream>

int * allocate_and_read(int N){
    int * arr = (int *) malloc(N*sizeof(int));
    for(int i=0; i<N; i++){
        std::cin >> arr[i];
    }
    return arr;
}

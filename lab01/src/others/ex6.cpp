#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <math.h>
#include <bits/ctype_base.h>

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("ERROR: Please provide correct arguments");
        exit(1);
    }

    const int N =  std::stoi(argv[1]);
    int number = 0;

    int i=0;
    for (int j=0; j<2; j++) {
        if (j==1)
            number |= 1<<i;
        if (!fork()) {
            if (++i == N) {
                printf("%d ", number);
                break;
            }
            j=-1;
        }
    }

}

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("ERROR: Please provide correct arguments");
        exit(1);
    }

    const int h =  std::stoi(argv[1]);
    const int n =  std::stoi(argv[2]);

    pid_t pid;

    int i=0;
    for (int j=0; j<n; j++) {
        if (!fork()) {
            if (++i == h) {
                break;
            }
            j=-1;
        }
    }

    printf("PID: %d\n", getpid());

}
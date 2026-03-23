#include <iostream>
#include <fstream>
#include <unistd.h>

#include "UserManager.h"


int main(const int argc, char * argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return EXIT_FAILURE;
    }

    BinaryFileUserManager m(argv[1]);
    m.run();

    return EXIT_SUCCESS;
}

//
// Created by arthur on 4/13/26.
//

#include "SocialNetwork.h"
#include <iostream>

int main() {
    SocialNetwork FiDiQuem("../Ex5/data/big.txt");
    // FiDiQuem.display_all_users();
    std::cout<<"--------------------------------------------------" << std::endl;
    FiDiQuem.display_user_friends("Node_25");
    std::cout<<"--------------------------------------------------" << std::endl;
    FiDiQuem.check_connection("Node_25", "Node_28");
    return EXIT_SUCCESS;
}

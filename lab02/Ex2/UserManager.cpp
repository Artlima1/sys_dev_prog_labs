#include "UserManager.h"

#include <fstream>
#include <iostream>

void UserManager::run() {
    bool exit = false;
    do {
        exit = this->cmd_menu();
    } while (!exit);
}

bool UserManager::cmd_menu() {
    bool ret = false;
    std::string cmd;

    std::cin >> cmd;
    if (cmd == "R") {
        this->read_cmd();
    }
    else if (cmd == "W") {
        this->write_cmd();
    }
    else if (cmd == "E") {
        ret = true;
    }
    return  ret;
}

void UserManager::read_cmd() {
    int id;
    user_data_t userInfo;

    std::cin >> id;
    if (this->read_user_info(id, userInfo)) {
        std::cout   << userInfo.id << " "
                    << userInfo.reg_num << " "
                    << userInfo.surname<< " "
                    << userInfo.name << " "
                    << userInfo.mark << "\n";
    }
}

void UserManager::write_cmd() {
    int id;
    user_data_t userInfo;

    std::cin >> id;
    std::cout << "Data: ";


    std::cin >> userInfo.id >> userInfo.reg_num >> userInfo.surname >> userInfo.name >> userInfo.mark;

    if (this->write_user_info(id, userInfo)) {
        std::cout << "Success!" << std::endl;
    }
}


BinaryFileUserManager::BinaryFileUserManager(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: opening files" << std::endl;
    }
    file.close();
    this->fileName = fileName;
}

bool BinaryFileUserManager::read_user_info(const int id, user_data_t &userInfo) {
    bool ret = false;

    std::fstream file(this->fileName,std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    const size_t offset = sizeof(user_data_t) * (id-1);
    file.seekg(offset, std::ios::beg);
    file.read(reinterpret_cast<char*>(&userInfo), sizeof(user_data_t));

    if (file.gcount() == sizeof(user_data_t)) {
        ret = true;
    } else {
        std::cout << "Invalid User ID" << std::endl;
    }

    file.close();
    return ret;
}

bool BinaryFileUserManager::write_user_info(const int id, user_data_t userInfo) {
    bool ret = false;

    std::fstream file(this->fileName,std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    try {
        const size_t offset = sizeof(user_data_t) * (id-1);
        file.seekp(offset, std::ios::beg);
        file.write(reinterpret_cast<char*>(&userInfo), sizeof(user_data_t));
        ret = true;
    } catch (error_t e) {
        std::cout << "Invalid User ID" << std::endl;
    }

    file.close();
    return ret;
}

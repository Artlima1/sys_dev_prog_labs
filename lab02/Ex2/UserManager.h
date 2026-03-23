//
// Created by arthur on 3/23/26.
//

#ifndef LAB02_USERMANAGER_H
#define LAB02_USERMANAGER_H

#include <string>

typedef struct {
    int id;
    long int reg_num;
    char surname[30];
    char name[30];
    int mark;
} user_data_t;

class UserManager {
public:
    void run();
    bool cmd_menu();
    void read_cmd();
    void write_cmd();
    virtual bool read_user_info(int id, user_data_t &userInfo) = 0;
    virtual bool write_user_info(int id, user_data_t userInfo) = 0;
};

class BinaryFileUserManager : public UserManager {
private:
    std::string fileName;
public:
    BinaryFileUserManager(const std::string &fileName);
    bool read_user_info(int id, user_data_t &userInfo) override;
    bool write_user_info(int id, user_data_t userInfo) override;
};

#endif //LAB02_USERMANAGER_H
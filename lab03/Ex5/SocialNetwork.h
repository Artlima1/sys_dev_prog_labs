//
// Created by arthur on 4/13/26.
//

#ifndef LAB03_SOCIALNETWORK_H
#define LAB03_SOCIALNETWORK_H

#include <string>
#include <map>
#include <set>

using std::string;
using std::set;
using std::map;

class SocialNetwork {
private:
    string _input_file;
    map<string, set<string>> _users;

    void _read_input_data();

public:
    SocialNetwork(const string &file_name);

    void display_all_users();
    void display_user_friends(const string &username);
    void check_connection(const string & u1, const string & u2);
};


#endif //LAB03_SOCIALNETWORK_H
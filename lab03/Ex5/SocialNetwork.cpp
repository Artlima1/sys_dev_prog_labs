//
// Created by arthur on 4/13/26.
//

#include "SocialNetwork.h"

#include <cstring>
#include <sstream>
#include <fstream>
#include <functional>
#include <iostream>

using std::fstream;
using std::ifstream;
using std::stringstream;

SocialNetwork::SocialNetwork(const string &file_name) {
    _input_file = file_name;
    _read_input_data();
}

void SocialNetwork::_read_input_data() {
    ifstream input_fs(_input_file);
    if (!input_fs.is_open()) {
        std::cerr << "Error: opening files" << std::endl;
    }

    string u1, u2;
    string buff;
    stringstream ssdata;
    while (getline(input_fs, buff)) {
        ssdata << buff;
        ssdata >> u1 >> u2;
        _users[u1].insert(u2);
        _users[u2].insert(u1);
        ssdata.clear();
    }
}

void SocialNetwork::display_all_users() {
    for (auto &u : _users) {
        std::cout << u.first << std::endl;;
    }
    std::cout << std::endl;
}

void SocialNetwork::display_user_friends(const string &username) {
    if (_users.find(username) != _users.end()) {
        for (const string & f: _users[username] ) {
            std::cout << f << std::endl;
        }
    }
}


void SocialNetwork::check_connection(const string &u1, const string &u2) {
    std::function<bool(string, set<string>&, string)> DFS =
        [&](const string cur, set<string> &path, string target) -> bool {
            if (path.contains(cur)) {
                return false;
            }

            if (cur==target) {
                std::cout << cur << std::endl;
                return true;
            }

            path.insert(cur);
            for (auto const f : _users[cur]) {
                if (DFS(f, path, target)) {
                    std::cout << cur << std::endl;
                    return true;
                }
            }
            path.erase(cur);
            return false;
        };

    set<string> start_path;
    DFS(u1, start_path, u2);
}

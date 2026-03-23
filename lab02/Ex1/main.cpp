#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <unistd.h>

using namespace std;

typedef struct {
    int id;
    long int reg_num;
    char surname[30];
    char name[30];
    int mark;
} user_data_t;

void read_from_txt(list<user_data_t> &l, const string &input_file);
void write_to_bin(list<user_data_t> &l, const string &output_file);
void read_from_bin(list<user_data_t> &l, const string &input_file);
void write_to_txt(list<user_data_t> &l, const string &output_file);

int main(const int argc, char * argv[]) {
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <file_name> <file_name> <file_name>" << endl;
        return EXIT_FAILURE;
    }

    list<user_data_t> users;
    read_from_txt(users, argv[1]);
    write_to_bin(users, argv[2]);
    read_from_bin(users, argv[2]);
    write_to_txt(users, argv[3]);

    return EXIT_SUCCESS;
}


void read_from_txt(list<user_data_t> &l, const string &input_file) {
    ifstream input_fs(input_file);
    if (!input_fs.is_open()) {
        cerr << "Error: opening files" << endl;
    }

    user_data_t data;
    string buff;
    stringstream ssdata;
    while (getline(input_fs, buff)) {
        ssdata << buff;
        ssdata >> data.id >> data.reg_num >> data.surname >> data.name >> data.mark;
        l.push_back(data);
        ssdata.clear();
    }

    input_fs.close();
}

void write_to_bin(list<user_data_t> &l, const string &output_file) {
    ofstream output_fs(output_file,  std::ios::out|std::ios::binary);
    if (!output_fs.is_open()) {
        cerr << "Error: opening files" << endl;
    }

    user_data_t data;
    while (!l.empty()) {
        data = l.front();
        output_fs.write(reinterpret_cast<const char*> (&data), sizeof(user_data_t));
        l.pop_front();
    }

    output_fs.close();
}

void read_from_bin(list<user_data_t> &l, const string &input_file) {
    ifstream input_fs(input_file, ios::in|ios::binary);
    if (!input_fs.is_open()) {
        cerr << "Error: opening files" << endl;
    }

    user_data_t data;

    while (input_fs.read(reinterpret_cast<char*> (&data), sizeof(user_data_t))) {
        l.push_back(data);
    }

    input_fs.close();
}


void write_to_txt(list<user_data_t> &l, const string &output_file) {
    ofstream output_fs(output_file);
    if (!output_fs.is_open()) {
        cerr << "Error: opening files" << endl;
    }

    user_data_t data;
    while (!l.empty()) {
        data = l.front();
        output_fs   << data.id << " "
                    << data.reg_num << " "
                    << data.surname<< " "
                    << data.name << " "
                    << data.mark << "\n";
        l.pop_front();
    }

    output_fs.close();
}
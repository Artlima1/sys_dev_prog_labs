


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <fstream>
#include <future>
#include <list>
#include <map>
#include <set>

using std::string;

std::mutex print_mtx;

struct file_proc_task_data_t {
    std::multiset<int> * elements = nullptr;
    string file_name;
};

void proc_file(file_proc_task_data_t & data);

int main(int argc, char *argv[]) {
    std::vector<string> files;

    std::string buff;
    getline(std::cin, buff);
    std::stringstream ss_line(buff);
    while (getline(ss_line, buff, ' '))
        files.push_back(buff);

    std::vector<std::thread> threads;
    auto * threads_data = new file_proc_task_data_t[files.size()];
    for (int i = 0; i < files.size(); i++) {
        threads_data[i].file_name = files[i];
        threads.emplace_back(
            [threads_data, i]
            {proc_file(std::ref(threads_data[i]));}
        );
    }

    for (auto &thread : threads) {
        thread.join();
    }

    std::multiset<int> all_elements;
    for (int i = 0; i < files.size(); i++) {
        all_elements.merge(*threads_data[i].elements);
    }

    for (auto e:all_elements) {
        std::cout << e << "  ";
    }
    std::cout << std::endl;

    delete[] threads_data;

    return EXIT_SUCCESS;
}


void proc_file(file_proc_task_data_t & data) {
    const string file_path = "../ex1/files/" + data.file_name;
    std::ifstream input_fs(file_path);

    if (!input_fs.is_open()) {
        std::cerr << "Error: opening files" << std::endl;
    }

    int n_elements, element;

    input_fs >> n_elements;

    data.elements = new std::multiset<int>[n_elements];

    for (int i = 0; i < n_elements; i++) {
        input_fs >> element;
        data.elements->insert(element);
    }
    input_fs.close();

}

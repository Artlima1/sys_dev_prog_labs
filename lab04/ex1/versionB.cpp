


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
#include <queue>

using std::string;

std::mutex print_mtx;

std::queue<int> finished_q;
std::mutex fq_mtx;
std::counting_semaphore<> fq_sem(0);

struct file_proc_task_data_t {
    std::multiset<int> * elements = nullptr;
    string file_name;
    int index=0;
};

void proc_file(file_proc_task_data_t & data);

int main(int argc, char *argv[]) {
    std::vector<string> files;

    std::string buff;
    getline(std::cin, buff);
    std::stringstream ss_line(buff);
    while (getline(ss_line, buff, ' '))
        files.push_back(buff);

    const int n_threads = files.size();

    std::vector<std::thread> threads;
    auto * threads_data = new file_proc_task_data_t[n_threads];
    for (int i = 0; i < n_threads; i++) {
        threads_data[i].file_name = files[i];
        threads_data[i].index = i;
        threads.emplace_back(
            [threads_data, i]
            {proc_file(std::ref(threads_data[i]));}
        );
    }

    std::multiset<int> all_elements;
    int finished = 0;
    int finished_index = 0;
    while (finished < n_threads) {
        fq_sem.acquire();
        {
            std::lock_guard<std::mutex> lock(fq_mtx);
            finished_index = finished_q.front();
            finished_q.pop();
        }
        all_elements.merge(*threads_data[finished_index].elements);
        finished ++;
    }

    for (auto e:all_elements) {
        std::cout << e << "  ";
    }
    std::cout << std::endl;

    for (auto &t: threads) {
        t.join();
    }

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

    {
        std::lock_guard<std::mutex> lock(fq_mtx);
        finished_q.push(data.index);
        fq_sem.release();
    }

}

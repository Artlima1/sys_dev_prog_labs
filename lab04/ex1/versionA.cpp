


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <future>
#include <set>
#include <ctime>

using std::string;

std::mutex print_mtx;

struct file_proc_task_data_t {
    std::multiset<int> * elements = nullptr;
    string file_name;
};

void proc_file(file_proc_task_data_t & data);
extern void read_file_to_set(std::multiset<int> * out, const string &file_name);
extern void write_set_to_file(std::multiset<int> * data, const string &file_name);

int main(int argc, char *argv[]) {
    clock_t start = clock();

    std::vector<string> files;

    std::string buff;
    getline(std::cin, buff);
    std::stringstream ss_line(buff);
    while (getline(ss_line, buff, ' '))
        files.push_back(buff);

    string output_file = files.back();
    files.pop_back();


    int n_threads = files.size();
    std::vector<std::thread> threads;
    auto * threads_data = new file_proc_task_data_t[n_threads];
    for (int i = 0; i < n_threads; i++) {
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
    for (int i = 0; i < n_threads; i++) {
        all_elements.merge(*threads_data[i].elements);
        delete threads_data[i].elements;
    }

    write_set_to_file(&all_elements, output_file);

    delete[] threads_data;

    clock_t end = clock();
    double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Execution Time: " << duration << " seconds" << std::endl;

    return EXIT_SUCCESS;
}


void proc_file(file_proc_task_data_t & data) {
    data.elements = new std::multiset<int>;
    read_file_to_set(data.elements, data.file_name);
}



#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <semaphore>
#include <chrono>
#include <queue>

#define VERSION_B

using std::string;

std::mutex print_mtx;
#ifdef  VERSION_B
std::queue<int> finished_q;
std::mutex fq_mtx;
std::counting_semaphore<> fq_sem(0);
#endif

struct file_proc_task_data_t {
    int* elements = nullptr;
    int size = 0;
    string file_name;
    int index;
};

void proc_file(file_proc_task_data_t & data);
extern void read_file_to_arr(int** out, int* n_out, const string &file_name);
extern void write_arr_to_file(const int* data, int size, const string &file_name);

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

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
        threads_data[i].index = i;
        threads.emplace_back(
            [threads_data, i]
            {proc_file(std::ref(threads_data[i]));}
        );
    }

    std::vector<int> all_elements;

#ifdef VERSION_A
    for (auto &thread : threads)
        thread.join();

    for (int i = 0; i < n_threads; i++) {
        std::vector<int> merged(all_elements.size() + threads_data[i].size);
        std::merge(all_elements.begin(), all_elements.end(),
                   threads_data[i].elements, threads_data[i].elements + threads_data[i].size,
                   merged.begin());
        all_elements = std::move(merged);
        delete[] threads_data[i].elements;
    }
#endif


#ifdef  VERSION_B
    int finished = 0;
    while (finished < n_threads) {
        fq_sem.acquire();
        int idx;
        {
            std::lock_guard<std::mutex> lock(fq_mtx);
            idx = finished_q.front();
            finished_q.pop();
        }
        std::vector<int> merged(all_elements.size() + threads_data[idx].size);
        std::merge(all_elements.begin(), all_elements.end(),
                   threads_data[idx].elements, threads_data[idx].elements + threads_data[idx].size,
                   merged.begin());
        all_elements = std::move(merged);
        delete[] threads_data[idx].elements;
        threads_data[idx].elements = nullptr;
        finished++;
    }

    for (auto &t: threads)
        t.join();
#endif

    write_arr_to_file(all_elements.data(), static_cast<int>(all_elements.size()), output_file);

    delete[] threads_data;

    auto finish = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(finish - start).count();
    std::cout << "Execution Time: " << duration << " seconds" << std::endl;

    return EXIT_SUCCESS;
}


void proc_file(file_proc_task_data_t & data) {
    read_file_to_arr(&data.elements, &data.size, data.file_name);
    std::sort(data.elements, data.elements + data.size);

    #ifdef  VERSION_B
    {
        std::lock_guard<std::mutex> lock(fq_mtx);
        finished_q.push(data.index);
        fq_sem.release();
    }
    #endif
}

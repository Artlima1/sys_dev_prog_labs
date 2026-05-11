

#include <condition_variable>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <vector>

#define INIT_VAR 0
#define ADDER_THREADS 5
#define MAX_VAR 15

void adder_thread();
void admin_thread();

int var;
std::mutex var_mtx;
std::counting_semaphore<0> adder_sem(0);
std::mutex done_mtx;
std::condition_variable done_cv;
bool done = false;

int main() {
    std::thread adm(admin_thread);

    std::vector<std::thread> adder_pool;
    for (int i = 0; i < ADDER_THREADS; i++) {
        srand ((unsigned)time(NULL));
        adder_pool.emplace_back([] {adder_thread();});
    }

    for (auto &t : adder_pool) {
        t.join();
    }

    {
        std::lock_guard<std::mutex> done_lock(done_mtx);
        done = true;
        done_cv.notify_one();
    }

    adm.join();
    return EXIT_SUCCESS;
}


void admin_thread() {
    {
        std::lock_guard<std::mutex> lock(var_mtx);
        var = INIT_VAR;
    }
    for (int i = 0; i < ADDER_THREADS; i++) {
        adder_sem.release();
    }

    std::unique_lock<std::mutex> lock(done_mtx);
    if (!done)
        done_cv.wait(lock);
    done_mtx.unlock();

    std::cout << "Final var = " << var << std::endl;
}

void adder_thread() {
    sleep (rand()%2);
    adder_sem.acquire();

    std::lock_guard<std::mutex> adder_lock(var_mtx);
    if (var < MAX_VAR) {
        var += 1+rand()%2;
        if (var >= MAX_VAR) {
            std::lock_guard<std::mutex> done_lock(done_mtx);
            done = true;
            done_cv.notify_all();
        }
        std::cout << "var = " << var << std::endl;
    }
}




#include <iostream>
#include <stdlib.h>
#include <thread>
#include <vector>

#define N_THREADS 9

struct election_info_t {
    int total_voters;
    int votes;
    std::thread::id leader;
    int leader_rank;
};

election_info_t ei;
std::mutex ei_mtx;
std::mutex print_mtx;
std::counting_semaphore<0> finish_sem(0);

void election_thread(int rank) {
    sleep (rand()%2);
    bool finished = false;

    ei_mtx.lock();
    if (ei.leader_rank < rank) {
        ei.leader_rank = rank;
        ei.leader = std::this_thread::get_id();
    }
    ei.votes++;

    std::thread::id leader = ei.leader;
    if (ei.votes < ei.total_voters) {
        ei_mtx.unlock();
        {
            std::lock_guard<std::mutex>  print_lock(print_mtx);
            std::cout   << "ID: " << std::this_thread::get_id()
                        << "\t | Rank: " << rank
                        << "\t | Leader: " << leader
                        << "\t | [WAITING]"
                        << std::endl;
        }
        finish_sem.acquire();
    }
    else {
        ei_mtx.unlock();
        for (int i=0; i<ei.total_voters-1; i++) finish_sem.release();
    }

    {
        std::lock_guard<std::mutex>  print_lock(print_mtx);
        std::cout   << "ID: " << std::this_thread::get_id()
                    << "\t | Rank: " << rank
                    << "\t | Leader: " << ei.leader
                    << "\t | [FINISHED]"
                    << std::endl;
    }


}

int main() {
    ei.total_voters = N_THREADS;
    ei.votes = 0;
    ei.leader_rank = 0;

    std::vector<std::thread> pool;
    int rank = 0;
    for (int i=0; i<N_THREADS; i++) {
        rank = rand()%25;
        pool.emplace_back([rank] { election_thread(rank); });
    }

    for (int i=0; i<N_THREADS; i++) {
        pool[i].join();
    }

    std::cout << "Final Leader: " << ei.leader << std::endl;

    return EXIT_SUCCESS;
}

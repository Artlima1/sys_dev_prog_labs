
#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

enum {
    CMD_NONE = -1,
    CMD_TERMINATE = 0,
    CMD_DISPLAY_ALL = 1,
    CMD_DISPLAY_LAST = 2,
    CMD_DELETE_ALL = 3
};

void ui();
void writer();
void worker();

std::queue<int> cmd_q;
std::mutex cmd_mtx;
std::counting_semaphore<> cmd_sem(0);

std::mutex v_mtx;
std::vector<int> v;

bool terminate=false;
std::mutex terminate_mtx;

int main() {
    std::thread worker_thread(worker);
    std::thread ui_thread(ui);
    std::thread writer_thread(writer);

    worker_thread.join();
    ui_thread.join();
    writer_thread.join();

    return EXIT_SUCCESS;
}


void writer() {
    while (true) {
        sleep(3);
        {
            std::lock_guard<std::mutex> lk(v_mtx);
            v.push_back(1+rand()%9);
        }

        {
            std::lock_guard<std::mutex> lk(terminate_mtx);
            if (terminate) break;
        }
    }
}

void worker() {
    int cmd = CMD_NONE;
    while (true) {
        cmd_sem.acquire();

        {
            std::lock_guard<std::mutex> cmd_lk(cmd_mtx);
            cmd = cmd_q.front();
            cmd_q.pop();
        }

        if (cmd == CMD_TERMINATE) {
            std::lock_guard<std::mutex> terminate_lk(terminate_mtx);
            terminate = true;
            break;
        }

        if (cmd == CMD_DISPLAY_ALL) {
            std::lock_guard<std::mutex> v_lk(v_mtx);
            if (v.empty()) {
                std::cout << "V is empty";
            }
            else {
                for (auto e : v) {
                    std::cout << e << " ";
                }
            }
            std::cout << std::endl;
            continue;
        }

        if (cmd == CMD_DISPLAY_LAST) {
            std::lock_guard<std::mutex> v_lk(v_mtx);
            if (v.empty()) {
                std::cout << "V is empty";
            }
            else {
                std::cout << v.at(v.size() - 1);
            }
            std::cout << std::endl;
            continue;
        }

        if (cmd==CMD_DELETE_ALL) {
            std::lock_guard<std::mutex> v_lk(v_mtx);
            v.clear();
            continue;
        }
    }
}

void ui() {
    int cmd=CMD_NONE;
    while (cmd != CMD_TERMINATE) {
        std::cin >> cmd;
        std::lock_guard<std::mutex> cmd_lk(cmd_mtx);
        cmd_q.push(cmd);
        cmd_sem.release();
    }
}

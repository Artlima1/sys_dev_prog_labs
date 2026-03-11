#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>

typedef struct {
    int N;
    int h;
    unsigned long path[];
} thread_tree_info_t;

void * leaf_thread(void * arg) {
    const auto * parent_data = (thread_tree_info_t *) arg;

    const int curr_h = parent_data->h+1;
    auto * node_data = (thread_tree_info_t *) malloc(sizeof(thread_tree_info_t) + (curr_h+1)*sizeof(unsigned long));
    memcpy(node_data, parent_data, sizeof(thread_tree_info_t) + curr_h*sizeof(unsigned long));
    node_data->h = curr_h;
    node_data->path[curr_h] = pthread_self();

    if (node_data->h == node_data->N) {
        for (int i=0; i <= curr_h; i++) {
            printf("%lu ",node_data->path[i]);
        }
        printf("\n");
    }
    else {
        pthread_t thread[2];
        pthread_create(&thread[0], nullptr, leaf_thread, node_data);
        pthread_create(&thread[1], nullptr, leaf_thread, node_data);
        pthread_join(thread[0], nullptr);
        pthread_join(thread[1], nullptr);
    }
    free(node_data);
    return nullptr;
}

int main(int argc, char * argv[]) {
    const int N =  std::stoi(argv[1]);
    pthread_t thread[2];

    int curr_h = 0;
    auto * node_data = (thread_tree_info_t *) malloc(sizeof(thread_tree_info_t) + (curr_h+1)*sizeof(unsigned long));
    node_data->N = N;
    node_data->h = curr_h;
    node_data->path[curr_h] = pthread_self();;

    pthread_create(&thread[0], nullptr, leaf_thread, node_data);
    pthread_create(&thread[1], nullptr, leaf_thread, node_data);

    pthread_join(thread[0], nullptr);
    pthread_join(thread[1], nullptr);

    free(node_data);
    printf("Main Thread Finished");

    return 0;
}
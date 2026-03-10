#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>

typedef struct {
    int N;
    int curr_h;
} thread_tree_t;

void * leaf_thread(void * arg) {
    auto * data = (thread_tree_t *) arg;
    if (data->curr_h == data->N) {
        printf("End\n");
    }
    else {
        auto new_arg = new thread_tree_t;
        * new_arg = * data;
        new_arg->curr_h++;
        pthread_t thread[2];
        pthread_create(&thread[0], NULL, leaf_thread, new_arg);
        pthread_create(&thread[1], NULL, leaf_thread, new_arg);

        pthread_join(thread[0], NULL);
        pthread_join(thread[1], NULL);
    }
    return nullptr;
}

int main(int argc, char * argv[]) {
    const int N =  std::stoi(argv[1]);
    pthread_t thread[2];
    pthread_t id = pthread_self();

    auto * arg_t = new thread_tree_t;
    arg_t->N = N;
    arg_t->curr_h = 0;

    pthread_create(&thread[0], NULL, leaf_thread, arg_t);
    pthread_create(&thread[1], NULL, leaf_thread, arg_t);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    free(arg_t);
    printf("Main Thread Finished");

    return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t mutex;
pthread_cond_t condvar;
int charcounter = 0;
bool tenisreached = false;
bool fiftyisreached = false;

void *watcherthread(void *arg) {
    pthread_mutex_lock(&mutex);
    while (!fiftyisreached) {
        if (charcounter > 10 && !tenisreached) {
            printf(">10\n");
            tenisreached = true;
        }
        if (charcounter > 50) {
            printf(">50\n");
            fiftyisreached = true;
            break;
        }
        pthread_cond_wait(&condvar, &mutex);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, watcherthread, NULL);
    while (true) {
        char input;
        if (scanf("%c", &input) == EOF) {
            break;
        }
        pthread_mutex_lock(&mutex);
        charcounter++;
        pthread_cond_signal(&condvar);
      
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(thread, NULL);

    printf("number of chars is: %d\n", charcounter);

    return 0;
}

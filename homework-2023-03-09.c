#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

void sem_wait(int semid, int sem_num) {
    struct sembuf op = {sem_num, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal(int semid, int sem_num) {
    struct sembuf op = {sem_num, 1, 0};
    semop(semid, &op, 1);
}

int main(int argc, char *argv[]) {

    int N = atoi(argv[1]);

    key_t key = IPC_PRIVATE;
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    if (semctl(semid, 0, SETVAL, 0) == -1) {
        perror("semctl");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork did't happen");
            return 1;
        } else if (pid == 0) {
            sem_wait(semid, i);
            printf("%d\n", i + 1);
            sem_signal(semid, (i + 1) % N);
            return 0;
        }
    }
    sem_signal(semid, 0);
    for (int i = 0; i < N; i++) {
        wait(NULL);

    return 0;
}

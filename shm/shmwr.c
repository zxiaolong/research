#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    key_t shmkey = 13;
    int shm_id = shmget(shmkey, 2048, IPC_CREAT | 0666);
    if (shm_id != -1) {
        void* shm = shmat(shm_id, NULL, 0);
        if (shm != (void*)-1) {
            char str[] = "I'm share memory333";
            memcpy(shm, str, strlen(str) + 1);
            shmdt(shm);
        } else {
            perror("shmat:");
        }
    } else {
        perror("shmget:");
    }

    return 0;
}
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() { 
    // 1. 获取 SHM
    key_t shmkey = 13;
    int shm_id = shmget(shmkey, 2048, IPC_CREAT | 0666);
    
    if (shm_id != -1) {
        void* shm = shmat(shm_id, NULL, 0);
        if (shm != (void*)-1) {
            char str[50] = { 0 };
            memcpy(str, shm, strlen("I'm share memory333"));
            printf("shm = %s\n", (char *)shm); 
            shmdt(shm);
        } else {
            perror("shmat:");
        }
    } else {
        perror("shmget:");
    }

    if (0 == shmctl(shm_id, IPC_RMID, 0))
        printf("delete shm success.\n");

    return 0;
}
//destroy.cpp
//用于删除ipc内核对象...
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <pthread.h>
#include <iostream>
#include <stdlib.h>



int main(int argc, char*argv[]){

        //argv：
        //      argv[1]:
        //              0: shared memory。
        //              1：message queue
        //              2：semaphore.
        //      argv[2]:
        //              key.
        //
        if(3 != argc){
                std::cout<<"usage "<<argv[0]<<" <type> <key>"<<std::endl;
                return -1;
        }

        char type = argv[1][0];
        long key = strtol(argv[2], NULL, 16);

        //然后删除内核对象.
        if('0' == type){
                //shared memory.
                int hshm = shmget(key, 0, 0);
                if(-1 == hshm){
                        std::cout<<"getshm faild."<<std::endl;
                        return -1;
                }
                //然后删除.
                if(-1 == shmctl(hshm, IPC_RMID, NULL)){
                        std::cout<<"remove shared memory faild."<<std::endl;
                        return -1;
                }
        }
        else if('1' == type){
                //message queue.
                int hmsg = msgget(key, 0);
                if(-1 == hmsg){
                        std::cout<<"get message faild."<<std::endl;
                        return -1;
                }
                if(-1 == msgctl(hmsg, IPC_RMID, NULL)){
                        std::cout<<"remove message queue faild."<<std::endl;
                        return -1;
                }
        }
        else if('2' == type){
                int hsem = semget(key, 0, 0);
                if(-1 == hsem){
                        std::cout<<"get semaphore faild."<<std::endl;
                        return -1;
                }
                if(-1 == semctl(hsem, 0, IPC_RMID)){
                        std::cout<<"remove semaphore faild."<<std::endl;
                        return -1;
                }
        }
        else{
                std::cout<<"type must be in {0,1,2}"<<std::endl;
        }



        return 0;
}
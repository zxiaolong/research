//buytickets.cpp
//这个进程用来买票.
//


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include<iostream>
#include <stdlib.h>
#include<string>

struct Tickets{

        int num;
        pthread_mutex_t mut;
};



int main(int argc, char*argv[]){

        if(argc != 2){
                std::cout<<"usage "<<argv[0]<<" <usrname>"<<std::endl;
                return -1;
        }

        std::string name = argv[1];


        //首先是要将共享内存加载到进程.

        key_t key = 0x999;
        int hshm = shmget(key, 0, 0);
        if(0 > hshm){
                std::cout<<"call shmget faild."<<std::endl;
                return -1;
        }

        struct Tickets* pres = (Tickets*)shmat(hshm, NULL, 0);
        if(NULL == pres){
                std::cout<<"挂载内存失败."<<std::endl;
                return -1;
        }

        //可以开始买票了.
        bool flag = true;
        while(flag){

                pthread_mutex_lock(&pres->mut);
                std::cout<<"当前余票："<<pres->num<<std::endl;
                flag = pres->num > 0 ? true : false;
                if(flag){
                        std::cout<<name<<" buy a ticket."<<std::endl;
                        pres->num--;
                }
                pthread_mutex_unlock(&pres->mut);
                sleep(2);
        }


        //卸载内存.
        if(0 != shmdt(pres)){

                std::cout<<"就连卸载内存都出现错误了o."<<std::endl;
        }

        return 0;
}
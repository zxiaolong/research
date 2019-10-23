//init.cpp
//这个进程用于初始化环境，
//      即创建共享内存和实例化共享内存空间的mutex变量.
//
//本例以火车站买票为例.


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

struct Tickets{
        int num;
        pthread_mutex_t mut;
};

int main(){
        //创建多进程共享的变量.资源.
        struct Tickets *pres = NULL;
        //首先创建共享内存.
        key_t key = 0x999;
        int hshm = shmget(key, getpagesize(), IPC_CREAT | IPC_EXCL | 0666);
        if(0 > hshm){
                printf("call shmget faild.\n");
                return -1;
        }

        //挂载共享内存.
        pres = (struct Tickets*)shmat(hshm, NULL, 0);
        if(NULL == pres){
                printf("挂载内存失败.\n");
                return -1;
        }

        //然后就是在共享内存区创建共享的资源.
        //首先将资源设置.
        pres->num = 10;

        //然后是初始化mutex.
        //但是在这之前我们需要设置下mutex的属性为：PTHREAD_PROCESS_SHARED
        pthread_mutexattr_t mutattr;
        if(0 != pthread_mutexattr_init(&mutattr)){
                printf("at pthread_mutexattr_init: initializer mutex_attr faild.\n");
                return -1;
        }

        //设置mutex_attr的共享属性.
        if(0 != pthread_mutexattr_setpshared(&mutattr, PTHREAD_PROCESS_SHARED)){
                printf("set PTHREAD_PROCESS_SHARED attributes faild.\n");
                return -1;
        }

        //然后就可以在共享内存区构建mutex变量了.
        if(0 != pthread_mutex_init(&pres->mut, &mutattr)){
                printf("初始化mutex失败.\n");
                return -1;
        }



        //在这之后是不是应该销毁mutattr捏.
        pthread_mutexattr_destroy(&mutattr);

        //然后我们就...将环境构建成功了.


        //至于接下来的事情就不管了哇.

        //算了，差点忘了要卸载共享内存了.
        if(0 != shmdt(pres)){
                printf("就连卸载内存都出现错误了o.\n");
        }

        return 0;
}

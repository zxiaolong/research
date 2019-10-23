#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

#define FILENAME "write_name_sem_file"

int main ()   
{   
    sem_t *sem_1 = NULL; 
    sem_t *sem_2 = NULL; 
    sem_1 = sem_open("write_name_sem_1", O_CREAT|O_RDWR, 0666, 1); //信号量值为 1  
    sem_2 = sem_open("write_name_sem_2", O_CREAT|O_RDWR, 0666, 0); //信号量值为 1  
    if( (sem_1 == SEM_FAILED) | (sem_2 == SEM_FAILED))
    {
        perror("sem_open");  
        exit(-1);  
    }  
    int count=0;  
    int fd = open(FILENAME,O_RDWR | O_CREAT| O_APPEND,0777);
    if(fd < 0)
    {
        perror("open");
    }
    char write_buf[] = "1";
    int i = 0; 
    while(1)
    {
        /*信号量减一，P 操作*/
        sem_wait(sem_1);
        for(i = 0;i<5;i++)
        {
            if (write(fd,write_buf,sizeof(write_buf)))
            {
                perror("write");
            }
            count++;
        }
        printf("in sem1 ....and count = %d\n",count);
        /*信号量加一，V 操作*/
        sem_post(sem_2);
        sleep(2);
    }
    //sem_del("write_name_sem"); //删除信号量文件 name_sem  
    return 0;
}
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
    int count=0;  
    char write_buf[] = "2";
    int i = 0;
    sem_t *sem_1 = NULL; 
    sem_t *sem_2 = NULL; 
    sem_1 = sem_open("write_name_sem_1", O_CREAT|O_RDWR, 0666, 1);
    sem_2 = sem_open("write_name_sem_2", O_CREAT|O_RDWR, 0666, 0);
    if( (sem_1 == SEM_FAILED) | (sem_2 == SEM_FAILED))
    {
        perror("sem_open");  
        exit(-1);  
    }  
    int fd = open(FILENAME,O_RDWR | O_CREAT| O_APPEND,0777);
    if(fd < 0)
    {
        perror("open");
    }
    while(1)
    {
        /*信号量减一，P 操作*/
        sem_wait(sem_2);
        for(i = 0;i<5;i++)
        {
            if (write(fd,write_buf,sizeof(write_buf)))
            {
                perror("write");
            }       
            count++;
        }
        printf("in sem2 .... count = %d\n",count); 
        /*信号量加一，V 操作*/
        sem_post(sem_1);
        sleep(2);
    }  
    return 0;  
}

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

typedef struct{
    long type;
    char name[20];
    int age;
}Msg;

int main()
{
    key_t key = ftok("/etc/msgque",'6');
    printf("key:%x\n",key);

    int msgid = msgget(key,O_RDONLY);
    if(msgid<0)
    {   
        perror("msgget error!");
        exit(-1);
    }   

    Msg rcv;
    long type;
    puts("please input type you want!");
    scanf("%ld",&type);

    msgrcv(msgid,&rcv,sizeof(rcv)-sizeof(type),type,0);
    printf("rcv--name:%s age:%d\n",rcv.name,rcv.age);

    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}
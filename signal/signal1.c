#include <stdio.h>
#include<signal.h>
 
void handler(int data)
{ 
    printf("sig is %d\n", data);    
}
 
int main()
{ 
    signal(2, handler);
    sleep(3);
 
    while(1)
    { 
        raise(2);
        sleep(1);
    }
}
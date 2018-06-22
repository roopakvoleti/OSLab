#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<wait.h>

#define MIN_PID 100
#define MAX_PID 1000
#define NO_OF_P 16      //no of process/threads

//not using map (bitmap), using a preallocated char array instead
int pid[MAX_PID-MIN_PID]={0};

int allocate_pid(void){
    int i,flag=1;
    for(i=0; i<MAX_PID-MIN_PID; i++){
        if(pid[i]==0){
            //pid available//next line should be in critical section
            //with a mutex lock, whicever thread gets the lock gets the id.
            pid[i]=1;
            flag=0;
            break;
        }
    }
    return flag?-1:i;
}
void release_pid(int id){
    pid[id]=0;
}
void *threadRoutine(void *arg){
    int tid =  *(( int* )arg);
    
    //get a pid
    int id = allocate_pid();



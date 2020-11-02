#ifndef ARRAYIMP_H_INCLUDED
#define ARRAYIMP_H_INCLUDED



#endif // ARRAYIMP_H_INCLUDED
#ifdef _WIN32
#include <time.h>
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#define N 100005
typedef struct
{
    int id;
    int priority;
    int timeex;
} process;
void displayProcess(process p)
{
    printf("the process id= %d \t",p.id);
    printf("of priority = %d \t",p.priority);
    printf("and execution time= %d \n",p.timeex);

}

typedef struct
{
    process *data;
    int front,rear ;
} queue;
queue init();
int	isEmpty(queue q );
int	isFull( queue	q );
int	enqueue(queue * q,	process e );
int dequeue(queue *q);
int front(queue q, process *e);
void insertProcess1(queue *q,process p);
void check(queue *q,process p);
;
;

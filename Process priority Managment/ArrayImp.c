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
void displayProcess(process p)//shows information of a process
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
queue init()//constructs an empty queue
{
    process *data=(process*)malloc(N*sizeof(process));

    queue q;
    q.front= 1 ; //	q. data[ 0 ]
    q.rear=0;
    q.data=data;
    return q;
}
int	isEmpty1(queue q )//checks if queue is empty
{
    return ( q.front	== ( q.rear	+1)%N);
}
int	isFull( queue	q )////checks if queue is full
{
    return ( q.front	== ( q.rear	+2)%N);
}

int	enqueue(queue * q,	process e )//inserts a process in the rear of the queue
{
    if( isFull( * q ) )
        return	0;
    q->rear = (q->rear + 1 ) % N;
    q->data[q->rear]=e;
    return	1;
}
int front(queue q, process *e)//returns the front of a queue
{
    if (isEmpty1(q))
        return 0;
    *e = q.data[q.front];
    return 1;
}
void display(queue s)//displays the processes in the queue from front to rear
{

    int i;
    if (isEmpty1(s))
        printf("Queue is empty \n");
    else
        {
            printf("Queue contains : \n");
            for (i = s.front; i <=s.rear; i++)
                {
                    displayProcess(s.data[i]);
                    printf("\n");
                }
        }
}

void insertProcess1(queue *q,process p)//inserts a process respecting the priority
{
    if(isFull(*q))//check if queue is full so no elements can be added
        printf("the queue is full and no more elements can be inserted ");
    if(isEmpty1(*q)) //checks if queue is empty so directly enqueue the process
        {
            enqueue(q,p);
        }
    else
        {
            check(q,p);//make the test check
            q->rear++;
            q->front=1;
        }



}
void check(queue *q,process p)
{
    int i,j;
    for(i=1; i<=q->rear; i++)
        {
            if(p.priority>=q->data[i].priority)//find the first process of same priority
                {
                    //shift all processes after the found one to the right (rear)
                    for(j=q->rear+1; j>i; j--)
                        {
                            q->data[j]=q->data[j-1];
                        }
                    q->data[i]=p;//insert it right to ith process
                    return;
                }
        }
    q->data[i]=p;
}
void executeByPriority(queue *q)//executes the highest priority process
{
    if(isEmpty1(*q))
        {

            printf("no elements to delete the queue is empty");
            return;
        }

    { double x=(double)q->data[q->rear].timeex/100;

        printf("the process of id (%d) is executed successfully \n",q->data[q->rear].id);
        q->rear--;//shift the rear back
        Sleep(x);//simulate the execution time
        if(q->rear==1)
            q->front=0;
        return;
    }

}

void displayall(queue q )
{
    int i;
    for(i=1; i<=q.rear; i++)
        {
            displayProcess(q.data[i]);
        }
}
void displayAll2(queue q,int x)
{
    int i=x,j,cou=x;
    if(x<=q.rear)
        {

            printf("the process having priority %d are:\n",q.data[i].priority);
            for(j=i; j<=q.rear; j++)
                {
                    if(q.data[j].priority==q.data[i].priority)
                        {
                            displayProcess(q.data[j]);
                            cou++;
                        }

                }
            displayAll2(q,cou);

        }

    else
        {
            return;
        }

}
void insertAll(queue *q)
{
    process p;
    //open the file and insert all the processes in the file
    FILE *fn;
    fn = fopen("Proccesses.txt","r");
    while(fscanf(fn,"%d %d %d",&p.id,&p.priority,&p.timeex)==3)
        {
            insertProcess1(q,p);
        }
    fclose(fn);
}
void executeAll(queue* q)
{
    //executes all the processes by priority
    int x=q->rear;

    for(int i=1; i<=x; i++)
        {
            executeByPriority(q);
        }
}


void displayAllArray(queue q)
{
    displayAll2(q,1);
}
double waiting1(queue q)
{
    double sum=0.0,ext=0.0;
    for(int i=100002;i>=1;i--)
    {
        sum+=ext+10592-(q.data[i].id*0.10592);
        ext+=q.data[i].timeex;

    }
    return sum/100000;
}
double turnarround1(queue q)
{
    double sum=0.0,ext=0.0;
    for(int i=100002;i>=1;i--)
    {
        sum+=(ext+10592+q.data[i].timeex)-(q.data[i].id*0.10592);
        ext+=q.data[i].timeex;
    }
    return sum/100000;
}


int main2()
{
    queue q;
    q=init();
   clock_t t;
    t = clock();
    insertAll(&q);
    t=clock()-t;
    printf("\n\n");


    double time_taken=((double)t/CLOCKS_PER_SEC);
 //  double w=waiting1(q);
    double r=turnarround1(q);

    clock_t t1;
    t1=clock();
    executeAll(&q);
    t1=clock()-t1;
    double time_taken1=((double)t1/CLOCKS_PER_SEC);
    printf("*~*~*~*~*~*~*~*~ Inserting all processes took %f seconds to execute. \n\n", time_taken);
   // printf("the average waiting time is %f \n",w);
    printf("the average turnarround time  is %f \n",r);
    printf("*~*~*~*~*~*~*~*~ Executing  all processes took %f seconds to execute. \n\n", time_taken1*100);
    printf("*~*~*~*~*~*~*~*~ The average time to execute a processes is %f milliseconds. \n\n",time_taken1*100/100000);
    return 1;
}
//Inserting all processes took 10.592 seconds to execute.
//The average time to insert a processes is 0.10592 milliseconds.
//the average waiting time is 24716519.141100 ms =6.865699761416 hours
//the average turnarround time is 24717013.828500 ms =6.865837174583 hours
//the time to execute all processes  is : 54168.8 seconds =15.0468 hours.
//The average time to execute(delete) a processes is 541.688 milliseconds.

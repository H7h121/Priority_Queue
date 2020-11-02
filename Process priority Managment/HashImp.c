#ifdef _WIN32
#include <time.h>
#include <Windows.h>
#else
#include <unistd.h>

#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#define SIZE 2009


typedef struct

{
    int id;
    int priority;
    int timeex;
} process;


typedef process element;
typedef struct node
{
    element e;
    struct node *next;
} node;
typedef struct list
{
    node *head;
    node *tail;
    int size;
} list;
typedef struct data
{
    list* li;
} data;



int isEmpty(list l)//checks if a list is empty
{
    return l.size==0;
}

int size(list l)//returns the size of a list
{
    return l.size;
}

void insertTail(list *l,element e)//inserts an element at the end of the list
{
    node *n;
    n=(node *)malloc(sizeof(node));
    n->e=e;
    n->next=NULL;
    if(isEmpty(*l))
        l->head=l->tail=n;
    else
        {
            l->tail->next=n;
            l->tail=n;
        }
    (l->size)++;
}

int removeHead(list *l)
{
    if(isEmpty(*l))
        return 0;
    else if(size(*l)==1)
        {
            node *temp;
            temp=l->head;
            l->head=l->tail=NULL;
            free(temp);
            (l->size)--;
            return 1;
        }
    else
        {
            node *temp;
            temp=l->head;
            l->head=l->head->next;
            free(temp);
            (l->size)--;
            return 1;
        }
}

void displayLL(list l)//displays the linked list component
{
    node *current=l.head;
    if(l.head==NULL)
        {
            printf("List is empty\n");
            return;
        }
    printf("");
    while(current != NULL)
        {
            //Prints each node by incrementing pointer
            printf("%d ", current->e.id);
            current = current->next;
        }
    printf("\n");

}


int hashCode(process key)//creates the hash code of each process
{
    return key.priority % SIZE;
}
data* createHashTable()//creates an empty hashTable
{
    int i;
    data *array = (struct data*) malloc(SIZE * sizeof(struct data));

    for (i = 0; i < SIZE; i++)
        {
            list *l=(list*)malloc(sizeof(list));
            l->head=NULL;
            l->tail=NULL;
            l->size=0;
            array[i].li=l;

        }
    return array;

}
data* insert(data* hashArray1,process key)//inserts a process respecting the priority
{
    data* b=hashArray1;
    int hashIndex = hashCode(key);//gets the hash key


    insertTail(b[hashIndex+1].li,key);//insert the process in the list at its hash key index +1


    return b;
}


data* executeHighestpriority1(data* a)//executes the highest priority process
{
    data* b=a;
    //create empty list
    list* l=(list*)malloc(sizeof(list));
    l->head=NULL;
    l->tail=NULL;
    l->size=0;
    int i=0,j;

    while(isEmpty(*a[i].li))//search for first non empty list in hash table
        {

            i++;
        }
    j=i;
    l=b[j].li;
    double x=(((double)b[j].li->head->e.timeex)/1000);//gets the sleep time

    printf("the process of id = %d executed successfully\n",l->head->e.id);
    removeHead(l);//remove it from the list


    //attach the list of executed process and complete the hash table b same as in a
    for(i=0; i<SIZE; i++)
        {
            if(i==j)
                {
                    b[j].li=l;
                }
            else
                b[i].li=a[i].li;
        }
        Sleep(x);//sleep the execution time



    return b;


}
void displayProcesses(data *a)//displays all the process from highest to lowest according to their arrival order
{
    for(int i=0; i<SIZE; i++)
        {
            if(!isEmpty(*a[i].li))
                {
                    printf("the waiting processes having priority %d are :",i);
                    displayLL(*a[i].li);
                }
            else
                printf("");
        }
}
double waiting(data *a)
{
    data* b=a;
    double sum=0.0,ext=0.0;
    for(int i=1;i<=2007;i++)
    {

        if(!isEmpty(*b[i].li)&&(b[i].li->head->next!=NULL))
        {
            sum+=ext+37-(b[i].li->head->e.id*0.000370);
            ext+=b[i].li->head->e.timeex;
            b[i].li->head=b[i].li->head->next;

        }
    }
    return sum/100000;
}
double turnarround(data *a)
{
    data* b=a;
    double sum=0.0,ext=0.0;
    for(int i=1;i<=2007;i++)
    {

        if(!isEmpty(*b[i].li)&&(b[i].li->head->next!=NULL))
        {
            sum+=b[i].li->head->e.timeex+ext+37-(b[i].li->head->e.id*0.000370);
            ext+=b[i].li->head->e.timeex;
            b[i].li->head=b[i].li->head->next;

        }
    }
    return sum/100000;
}
int main1()
{
    int x=0,y=0;
    data *a=createHashTable();//create empty hash table

    process p;
    //open the file and read the processes
    FILE *fn;
    fn = fopen("Proccesses.txt","r");
    clock_t t;
    t = clock();//time before the insert
    while(fscanf(fn,"%d %d %d",&p.id,&p.priority,&p.timeex)==3)
        {
            a=insert(a,p);
            x++;

        }
    t=clock()-t;//time after the insert
    double time_taken=((double)t/CLOCKS_PER_SEC);
    //double w=waiting(a);
    //double r=turnarround(a);

    clock_t t1;
    t1 = clock();//time before the execution
    //execute all processes
    for(int i=0; i<x; i++)
        {
            a=executeHighestpriority1(a);
            y++;
        }
    t1=clock()-t1;//time after the execution
    double time_taken1=((double)t1/CLOCKS_PER_SEC);


    printf("*~*~*~*~*~*~*~*~ Inserting all processes took %f seconds to execute. \n\n", time_taken);
    printf("*~*~*~*~*~*~*~*~ The average time to insert a processes is %f milliseconds. \n\n", time_taken*1000/x);
   // printf("the average waiting time is %f \n",w);
   // printf("the average turnarround time  is %f \n",r);
    printf("*~*~*~*~*~*~*~*~ Executing  all processes took %f seconds . \n\n", time_taken1*100);
    printf("*~*~*~*~*~*~*~*~ The average time to execute a processes is %f milliseconds. \n\n",time_taken1*1000/x);
    printf("y is %d \n",y);
    printf("x is %d",x);
    return 1;
}
//Inserting all processes took 37 milliseconds to execute.
//The average time to insert a processes is 0.000370 milliseconds.
//the time to execute all processes  is : 53261.7 seconds =14.794916 hours.
//The average time to execute(delete) a processes is 532.6170 milliseconds.


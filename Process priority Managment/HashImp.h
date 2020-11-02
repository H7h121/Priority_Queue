#ifndef HASHIMP_H_INCLUDED
#define HASHIMP_H_INCLUDED



#endif // HASHIMP_H_INCLUDED
#include<stdlib.h>
#include<stdio.h>

typedef struct

 {
     int id;
     int priority;
     int timeex;
     }process;


typedef process element;
typedef struct node{
                    element e;
                    struct node *next;
                   }node;
typedef struct list{
	                 node *head;
	                 node *tail;
	                 int size;}list;
typedef struct data
{
    list* li;
}data;
int isEmpty(list l);
int size(list l);
void insertTail(list *l,element e);
int removeHead(list *l);
void displayLL(list l);
int hashCode(process key);
data* createHashTable();
data* insert(data* hashArray1,process key);
data* executeHighestpriority1(data* a);
void displayProcesses(data *a);














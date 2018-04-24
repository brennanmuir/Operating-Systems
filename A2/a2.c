/*
* Brennan Muir
* CS 4540 Operating Systems
* A2: Scheduling Assignment
*
* C Program to Implement Priority Queue to Add and Delete Processes
* Credits to Sanfoundry Technology Education Blog
* www.sanfoundry.com/c-program-priority-queue/
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

typedef struct process process;
struct process
{
	char *name;					//name of process
	int startPriority;			//reset current priority to this each time process moved into wait queue, does not change
	int currentPriority;		//may change with aging
	int timeInCPUBetweenIO;		//A  set once
	int timeOfIO;				//B  set once
	int timeInMachine;			//C  sum of timeInCPUBetweenIO and timeOfIO
	int timeInCPUCurrently;		//D  set to 0 when moved into CPU
	int timeLeft;				//E  time left waiting for current IO
	int timeInQueue;			//F  time process has been waiting in ready queue
	int timeInCPU;				//G  total time in CPU
	int timeInIO;				//H  total time in IO
	int timeInReadyQueue;		//I  total time in ready queue
	int timeInReadyQueueMin;	//J  smallest time in ready queue
	int timeInReadyQueueMax;	//K  longest time in ready queue

};
struct timespec start, end;

void addProcessToQueue(int);
void deleteProcessFromQueue(int);
void create();
void check(int);
void displayQueue();

int pQueue[MAX];
int front, rear;


void main()
{
    int n, ch;

    printf("\n1 - Add a process to the queue");
    printf("\n2 - Delete a process from the queue");
    printf("\n3 - Display the queue");
    printf("\n4 - Exit");

    create();

    while(1){
        printf("\nEnter your choice : ");
        scanf("%d", &ch);
     	clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        switch(ch){
        case 1:
            printf("\nEnter value to be inserted : ");
            scanf("%d",&n);
            addProcessToQueue(n);
            break;
        case 2:
            printf("\nEnter value to delete : ");
            scanf("%d",&n);
            deleteProcessFromQueue(n);
            break;
        case 3:
            displayQueue();
            break;
        case 4:
            exit(0);
        default:
            printf("\nChoice is incorrect, Enter a correct choice");
        }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    int delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    int delta_ms = delta_us / 1000;
    printf("\nProcess took %d milliseconds to run.\n", delta_ms);
    }
}

/* Function to create an empty priority queue */
void create()
{
    front = rear = -1;
}

/* Function to insert process into priority queue */
void addProcessToQueue(int data){
    if(rear >= MAX - 1){
        printf("\nQueue overflow no more elements can be inserted");
        return;
    }
    if((front == -1) && (rear == -1)){
        front++;
        rear++;
        pQueue[rear] = data;
        return;
    }else{
        check(data);
    }
    rear++;
}

/* Function to check priority and place element */
void check(int data){
    int i,j;

    for(i = 0; i <= rear; i++){
        if(data >= pQueue[i]){
            for(j = rear + 1; j > i; j--){
                pQueue[j] = pQueue[j - 1];
            }
            pQueue[i] = data;
            return;
        }
    }
    pQueue[i] = data;
}

/* Function to delete an element from queue */
void deleteProcessFromQueue(int data){
    int i;

    if((front==-1) && (rear==-1)){
        printf("\nQueue is empty no elements to delete");
        return;
    }

    for(i = 0; i <= rear; i++){
        if(data == pQueue[i]){
            for(; i < rear; i++){
                pQueue[i] = pQueue[i + 1];
            }

        pQueue[i] = -99;
        rear--;

        if(rear == -1){
            front = -1;
        }
        return;
        }
    }
    printf("\n%d not found in queue to delete", data);
}

/* Function to display queue elements */
void displayQueue(){
    if((front == -1) && (rear == -1)){
        printf("\nQueue is empty");
        return;
    }

    for(; front <= rear; front++){
        printf(" %d ", pQueue[front]);
    }

    front = 0;
}

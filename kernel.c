#include<stdio.h>
#include<stdlib.h>
#include"shell.h"
#include"pcb.h"
#include"ram.h"
#include"cpu.h"
#include"interpreter.h"

/*
This is a node in the Ready Queue implemented as 
a linked list.
A node holds a PCB pointer and a pointer to the next node.
PCB: PCB
next: next node
*/
typedef struct ReadyQueueNode {
    PCB*  PCB;
    struct ReadyQueueNode* next;
} ReadyQueueNode;

ReadyQueueNode* head = NULL;
ReadyQueueNode* tail = NULL;
int sizeOfQueue = 0;

void boot()
{
    for (int i = 0; i < 40; i++)
    {
        ram[i] = NULL;
    }

    system("rm -r BackingStore");
    system("mkdir BackingStore");
}

int kernel()
{
    shellUI();
    return 0;
}

/*
Adds a pcb to the tail of the linked list
*/
void addToReady(struct PCB* pcb) {
    ReadyQueueNode* newNode = (ReadyQueueNode *)malloc(sizeof(ReadyQueueNode));
    newNode->PCB = pcb;
    newNode->next = NULL;
    if (head == NULL){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    sizeOfQueue++;
}

/*
Returns the size of the queue
*/
int size(){
    return sizeOfQueue;
}

/*
Pops the pcb at the head of the linked list.
pop will cause an error if linkedlist is empty.
Always check size of queue using size()
*/
struct PCB* pop(){
    PCB* topNode = head->PCB;
    ReadyQueueNode * temp = head;
    if (head == tail){
        head = NULL;
        tail = NULL;
    } else {
        head = head->next;
    }
    free(temp);
    sizeOfQueue--;
    return topNode;
}

/*
Passes a filename
Opens the file, copies the content in the RAM.
Creates a PCB for that program.
Adds the PCB on the ready queue.
Return an errorCode:
ERRORCODE 0 : NO ERROR
ERRORCODE -3 : SCRIPT NOT FOUND
ERRORCODE -5 : NOT ENOUGH RAM (EXEC)
*/
int myinit(char* filename){
    // Open the filename to get FILE *
    // call addToRam on that File *
    // If error (check via start/end variable), return that error
    // Else create pcb using MakePCB
    // Then add it to the ReadyQueue
    FILE * fp = fopen(filename,"r");
    if (fp == NULL) return -3;
    int start;
    int end;
    addToRAM(fp,&start,&end);
    fclose(fp);
    if (start == -1) return -5;
    PCB *pcb = makePCB(fp);
    addToReady(pcb);
    return 0;
}

int scheduler()
{
    // set CPU quanta to default, IP to -1, IR = NULL
    CPU.quanta = DEFAULT_QUANTA;
    CPU.IP = -1;
    while (size() != 0){
        //printf("we got here");
        //pop head of queue
        PCB* pcb = pop();
        //copy PC of PCB to IP of CPU
        CPU.IP = pcb->PC;

        //int isOver = FALSE;
        //int remaining = (pcb->pages_max) - (pcb->PC) + 1;
        //printf("\n%d", remaining);
        int quanta = DEFAULT_QUANTA;
        /*
        if (DEFAULT_QUANTA >= remaining) {
            isOver = TRUE;
            quanta = remaining;
        }
        */
        //int errorCode = run(quanta);
        /*
        if ( errorCode!=0 || isOver ){
            newremoveFromRam(pcb->PC);
            free(pcb);
        } else {
            pcb->PC += DEFAULT_QUANTA;
            addToReady(pcb);
        }*/
    }
    // reset RAM
    resetRAM();
    return 0;
}

/*
Flushes every pcb off the ready queue in the case of a load error
*/
void emptyReadyQueue()
{
    while (head != NULL){
        ReadyQueueNode * temp = head;
        head = head->next;
        free(temp->PCB);
        free(temp);
    }
    sizeOfQueue = 0;
}


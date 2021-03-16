#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "kernel.h"
#include "shell.h"
#include "memorymanager.h"
#include "ram.h"

int fileCount = 0;

int countTotalPages (FILE *f)
{
    rewind(f);
    int lineCount = 0; int page = 0;
    char c = getc(f);
    while (c != EOF)
    {
        if (c == '\n')
        {
            lineCount++;
        }
        c = getc(f);
    }
    if (lineCount % 4 == 0){
        page = (lineCount/4);
    }
    else {
        page = ((lineCount/4) + 1);
    }
    return page;
}

void loadPage(int pageNumber, FILE *f, int frameNumber)
{
    rewind(f);
    int start = frameNumber;
    int end = pageNumber + 3;

    while (start < end){
        if (feof(f)){
            break;
        }
        char *space = NULL;
        size_t space_size;
        getline(&space, &space_size, f);
        ram[start] = strdup(space);
        start++;
    }
}

int findFrame()
{
    for (int i = 0; i < 40; i++)
    {
        if (ram[i] == NULL && ram[i+1] == NULL && ram[i+2] == NULL && ram[i+3] == NULL)
        {
            return i;
        }
    }
    return -1;
}

int findVictim(PCB *p)
{
    int rFrameNumber = rand() % 10;
    for (int i = 0; i < 10; i++)
    {
        if (p->pageTable[i] == rFrameNumber)
        {
            rFrameNumber++;
            rFrameNumber = rFrameNumber % 10;
            i = 0;
        }
    }
    int freeIndex = rFrameNumber*4;
    ram[freeIndex] = NULL;
    ram[freeIndex+1] = NULL;
    ram[freeIndex+2] = NULL;
    ram[freeIndex+3] = NULL;
    return rFrameNumber;
}

int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame)
{
    if (frameNumber == -1) {
        p->pageTable[pageNumber] = victimFrame;
    }
    else {
        p->pageTable[pageNumber] = frameNumber;
    }
    return 1;
}

int launcher (FILE *p)
{
    int error = 0;
    char bStore[25];
    sprintf(bStore, "BackingStore/00%d.txt", fileCount);
    FILE *location = fopen(bStore, "w");
    char c = fgetc(p);
    while (c != EOF)
    {
        fputc(c, location);
        c = fgetc(p);
    }
    fclose(p); fclose(location);
    location = fopen(bStore, "r");

    int pageTotal = countTotalPages(location);
    PCB *currentPCB = makePCB(location);

    currentPCB->pages_max = pageTotal;
    addToReady(currentPCB);
    //printf("\ncurrent page total is: %d", pageTotal);
    //printf("%d",currentPCB->PC);

    for (int i = 0; i < pageTotal; i++)
    {
        int testVictim = findFrame();
        if (testVictim != 1)
        {
            int thisVictim = findVictim(p);
            loadPage(pageTotal, p, testVictim);
            updatePageTable(p, pageTotal, testVictim, thisVictim);
        }
        else{
            int thisVictim = findVictim(p);
            loadPage(pageTotal, p, thisVictim);
            updatePageTable(p, pageTotal, testVictim, thisVictim);
        }
    }

    fileCount++;
    return 1;
}
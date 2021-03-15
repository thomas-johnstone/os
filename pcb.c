#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "memorymanager.h"
/*
PCB has 3 fields
PC : Points to the the current line reached for that program
start: Points to first line of that program
end: Points to last line of that program

typedef struct PCB
{
    int PC;
    int start;
    int end;
}PCB;
*/

/*
Passes 2 parameters (start , end)
This method creates a PCB with fields set as this:
PC = start
start = start
end = end


 */

PCB *makePCB(FILE *f){
    PCB *pcb = (PCB*) malloc(sizeof(PCB));
    pcb->PC = f;
    pcb->PC_page = 0;
    pcb->PC_offset = 0;
    pcb->pages_max = countTotalPages(f);
    return pcb;
}



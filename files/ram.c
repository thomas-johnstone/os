#include<stdio.h>
#include<string.h>
/*
Stores the index of the next available block of cell
*/
int nextFree = 0;

/*
Ram structure implemented as an array.
Size is 40 strings
*/
char *ram[40];

/*
This function will delete the content in ram between the 2 indices parameters (inclusive)
start : pointer to variable which will store the index of first line of file in ram
end : pointer to variable which will store the index of last line of file in ram
*/
void removeFromRam (int start, int end){
    for (int i = start; i <= end; i++)
    {
        ram[i] = NULL;
    }
}

void newremoveFromRam (int i)
{
    for (int i = 0; i < 10; i++)
    {
        ram[i] = NULL;
    }
}

/*
This function will add the content of a file to the local ram array variable
In the case of an error (due to lack of RAM), -1 will be assigned to
the values pointed by start and end. Use this to check for errors.
p : file pointer
start : pointer to variable which will store the index of first line of file in ram
end : pointer to variable which will store the index of last line of file in ram
*/
void addToRAM (FILE *p, int *start, int *end){
    *start = nextFree;
    int i = *start;
    char buffer[40];
    // Copy content of the file while
    // we have not reached the end of the file
    // and RAM is not full yet.
    while (!feof(p) && i < 40){
        fgets(buffer,39,p);
        ram[i] = strdup(buffer);
        i++;
    }
    // If RAM is full and we have not reached the end of the 
    // file, remove the content from RAM and return -1 in *start,*end
    // Update nextFree as well
    
    if (i >= 40 && !feof(p)){
        removeFromRam(0,i - 1);
        nextFree = 0;
        *start = -1;
        *end = -1;        
    // Else update the nextFree spot and *end
    } else {
        nextFree = i;
        *end = i - 1;
    }
}

/*
Reset the pointer to the free cell back to index 0
*/
void resetRAM(){
    nextFree = 0;
}



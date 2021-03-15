#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct MEM {
    char* var;
    char* value;
} environmentVars[25];

//restricts number of environment variables to 25
int memorySize = 25;

// This global variable stores the index of the last stored variable. Set to 0 at first. Its limit is the memory size
int lastVarIndex= 0;

/*
This function passes the name of a variable.
It will search the array of environment variables for an exact variable name match.
If found, it returns the index of the matched variable. 
If not found, it returns -1
*/
int findVariable(char * varName) {
    for (int i = 0; i<lastVarIndex; i++){
        if ( strcmp(environmentVars[i].var,varName) == 0 ){
            return i;
        }
    }
    return -1;
}

/*
This functions takes a variable name and a value and adds this set packaged in a MEM object at the end of
the shell memory array. It also increments the lastVarIndex global variable.
If running out of memory, return ERRORCODE: -1
*/
int addVariable (char *var, char* value){

    if (lastVarIndex == memorySize) return -1;
    environmentVars[lastVarIndex].var = var;
    environmentVars[lastVarIndex].value = value;
    lastVarIndex ++;
    return 0;
}

/*
This functions takes a variable name and value.
It assigns the value argument to the environment variable varName in the shell memory array.
Return ERRORCODE -1 if out of memory else 0
*/
int setVariable (char * varName, char * value) {
    //Find the position of the variable in the array
    int position = findVariable(varName);

    if (position == -1){
        //if the variable is not found, try add this variable to the memory
        return addVariable(varName, value);
    } else {
        //overwrite the value of the variable
        //strcpy( environmentVars[position].value , value) ;
        environmentVars[position].value = value;
    }

    return 0;
}

/*
This function passes a variable name.
The memory shell array is searched for that variable name.
If found, it return the value,
If not found, it return "NONE"
*/
char* getValue (char *var){
    int position = findVariable(var);
    if (position==-1) return "_NONE_";
    return environmentVars[position].value;
}

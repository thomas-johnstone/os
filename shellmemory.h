/*
This functions takes a variable name and value.
It assigns the value argument to the environment variable varName in the shell memory array.
Return ERRORCODE -1 if out of memory else 0
*/
int setVariable (char * varName, char * value);

/*
This function passes a variable name.
The memory shell array is searched for that variable name.
If found, it return the value,
If not found, it return "_NONE_"
*/
char* getValue (char *var);
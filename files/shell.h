/*
This functions passes an int errorCode and command string and display the 
appropriate error message for that errorCode
ERRORCODE -1 : RAN OUT OF SHELL MEMORY
ERRORCODE -2 : INCORRECT NUMBER OF ARGUMENTS
ERRORCODE -3 : SCRIPT NOT FOUND
ERRORCODE -4 : UNKNOWN COMMAND.
ERRORCODE -5 : NOT ENOUGH RAM (EXEC)
ERRORCODE -6 : SCRIPT <NAME> ALREADY LOADED (EXEC)
*/
void displayCode(int errorCode,char* command);

int parse(char ui[]);

int shellUI();


#define DEFAULT_QUANTA 2

struct CPU { 
    int IP; 
    char IR[1000]; 
    int quanta; 
} CPU;

int run(int);
cmake_minimum_required(VERSION 3.15)
project(osa3_wip C)

set(CMAKE_C_STANDARD 99)

add_executable(osa3_wip files/cpu.c files/cpu.h files/interpreter.c files/interpreter.h files/kernel.c files/kernel.h
        files/pcb.c files/pcb.h files/ram.c files/ram.h files/script1.txt files/script2.txt files/script3.txt files/shell.c files/shell.h
        files/shellmemory.c files/shellmemory.h files/TESTFILE.txt files/memorymanager.c files/memorymanager.h files/main.c)
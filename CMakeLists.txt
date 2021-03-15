cmake_minimum_required(VERSION 3.15)
project(osa3_wip C)

set(CMAKE_C_STANDARD 99)

add_executable(osa3_wip cpu.c cpu.h interpreter.c interpreter.h kernel.c kernel.h
        pcb.c pcb.h ram.c ram.h script1.txt script2.txt script3.txt shell.c shell.h
        shellmemory.c shellmemory.h TESTFILE.txt memorymanager.c memorymanager.h main.c)
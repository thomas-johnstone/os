#!/bin/bash

clear

gcc -c main.c shell.c interpreter.c shellmemory.c kernel.c cpu.c pcb.c ram.c shell.h interpreter.h shellmemory.h kernel.h cpu.h pcb.h ram.h memorymanager.c memorymanager.h

gcc -o mykernel main.o shell.o interpreter.o shellmemory.o kernel.o cpu.o pcb.o ram.o memorymanager.o
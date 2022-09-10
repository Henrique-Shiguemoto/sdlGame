CC=g++
COMPILER_FLAGS=-g -Wall -Werror -std=c++14
INCLUDE_FLAGS=-IC:\dev\SDL2\SDL2-2.0.22\include
LINKER_FLAGS=-LC:\dev\SDL2\SDL2-2.0.22\lib\x64\SDL2.lib -LC:\dev\SDL2\SDL2-2.0.22\lib\x64\SDL2main.lib
DEBUGGER=gdb

main: main.o
	$(CC) main.o $(COMPILER_FLAGS) -o main $(INCLUDE_FLAGS) $(LINKER_FLAGS)

main.o: main.cpp
	$(CC) -c main.cpp $(INCLUDE_FLAGS) $(LINKER_FLAGS)

debug: main
	$(DEBUGGER) main

run: main
	main

clean: 
	del *.o main *.pdb *.ilk
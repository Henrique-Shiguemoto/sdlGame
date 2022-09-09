CC=g++
BIN=main
OBJ=main.o
DEBUG_FLAGS= -Wall -Wextra -Werror -g -std=c++17
DEBUGGER=gdb

$(BIN): main.o
	$(CC) $(DEBUG_FLAGS) -o $(BIN) $(OBJ)

$(OBJ): main.cpp main.h
	$(CC) -c main.cpp

run: $(BIN)
	$(BIN)
	
debug: $(BIN)
	$(DEBUGGER) $(BIN)

clean: 
	del *.o *.exe
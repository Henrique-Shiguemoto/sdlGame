CC=g++
COMPILER_FLAGS=-g -Wall -Werror -std=c++14
INCLUDE_FLAGS=-Isrc/include
LINKER_FLAGS=-Lsrc/lib -lmingw32 -lSDL2main -lSDL2
BIN=main
OBJS=main.o GameConstants.o
SRC=main.cpp GameConstants.cpp
DEBUGGER=gdb

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(INCLUDE_FLAGS) $(LINKER_FLAGS)

main.o: $(SRC)
	$(CC) $(COMPILER_FLAGS) -c $(SRC) $(INCLUDE_FLAGS) $(LINKER_FLAGS)

GameConstants.o: GameConstants.cpp GameConstants.h
	$(CC) $(COMPILER_FLAGS) -c GameConstants.cpp

run: $(BIN)
	$(BIN)

debug: $(BIN)
	$(DEBUGGER) $(BIN)

clean:
	del *.o *.exe
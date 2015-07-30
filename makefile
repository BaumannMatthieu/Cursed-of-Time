CC	=g++
CFLAGS	=-Wall -std=c++11
LDFLAGS	=-LSFML-2.3/lib -lsfml-graphics -lsfml-window -lsfml-system
EXEC	= bin/Cursed_Crown
SRC	=$(wildcard src/*.cpp)
OBJ	=$(SRC:.cpp=.o)
INC	=$(SRC:.cpp=.hpp)
INL	=$(INC:.hpp=.inl)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)
	
%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

%.cpp: %.hpp

clean:
	rm -f src/*.o bin/*


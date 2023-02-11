CC=gcc
CFLAGS=-O2 -pedantic -Wall -Wextra
BIN=gauss2.0
SRCS=$(wildcard ./*.c)
OBJS=$(patsubst ./%.c, ./%.o, $(SRCS))
HEADERS=$(wildcard ./*.h*)

.PHONY: all test clean

test: all
	./$(BIN) example1.eq
	
all: $(BIN) $(HEADERS)

$(BIN): $(OBJS)
	g++ -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	g++ -c -o $@ $< $(CFLAGS)

clean: 
	rm -rf $(OBJS) $(BIN)

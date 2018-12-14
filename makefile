CC=g++
CFLAGS=-Wall -Werror
LIBS=-lpthread -lrt

HOST_SOURCE= host.cpp
CONN_SOURCES=$(shell find . -name "conn_*.cpp")
EXECUTABLES=$(CONN_SOURCES:./conn/conn_%.cpp=./host_%)

all: $(EXECUTABLES)
	
host_%: conn/conn_%.o $(HOST_SOURCE:.cpp=.o)
	$(CC) -o $@ $^ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f `find . -maxdepth 1 -executable -type f`

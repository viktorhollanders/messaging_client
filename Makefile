CXX = g++
CXXFLAGS = -Wall -std=c++11
CXXDEBUGFLAGS = -ggdb -fsanitize=address

SRC := src
INCLUDE := include
LIB     := lib
OBJECTS := obj
BIN     := bin
EXECUTABLE := $(BIN)/main

.PHONY : all client server clean
	
all: client server


$(OBJECTS)/%.o: $(SRC)/%.cpp
	@echo "Compiling $< ..."
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c $< -o $@


# link
client: $(OBJECTS)/client.o
	@echo "🔧 Building client..."
	$(CXX) $(CXXFLAGS) $^ -o $(BIN)/client

server: $(OBJECTS)/server.o
	@echo "🔧 Building server..."
	$(CXX) $(CXXFLAGS) $^ -o $(BIN)/server

clean:
	@echo "🧹 cleaning ..."
	-rm -f ./bin/*
	-rm -f ./obj/*

startServer:
	./$(BIN)/server

startClient:
	./$(BIN)/client

start: startServer startClient

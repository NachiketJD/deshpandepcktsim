# Makefile for deshpandepcktsim (Windows - MinGW)

CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC = src/main.cpp src/topology.cpp src/node.cpp
OUT = deshpandepcktsim.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	del $(OUT)

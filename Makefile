# Makefile for deshpandepcktsim (Windows - MinGW)

CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRCS = src/main.cpp src/ospf.cpp src/rip.cpp src/eigrp.cpp src/bgp.cpp
INCLUDES = -Iinclude

OUT = deshpandepcktsim.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	del $(OUT)

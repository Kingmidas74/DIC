SOURCES = ./src/Source.cpp
TARGET := ./build/
BASE_OPTIONS := -std=c++11 -qopenmp -O3 -vec-report=5

all:
	mkdir -p $(TARGET)
	icpc $(SOURCES) -o $(TARGET)dic.mic -mmic $(BASE_OPTIONS)
	icpc $(SOURCES) -o $(TARGET)dic $(BASE_OPTIONS)
	cp -a -n ./src/datasets/. $(TARGET)

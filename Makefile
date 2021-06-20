SOURCE_FOLDER	 := ./src
ENTRY_POINT	 := $(SOURCE_FOLDER)/Source.cpp
TARGET		 := ./build/
BASE_OPTIONS	 := -std=c++2a -fopenmp -g -O3 -I $(SOURCE_FOLDER)

all:
	mkdir -p $(TARGET)
	g++ $(ENTRY_POINT) -o $(TARGET)dic $(BASE_OPTIONS)
	cp -a -n $(SOURCE_FOLDER)/datasets/. $(TARGET)

SOURCE_FOLDER	 := ./src
ENTRY_POINT	 := $(SOURCE_FOLDER)/Source.cpp
TARGET		 := ./build/
BASE_OPTIONS	 := -std=c++11 -qopenmp -O3 -vec-report=5 -I $(SOURCE_FOLDER)

all:
	mkdir -p $(TARGET)
	icpc $(ENTRY_POINT) -o $(TARGET)dic.mic -mmic $(BASE_OPTIONS)
	icpc $(ENTRY_POINT) -o $(TARGET)dic $(BASE_OPTIONS)
	cp -a -n $(SOURCE_FOLDER)/datasets/. $(TARGET)

CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=main.cpp src/Parser.cpp src/File.cpp src/Errors.cpp src/Consts.cpp \
	src/BatteryPredict.cpp src/WeightedMeanPredict.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o src/*.o $(EXECUTABLE) 

test: all
	./$(EXECUTABLE)

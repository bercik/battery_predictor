CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=src/main.cpp src/Parser.cpp src/File.cpp src/Errors.cpp \
	src/Consts.cpp src/BatteryPredict.cpp src/WeightedMeanPredict.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=battery_predictor.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf src/*.o $(EXECUTABLE) 

test: all
	./$(EXECUTABLE)

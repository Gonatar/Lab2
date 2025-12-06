CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = program
SOURCES = main.cpp Worker.cpp WorkerControl.cpp Menu.cpp FileProcessor.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
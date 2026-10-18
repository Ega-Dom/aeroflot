CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET   = aeroflot
SOURCES  = main.cpp AEROFLOT.cpp FlightList.cpp TextProcessor.cpp Exceptions.cpp Input.cpp
OBJECTS  = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = 10kinds
SRC = 10kinds.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
SRC = src/main.cpp src/repository.cpp src/index.cpp src/object.cpp src/utils.cpp src/status.cpp src/restore.cpp src/delete.cpp src/diff.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = mygit

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

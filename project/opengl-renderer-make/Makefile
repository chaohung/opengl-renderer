PROGRAM = main

SRC_DIR = ../..

OBJ_DIR = ./build/objs

TARGET = ./build/$(PROGRAM)

SRCS = $(wildcard $(SRC_DIR)/src/*.cpp) $(wildcard ./*.cpp)

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

INCLUDE_DIR =\
-I$(SRC_DIR)/src\
-I/usr/local/include\
-I/usr/local/include/eigen3\

LIB_DIR =\
-L$(SRC_DIR)/src\
-L/usr/local/lib\

CXXFLAGS = -std=gnu++11

LDFLAGS = -lglfw3 -framework OpenGL -framework Cocoa -framework CoreVideo -framework IOKit

CXX = g++

all : $(TARGET)

$(TARGET) : $(OBJ_DIR) $(OBJS)
	$(CXX) $(LIB_DIR) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/%.o : ./%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/hsu-atlas-tree/src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJS)

.PHONY: all clean
.SUFFIXES: .cpp .o

PROGRAM = main

SRC_DIR = ../../src

OBJ_DIR = ./build/objs

TARGET = ./build/$(PROGRAM)

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/../atlas-tree/src/*.cpp)

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

DEPS = $(OBJS:.o=.d)

INCLUDE_DIR =\
-I$(SRC_DIR)/../atlas-tree/src\
-I$(SRC_DIR)\
-I/usr/local/include\
-I/usr/local/include/eigen3\

LIB_DIR =\
-L/usr/local/lib\

CXXFLAGS = -std=gnu++11

LDFLAGS = -lglfw3 -framework OpenGL -framework Cocoa -framework CoreVideo -framework IOKit

CXX = g++

all : $(TARGET)

-include $(DEPS)

$(TARGET) : $(OBJ_DIR) $(OBJS) ./main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ $(LDFLAGS) $(LIB_DIR) $(OBJS) ./main.cpp

$(OBJ_DIR)/%.o : $(SRC_DIR)/../atlas-tree/src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c -MMD $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c -MMD $< -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJS)

.PHONY: all clean
.SUFFIXES: .cpp .o

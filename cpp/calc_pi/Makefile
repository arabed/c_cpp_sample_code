DEBUG_MODE = yes
EXECUTABLE_NAME = main
EXECUTABLE_DIR = ./bin

CXX_STANDARD = c++17
CXX_WARNINGS = -Wall -Wextra -Wpedantic
CXX = g++
CXXFLAGS = $(CXX_WARNINGS) -std=$(CXX_STANDARD) -I./include
LDFLAGS =

ifeq ($(DEBUG_MODE), yes)
	CXXFLAGS += -g -O0
	CXXFLAGS += -DDEBUG_BUILD
else
	CXXFLAGS += -O3
endif

CXX_COMPILER_CALL = $(CXX) $(CXXFLAGS) $(CPPFLAGS)

CXX_SOURCES_DIR = ./src
CXX_OBJECTS_DIR = ./.objs
CXX_SOURCES = $(wildcard $(CXX_SOURCES_DIR)/*.cpp)
CXX_OBJECTS = $(patsubst $(CXX_SOURCES_DIR)/%.cpp, $(CXX_OBJECTS_DIR)/%.o, $(CXX_SOURCES))

all: prepare build

rebuild: clean prepare build

prepare:
	mkdir -p $(CXX_OBJECTS_DIR)
	mkdir -p $(EXECUTABLE_DIR)

build: $(CXX_OBJECTS)
	$(info "CXX_SOURCES:$(CXX_SOURCES)")
	$(info "CXX_OBJECTS:$(CXX_OBJECTS)")
	$(CXX_COMPILER_CALL) $(CXX_OBJECTS) $(LDFLAGS) -o $(EXECUTABLE_DIR)/$(EXECUTABLE_NAME)

execute:
	./main

clean:
	rm -f $(CXX_OBJECTS_DIR)/*
	rm -df $(CXX_OBJECTS_DIR)
	rm -f $(EXECUTABLE_DIR)/*
	rm -df $(EXECUTABLE_DIR)

##############
## PATTERNS ##
##############
# $@: the file name of the target
# $<: the name of the first dependency
# $^: the names of all prerequisites
$(CXX_OBJECTS_DIR)/%.o: $(CXX_SOURCES)
	$(CXX_COMPILER_CALL) -c $< -o $@

.PHONY: rebuild clean prepare build

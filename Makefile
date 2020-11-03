EXE = main
OBJ_DIR = obj

SOURCES = $(wildcard src/*.cpp)

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))

CXXFLAGS = -std=c++17 -I./include -Wall -O2

LIBS =

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: create_object_directory $(EXE)
	@echo Compile Success

create_object_directory:
	mkdir -p $(OBJ_DIR)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(EXE) $(OBJ_DIR)

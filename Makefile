EXE = dijkstra_series
OBJ_DIR = obj

SOURCES = src/Graph.cpp src/Timer.cpp

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
OBJS_SERIES = $(OBJS) $(OBJ_DIR)/dijkstra_series.o

CXXFLAGS = -std=c++17 -I./include -Wall -O2

LIBS =

all: create_object_directory $(EXE)
	@echo Compile Success

create_object_directory:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

dijkstra_series: $(OBJS_SERIES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(EXE) $(OBJ_DIR)

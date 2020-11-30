EXE = dijkstra_series dijkstra_boost
OBJ_DIR = obj

SOURCES = src/Graph.cpp

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
OBJS_SERIES = $(OBJS) $(OBJ_DIR)/dijkstra_series.o
OBJS_BOOST = $(OBJS) $(OBJ_DIR)/dijkstra_boost.o

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

dijkstra_boost: $(OBJS_BOOST)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(EXE) $(OBJ_DIR)

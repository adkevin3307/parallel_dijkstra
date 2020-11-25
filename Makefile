EXE = dijkstra_series
OBJ_DIR = obj

series_SOURCES = src/dijkstra_series.cpp $(common)

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(series_SOURCES)))))

CXXFLAGS = -std=c++17 -I./include -Wall -O2 -fopenmp -g
LIBS = 

common = $(OBJ_DIR)/Graph.o
openMP_obj = $(OBJ_DIR)/dijkstra_openMP.o $(common)

all: create_object_directory $(EXE)
	@echo Compile Success

openMP: $(openMP_obj)
	$(CXX) $(CXXFLAGS) -o $@ $^  

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

create_object_directory:
	mkdir -p $(OBJ_DIR)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(EXE) $(OBJ_DIR)/* openMP

runOpenMP:
	./openMP ./Data/USA-road-d.NY.txt

runSerial:
	./dijkstra_series ./Data/USA-road-d.NY.txt

EXE = dijkstra_series
OBJ_DIR = obj

series_SOURCES = src/dijkstra_series.cpp $(common)

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(series_SOURCES)))))

CXXFLAGS = -std=c++17 -I./include -Wall  -fopenmp 
LIBS = 

common = obj/Graph.o
openMP_obj = obj/dijkstra_openMP.o $(common)
openCL_obj = obj/dijkstra_openCL.o $(common)
openCL_FLAGS = -lOpenCL

openMP:$(openMP_obj)
	$(CXX) $(CXXFLAGS) -o $@ $^

openCL:$(openCL_obj)
	$(CXX) $(CXXFLAGS) -o $@ $^	$(openCL_FLAGS) -g


$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -g

allOpenCL: clean openCL


all: create_object_directory $(EXE)
	@echo Compile Success

create_object_directory:
	mkdir -p $(OBJ_DIR)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(EXE) $(OBJ_DIR)/* openCL || true

runOpenMP:
	./openMP ./Data/USA-road-d.NY.txt

runSerial:
	./dijkstra_series ./Data/USA-road-d.NY.txt
runOpenCL:
	./openCL ./Data/USA-road-d.NY.txt
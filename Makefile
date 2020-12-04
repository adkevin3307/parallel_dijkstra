EXE = dijkstra_serial dijkstra_boost dijkstra_openmp dijkstra_thread dijkstra_pthread
OBJ_DIR = obj

SOURCES = src/Graph.cpp src/Timer.cpp

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
OBJS_SERIAL = $(OBJS) $(OBJ_DIR)/dijkstra_serial.o
OBJS_BOOST = $(OBJS) $(OBJ_DIR)/dijkstra_boost.o
OBJS_OPENMP = $(OBJS) $(OBJ_DIR)/dijkstra_openmp.o
OBJS_THREAD = $(OBJS) $(OBJ_DIR)/dijkstra_thread.o
OBJS_PTHREAD = $(OBJS) $(OBJ_DIR)/dijkstra_pthread.o

CXXFLAGS = -std=c++17 -I./include -Wall -O2 -g -fopenmp

LIBS =

all: create_object_directory $(EXE)
	@echo Compile Success

create_object_directory:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

dijkstra_serial: $(OBJS_SERIAL)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

dijkstra_boost: $(OBJS_BOOST)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

dijkstra_openmp: $(OBJS_OPENMP)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

dijkstra_thread: $(OBJS_THREAD)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

dijkstra_pthread: $(OBJS_PTHREAD)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(EXE) $(OBJ_DIR)

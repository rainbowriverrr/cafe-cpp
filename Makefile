# VARIABLES

FLAGS = -std=c++17 -I src/data
LIBS = -lsqlite3 -lwt -lwthttp
OBJ = target/data/DBHelper.o target/data/SqlCondition.o target/data/MenuItem.o
MKDIR_P = @ mkdir -p $(@D)

# EXECUTABLES

TestDBHelper.out: $(OBJ) target/tests/TestDBHelper.o
	g++ $(FLAGS) $(LIBS) $(OBJ) target/tests/TestDBHelper.o -o $@

# OBJECTS

# tests
target/tests/TestDBHelper.o: src/tests/TestDBHelper.cpp
	$(MKDIR_P)
	g++ $(FLAGS) -c src/tests/TestDBHelper.cpp -o $@

# data
target/data/DBHelper.o: src/data/DBHelper.cpp src/data/DBHelper.hpp
	$(MKDIR_P)
	g++ $(FLAGS) -c src/data/DBHelper.cpp -o $@
target/data/SqlCondition.o: src/data/SqlCondition.cpp src/data/SqlCondition.hpp
	$(MKDIR_P)
	g++ $(FLAGS) -c src/data/SqlCondition.cpp -o $@
target/data/MenuItem.o: src/data/MenuItem.cpp src/data/MenuItem.hpp src/data/Model.hpp
	$(MKDIR_P)
	g++ $(FLAGS) -c src/data/MenuItem.cpp -o $@

# PHONY

cleanout:
	rm -rf *.out

cleanobj:
	rm -rf target

clean:
	rm -f *.out
	rm -rf target


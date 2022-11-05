# VARIABLES

CXX = g++
CXXFLAGS = -std=c++17 -I src/data
LDLIBS = -lsqlite3 -lwt -lwthttp
OBJ = target/data/DBHelper.o target/data/SqlCondition.o target/data/MenuItem.o
MKDIR_P = @ mkdir -p $(@D)

# EXECUTABLES

TestDBHelper.out: $(OBJ) target/tests/TestDBHelper.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

# OBJECTS

target/%.o: src/%.cpp
	$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(wildcard target/**/*.d)

# PHONY

.PHONY: clean cleanout cleanobj cleandb

clean: cleanout cleanobj

cleanout:
	rm -rf *.out

cleanobj:
	rm -rf target

cleandb:
	rm -i resources/data.db

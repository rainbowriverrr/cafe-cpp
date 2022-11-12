# VARIABLES

CXX = g++
CXXFLAGS = -std=c++17 -I src/data -I src/web
LDLIBS = -lsqlite3 -lwt -lwthttp

_MAIN = Main.cpp
MAIN = $(subst src/,target/,$(subst .cpp,.o,$(wildcard src/*/$(_MAIN))))
TESTS = $(subst src/,target/,$(subst .cpp,.o,$(wildcard src/tests/*.cpp)))
OBJ = $(subst src/,target/,$(subst .cpp,.o,$(wildcard src/*/*.cpp)))

MKDIR_P = @ mkdir -p $(@D)

.SECONDARY: $(OBJ)

.PHONY: clean cleanout cleanobj cleandb dbtables dbtestdata

# EXECUTABLES

main: $(basename $(notdir $(MAIN)))

$(basename $(notdir $(MAIN))): $(filter-out $(TESTS),$(OBJ))
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)
	@ $(MAKE) dbtestdata

tests: $(basename $(notdir $(TESTS)))

%: $(filter-out $(MAIN) $(TESTS),$(OBJ)) target/tests/%.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)
	@ $(MAKE) dbtables

# OBJECTS

target/%.o: src/%.cpp
	$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(wildcard target/*/*.d)

# PHONY

dbtables: cleandb
	sqlite3 resources/data.db < tables.sql

dbtestdata: dbtables
	sqlite3 resources/data.db < test_data.sql

clean: cleanout cleanobj cleandb

cleanout:
	rm -f $(basename $(notdir $(MAIN) $(TESTS)))

cleanobj:
	rm -rf target

cleandb:
	rm -f resources/data.db


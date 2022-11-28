# VARIABLES

CXX = g++
CXXFLAGS = -std=c++17 -I src/data -I src/web
LDLIBS = -lsqlite3 -lwt -lwthttp

_MAIN = Main.cpp
MAIN = $(subst src/,target/,$(subst .cpp,.o,$(wildcard src/*/$(_MAIN))))
TESTS = $(subst src/,target/,$(subst .cpp,.o,$(wildcard src/tests/*.cpp)))
OBJ = $(subst src/,target/,$(subst .cpp,.o,$(wildcard src/*/*.cpp)))

MKDIR_P = @ mkdir -p $(@D)

# SPECIAL TARGETS

.SECONDARY: $(OBJ)

.PHONY: main tests clean cleanout cleanobj cleandb dbreset dbtables dbtestdata

# EXECUTABLES

all: main tests

main: $(basename $(notdir $(MAIN))) dbtables

$(basename $(notdir $(MAIN))): $(filter-out $(TESTS),$(OBJ))
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

tests: $(basename $(notdir $(TESTS))) dbtables

%: $(filter-out $(MAIN) $(TESTS),$(OBJ)) target/tests/%.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# OBJECTS

target/%.o: src/%.cpp
	$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(wildcard target/*/*.d)

# PHONY

dbreset: cleandb dbtables

dbtables:
	sqlite3 sql/data.db < sql/tables.sql

dbtestdata: dbtables
	sqlite3 sql/data.db < sql/test_data.sql

clean: cleanout cleanobj cleandb

cleanout:
	rm -f $(basename $(notdir $(MAIN) $(TESTS)))

cleanobj:
	rm -rf target

cleandb:
	rm -f sql/data.db


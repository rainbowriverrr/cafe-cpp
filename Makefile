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

# EXECUTABLES

all: main tests

main: $(basename $(notdir $(MAIN)))

$(basename $(notdir $(MAIN))): $(filter-out $(TESTS),$(OBJ))
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)
	sqlite3 resources/data.db < q.sql

tests: $(basename $(notdir $(TESTS)))

%: $(filter-out $(MAIN) $(TESTS),$(OBJ)) target/tests/%.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# OBJECTS

target/%.o: src/%.cpp
	$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(wildcard target/*/*.d)

# PHONY

.PHONY: clean cleanout cleanobj cleandb

clean: cleanout cleanobj cleandb

cleanout:
	rm -f $(basename $(notdir $(MAIN) $(TESTS)))

cleanobj:
	rm -rf target

cleandb:
	rm -f resources/data.db


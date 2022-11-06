# VARIABLES

CXX = g++
CXXFLAGS = -std=c++17 -I src/data
LDLIBS = -lsqlite3 -lwt -lwthttp

_MAIN = Application.cpp
MAIN = $(subst src/,target/,$(subst .cpp,.o,$(wildcard src/*/$(_MAIN))))
TESTS = $(subst src/,target/,$(subst .cpp,.o,$(wildcard src/tests/*.cpp)))
OBJ = $(subst src/,target/,$(subst .cpp,.o,$(wildcard src/*/*.cpp)))

MKDIR_P = @ mkdir -p $(@D)

.SECONDARY: $(OBJ)

# EXECUTABLES

all: main tests

main: $(basename $(notdir $(MAIN)))

$(basename $(notdir $(MAIN))): $(filter-out $(TESTS),$(OBJ))
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

tests: $(basename $(notdir $(TESTS)))

%: $(filter-out $(MAIN) $(TESTS),$(OBJ)) target/tests/%.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

# OBJECTS

target/%.o: src/%.cpp
	$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(wildcard target/*/*.d)

# PHONY

.PHONY: clean cleanout cleanobj cleandb

clean: cleanout cleanobj

cleanout:
	rm -f $(basename $(notdir $(MAIN) $(TESTS)))

cleanobj:
	rm -rf target

cleandb:
	rm -i resources/data.db


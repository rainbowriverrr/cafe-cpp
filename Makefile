STD = -std=c++17
OBJ = main.o DBHelper.o SqlCondition.o MenuItem.o

test: main.o DBHelper.o SqlCondition.o MenuItem.o
	g++ -o test main.o DBHelper.o SqlCondition.o MenuItem.o -lsqlite3
##
test: $(OBJ)
	g++ -o test $(OBJ) -lsqlite3

main.o: main.cpp
	g++ -c $(STD) main.cpp
DBHelper.o: DBHelper.cpp
	g++ -c $(STD) DBHelper.cpp
SqlCondition.o: SqlCondition.cpp
	g++ -c $(STD) SqlCondition.cpp
MenuItem.o: MenuItem.cpp
	g++ -c $(STD) MenuItem.cpp

clean:
	rm test
	rm $(OBJ)

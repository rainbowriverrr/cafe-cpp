STD = -std=c++20
OBJ = main.o DBHelper.o SqlCondition.o MenuItem.o

test: $(OBJ)
	g++ -o test -lsqlite3 $(OBJ)

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

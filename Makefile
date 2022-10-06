std = -std=c++20

test: main.o DBHelper.o SqlCondition.o MenuItem.o
	g++ -o test main.o DBHelper.o SqlCondition.o MenuItem.o -lsqlite3

main.o: main.cpp
	g++ -c $(std) main.cpp
DBHelper.o: DBHelper.cpp
	g++ -c $(std) DBHelper.cpp
SqlCondition.o: SqlCondition.cpp
	g++ -c $(std) SqlCondition.cpp
MenuItem.o: MenuItem.cpp
	g++ -c $(std) MenuItem.cpp

clean:
	rm test
	rm *.o

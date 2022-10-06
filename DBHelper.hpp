//
//  DBHelper.hpp
//  DAL Test
//
//  Created by Julian Koksal on 2022-09-25.
//
//  Data Access Layer

#ifndef DBHelper_hpp
#define DBHelper_hpp

#include <string>
#include <any>
#include <vector>
#include <set>
#include <map>
#include <typeinfo>
#include <iostream>

#include <sqlite3.h>

#include "Model.hpp"
#include "SqlCondition.hpp"

class DBHelper
{
public:
    DBHelper();
    
    ~DBHelper();
    
    // Creates the MenuItem table. Used only for the example.
    void createTableMenuItem();
    
    // Reads all rows from the table represented by model, and returns the result as a vector<T>.
    // model must inherit from Model.
    // The values of model do not matter, it is used only to determine the table name, columns, and column types, and to cast the results.
    // conditions is a vector of SqlCondition objects used to generate the WHERE clause of the select statement.
    // orderBy is the field and direction used to generate the ORDER BY clause of the select statement. e.g. "price DESC"
    // columns is the set of column names to select. If it is empty, all columns will be selected.
    template<class T, class = std::enable_if_t<std::is_base_of<Model, T>::value>>
    std::vector<T> selectWhere(T *model, std::vector<SqlCondition> conditions = std::vector<SqlCondition>(), std::string orderBy = "", std::set<std::string> columns = std::set<std::string>())
    {
        std::vector<T> result;
        // Helper reads from the database.
        std::vector<Model *> helperResult = selectWhereHelper(model, conditions, orderBy, columns);
        // Converts the results to static T objects and deletes the dynamic objects created by selectWhereHelper().
        for (int i = 0; i < helperResult.size(); i++)
        {
            T *row = (T *)helperResult[i];
            result.push_back(*row);
            delete row;
        }
        return result;
    }
    
    // Inserts the given model to its associated table in the database.
    void insert(Model *model);
    
    // Updates the given model in the database by its primary key(s).
    void update(Model *model);
    
    // Conditionally updates the table that model represents with the values of model.
    void updateWhere(Model *model, std::vector<SqlCondition> conditions);
    
    // Deletes the given model from the database by its primary key(s).
    void destroy(Model *model);
    
    // Conditionally deletes from the table that model represents.
    void destroyWhere(Model *model, std::vector<SqlCondition> conditions);
    
private:
    // SQLite3 handle
    sqlite3* db;
    
    // Helper method reads all rows from the table represented by model, and returns the result as a vector<Model *>.
    // The values of model do not matter, it is used only to determine the table name, columns, and column types, and to cast the results.
    // conditions is a vector of SqlCondition objects used to generate the WHERE clause of the select statement.
    // orderBy is the field and direction used to generate the ORDER BY clause of the select statement. e.g. "price DESC"
    // columns is the set of column names to select. If it is empty, all columns will be selected.
    std::vector<Model *> selectWhereHelper(Model *model, std::vector<SqlCondition> conditions, std::string orderBy, std::set<std::string> columns);
    
    // Opens the sqlite3 database handle.
    void openDB();
    
    // Closes the sqlite3 database handle.
    void closeDB();
};

#endif /* DBHelper_hpp */

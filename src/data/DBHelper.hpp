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

#include "sqlite3.h"

#include "Model.hpp"
#include "SqlCondition.hpp"

class DBHelper
{
public:
    ~DBHelper();
    
    static const DBHelper & getInstance();
    
    // Creates the MenuItem table. Used only for the example.
    void createTableMenuItem() const;
    
    // Reads all rows from the table represented by model, and returns the result as a vector<T>.
    // model must inherit from Model.
    // The values of model do not matter, it is used only to determine the table name, columns, and column types, and to cast the results.
    // conditions is used to generate the WHERE clause of the select statement.
    // orderBy is the field and direction used to generate the ORDER BY clause of the select statement. e.g. "price DESC"
    // columns is the set of column names to select. If it is empty, all columns will be selected.
    template<class T, class = std::enable_if_t<std::is_base_of<Model, T>::value>>
    std::vector<T> selectWhere(const T &model, std::vector<SqlCondition> conditions = std::vector<SqlCondition>(), std::string orderBy = "", std::set<std::string> columns = std::set<std::string>()) const
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
    void insert(const Model &model) const;
    
    // Updates the given model in the database by its primary key(s).
    void update(const Model &model) const;
    
    // Conditionally updates the table that model represents with the values of model.
    // conditions is used to generate the WHERE clause of the update statement.
    // columns is the set of column names to update. If it empty, all columns will be updated.
    void updateWhere(const Model &model, std::vector<SqlCondition> conditions, std::set<std::string> columns) const;
    
    // Deletes the given model from the database by its primary key(s).
    void destroy(const Model &model) const;
    
    // Conditionally deletes from the table that model represents.
    void destroyWhere(const Model &model, std::vector<SqlCondition> conditions) const;
    
private:
    DBHelper(const DBHelper &other);
    
    DBHelper& operator=(const DBHelper &other);
    
    static const DBHelper * instance;
    
    // SQLite3 handle
    sqlite3* db;
    
    // Helper method reads all rows from the table represented by model, and returns the result as a vector<Model *>.
    // The values of model do not matter, it is used only to determine the table name, columns, and column types, and to cast the results.
    // conditions is a vector of SqlCondition objects used to generate the WHERE clause of the select statement.
    // orderBy is the field and direction used to generate the ORDER BY clause of the select statement. e.g. "price DESC"
    // columns is the set of column names to select. If it is empty, all columns will be selected.
    std::vector<Model *> selectWhereHelper(const Model &model, std::vector<SqlCondition> conditions, std::string orderBy, std::set<std::string> columns) const;
    
    DBHelper();
    
    // Opens the sqlite3 database handle.
    void openDB();
    
    // Closes the sqlite3 database handle.
    void closeDB();
};

#endif /* DBHelper_hpp */

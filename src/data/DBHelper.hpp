//
//  DBHelper.hpp
//

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

/**
 * @brief Data access layer class.
 *
 * Provides an abstract interface for accessing the SQLite3 database.
 *
 * @author Julian Koksal
 * @date 2022-09-25
 */
class DBHelper
{
public:
    /**
     * @brief Gets the singleton instance of this class.
     *
     * @return singleton instance of DBHelper
     */
    static const DBHelper & getInstance();
    
    /**
     * @brief Reads rows from the table represented by model and returns the result as a vector.
     *
     * Casts the results of DBHelper::selectWhereHelper() to type T, which is the subclass of Model that the model parameter was.
     * Conditions, sorting, and projection can be specified with the parameters, but are optional.
     * If no optional parameters are given, returns all rows and columns of the table unsorted.
     *
     * @param model Must inherit from Model. Used to determine the table name, column names and types, and to cast the results.
     *              In the results, columns that are not selected will have the same value as in this object.
     * @param conditions Used to generate the WHERE clause of the select statement.
     * @param orderBy The field and direction used to generate the ORDER BY clause of the select statement. e.g. "price DESC".
     * @param columns The set of column names to select. If empty, all columns are selected.
     * @return The result of the select statement as a vector of models.
     */
    template<class T, class = std::enable_if_t<std::is_base_of<Model, T>::value>>
    std::vector<T> selectWhere(const T &model, const std::vector<SqlCondition> &conditions = { }, const std::string &orderBy = "",
                               const std::set<std::string> &columns = { }) const
    {
        std::vector<T> result;
        // Helper reads from the database.
        std::vector<Model *> helperResult = selectWhereHelper(model, conditions, orderBy, columns);
        // Converts the results to static T objects and deletes the dynamic objects created by selectWhereHelper().
        for (std::vector<Model *>::iterator it = helperResult.begin(); it != helperResult.end(); it++)
        {
            T *row = (T *)*it;
            result.push_back(*row);
            delete row;
        }
        return result;
    }
    
    /**
     * @brief Inserts the given model to its associated table in the database.
     *
     * The model is inserted as is, with the exception of the INTEGER PRIMARY KEY if model.isAutoGenerated() returns true.
     * In that case, that column will be set to NULL and SQLite3 will automatically choose the next highest integer as the key.
     * Returns that key, or 0 if there is no auto generated key.
     *
     * @param model The model to insert to the database.
     * @return the key of the inserted record if it has an autogenerated INTEGER PRIMARY KEY, 0 otherwise
     */
    long long insert(const Model &model) const;
    
    /**
     * @brief Updates the given model in the database by its primary key(s).
     *
     * Updates the row in the table with PRIMARY KEY(s) that match the key(s) of model.
     * All columns are updated to the corresponding values of model.
     *
     * @param model The model to update, identified by its keys member.
     */
    void update(const Model &model) const;
    
    /**
     * @brief Conditionally updates the table that model represents with the values of model.
     *
     * Updates all rows in the table that match the conditions given to have the values of model.
     * Only columns given in the columns parameter are updated. If columns is empty, all columns are updated.
     *
     * @param conditions Used to generate the WHERE clause of the update statement.
     * @param columns The set of column names to update. If empty, all columns are updated.
     */
    void updateWhere(const Model &model, const std::vector<SqlCondition> &conditions, const std::set<std::string> &columns) const;
    
    /**
     * @brief Deletes the given model from its table, identified by its primary key(s).
     *
     * Deletes the row in the table with PRIMARY KEY(s) that match the key(s) of model.
     * Called destroy because delete is a C++ keyword.
     *
     * @param model The model to delete.
     */
    void destroy(const Model &model) const;
    
    /**
     * @brief Conditionally deletes from the table that model represents.
     *
     * Deletes all rows in the table that match the conditions given.
     * Called destroy because delete is a C++ keyword.
     *
     * @warning Use with caution! Will delete every row in the table if conditions is empty.
     *
     * @param model Used to determine the table name.
     * @param conditions Used to generate the WHERE clause of the delete statement.
     */
    void destroyWhere(const Model &model, const std::vector<SqlCondition> &conditions) const;
    
private:
    /**
     * @brief Singleton instance of DBHelper.
     */
    static const DBHelper * instance;
    
    /**
     * @brief SQLite3 database handle.
     */
    sqlite3* db;
    
    /**
     * @brief Constructor.
     *
     * Opens the SQLite3 database handle using the file "sql/data.db".
     */
    DBHelper();
    
    /**
     * @brief Destructor.
     *
     * Closes the sqlite3 database handle.
     */
    ~DBHelper();
    
    /**
     * @brief Copy constructor.
     *
     * Not implemented to prevent copying of singleton instance.
     */
    DBHelper(const DBHelper &other);
    
    /**
     * @brief Assignment operator overload.
     *
     * Not implemented to prevent assignment of singleton instance.
     */
    DBHelper& operator=(const DBHelper &other);
    
    /**
     * @brief Reads rows from the table represented by model and returns the result as a vector.
     *
     * Conditions, sorting, and projection can be specified with the parameters, but are optional.
     * Returns all rows and columns of the table, unsorted, if no optional parameters are given.
     *
     * Used only by DBHelper::selectWhere().
     * Its purpose is to keep most of the implementation of DBHelper::selectWhere() (a template function) outside of the header file.
     *
     * @param model Used to determine the table name, column names and types, and to cast the results.
     * @param conditions Used to generate the WHERE clause of the select statement.
     * @param orderBy The field and direction used to generate the ORDER BY clause of the select statement. e.g. "price DESC".
     * @param columns The set of column names to select. If empty, all columns are selected.
     * @return The result of the select statement as a vector of Model pointers.
     */
    std::vector<Model *> selectWhereHelper(const Model &model, const std::vector<SqlCondition> &conditions, const std::string &orderBy,
                                           const std::set<std::string> &columns) const;
    
    /**
     * @brief Prepares a sqlite3 statement from the given query.
     *
     * @param query the query used to prepare the statement
     * @param queryType the type of query (select, insert, etc), used to generate error messages
     */
    sqlite3_stmt * prepareStatement(const std::string &query, const std::string &queryType) const;
    
    /**
     * @brief Generates the WHERE clause of a query from a vector of SqlCondition objects.
     *
     * @param conditions iterated to generate the WHERE clause
     * @return the WHERE clause of a query
     */
    std::string generateWhereClauseFromConditions(const std::vector<SqlCondition> &conditions) const;
    
    /**
     * @brief Generates the WHERE clause of a query from a vector of key column names.
     *
     * @param keys iterated to generate the WHERE clause
     * @return the WHERE clause of a query
     */
    std::string generateWhereClauseFromKeys(const std::vector<std::string> &keys) const;
    
    /**
     * @brief Iterates the columns vector and binds the corresponding value in the model to the statement, starting at index.
     *
     * Index is incremented with each iteration to allow multiple uses of bind statement methods on the same statement.
     *
     * @param statement the sqlite3 statement to bind
     * @param model the model to get values from
     * @param columns the names of the columns to bind the values of
     * @param index the sqlite3 statement parameter index
     * @param queryType the type of query (select, insert, etc), used to generate error messages
     */
    void bindStatementColumns(sqlite3_stmt *statement, const Model &model, const std::vector<std::string> &columns, int &index,
                       const std::string &queryType) const;
    
    /**
     * @brief Iterates the conditions and binds their values to the statement, starting at index.
     *
     * Index is incremented with each iteration to allow multiple uses of bind statement methods on the same statement.
     *
     * @param statement the sqlite3 statement to bind
     * @param conditions the conditions to bind the values of
     * @param index the sqlite3 statement parameter index
     * @param queryType the type of query (select, insert, etc), used to generate error messages
     */
    void bindStatementConditions(sqlite3_stmt *statement, const std::vector<SqlCondition> &conditions, int &index,
                       const std::string &queryType) const;
    
    /**
     * @brief Finalizes the statement.
     *
     * Runs the destructor for statement, preventing resource leaks.
     *
     * @param statement the sqlite3 statement to finalize
     * @param errorMessage the message to print if an error occurred when running the statement
     */
    void finalizeStatement(sqlite3_stmt *statement, const std::string &errorMessage) const;
    
    /**
     * @brief Opens the sqlite3 database handle.
     *
     * Opens the SQLite3 database handle using the file "sql/data.db".
     */
    void openDB();
    
    /**
     * @brief Closes the sqlite3 database handle.
     *
     * Prevents resource leaks.
     */
    void closeDB();
};

#endif /* DBHelper_hpp */

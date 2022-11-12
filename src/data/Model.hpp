//
//  Model.hpp
//

#ifndef Model_hpp
#define Model_hpp

#include <string>
#include <any>
#include <set>
#include <map>
#include <vector>

/**
 * @brief Abstract class representing a row of a database table.
 *
 * Member variables represent the columns of the table.
 * Has private pure virtual methods to identify the table name, columns, primary keys, and if the key should be an autogenerated integer.
 * These methods provide an interface for DBHelper to use. When implemented in a subclass, they should always return the same values for that class.
 *
 * @author Julian Koksal
 * @date 2022-09-25
 */
class Model
{
    friend class DBHelper;
private:
    /**
     * @brief Returns the name of the SQL table that this model represents.
     *
     * @note Used by DBHelper. When implemented in a subclass, it should always return the same value for that class.
     *
     * @return the table name
     */
    virtual std::string tableName() const = 0;
    
    /**
     * @brief Returns the column names of the SQL table, in the correct order.
     *
     * The order of the vector should be the same as the order of the columns in the SQL table.
     *
     * @note Used by DBHelper. When implemented in a subclass, it should always return the same value for that class.
     *
     * @return vector of column names
     */
    virtual std::vector<std::string> columns() const = 0;
    
    /**
     * @brief Return the column name(s) of the primary key(s) of the SQL table.
     *
     * Returns a subset of column names from columns(), where those names are the PRIMARY KEY columns of the table.
     *
     * @note Used by DBHelper. When implemented in a subclass, it should always return the same value for that class.
     *
     * @return vector of primary keys
     */
    virtual std::set<std::string> keys() const = 0;
    
    /**
     * @brief Return true if the primary key is of type INTEGER and should have a unique value automatically chosen when inserting, false otherwise.
     *
     * When calling DBHelper::insert(model), where model is an object that extends Model, NULL will be used as the value of the primary key column.
     * In place of NULL, SQLite3 will automatically choose the next highest integer as the key.
     *
     * For more details, see:
     *     https://www.sqlite.org/lang_createtable.html#rowid
     *     https://www.sqlite.org/autoinc.html
     *
     * @note Used by DBHelper. When implemented in a subclass, it should always return the same value for that class.
     *
     * @return true if the key should be auto generated, false otherwise
     */
    virtual bool isAutoGeneratedKey() const = 0;
    
    /**
     * @brief Returns a map representation of this object.
     *
     * For each member variable of this object the map has a key value pair where the key is the name of the member variable
     * and the value is the value of the member variable.
     *
     * @note Used by DBHelper to iterate the member variables of this object.
     *
     * @return a map representation of this object
     */
    virtual std::map<std::string, std::any> toMap() const = 0;
    
    /**
     * @brief Returns a pointer to a new object with member variables initialized according to mMap.
     *
     * This is essentially the inverse of toMap(). mMap should be a map as described there.
     *
     * @note Used by DBHelper to create an object from the SQLite3 API results.
     *
     * @param mMap a map representation of the object, as created by a call to toMap()
     * @return pointer to the new model
     */
    virtual Model * fromMap(std::map<std::string, std::any> mMap) const = 0;
};

#endif /* Model_hpp */

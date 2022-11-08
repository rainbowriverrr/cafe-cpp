//
//  SqlCondition.hpp
//

#ifndef SqlCondition_hpp
#define SqlCondition_hpp

#include <string>
#include <any>
#include <stdexcept>

/**
 * Class representing a condition in the WHERE clause of a SQL query.
 * Has three member variables, field, op, and value which describe a condition as:
 *     {field} {op} {value}
 * For example:
 *     ItemID = 123
 *     Price >= 2.00
 * @author Julian Koksal
 * @date 2022-10-02
 */
class SqlCondition
{
    friend class DBHelper;
public:
    /** Constructor creates a SqlCondition object initialized with the given values.
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    
    SqlCondition(std::string field, std::string op, bool value);
    /** Constructor creates a SqlCondition object initialized with the given values.
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    
    SqlCondition(std::string field, std::string op, int value);
    /** Constructor creates a SqlCondition object initialized with the given values.
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    
    SqlCondition(std::string field, std::string op, double value);
    /** Constructor creates a SqlCondition object initialized with the given values.
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    
    SqlCondition(std::string field, std::string op, std::string value);
    /** Constructor creates a SqlCondition object initialized with the given values.
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    
    SqlCondition(std::string field, std::string op, const char *value);
    
    /**
     * Destructor.
     */
    ~SqlCondition();
private:
    /** The name of the field (column) in the SQL table this condition applies to. */
    std::string field;
    
    /** A string representation of the operator of the condition. E.g. "=", ">=", "!=", etc */
    std::string op;
    
    /** The value that is compared to. */
    std::any value;
    
    /**
     * Returns true if op is a valid operator. False otherwise.
     * Valid operators: =, !=, <>, >, >=, <, <=
     * @param op The operator.
     * @return True if op is valid, false otherwise.
     */
    bool isValidOp(std::string op);
    
    /**
     * Returns true if op is a valid operator for strings.
     * Valid string operators: =, !=, <>, >, >=, <, <=, contains, startswith, endswith
     * @param op The operator.
     * @return True if op is valid, false otherwise.
     */
    bool isValidStrOp(std::string op);
};

#endif /* SqlCondition_hpp */

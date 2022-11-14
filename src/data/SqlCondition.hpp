//
//  SqlCondition.hpp
//

#ifndef SqlCondition_hpp
#define SqlCondition_hpp

#include <string>
#include <any>
#include <vector>
#include <stdexcept>

/**
 * @brief Class representing a condition in the WHERE clause of a SQL query.
 *
 * Has three member variables, field, op, and value which describe a condition as:
 *     {field} {op} {value}
 * For example:
 *     ItemID = 123
 *     Price >= 2.00
 *
 * @author Julian Koksal
 * @date 2022-10-02
 */
class SqlCondition
{
    friend class DBHelper;
public:
    /**
     * @brief Constructor creates a SqlCondition object initialized with the given values.
     *
     * Throws a runtime exception if op is not one of the valid operators.
     *
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    SqlCondition(std::string field, std::string op, bool value);
    
    /**
     * @brief Constructor creates a SqlCondition object initialized with the given values.
     *
     * Throws a runtime exception if op is not one of the valid operators.
     *
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    SqlCondition(std::string field, std::string op, int value);
    
    /**
     * @brief Constructor creates a SqlCondition object initialized with the given values.
     *
     * Throws a runtime exception if op is not one of the valid operators.
     *
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    SqlCondition(std::string field, std::string op, double value);
    
    /**
     * @brief Constructor creates a SqlCondition object initialized with the given values.
     *
     * Throws a runtime exception if op is not one of the valid string operators.
     *
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    SqlCondition(std::string field, std::string op, std::string value);
    
    /**
     * @brief Constructor creates a SqlCondition object initialized with the given values.
     *
     * this->value is set to a std::string constructed from the value parameter.
     * Throws a runtime exception if op is not one of the valid string operators.
     *
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    SqlCondition(std::string field, std::string op, const char *value);
    
    /**
     * @brief Constructor creates a SqlCondition object initialized with the given values.
     *
     * Throws a runtime exception if op is not "IN".
     *
     * @param field The field (column name).
     * @param op The operator.
     * @param value The value.
     */
    SqlCondition(std::string field, std::string op, std::vector<std::string> value);
    
    /**
     * @brief Destructor.
     */
    ~SqlCondition();
private:
    /**
     * @brief The name of the field (column) in the SQL table this condition applies to.
     */
    std::string field;
    
    /**
     * @brief A string representation of the operator of the condition. E.g. "=", ">=", "!=", etc
     */
    std::string op;
    
    /**
     * @brief The value that is compared to.
     */
    std::any value;
    
    /**
     * @brief Returns true if op is a valid operator. False otherwise.
     *
     * Valid operators: =, !=, <>, >, >=, <, <=
     *
     * @param op The operator.
     * @return True if op is valid, false otherwise.
     */
    bool isValidOp(std::string op);
    
    /**
     * @brief Changes op to uppercase, then returns true if op is a valid operator for strings.
     *
     * Valid string operators: =, !=, <>, >, >=, <, <=, CONTAINS, STARTSWITH, ENDSWITH
     *
     * @param op The operator.
     * @return True if op is valid, false otherwise.
     */
    bool isValidStrOp(std::string &op);
    
    /**
     * @brief Changes op to uppercase, then returns true if op is a valid operator for vectors.
     *
     * Valid vector operators: IN
     *
     * @param op The operator.
     * @return True if op is valid, false otherwise.
     */
    bool isValidVectorOp(std::string &op);
};

#endif /* SqlCondition_hpp */

//
//  SqlCondition.hpp
//  DAL Test
//
//  Created by Julian Koksal on 2022-10-02.
//
//  Represents a condition in the where clause of a SQL query.
//  Has three member variables, field, op, and value which describe a condition as:
//      {field} {op} {value}
//  For example:
//      ItemID = 123
//      Price >= 2.00

#ifndef SqlCondition_hpp
#define SqlCondition_hpp

#include <string>
#include <any>

class SqlCondition
{
    friend class DBHelper;
public:
    // Constructors create a SqlCondition object initialized with the given values.
    SqlCondition(std::string field, std::string op, bool value);
    SqlCondition(std::string field, std::string op, int value);
    SqlCondition(std::string field, std::string op, double value);
    SqlCondition(std::string field, std::string op, std::string value);
    SqlCondition(std::string field, std::string op, const char *value);
    
    // Destructor.
    ~SqlCondition();
private:
    // The name of the field (column) in the SQL table this condition applies to.
    std::string field;
    // A string representation of the operator of the condition. E.g. "=", ">=", "!=", etc
    std::string op;
    // The value that is compared to.
    std::any value;
    
    // Returns true if op is a valid operator.
    // Valid operators: =, !=, <>, >, >=, <, <=
    bool isValidOp(std::string op);
    
    // Returns true if op is a valid operator for strings.
    // Valid string operators: =, !=, <>, >, >=, <, <=, contains, startswith, endswith
    bool isValidStrOp(std::string op);
};

#endif /* SqlCondition_hpp */

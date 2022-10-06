//
//  SqlCondition.cpp
//  DAL Test
//
//  Created by Julian Koksal on 2022-10-02.
//

#include <stdexcept>
#include "SqlCondition.hpp"

SqlCondition::SqlCondition(std::string field, std::string op, bool value)
{
    if (!isValidOp(op))
    {
        throw std::runtime_error("Error in SqlCondition constructor. '" + op + "' is not a valid operator.");
    }
    this->field = field;
    this->op = op;
    this->value = value;
}

SqlCondition::SqlCondition(std::string field, std::string op, int value)
{
    if (!isValidOp(op))
    {
        throw std::runtime_error("Error in SqlCondition constructor. '" + op + "' is not a valid operator.");
    }
    this->field = field;
    this->op = op;
    this->value = value;
}

SqlCondition::SqlCondition(std::string field, std::string op, double value)
{
    if (!isValidOp(op))
    {
        throw std::runtime_error("Error in SqlCondition constructor. '" + op + "' is not a valid operator.");
    }
    this->field = field;
    this->op = op;
    this->value = value;
}

SqlCondition::SqlCondition(std::string field, std::string op, std::string value)
{
    if (!isValidStrOp(op))
    {
        throw std::runtime_error("Error in SqlCondition constructor. '" + op + "' is not a valid operator.");
    }
    this->field = field;
    this->op = op;
    this->value = value;
    
    if (op == "contains")
    {
        this->op = "LIKE";
        this->value = "%" + value + "%";
    }
    if (op == "startswith")
    {
        this->op = "LIKE";
        this->value = value + "%";
    }
    if (op == "endswith")
    {
        this->op = "LIKE";
        this->value = "%" + value;
    }
}

SqlCondition::SqlCondition(std::string field, std::string op, const char *value)
{
    if (!isValidStrOp(op))
    {
        throw std::runtime_error("Error in SqlCondition constructor. '" + op + "' is not a valid operator.");
    }
    this->field = field;
    this->op = op;
    this->value = std::string(value);
    
    if (op == "contains")
    {
        this->op = "LIKE";
        this->value = "%" + std::string(value) + "%";
    }
    if (op == "startswith")
    {
        this->op = "LIKE";
        this->value = std::string(value) + "%";
    }
    if (op == "endswith")
    {
        this->op = "LIKE";
        this->value = "%" + std::string(value);
    }
}

SqlCondition::~SqlCondition()
{
    
}

bool SqlCondition::isValidOp(std::string op)
{
    return op == "=" || op == "!=" || op == "<>" || op == ">" || op == ">=" || op == "<" || op == "<=";
}

bool SqlCondition::isValidStrOp(std::string op)
{
    std::string opLower;
    for (std::string::iterator it = op.begin(); it != op.end(); it++)
    {
        opLower.push_back(std::tolower(*it));
    }
    return isValidOp(op) || opLower == "contains" || opLower == "startswith" || opLower == "endswith";
}

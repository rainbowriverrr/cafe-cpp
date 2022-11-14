//
//  SqlCondition.cpp
//
//  Created by Julian Koksal on 2022-10-02.
//

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
    
    if (op == "CONTAINS")
    {
        this->op = "LIKE";
        this->value = "%" + value + "%";
    }
    else if (op == "STARTSWITH")
    {
        this->op = "LIKE";
        this->value = value + "%";
    }
    else if (op == "ENDSWITH")
    {
        this->op = "LIKE";
        this->value = "%" + value;
    }
    else
    {
        this->op = op;
        this->value = value;
    }
}

SqlCondition::SqlCondition(std::string field, std::string op, const char *value)
{
    if (!isValidStrOp(op))
    {
        throw std::runtime_error("Error in SqlCondition constructor. '" + op + "' is not a valid operator.");
    }
    
    this->field = field;
    
    if (op == "CONTAINS")
    {
        this->op = "LIKE";
        this->value = "%" + std::string(value) + "%";
    }
    else if (op == "STARTSWITH")
    {
        this->op = "LIKE";
        this->value = std::string(value) + "%";
    }
    else if (op == "ENDSWITH")
    {
        this->op = "LIKE";
        this->value = "%" + std::string(value);
    }
    else
    {
        this->op = op;
        this->value = std::string(value);
    }
}

SqlCondition::SqlCondition(std::string field, std::string op, std::vector<std::string> value)
{
    if (!isValidVectorOp(op))
    {
        throw std::runtime_error("Error in SqlCondition constructor. Only the operator 'IN' can be used if value is a vector.");
    }
    if (value.empty())
    {
        throw std::runtime_error("Error in SqlCondition constructor. Vector value cannot be empty.");
    }
    
    this->field = field;
    this->op = op;
    this->value = value;
}

SqlCondition::~SqlCondition()
{
    
}

bool SqlCondition::isValidOp(std::string op)
{
    return op == "=" || op == "!=" || op == "<>" || op == ">" || op == ">=" || op == "<" || op == "<=";
}

bool SqlCondition::isValidStrOp(std::string &op)
{
    std::string opUpper;
    for (std::string::iterator it = op.begin(); it != op.end(); it++)
    {
        opUpper.push_back(std::toupper(*it));
    }
    op = opUpper;
    return isValidOp(op) || op == "CONTAINS" || op == "STARTSWITH" || op == "ENDSWITH";
}

bool SqlCondition::isValidVectorOp(std::string &op)
{
    std::string opUpper;
    for (std::string::iterator it = op.begin(); it != op.end(); it++)
    {
        opUpper.push_back(std::toupper(*it));
    }
    op = opUpper;
    return op == "IN";
}

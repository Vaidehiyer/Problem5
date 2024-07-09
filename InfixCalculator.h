/**
 * @file InfixCalculator.h
 * @author Hakim Abdisalam
 * StartID: oc3378es
 * @brief InfixCalculator header file
 * @version 0.1
 * @date 2024-07-07
 * Instructor: Jerome Covington
 * Due date: 07/08/2024
 *
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef INFIX_CALCULATOR_H
#define INFIX_CALCULATOR_H

#include "LinkedStack.h"      // Assuming we have LinkedStack from textbook available in project folder
#include <string>

using namespace std;

class InfixCalculator
{
private:
    string infixExpression;         // To store the infix expression given by user

    /**
     * @brief Checks if the given expression is well formed
     * 
     * @param expression : infix expr
     * @return true if expression is well formed; false otherwise
     */
    bool isWellFormed(const string &expression) const;

    /**
     * @brief Checks if the expression has balanced parenthesis
     * 
     * @param expression : infix expression
     * @return true if brackets are balanced; false otherwise
     */
    bool checkBalancedBrackets(const string &expression) const;

    /**
     * @brief Helper function which returns the precedence of an operator
     * High: (), MEdium (2): *,/, Low (1): +,-
     * 
     * @param op : Operator to check precedence
     * @return int : Precedence 
     */
    int precedence(char op) const;

    /**
     * @brief Converts infix expr to its postfix form and returns the postfix
     * expr as a string
     * 
     * @pre The expression must be well formed and balanced in brackets
     * @param infix : Infix expr to convert
     * @return string : Postfix form
     */
    string infixToPostfix(const string &infix) const;

    /**
     * @brief Evaluates the postfix expression to find out the result
     * 
     * @param postfix : To evaluate
     * @return int : Result of the expression
     */
    int evaluatePostfix(const string &postfix) const;

public:
    // Default constructor
    InfixCalculator();

    // Function to set infix expression
    bool setInfixExpression(const string &expression);

    // Function to evaluate the stored infix expression
    int evaluate() const;
};

#endif // INFIX_CALCULATOR_H

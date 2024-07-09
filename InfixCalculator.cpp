/**
 * @file InfixCalculator.cpp
 * @author Hakim Abdisalam
 * StartID: oc3378es
 * @brief InfixCalculator implementation file
 * @version 0.1
 * @date 2024-07-07
 * Instructor: Jerome Covington
 * Due date: 07/08/2024
 *
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "InfixCalculator.h"
#include <cctype>
#include <stdexcept>

// Default constructor
InfixCalculator::InfixCalculator() : infixExpression("") {}

int InfixCalculator::precedence(char op) const
{
    if (op == '+' || op == '-') // Low precedence
        return 1;
    if (op == '*' || op == '/') // High precedence
        return 2;
    return 0; // Not valid
}

bool InfixCalculator::isWellFormed(const string &expression) const
{
    int length = expression.length();
    if (length == 0)
        return false;

    for (int i = 0; i < length; ++i)
    {
        char ch = expression[i];

        // Check for spaces
        if (isspace(ch))
            return false;

        // Check for valid characters
        if (!(isdigit(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')'))
            return false;

        // Check for proper sequence
        if (isdigit(ch))
        {
            if (i > 0 && isdigit(expression[i - 1]))
                return false; // Two consecutive digits
            if (i > 0 && expression[i - 1] == ')')
                return false; // Operand after closing parenthesis
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            if (i == 0 || i == length - 1)
                return false; // Operator at the beginning or end
            if (expression[i - 1] == '(' || expression[i + 1] == ')')
                return false; // Operator after opening or before closing parenthesis
            if (!isdigit(expression[i - 1]) && expression[i - 1] != ')')
                return false; // Operator after another operator or at the start
            if (!isdigit(expression[i + 1]) && expression[i + 1] != '(')
                return false; // Operator before another operator or at the end
        }
    }

    return true;
}

bool InfixCalculator::checkBalancedBrackets(const string &expression) const
{
    LinkedStack<char> aStack;
    bool balancedSoFar = true;
    int i = 0;

    while (balancedSoFar && i < expression.length())
    {

        // character at position i in expression
        char ch = expression[i];
        i++;

        // Push an open brace
        if (ch == '(')
        {
            aStack.push(ch);
        }

        // Close brace
        else if (ch == ')')
        {
            if (!aStack.isEmpty())
            {
                aStack.pop(); // Pop a matching open brace
            }
            else // No matching open brace
            {
                balancedSoFar = false;
            }
        }
    }

    return balancedSoFar && aStack.isEmpty();
}

string InfixCalculator::infixToPostfix(const string &infix) const
{
    LinkedStack<char> aStack;
    string postfixExp;

    for (char ch : infix)
    {
        if (isdigit(ch))
        {
            postfixExp += ch; // Append operand to postfix expression
        }
        else if (ch == '(')
        {
            aStack.push(ch); // Save '(' on stack
        }
        else if (ch == ')')
        {
            // Pop stack until matching '('
            while (!aStack.isEmpty() && aStack.peek() != '(')
            {
                postfixExp += aStack.peek();
                aStack.pop();
            }
            aStack.pop(); // Remove the open parenthesis
        }
        else
        {
            // Process stack operators of greater precedence
            while (!aStack.isEmpty() && aStack.peek() != '(' &&
                   precedence(ch) <= precedence(aStack.peek()))
            {
                postfixExp += aStack.peek();
                aStack.pop();
            }
            aStack.push(ch); // Save the operator
        }
    }

    // Append remaining operators in the stack to postfixExp
    while (!aStack.isEmpty())
    {
        postfixExp += aStack.peek();
        aStack.pop();
    }

    return postfixExp;
}

// Function to evaluate a postfix expression
int InfixCalculator::evaluatePostfix(const string &postfix) const
{
    LinkedStack<int> aStack;

    for (char ch : postfix)
    {
        if (isdigit(ch))
        {
            aStack.push(ch - '0'); // Convert char to int and push onto stack
        }
        else
        {
            // Pop out the top 2 operands
            int operand2 = aStack.peek();
            aStack.pop();
            int operand1 = aStack.peek();
            aStack.pop();
            int result;

            // PErform the operation on the two operands and push back the reuslt
            switch (ch)
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            default:
                throw invalid_argument("Invalid operator in postfix expression");
            }

            aStack.push(result);
        }
    }

    return aStack.peek();
}

// Function to set infix expression
bool InfixCalculator::setInfixExpression(const string &expression)
{
    if (isWellFormed(expression) && checkBalancedBrackets(expression))
    {
        infixExpression = expression;
        return true;
    }
    return false;
}

// Evaluates the infix expression
int InfixCalculator::evaluate() const
{
    string postfix = infixToPostfix(infixExpression);

    return evaluatePostfix(postfix);
}

/**
 * @file Tester.cpp
 * @author Hakim Abdisalam
 * StartID: oc3378es
 * @brief Program to tests the infix calculator by asking inputs from suer.
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
#include <iostream>

int main()
{
    InfixCalculator calculator;    // Define the calculator
    std::string expression;        // To store infix expression
    char continueInput = 'y';      // To check if user wants to continue

    // USe a loop to ask for repeated inptus
    while (continueInput == 'y' || continueInput == 'Y')
    {
        bool validExpression = false;    // To check if expression is valid

        // Ask for input until user enters valid expression
        while (!validExpression)
        {
            // Get input
            std::cout << "Enter an infix expression (Spaces not allowed; only single digit numbers allowed): ";
            std::getline(std::cin, expression);

            // Check for validity
            if (calculator.setInfixExpression(expression))
            {
                validExpression = true;
            }
            else
            {
                std::cout << "The expression is not well-formed or the parentheses are not balanced."
                             "Please reenter the expression. Note: Spaces are not allowed in the expression.\n";
            }
        }

        // Evaluate the expression and show the result
        try
        {
            int result = calculator.evaluate();
            std::cout << "The result of the expression is: " << result << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "Error in evaluating the expression: " << e.what() << std::endl;
        }

        // Ask for next input 
        std::cout << "Do you want to evaluate another expression? (y/n): ";
        std::cin >> continueInput;
        std::cin.ignore(); // Clear the newline character from the buffer
    }

    return 0;
}

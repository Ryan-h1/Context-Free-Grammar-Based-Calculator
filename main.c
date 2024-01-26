/***
 * @file main.c
 * @author Ryan Hecht
 * @date 2024-01-26
 *
 * @brief This program uses a CFG to evaluate simple arithmetic expressions. It was made to help me
 * understand my "Organization of Programming Languages" course material.
 *
 * Context-Free Grammar (CFG) Rules:
 * sim_exp → md_exp
 * sim_exp → sim_exp l_op md_exp
 * md_exp → num
 * md_exp → md_exp h_op num
 * l_op → + | -
 * h_op → * | /
 * num → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
 *
 * The code defines four functions to evaluate arithmetic expressions
 * recursively: 'get_op()', 'get_num()', 'sim_sub_exp()', and 'md_sub_exp()'.
 * The main function is 'sim_exp()', which evaluates a simple arithmetic
 * expression by calling 'md_exp()' to evaluate the first
 * multiplicative/divisive expression, and then calling 'sim_sub_exp()' to
 * evaluate the rest of the expression recursively.
 *
 * The main function also includes a loop that prompts the user to enter a simple arithmetic
 * expression, evaluates it, prints the result, and then asks if the user wants
 * to continue. If the user enters 'Y', the loop continues, and if the user
 * enters 'N' or any other character, the program exits.
 *
 */

#include <stdio.h>
#include <stdlib.h>

// constants
#define END_TOKEN '\n'

// define functions
char get_op(void);
float get_num(void);
float sim_sub_exp(float sub_exp);
float sim_exp(void);
float md_sub_exp(float sub_exp);
float md_exp(void);

/**
 * Main method
 */
int main()
{
    char continue_flag = 'Y';
    while (continue_flag == 'Y')
    {
        printf("Enter a simple arithmetic expression: ");
        float result = sim_exp();
        printf("Result: %f\n", result);
        printf("Do you want to continue? (Y/N) ");
        char c = getchar();
        while (c == ' ' || c == '\n')
        { // skip spaces and newlines
            c = getchar();
        }
        continue_flag = c;
    }
    return 0;
}


/**
 * This function reads the next operator from standard input and returns it.
 * If the character read is not a valid operator, the program prints an error message and exits.
 *
 * @return char Representing the next operator
 */
char get_op(void)
{
    char c = getchar();
    while (c == ' ')
    { // skip spaces
        c = getchar();
    }
    if (c == END_TOKEN || c == '+' || c == '-' || c == '*' || c == '/')
    {
        return c;
    }
    else
    {
        printf("Error: invalid operator %c\n", c);
        exit(EXIT_FAILURE);
    }
}

/**
 * This function reads the next numeric value from standard input and
 * returns it as a float.
 *
 * @return float Representing the next numeric value
 */
float get_num(void)
{
    float num;
    scanf("%f", &num);
    return num;
}

/**
 * This function evaluates the current sub-expression to the left of the
 * next operator (passed as 'sub_exp') and returns the result. If the next
 * operator is '+', '-', or '\n', it pushes it back to standard input
 * and returns 'sub_exp'. If the next operator is '*' or '/', it reads
 * the next numeric value with 'get_num()'and then calls itself recursively
 * with the result of 'sub_exp *|/ next_num', depending on the operator.
 * If the next operator is not valid, the program prints an error message
 * and exits.
 *
 * @param sub_exp The current sub-expression to the left of the next operator
 * @return float The result of the current sub-expression
 */
float sim_sub_exp(float sub_exp)
{
    char next_op = get_op();
    if (next_op == END_TOKEN)
    {
        ungetc(next_op, stdin); // push back '\n'
        return sub_exp;
    }
    else if (next_op == '+' || next_op == '-')
    {
        float next_md_exp = md_exp();
        if (next_op == '+')
        {
            return sim_sub_exp(sub_exp + next_md_exp);
        }
        else
        {
            return sim_sub_exp(sub_exp - next_md_exp);
        }
    }
    else
    {
        printf("Error: invalid operator %c\n", next_op);
        exit(EXIT_FAILURE);
    }
}

/**
 * This function evaluates a simple arithmetic expression recursively.
 * It evaluates the first multiplicative/divisive expression with 'md_exp()'
 * and then calls 'sim_sub_exp()' with the result.
 *
 * @return float The result of the arithmetic expression
 */
float sim_exp(void)
{
    float m = md_exp();
    return sim_sub_exp(m);
}

/**
 * This function evaluates the current sub-expression to the left of the
 * next operator (passed as 'sub_exp') and returns the result. If the next
 * operator is '+', '-', or '\n', it pushes it back to standard input
 * and returns 'sub_exp'. If the next operator is '*' or '/', it reads
 * the next numeric value with 'get_num()'and then calls itself recursively
 * with the result of 'sub_exp *|/ next_num', depending on the operator.
 * If the next operator is not valid, the program prints an error message
 * and exits.
 *
 * @param sub_exp The current sub-expression to the left of the next operator
 * @return float The result of the current sub-expression
 */
float md_sub_exp(float sub_exp)
{
    char next_op = get_op();
    if (next_op == '+' || next_op == '-' || next_op == END_TOKEN)
    {
        ungetc(next_op, stdin); // push back '+', '-', or '\n'
        return sub_exp;
    }
    else if (next_op == '*' || next_op == '/')
    {
        float next_num = get_num();
        if (next_op == '*')
        {
            return md_sub_exp(sub_exp * next_num);
        }
        else
        {
            return md_sub_exp(sub_exp / next_num);
        }
    }
    else
    {
        printf("Error: invalid operator %c\n", next_op);
        exit(EXIT_FAILURE);
    }
}

/**
 * This function evaluates the first multiplicative/divisive expression
 * recursively. It evaluates the first numeric value with 'get_num()' and
 * then calls 'md_sub_exp()' with the result.
 *
 * @return float The result of the multiplicative/divisive expression
 */
float md_exp(void)
{
    float m = get_num();
    return md_sub_exp(m);
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

float evaluate_expression(char *, int *);

int main(int argc, char **argv) {
    float result;
    result = evaluate_expression(argv[1], 0);
    fprintf(stdout, "result expression '%s': %d", argv[1], result);


    return(EXIT_SUCCESS);
}


float evaluate_expression(char *expression, int *pos) {
    // prefix expression

    // left right recursion
    float left, right;
    float result;
    char operator;
    int k; // position along the expression

    // discard spaces
    if (isspace(expression[k]))
        k++;

    // manage expression
    if (expression[k]=='+'||expression[k]=='-' || expression[k]=='/' || expression[k]=='*') {
        // operator found, save and recur to find the operands or another operator
        operator = expression[k];
        k++;
        left = evaluate_expression(&expression[k], &k);
        right = evaluate_expression(&expression[k], &k);
        switch(operator) {
            case '+' : result = left + right; break;
            case '-' : result = left - right; break;
            case '/' : result = left / right; break;
            case '*' : result = left * right; break;
            default: break;
        }
    }

    else {
        // real value, float represented as n.m, take account of that point
        sscanf(&expression[k], "%f", &result);
        while (isdigit(expression[k]) || expression[k]=='.') {
            k++;
        }
    }
    return result;
}
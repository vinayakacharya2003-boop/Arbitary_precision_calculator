/*
Name : Vinayak Acharya
Date : 17/12/25
Description:
This program implements a command-line arithmetic calculator using 
doubly linked lists to handle large integers that cannot be stored using standard C data types.

The calculator supports the following operations:

Addition (+)

Subtraction (-)

Multiplication (x)

Division (/)

Each operand is read from the command line and converted into a doubly linked list, 
where each node stores a single digit. This approach allows the program to perform arithmetic operations 
on numbers of any length, overcoming the limitations of built-in integer types.

Working Principle:-
1)Command-Line Input Handling
The program expects input in the format:
./a.out <number1> <operator> <number2>
It validates the number of arguments and the operator.

2)Digit-to-List Conversion
Each digit of the input numbers is stored in a doubly linked list.
The most significant digit is stored at the head.

3)Operation Execution
Based on the operator provided:
The corresponding arithmetic function is called.
Operations are performed digit-by-digit using linked list traversal.

4)Division by Zero Handling
If division by zero is detected, the program safely returns Infinity instead of terminating or failing.

5)Result Storage
The result of the operation is stored in another doubly linked list.
Negative results are handled using a special node to indicate the sign.

6)Formatted Output
Results are displayed using colored output (ANSI escape codes) for better readability.
Errors and invalid inputs are clearly highlighted.

*/

#include "apc.h"
#include <stdio.h>

/* Helper: check if result is zero */
int is_zero(Dlist *head)
{
    return (head && head->data == 0 && head->next == NULL);
}

int main(int argc, char *argv[])
{   // Declare operand and result lists
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    // Variables to store sign of operands
    int sign1 = 1, sign2 = 1;
    int i = 0;

    /* -------- Operand 1 -------- */
    if (argv[1][0] == '-')  // Check sign
    {
        sign1 = -1;
        i = 1;
    }
    for (; argv[1][i] != '\0'; i++) // Convert first operand digits into linked list
    {
        insert_last(&head1, &tail1, argv[1][i] - '0');
    }

    /* -------- Operand 2 -------- */
    i = 0;
    if (argv[3][0] == '-')  // Check sign
    {
        sign2 = -1;
        i = 1;
    }

    // Convert second operand digits into linked list
    for (; argv[3][i] != '\0'; i++)
    {
        insert_last(&head2, &tail2, argv[3][i] - '0');
    }

    // Extract operator from command-line argument
    char operator = argv[2][0];

    // Perform operation based on operator
    switch (operator)
    {
        case '+':
        // If both operands have same sign, perform addition
            if (sign1 == sign2)
            {
                addition(&head1,&tail1,&head2,&tail2,&headR,&tailR);
                // Print negative sign if result is negative
                if (sign1 == -1 && !is_zero(headR))
                    printf("-");
            }
            else
            {
                // If signs differ, perform subtraction
                if (compare(head1, head2) >= 0)
                {
                    subtraction(&head1,&tail1,&head2,&tail2,&headR,&tailR);
                    // Result sign depends on larger operand
                    if (sign1 == -1 && !is_zero(headR))
                        printf("-");
                }
                else
                {
                    subtraction(&head2,&tail2,&head1,&tail1,&headR,&tailR);
                    if (sign2 == -1 && !is_zero(headR))
                        printf("-");
                }
            }
            print_list(headR);
            break;

        case '-':
            /* A - B  ==>  A + (-B) */
            sign2 = -sign2;

            // If both operands have same sign, perform addition
            if (sign1 == sign2)
            {
                addition(&head1,&tail1,&head2,&tail2,&headR,&tailR);
                // Print negative sign if result is negative
                if (sign1 == -1 && !is_zero(headR))
                    printf("-");
            }
            else
            {
                // If signs differ, perform subtraction
                if (compare(head1, head2) >= 0)
                {
                    subtraction(&head1,&tail1,&head2,&tail2,&headR,&tailR);
                    // Result sign depends on first operand
                    if (sign1 == -1 && !is_zero(headR))
                        printf("-");
                }
                else
                {
                    subtraction(&head2,&tail2,&head1,&tail1,&headR,&tailR);
                    // Result sign depends on first operand
                    if (sign2 == -1 && !is_zero(headR))
                        printf("-");
                }
            }
            print_list(headR);
            break;

        case 'x': // Perform multiplication
            multiplication(&head1,&tail1,&head2,&tail2,&headR,&tailR);

            // Result sign depends on operand signs
            if (sign1 * sign2 == -1 && !is_zero(headR))
                printf("-");
            print_list(headR);
            break;

        case '/':  // Perform division
            division(&head1,&tail1,&head2,&tail2,&headR,&tailR);

            // Result sign depends on operand signs
            if (sign1 * sign2 == -1 && !is_zero(headR))
                printf("-");
            print_list(headR);
            break;

        default:  // Handle invalid operator
            printf("Invalid Input:-( Try again...\n");
    }

    return 0;
}

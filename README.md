# Arbitary_precision_calculator
This program implements a command-line arithmetic calculator using  doubly linked lists to handle large integers that cannot be stored using standard C data types.
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

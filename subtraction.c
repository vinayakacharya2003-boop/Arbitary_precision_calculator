#include "apc.h"
#include<stdio.h>

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR)
{
	/* Definition goes here */
    if (!head1 || !tail1 || !head2 || !tail2 || !headR || !tailR)
    return FAILURE;

    // Compare both numbers to decide sign
	 int cmp = compare(*head1, *head2);
    int negative = 0;

    if (cmp == -1) // If first number is smaller, swap operands and mark result negative
    {
        negative = 1;

        // swap head pointers
        Dlist *tempH = *head1;
        *head1 = *head2;
        *head2 = tempH;

        // swap tail pointers
        Dlist *tempT = *tail1;
        *tail1 = *tail2;
        *tail2 = tempT;
    }
    else if (cmp == 0) // equal numbers → result = 0
    {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }
    
    // Initialize pointers to least significant digits
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;
    int borrow = 0;

    // Perform digit-by-digit subtraction from LSB to MSB
    while (t1 || t2)
    {
        // Get digits or zero if list ended
        int d1 = (t1 ? t1->data : 0);
        int d2 = (t2 ? t2->data : 0);

        d1 = d1 - borrow; // Apply previous borrow

        if (d1 < d2) //borrow condition handles
        {
            d1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        // Calculate difference digit
        int diff = d1 - d2;

        // Insert result digit at front
        if (insert_first(headR, tailR, diff) == FAILURE)
            return FAILURE;

        // Move to previous digits
        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }
    
    // Move to previous digits
    while ((*headR)->data == 0 && (*headR)->next)
    {
        delete_first(headR, tailR);
    }
    
    // Print minus sign if result is negative
	if (negative)
    printf("-");
    //print_list(*headR);
    return SUCCESS;
}

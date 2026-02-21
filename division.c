#include "apc.h"
#include<stdio.h>

int division(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR)
{
    // Variable to store quotient count
    int count = 0;
    // Temporary list to store subtraction result
    Dlist *tempH = NULL, *tempT = NULL;

    /* --------Division by zero-------- */
    if (*head2 == NULL ||((*head2)->data == 0 && (*head2)->next == NULL))
        return FAILURE;

    /* ---------If dividend < divisor → quotient = 0-------- */
    if (compare(*head1, *head2) == -1)
    {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }

    /* --------Repeated subtraction-------- */
    while (compare(*head1, *head2) >= 0)
    {
        // Reset temporary result list
        tempH = tempT = NULL;

        // Subtract divisor from dividend
        subtraction(head1, tail1,head2, tail2,&tempH, &tempT);

        // Delete old dividend list
        delete_list(head1, tail1);

        // Update dividend with subtraction result
        *head1 = tempH;
        *tail1 = tempT;

        // Increment quotient count
        count++;
    }

    /* --------Store quotient-------- */
    if (count == 0)
    {
        insert_first(headR, tailR, 0);
    }
    else
    {   // Convert quotient count to linked list
        while (count > 0)
        {
            insert_first(headR, tailR, count % 10);
            count /= 10;
        }
    }
    // Successful
    return SUCCESS;
}


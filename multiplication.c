#include "apc.h"
#include <stdio.h>

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR)
{
    // Lists to store intermediate and final results
    Dlist *headR1 = NULL, *tailR1 = NULL;
    Dlist *headR2 = NULL, *tailR2 = NULL;
    Dlist *temp1, *temp2;

    // Variables for multiplication
    int prod, data, carry;
    int shift = 0;

    /* ----------Check for invalid input lists---------- */
    if (*head1 == NULL || *head2 == NULL)
    return FAILURE;

    // If any operand is zero, result is zero
    if ((*head1)->data == 0 || (*head2)->data == 0)
    {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }

    // Start multiplication from least significant digit of second operand
    temp2 = *tail2;   

    // Loop through each digit of second operand
    while (temp2)
    {
        // Initialize partial product
        temp1 = *tail1;
        carry = 0;
        headR2 = tailR2 = NULL;

        /* ---------- build partial product---------- */
        while (temp1)
        {
            prod = temp1->data * temp2->data + carry;
            data = prod % 10;
            carry = prod / 10;

            insert_first(&headR2, &tailR2, data);
            temp1 = temp1->prev;
        }

        if (carry)
            insert_first(&headR2, &tailR2, carry);

        /* ---------- add shift zeros---------- */
        for (int i = 0; i < shift; i++)
            insert_last(&headR2, &tailR2, 0);

        /* ---------- accumulate result---------- */
        if (headR1 == NULL)
        {
            headR1 = headR2;
            tailR1 = tailR2;
        }
        else
        {
            addition(&headR1, &tailR1,
                     &headR2, &tailR2,
                     headR, tailR);

            // Free old result lists
            delete_list(&headR1, &tailR1);
            delete_list(&headR2, &tailR2);

            // Update accumulated result
            headR1 = *headR;
            tailR1 = *tailR;
            *headR = *tailR = NULL;
        }

        // Move to next digit and increase shift
        shift++;
        temp2 = temp2->prev;
    }

    /* ---------- remove leading zeros---------- */
    while (headR1 && headR1->data == 0 && headR1->next)
        delete_first(&headR1, &tailR1);

    // Assign final result
    *headR = headR1;
    *tailR = tailR1;

    return SUCCESS;
}

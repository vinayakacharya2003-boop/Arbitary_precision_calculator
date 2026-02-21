#include "apc.h"
#include<stdio.h>


int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR)
{
	// Definition goes here 
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    int data, carry = 0;

	// Exactly same as board
    while (temp1 || temp2)     
    {
		// case: both digits present
        if (temp1 && temp2)    
        {
            data = temp1->data + temp2->data + carry;
        }
		// only list1 has data
        else if (temp1 && temp2 == NULL)   
        {
            data = temp1->data + carry;
        }
		// only list2 has data
        else if (temp2 && temp1 == NULL)   
        {
            data = temp2->data + carry;
        }

        // Carry logic exactly like whiteboard
        if (data > 9)
        {
            carry = data / 10;
            data = data % 10;
        }
        else
        {
            carry = 0;
        }

        // Insert into result
        insert_first(headR, tailR, data);

        // Move both pointers (prev)
        if (temp1)
            temp1 = temp1->prev;

        if (temp2)
            temp2 = temp2->prev;
    }

    // If extra carry exists
    if (carry)
        insert_first(headR, tailR, carry);
    //print_list(*headR);
    return SUCCESS;
}
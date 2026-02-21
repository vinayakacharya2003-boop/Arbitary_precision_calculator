#include "apc.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int insert_first(Dlist **head, Dlist **tail, int data)
{
    // Allocate memory for new node
    Dlist *new = malloc(sizeof(Dlist));

    // Check memory allocation
    if(new == NULL)
        return FAILURE;

    // Initialize node data and links
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;

    // If list is empty, make new node head and tail
    if(*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {    // Insert node at beginning
        new -> next = *head;
        (*head) -> prev = new;
        *head = new;
        return SUCCESS;
    }
}

int insert_last(Dlist **head, Dlist **tail, int data)
{
     // Allocate memory for new node
    Dlist *new = malloc(sizeof(Dlist));

    // Check memory allocation
    if(new == NULL)
        return FAILURE;

    // Initialize node data and links
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;
    
    // If list is empty, insert first node
    if(*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        // Insert node at end
        new -> prev = *tail;
        (*tail) -> next = new;
        *tail = new;
    }
    return SUCCESS;
}

void print_list(Dlist *head)
{
    // Check if list is empty
    if (!head)
    {
        printf("INFO : List is empty\n");
        return;
    }

    // Traverse list and print digits
    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

void digit_to_list(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   char *argv[])
{
    int i = 0;

    // Skip sign of first operand if present
    if (argv[1][0] == '-' || argv[1][0] == '+')
        i = 1;

    // Convert first operand digits to list
    for (; argv[1][i] != '\0'; i++)
    {
        insert_last(head1, tail1, argv[1][i] - '0');
    }

    /* Operand 2 */
    i = 0;

    // Skip sign of second operand if present
    if (argv[3][0] == '-' || argv[3][0] == '+')
        i = 1;

    // Convert second operand digits to list
    for (; argv[3][i] != '\0'; i++)
    {
        insert_last(head2, tail2, argv[3][i] - '0');
    }
}

int compare(Dlist *h1, Dlist *h2)
{
    // If both NULL → equal
    if (!h1 && !h2)
        return 0;

    // Calculate lengths
    int len1 = 0, len2 = 0;
    Dlist *temp1 = h1;
    Dlist *temp2 = h2;

    while (temp1)
    {
        len1++;
        temp1 = temp1->next;
    }

    while (temp2)
    {
        len2++;
        temp2 = temp2->next;
    }

    // First compare by length
    if (len1 > len2)
        return 1;   // h1 > h2
    else if (len1 < len2)
        return -1;  // h1 < h2

    // Same length → compare digit by digit
    temp1 = h1;
    temp2 = h2;

    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data)
            return 1;
        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    // All digits same
    return 0;
}

int delete_first(Dlist **head, Dlist **tail)
{
    // Check if list is empty
    if(*head == NULL && *tail == NULL)
    return FAILURE;
    
    // Store first node temporarily
    Dlist *temp = *head;

    // If only one node exists
    if(*head == *tail)
    {
        *head = NULL;
        *tail = NULL;
        free(temp);
        return SUCCESS;
    }
    else{
        // Delete first node and update head
    *head = temp-> next;
    (*head)->prev = NULL;
    free(temp);
    
    return SUCCESS;
    }

}

int delete_list(Dlist **head, Dlist **tail)
{
    // Check if list is empty
    if(*head == NULL && *tail == NULL)
    return FAILURE;
    
    // Traverse and free all nodes
    Dlist *temp = *head;
    
    while(temp != NULL)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }
    // Reset head and tail
    *head = NULL;
    *tail = NULL;
    return SUCCESS;
}


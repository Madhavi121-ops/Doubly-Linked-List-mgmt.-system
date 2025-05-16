//Doubly Circular linked list

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;  
};

typedef struct node NODE;
typedef struct node* PNODE;
typedef struct node** PPNODE;

void Display(PNODE First, PNODE Last)
{
    if(First == NULL && Last == NULL)
    {
        printf("LL is empty\n");
        return;
    }

    printf(" <=> ");
    do
    {
        printf(" | %d | <=> ",First->data);
        First = First->next;
    }while(Last->next != First);
    printf("\n");
}

int Count(PNODE First, PNODE Last)
{
    int iCount = 0;

    if(First == NULL && Last == NULL)
    {
        return 0;
    }

    do
    {
        iCount++;
        First = First->next;  
    }while(First != Last->next);

    return iCount;
}

void InsertFirst(PPNODE First, PPNODE Last, int No)
{
    PNODE newn = NULL;

    newn = (PNODE)malloc(sizeof(NODE));

    newn->data = No;
    newn->next = NULL; 
    newn->prev = NULL;

    if(*First == NULL && *Last == NULL)
    {
        *First = newn;
        *Last = newn;
    }
    else
    {
        newn->next = *First;
        (*First)->prev = newn;
        *First = newn;
    }
    (*Last)->next = *First;
    (*First)->prev = *Last;
}

void InsertLast(PPNODE First, PPNODE Last, int No)
{
    PNODE newn = NULL;

    newn = (PNODE)malloc(sizeof(NODE));

    newn->data = No;
    newn->next = NULL; 
    newn->prev = NULL;

    if(*First == NULL && *Last == NULL)
    {
        *First = newn;
        *Last = newn;
    }
    else
    {
        (*Last)->next = newn;
        newn->prev = *Last;
        *Last = newn;
    }
    (*Last)->next = *First;
    (*First)->prev = *Last;
}

void InsertAtPos(PPNODE First, PPNODE Last, int No, int iPos)
{
    int i = 0;
    int iLength = 0;
    PNODE temp = NULL;
    PNODE newn = NULL;

    iLength = Count(*First, *Last);

    if(iPos < 1 || iPos > iLength+1)
    {
        printf("Invalid Position\n");
        return;
    }

    if(iPos == 1)
    {
        InsertFirst(First, Last ,No);
    }
    else if(iPos == iLength+1)
    {
        InsertLast(First, Last ,No);
    }
    else
    {
        temp = *First;

        newn = (PNODE)malloc(sizeof(NODE));

        newn->data = No;
        newn->next = NULL;
        newn->prev = NULL;

        for(i = 1; i < iPos-1; i++)
        {
            temp = temp->next;
        }
        newn->next = temp->next;
        temp->next->prev = newn;

        temp->next = newn;
        newn->prev = temp;
    }
}

void DeleteFirst(PPNODE First, PPNODE Last)
{
    if(*First == NULL && *Last == NULL)
    {
        return;
    }
    else if(*First == *Last)
    {
        free (*First);
        *First = NULL;
        *Last = NULL;
    }
    else
    {
        *First = (*First)->next;
        free((*Last)->next);
        (*Last)->next = *First;

        (*Last)->next = *First;
        (*First)->prev = *Last;
    }
}

void DeleteLast(PPNODE First, PPNODE Last)
{
    if(*First == NULL && *Last == NULL)
    {
        return;
    }
    else if(*First == *Last)
    {
        free (*First);
        *First = NULL;
        *Last = NULL;
    }
    else
    {
        *Last = (*Last)->prev;
        free((*First)->prev);

        (*Last)->next = *First;
        (*First)->prev = *Last;
    }
}

void DeleteAtPos(PPNODE First,PPNODE Last, int iPos)
{   
    int i = 0;
    int iLength = 0;
    PNODE temp1 = NULL;
    PNODE temp2 = NULL;

    iLength = Count(*First, *Last);

    if(iPos < 1 || iPos > iLength)
    {
        printf("Invalid Position\n");
        return;
    }

    if(iPos == 1)
    {
        DeleteFirst(First, Last);
    }
    else if(iPos == iLength)
    {
        DeleteLast(First, Last);
    }
    else
    {
        temp1 = *First;

        for(i = 1; i < iPos-1; i++)
        {
            temp1 = temp1->next;
        }
        temp1->next = temp2->next->next;
        free(temp2->next->prev);
        temp1->next->prev = temp2;
    }
}


int main()
{
    PNODE Head = NULL;
    PNODE Tail = NULL;
    int iRet = 0;

    InsertFirst(&Head,&Tail,51);
    InsertFirst(&Head,&Tail,21);
    InsertFirst(&Head,&Tail,11);

    InsertLast(&Head,&Tail,101);
    InsertLast(&Head,&Tail,111);
    InsertLast(&Head,&Tail,121);

    Display(Head, Tail);
    iRet = Count(Head, Tail);
    printf("Number of elements are : %d\n",iRet);

    DeleteFirst(&Head,&Tail);
    Display(Head, Tail);
    iRet = Count(Head, Tail);
    printf("Number of elements are : %d\n",iRet);

    DeleteLast(&Head,&Tail);
    Display(Head, Tail);
    iRet = Count(Head, Tail);
    printf("Number of elements are : %d\n",iRet);

    InsertAtPos(&Head, &Tail, 105,5);
    Display(Head, Tail);
    iRet = Count(Head, Tail);
    printf("Number of elements are %d\n",iRet);

    DeleteAtPos(&Head, &Tail, 5);
    Display(Head, Tail);
    iRet = Count(Head, Tail);
    printf("Number of elements are %d\n",iRet);

    return 0;
}
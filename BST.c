
//code for insertion, deletion, search, printing in bst 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//structure of library is here
struct library
{
    struct library *l;
    char bookName[30];
    char author[30];
    int bookCode;
    struct library *r;
};

typedef struct library lb;
lb *hptr = NULL;

//all the function prototypes are here
void insert();
void delete(lb *p,char bokName[],lb*prev);
void print(lb *p);
void search(lb *p,char bokName[]);
lb *findLastNode(lb *p);
int main(void)
{
    int flag = 0;
    int choice;
    while(3)
    {
        printf("1: Inert Book 2: Delete Book 3: Print All Books 4: Search Book 5: Quit\nChoice: ");
        scanf("%d", &choice);
        if(choice == 5)
        {
            flag = 1;
            break;
        }
        else
        {
            char bokName[30];
            switch(choice)
            {
                case 1: insert();break;
                case 2: 
                {
                    printf("Enter the Book Name you want to delete: ");
                    scanf("%s", bokName);
                    delete(hptr,bokName,NULL);
                    break;
                }
                case 3: print(hptr);break;
                case 4: 
                {
                    printf("Enter the book your are Looking for: ");
                    scanf("%s", bokName);
                    search(hptr,bokName);
                    break;
                }
                default: puts("Please Enter the right choice");
            }
        }
    }
}

void insert()
{
    lb *space = malloc(sizeof(lb));
    lb *tmptr = hptr;
    printf("Enter the Book Name: ");
    scanf("%s", space->bookName);
    printf("Enter the Book Author: ");
    scanf("%s", space->author);
    printf("Enter the Book code: ");
    scanf("%d", &space->bookCode);
    space->l = NULL;
    space->r = NULL;
    if(hptr == NULL)
    {
        hptr = space;
    }
    else
    {
        lb *prev = NULL;
        while(4)
        {
            /* in this we have to loop till we don't find the right(here right mean correct) leaf node where our
            input fit and once we went on the NULL leaf node, it's not possible to come back
            and , that's why we are using prev pointer here, it will store the address of the
            node from where the p recursed from */
            prev = tmptr;
            //comparision is happening, weather to go right or left
            if(strcmp(space->bookName,tmptr->bookName) < 0)
            {
                tmptr = tmptr->l;
            }
            else
            {
                tmptr = tmptr->r;
            }
            if(tmptr == NULL)
            {
                /* once the leaf node, i.e both the node should be NULL has been found then it will go to the
                previous node by prev variable and check that which side the input fit, either left or right
                and it will insert the input accordingly */
                if(strcmp(space->bookName,prev->bookName) < 0)
                {
                    prev->l = space;
                }
                else
                {
                    prev->r = space;
                }
                break;
            }
        }
    }
}

//print function is here
void print(lb *p)
{
    if(p!=NULL)
    {
        print(p->l);
        printf("Book Name: %s\nBook Author: %s\nBook Code: %d\n",p->bookName, p->author, p->bookCode);
        print(p->r);
    }
    printf("-----------------------------------------\n");
}

//search is here
void search(lb *p,char bokName[])
{
    if(p!= NULL)
    {
        if(strcmp(p->bookName,bokName) == 0)
        {
            puts("------------------------------");
            printf("Book Name: %s\nBook Author: %s\nBook Code: %d\n",p->bookName, p->author, p->bookCode);
            return;
        }
        search(p->l,bokName);
        search(p->r,bokName);
    }
}

//delete is here
void delete(lb *p,char bokName[],lb *prev)
{
    /* here prev is storing the address of the previous value of the node 
    to be deleted, i.e it is storing the address of the node before the
    node to be deleted */


    /* These are the recursion steps, if key is less then the value to found then function
    will recurse to right or if key is greated the function will recurse to the right */
    if(strcmp(p->bookName,bokName) < 0)
    {
        delete(p->r,bokName,p);
    }
    else if(strcmp(p->bookName,bokName) > 0)
    {
        delete(p->l,bokName,p);
    }
    //this part of code will run if the value has been found successfully
    else
    {
        //case 1: node to be deleted is the leaf node
        if(p->l == NULL && p->r == NULL)
        {
            /* checking if the node to be deleted has both the node NULL and the p
            itself is equal to hptr the it will just make that hptr to NULL */
            if(p == hptr)
            {
                hptr = NULL;
            }
            /* if the node to be delete has both the node equal to NULL but the  node is not 
            hptr then it will first access the previous node by prev varaible and check that 
            weather left node of prev is NULL or not, in place of checking the left node of
            prev , it is very okay if anyone check the right node */
            else if(prev->l != NULL)
            {
                /* in the prev node if left node is the key then its fine , delete the left node by
                making it NULL, else if left node is not the key , then one thing we are sure that 
                either left node or right node has the key and if left node don't have then of course the
                right node will have to key. so, we delete the right node i.e we make it NULL */
                if(strcmp(prev->l->bookName,bokName) == 0)
                {
                    prev->l = NULL;
                }
                else
                {
                    prev->r = NULL;
                }
            }
            else
            {
                prev->r = NULL;
            }
            return;
        }
        //this is case two, when one of the node is NULL
        else if(p->l == NULL || p->r == NULL)
        {
            //case 1: if p->l is equal to NULL
            if(p->l == NULL)
            {
                //replace the node to be deleted with right node
                lb *temp = p->r;
                strcpy(p->bookName,temp->bookName);
                p->bookCode = temp->bookCode;
                strcpy(p->author,temp->author);
                p->r = temp->r;
                p->l = temp->l;
                return;
            }
            else
            {
                //replace the node with left node
                strcpy(p->bookName,(p->l)->bookName);
                p->bookCode = (p->l)->bookCode;
                strcpy(p->author,(p->l)->author);
                p->r = (p->l)->r;
                p->l = (p->l)->l;
                return;
            }
        }
        //case 3: when both the node are not NULL
        else
        {
            /* this will first check weather if the left node of the right node of p
            is NULL or not cause if it is NULL then we don't have to proceed further,
            we will just stop there and copy the value of p->r tp the p */
            if((p->r)->l == NULL)
            {

                strcpy(p->bookName,(p->r)->bookName);
                p->bookCode = (p->r)->bookCode;
                strcpy(p->author,(p->r)->author);
                p->r = (p->r)->r;
            }
            /* if left node of right node of p is not NULL then it will move until it don't find 
            the last node with both the left node and right node equal to NULL and when it will
            find it will delete that node and copy the node value to the p */
            else
            {
                lb *temp = findLastNode(p->r);
                strcpy(p->bookName,temp->bookName);
                p->bookCode = temp->bookCode;
                strcpy(p->author,temp->author);
                //free(temp);
                temp = NULL;
                free(temp);
            }
        }
    }
}
/* after going in one right node to delete, this function will look for
the last node of the left side */
lb *findLastNode(lb *p)
{
    while(p->l != NULL)
    {
        if(p->l != NULL)
        {
            p = p->l;
        }
        else
        {
            p = p->r;
        }
    }
    return p;
}

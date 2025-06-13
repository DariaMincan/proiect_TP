#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "list.h"

NODE *create_node(NODE *head, int elem)
{
    NODE *node=malloc(sizeof(NODE));
    if(node==NULL)
    {
        perror("Nu s-a alocat dinamic");
        exit(-1);
    }
    node->data=elem;
    node->next=head;
    return node;
    
}

void delete_node(NODE *head, int elem)
{
    NODE *temp=head;
    NODE *previous=NULL;
    if(temp!=NULL && temp->data==elem)
    {
        head=temp->next;
        free(temp);
        return;
    }

    while(temp!=NULL && temp->data!=elem)
    {
        previous=temp;
        temp=temp->next;
    }

    if(temp==NULL)
    {
        return;
    }

    previous->next=temp->next;
    free(temp);

}

void free_list(NODE *head)
{
    if(head)
    {
        free_list(head->next);
        free(head);
    }
}

void print_list(NODE *head)
{
    while(head)
    {
        printf("%d " , head->data);
        head=head->next;
    }
}

void add_medie(NODE *head, int pozitie)
{
    NODE *temp=head;
    NODE *previous=NULL;
    int poz=1;
    while(pozitie!=poz && temp!=NULL)
    {
        temp=temp->next;
        poz++;
    }
    NODE *new_node=malloc(sizeof(NODE));
    new_node->value=(temp->value+temp->next->value)/2;
    new_node->next=temp->next;
    temp->next=new_node;

}
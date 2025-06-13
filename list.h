#ifndef __list__
#define __list__
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}NODE;


NODE *create_node(NODE * , int);
void delete_node(NODE * , int);
void add_medie(NODE *, int);


#endif
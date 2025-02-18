#ifndef _LIST_MEM_
#define _LIST_MEM_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "Lista.h"

typedef struct Lista_MEM
{
    FILE *ref;
    char *file_name;
    long maxSize;
    int size;

}Lista_MEM_t;


struct Lista_MEM *new_Lista_MEM(char file_name[21]);

void ListMEM_insert(Lista_MEM_t *lista,struct node *pais);

void ListMEM_send_to(Lista_MEM_t *lista,struct list *main_memory);

void ListMEM_saveSize(Lista_MEM_t *lista,int n);

#endif 

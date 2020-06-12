#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "Lista.h"
#include "Lista_MEM.h"

#define SIZE_LIST 401



Lista_MEM_t* new_Lista_MEM(char file_name[21]){
    
    Lista_MEM_t *new = malloc(sizeof(Lista_MEM_t));
    
    new->maxSize = SIZE_LIST;
    new->file_name=file_name;
    new->ref = fopen(file_name, "r+");
    if( new->ref== NULL){
        
        new->ref = fopen(file_name, "w+");
        new->size=1; //size 0
    }
    else
    {
        fseek(new->ref, 0, SEEK_SET);
        fread(&new->size, sizeof(int), 1, new->ref);
    }

    return new;
}



void ListMEM_send_to(Lista_MEM_t *lista,list_t *main_memory)
{
    country_t current_country;

    fseek(lista->ref, 0, SEEK_SET);
    fwrite(&lista->size, sizeof(int), 1, lista->ref);

    for(int i =1;i < lista->size;i++)
    {
        int offset = sizeof(struct country)*i;
        fseek(lista->ref, offset, SEEK_SET);
        fread(&current_country, sizeof(struct country), 1, lista->ref);

        node_t *new_node = newNode();
        new_node->country=current_country;
        list_insert_node(main_memory,new_node);
    }   
}

void ListMEM_saveSize(Lista_MEM_t *lista,int n)
{
    fseek(lista->ref, 0, SEEK_SET);
    fwrite(&n, sizeof(int), 1, lista->ref);
}



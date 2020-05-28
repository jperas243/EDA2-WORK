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
        //printf("Size MEM sem dat:%d\n",new->size);
    }
    else
    {
        fseek(new->ref, 0, SEEK_SET);
        fread(&new->size, sizeof(int), 1, new->ref);
        //printf("Size MEM com dat:%d\n",new->size);

    }

    return new;
}



void ListMEM_send_to(Lista_MEM_t *lista,list_t *main_memory)
{
    country_t current_country;

    //ListMEM_printf(lista);

    fseek(lista->ref, 0, SEEK_SET);
    fwrite(&lista->size, sizeof(int), 1, lista->ref);

    //printf("Size RAM:%d",lista->size+1);
    for(int i =1;i < lista->size;i++)
    {
        int offset = sizeof(struct country)*i;
        fseek(lista->ref, offset, SEEK_SET);
        fread(&current_country, sizeof(struct country), 1, lista->ref);

        //printf("%s\n",current_country.country_name);
        node_t *new_node = newNode();
        new_node->country=current_country;
        list_insert_node(main_memory,new_node);
    }

    //list_print_content(main_memory);

    
}

void ListMEM_saveSize(Lista_MEM_t *lista,int n)
{
    fseek(lista->ref, 0, SEEK_SET);
    fwrite(&n, sizeof(int), 1, lista->ref);
}


void ListMEM_printf(Lista_MEM_t *lista)
{
    country_t current_country;

    printf("\nMEM:[");
    for(int i =1;i < lista->size;i++)
    {
        int offset = sizeof(struct country)*i;
        fseek(lista->ref, offset, SEEK_SET);
        fread(&current_country, sizeof(struct country), 1, lista->ref);

        printf("+ %s - correntes: %li, diplomandos: %li, abandonaram: %li, total: %li\n",
                current_country.country_name, current_country.num_active_students, current_country.num_done_students, current_country.num_left_students,
                current_country.num_active_students+ current_country.num_done_students+current_country.num_left_students);
        
    }
    printf("]\n");
}

/*

int main(int argc, char const *argv[])
{
    Lista_MEM_t *ola = new_Lista_MEM("boas.dat");
    ListMEM_delete(ola);
    return 0;
}
 */

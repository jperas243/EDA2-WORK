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
    new->index = 0;
    new->file_name=file_name;
    new->ref = fopen(file_name, "r+");
    if( new->ref== NULL)
        new->ref = fopen(file_name, "w+");

    return new;
}

void ListMEM_insert(Lista_MEM_t *lista,node_t *pais)
{
    country_t current_country = pais->country;
    
    int offset = sizeof(struct country)*lista->index;
    lista->index++;
    fseek(lista->ref, offset, SEEK_SET);
    fwrite(&current_country, sizeof(struct country), 1, lista->ref);
}

void ListMEM_send_to(Lista_MEM_t *lista,list_t *main_memory)
{
    country_t current_country;

    for(int i =0;i < lista->index;i++)
    {
        int offset = sizeof(struct country)*i;
        fseek(lista->ref, offset, SEEK_SET);
        fread(&current_country, sizeof(struct country), 1, lista->ref);

        node_t *new_node = newNode();
        new_node->country=current_country;
        list_insert_node(main_memory,new_node);
    }
    
}

void ListMEM_delete(Lista_MEM_t *lista)
{
    remove(lista->file_name);
    free(lista);
}

void ListMEM_newfile(Lista_MEM_t *lista,char *file_name)
{
    remove(lista->file_name);
    lista = new_Lista_MEM(file_name);
}

/*

int main(int argc, char const *argv[])
{
    Lista_MEM_t *ola = new_Lista_MEM("boas.dat");
    ListMEM_delete(ola);
    return 0;
}
 */

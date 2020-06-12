#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "Lista_MEM.h"


country_t *newCountry()
{
    country_t *new = malloc(sizeof(country_t));
    return new;
}

node_t *newNode()
{
    node_t *new = NULL;
    new = malloc(sizeof(node_t));
    new->next = NULL;
    return new;
}

list_t *newList()
{
    list_t *new = malloc(sizeof(list_t));
    new->header = newNode();
    new->size = 0;
    return new;
}


//Escreve na consola a informacao de um dado pais
void list_print(list_t *list, char *cod){
    
    node_t *current = newNode();
    current = list->header->next;
    while (current!=NULL)
    {
        if (strcmp(current->country.country_name, cod) == 0 )
        {
            if (current->country.num_active_students+ current->country.num_done_students+current->country.num_left_students!=0)
            {
                printf("+ %s - correntes: %u, diplomados: %u, abandonaram: %u, total: %u\n",
                cod, current->country.num_active_students, current->country.num_done_students, current->country.num_left_students,
                current->country.num_active_students+ current->country.num_done_students+current->country.num_left_students);
            }
            else
            {
                printf("+ sem dados sobre %s\n",current->country.country_name);
            }
            
        }
        current=current->next;

    }
}


//Insere na lista em memora central um novo pais
void list_insert(list_t *list, char *cod){
  

    node_t *new = newNode();

    strcpy(new->country.country_name,cod);
    new->country.num_active_students=1;
    new->country.num_done_students=0;
    new->country.num_left_students=0;

    new->next=list->header->next;
    list->header->next=new;

    list->size++;
    
}

void list_insert_node(list_t *list, node_t *country){
  
    country->next=list->header->next;
    list->header->next=country;
    list->size++;
    
}

node_t *list_find(list_t *list, char *cod)
{
    node_t *current = list->header->next;

    if (current==NULL)
    {
        return NULL;
    }

    while (current!=NULL)
    {
        if (strcmp(current->country.country_name, cod) == 0)
        {
            return current;
        }
        current=current->next;
    }
    
    return NULL;
}

void increment_of(node_t *node,char *var)
{
    if (strcmp(var,"active")==0)
    {
        node->country.num_active_students++;
    }
    else if (strcmp(var,"done")==0)
    {
        node->country.num_done_students++;
    }
    else if (strcmp(var,"left")==0)
    {
        node->country.num_left_students++;
    }

}

void decrement_of(node_t *node,char *var)
{
    if (strcmp(var,"active")==0)
    {
        node->country.num_active_students--;
    }
    else if (strcmp(var,"done")==0)
    {
        node->country.num_done_students--;
    }
    else if (strcmp(var,"left")==0)
    {
        node->country.num_left_students--;
    }
}


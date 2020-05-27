#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct country
{
    char country_name[3]; 
    long num_active_students, 
        num_done_students,
        num_left_students; 

} country_t;


typedef struct node {
    
    country_t country;
    struct node *next ;

} node_t;

typedef struct list {
   
    node_t *header;

}list_t;

country_t *newCountry()
{
    country_t *new = malloc(sizeof(country_t));
    return new;
}

node_t *newNode(){
    
    node_t *new = malloc(sizeof(node_t));
    return new;
}

list_t *newList(){
    
    list_t *new = malloc(sizeof(list_t));
    new->header = newNode();
    return new;
}

void list_print(list_t *list, char *cod) {
    
    node_t *current = newNode();
    current = list->header->next;
    while (current!=NULL)
    {
        if (strcmp(current->country.country_name, cod) == 0 )
        {
            if (current->country.num_active_students+ current->country.num_done_students+current->country.num_left_students!=0)
            {
                printf("+ %s - correntes: %li, diplomandos: %li, abandonaram: %li, total: %li\n",
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

void list_insert(list_t *list, char *cod){
  

    node_t *new = newNode();
    strcpy(new->country.country_name,cod);
    new->country.num_active_students=1;
    new->country.num_done_students=0;
    new->country.num_left_students=0;

    new->next=list->header->next;
    list->header->next=new;
    
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

void list_print_content(list_t *lista)
{
    node_t *current = lista->header->next;

    printf("[");
    while (current!=NULL)
    {
        list_print(lista,current->country.country_name);
        current=current->next;
    }
    printf("]\n");

}

/*

int main(int argc, char const *argv[])
{
    list_t *list = newList();
    
    //printf("%d",list_search(list,"PT"));
    list_insert(list, "PT");
    node_t *ola = list_find(list,"PT");
    printf("%s",ola->country.country_name);

    //list_print(list, "PT");
    return 0;
}
*/

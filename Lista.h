#ifndef _LIST_
#define _LIST_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct country
{
    char country_name[3]; 
    unsigned int num_active_students, 
    num_done_students,
    num_left_students; 

} country_t;


typedef struct node {
    
    country_t country;
    struct node *next ;

} node_t;

typedef struct list {
   
    node_t *header;
    int size;

}list_t;

struct country *newCountry();
struct node *newNode();
struct list *newList();

void list_print(list_t *list, char *cod);
void list_insert(list_t *list, char *cod);
void list_insert_node(list_t *list, struct node *country);
struct node *list_find(list_t *list, char *cod);
void increment_of(node_t *node,char *var);
void decrement_of(node_t *node,char *var);
void list_print_content(list_t *lista);

#endif

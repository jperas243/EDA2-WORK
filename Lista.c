#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#include "HashTable.c"

#define LISTSAVE "countries.bin"


typedef struct node {
    country_t *country;
    struct node *next ;
} node_t;

typedef struct list {
    node_t *header;
}list_t;

node_t *newNode(){
    node_t *new = malloc(sizeof(node_t));
    return new;
}

list_t *newList(){
    list_t *new = malloc(sizeof(list_t));
    node_t *header_new = newNode();
    new->header = header_new;
    return new;
}
void list_print(list_t *list, char *cod) {
    node_t *current = newNode();
    current = list->header->next;
    while (current)
    {
        if (strcmp(current->country->country_name, cod) == 0)
        {
            printf("+ %s - correntes: %li, diplomandos: %li, abandonaram: %li, total: %li\n",
            cod, current->country->num_active_students, current->country->num_done_students, 
            current->country->num_left_students, current->country->num_total_students);
        }
    }
}

node_t *list_search(list_t *list, char *cod){
    node_t *current = newNode();
    current = list->header->next;
    if (list->header->next == NULL)
    {
        return NULL;
    }
    
    while (current->next != NULL)
    {
        printf("%s %s\n", current->country->country_name, cod);
        sleep(2);
        if (strcmp(current->country->country_name, cod) == 0)
        {
            printf("ola");
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void list_insert(list_t *list, char *cod){
  
    if (list_search(list, cod) == NULL)
    {
        node_t *newValue = newNode();
        newValue->country->country_name = cod;
        newValue->country->num_active_students = 1;
        newValue->country->num_done_students = 0; 
        newValue->country->num_left_students = 0;
        newValue->country->num_total_students = 1; 

        node_t *current =list->header;

        while (current->next != NULL)
        {
            current = current->next;
        }
    
        current->next = newValue;        
    }    
}

int main(int argc, char const *argv[])
{
    list_t *list = newList();
    list_insert(list, "PT");
    //list_print(list, "PT");
    return 0;
}



/*
void add_tail(struct node *headptr, int val) {
    struct node *tmp = headptr;
    struct node *tmp2 = malloc(sizeof(struct node)) ;
    tmp2->val = val ;
    tmp2->next=NULL ;

    while(tmp->next) {
        tmp=tmp->next ;
    }
    tmp->next=tmp2 ;
}

void del_list(struct node *headptr) {
    struct node *tmp = headptr->next ;
    struct node *tmp2 = NULL ;
    while (tmp) {
        tmp2=tmp->next ;
        free(tmp);
        tmp=tmp2 ;
    }
    headptr->next=NULL ;
}

void save_list(struct node *headptr) {
    FILE *text = fopen(LISTSAVE, "wb+") ;
    struct node *tmp=headptr->next ;
    int cnt=0 ;

    if ( text==NULL || headptr==NULL ) {
        printf("filed to save.\n") ;
        return ;
    }
    while (tmp!=NULL ) {
        cnt++ ;
        fwrite(&tmp->val, sizeof(int), 1, text) ;
        tmp = tmp->next ;
    }
    fclose(text) ;
    printf("write %d items ok\n", cnt) ;
}

void read_list(struct node *headptr) {
    FILE *text = fopen(LISTSAVE, "rb") ;
    int val ;
    int cnt=0 ;
    while( fread(&val, sizeof(int), 1, text) > 0 ) {
        add_tail(headptr, val) ;
        cnt++ ;
    }
    fclose(text);
    printf("read %d items ok\n", cnt) ;
}

*/
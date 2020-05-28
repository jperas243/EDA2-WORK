#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

struct country;
struct node;
struct list;

struct country *newCountry();
struct node *newNode();
struct list *newList();

void list_print(struct list, char *cod);
void list_insert(struct list, char *cod);
void list_insert_node(struct list *list, struct node *country);
struct node *list_find(struct list *list, char *cod);
void increment_of(struct node *node,char *var);
void decrement_of(struct node *node,char *var);
void list_print_content(struct list *lista);


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "Lista.h"

struct Lista_MEM;


struct Lista_MEM *new_Lista_MEM(char file_name[21]);

void ListMEM_insert(struct Lista_MEM *lista,struct node *pais);

void ListMEM_send_to(struct Lista_MEM *lista,struct node *main_memory);

void ListMEM_delete(struct Lista_MEM *lista);

void ListMEM_newfile(struct Lista_MEM *lista,char *file_name);



#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Lista.h"

#define INEXISTENTE -3
#define ABANDONOU -2
#define TERMINOU -1

typedef struct hashTable{
    
    FILE *ref;
    long maxSize;

}HashTable_t;

typedef struct student {

    char id[7]; 
    char country[3];
    bool done;
    bool left;
    bool invalid_position;
    bool removed;

}student_t;

struct hashTable* new_HashTable(char file_name[21]);
student_t clear_student(student_t n);


long hash(char *str);
long aux_func(int n);
long position_process(HashTable_t *table,char *name);
bool insert_hashtable(HashTable_t *table,student_t student);
int find_apply_hashtable(HashTable_t *table,char *id, char *option, list_t *lista);

#endif

#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


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

}student_t;

struct hashTable* new_HashTable(char file_name[21]);

long hash(char *str);
long aux_func(int n);
long position_process(HashTable_t *table,char *name);
bool insert_hashtable(HashTable_t *table,student_t student);
int find_hashtable(HashTable_t *table,char *id);
int remove_hashtable(HashTable_t *table,char *id);

#endif

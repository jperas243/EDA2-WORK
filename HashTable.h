#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct hashTable;
struct student;

struct hashTable* new_HashTable(char file_name[21]);

unsigned long hash(char *str);
long aux_func(int n);
long position_process(struct hashTable *table,char *name);
bool insert_hashtable(struct hashTable *table,struct student student);
int find_hashtable(struct hashTable *table,char *id);
int remove_hashtable(struct hashTable *table,char *id);



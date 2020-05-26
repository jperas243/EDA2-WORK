#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 20000003;

typedef struct hashTable{
    int maxSize;
    FILE *ref;

 }HashTable_t;

typedef struct student {

    char *student_id; 
    char *student_country;
    bool student_done;
    bool student_left;
    bool invalid_position;

} student_t;

HashTable_t* new_HashTable(char file_name[21]){
    HashTable_t *new = malloc(sizeof(HashTable_t));
    new->maxSize = SIZE;
    if(fopen(file_name, "r+") == NULL)
        new->ref = fopen(file_name, "w+");

    return new;
    
}

student_t *new_student(char *id, char *country){
    student_t *new = malloc(sizeof(student_t));
    new->student_id = id;
    new->student_country = country;
    new->student_done = false;
    new->student_left = false;
    new->invalid_position = true;

    return new;
}

int hashCode(const char *str) {
    int hash = 0;
    for (int i = 0; i < strlen(str); i++)
        hash = 31 * hash + str[i];
    return hash % SIZE;
}

int position_process(char *id, char *country)
{



/*
    if()
    {

    }
*/

    //return hash;
}

int aux_func(int n)
{
    return n*n;
}

bool insert_hashtable(char *id, char *cod) {

    return false;  
  
}

int main(int argc, char const *argv[])
{
    HashTable_t *alunos = new_HashTable("teste.dat");

    



    return 0;
}
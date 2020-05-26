#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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

void new_HashTable(int size, char *file_name){
    HashTable_t *new = malloc(sizeof(HashTable_t));
    new->maxSize = size;
    if(fopen(file_name, "r+") == NULL)
        new->ref = fopen(file_name, "w+");

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

bool insert(char *id, char *country, HashTable_t hashTable) {
    


}

int main(int argc, char const *argv[])
{
    new_HashTable(20000003, "data.bin");

    return 0;
}
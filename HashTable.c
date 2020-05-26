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

    char student_id[7]; 
    char student_country[3];
    bool student_done;
    bool student_left;
    bool invalid_position;

} student_t;

HashTable_t* new_HashTable(char file_name[21]){
    
    HashTable_t *new = malloc(sizeof(HashTable_t));
    new->maxSize = SIZE;
    new->ref = fopen(file_name, "r+");
    if( new->ref== NULL)
        new->ref = fopen(file_name, "w+");

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

bool insert_hashtable(HashTable_t table,char *id, char *cod) {

    //fread();
    return false;  
  
}

int remove_hashtable(HashTable_t table,char *id)
{
    return 0;
}

int find_hashtable(HashTable_t table,char *id)
{
    return 0;
}

int main(int argc, char const *argv[])
{
    //HashTable_t *alunos = new_HashTable("teste.dat");
    FILE *ref = fopen("teste.dat","wb+");

    student_t aluno1;
    strcpy(aluno1.student_id,"ABFC12");
    student_t aluno2;
    strcpy(aluno2.student_id,"ABFC30");



    int offset = sizeof(struct student)*0;
    fseek(ref, offset, SEEK_SET);
    
    fwrite(&aluno1,sizeof(struct student),1,ref);


    offset = sizeof(struct student)*0;
    fseek(ref, offset, SEEK_SET);

    fread(&aluno2, sizeof(struct student), 1, ref);

    printf("%s\n",aluno2.student_id);


    return 0;
}
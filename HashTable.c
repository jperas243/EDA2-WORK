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

    char id[7]; 
    char country[3];
    bool done;
    bool left;
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


unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%SIZE;
}

int aux_func(int n)
{
    return n*n;
}

int position_process_id(HashTable_t *table,char *id)
{
    int position = hash(id);
    int counter = 1;
    student_t atual;

    if (position<0){
        position=0-position;
    }

    int offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&atual, sizeof(struct student), 1, table->ref);

    while (atual.invalid_position)
    {
        if (position<0){
            position=0-position;
        }
        
        position=(position+aux_func(counter))%SIZE;
        
        int offset = sizeof(struct student)*position;
        fseek(table->ref, offset, SEEK_SET);
        fread(&atual, sizeof(struct student), 1, table->ref);
        counter++;
    }

    return position;
    
}


bool insert_hashtable(HashTable_t *table,student_t student) {

    int hash = position_process_id(table,student.id);
    printf("%d",hash);
    
    if (hash==-1)
    {
        return false;
    }
    else
    {
        student.done=false;
        student.left=false;
        student.invalid_position=true;

        int offset = sizeof(struct student)*hash;
        fseek(table->ref, offset, SEEK_SET);
        fwrite(&student, sizeof(struct student), 1, table->ref);

        return true;
    }
    
    

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

/*

int main(int argc, char const *argv[])
{
    HashTable_t *alunos = new_HashTable("teste.dat");

    student_t aluno1;
    strcpy(aluno1.id,"ABFC12");
    student_t aluno2;
    strcpy(aluno2.id,"ABFC30");



    int offset = sizeof(struct student)*0;
    fseek(alunos->ref, offset, SEEK_SET);
    
    fwrite(&aluno1,sizeof(struct student),1,alunos->ref);


    offset = sizeof(struct student)*0;
    fseek(alunos->ref, offset, SEEK_SET);

    fread(&aluno2, sizeof(struct student), 1, alunos->ref);

    printf("%s\n",aluno2.id);


    return 0;
}

*/

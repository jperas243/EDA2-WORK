#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 20000003;

typedef struct hashTable{
    int maxSize;
    FILE *ref;

}HashTable_t;

typedef struct country
{
    char country_name[3]; 
    long num_total_students,num_active_students, num_done_students,num_left_students; 

} country_t;

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

/*
void disk_read(struct estrutura)
{

}
*/

void disk_write()
{

}


unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++){
        
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash%SIZE;
}

long aux_func(int n)
{
    return n*n;
}

long position_process(HashTable_t *table,char *id)
{
    long position = (long)hash(id);
    int counter = 1;
    student_t atual;

    if (position<0){
        position=0-position;
    }

    int offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&atual, sizeof(struct student), 1, table->ref);

    if (strcmp(atual.id,id)==0 && atual.invalid_position==true)
    {
        return -1;
    }
    
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

        printf("%s %s\n",atual.id,id);
        if (strcmp(atual.id,id)==0 && atual.invalid_position==true)
        {
            return -1;
        }


        //printf("%s %ld\n",atual.id,position);
        //sleep(2);
    }

    return position;
    
}


bool insert_hashtable(HashTable_t *table,student_t student) {

    int hash = position_process(table,student.id);
    printf("%d\n",hash);
    
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

int find_hashtable(HashTable_t *table,char *id)
{
    long position = (long)hash(id);
    int counter = 1;
    student_t atual;

    if (position<0){
        position=0-position;
    }

    int offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&atual, sizeof(struct student), 1, table->ref);

    printf("%li %s\n",position,atual.id);
    sleep(2);
    if (strcmp(atual.id,id)==0 && atual.invalid_position==true)
    {
        return position;
    }
    
    while (atual.invalid_position==true)
    {
        if (position<0){
            position=0-position;
        }
        
        position=(position+aux_func(counter))%SIZE;
        
        int offset = sizeof(struct student)*position;
        fseek(table->ref, offset, SEEK_SET);
        fread(&atual, sizeof(struct student), 1, table->ref);
        counter++;

        printf("%li %s\n",position,atual.id);
        sleep(2);

        if (strcmp(atual.id,id)==0 && atual.invalid_position==true)
        {
            return position;
        }
    }
    return -1;
}

int remove_hashtable(HashTable_t *table,char *id)
{
    int position = find_hashtable(table,id);
    student_t to_remove;
    printf("%d\n",position);

    long offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&to_remove, sizeof(struct student), 1, table->ref);

    if (position==-1)
    {
        return 0; //nao existente
    }
    else if (to_remove.done==true)
    {
        return -1; //terminou o curso
    }
    else if (to_remove.left==true)
    {
        return -2; //abandonou o curso
    }
    else
    {
        to_remove.invalid_position=false;

        fseek(table->ref, offset, SEEK_SET);
        fwrite(&to_remove, sizeof(struct student), 1, table->ref);
    }

    return 1; //sucesso
}

/*

int main(int argc, char const *argv[])
{
    HashTable_t *alunos = new_HashTable("teste.dat");

    student_t aluno1;
    strcpy(aluno1.id,"ABFC12");
    strcpy(aluno1.country,"PT");
    aluno1.done=false;
    aluno1.left=false;
    aluno1.invalid_position=true;

    printf("%d----\n",find_hashtable(alunos,"ABFC12"));
    printf("%d----\n",remove_hashtable(alunos,"ABFC12"));
    printf("%d----\n",insert_hashtable(alunos,aluno1));
    printf("%d----\n",find_hashtable(alunos,"ABFC12"));





    return 0;
}
*/


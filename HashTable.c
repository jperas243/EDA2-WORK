#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "HashTable.h"
#include "Lista.h"

#define SIZE 20000003

HashTable_t* new_HashTable(char file_name[21]){
    
    HashTable_t *new = malloc(sizeof(HashTable_t));
    new->maxSize = SIZE;
    new->ref = fopen(file_name, "r+");
    if( new->ref== NULL)
        new->ref = fopen(file_name, "w+");

    return new;
}

student_t clear_student(student_t n)
{
    strcpy(n.id,"\0");
    strcpy(n.country,"\0");
    n.removed=false;
    n.invalid_position=false;
    n.left=false;
    n.done=false;

    return n;
}

long hash(char *str)
{
    long hash = 0;
    int length=6;
    
    for (int i = 0; i < 6; i++)
    {
        hash = + hash + (str[i]-48)*pow(23,length);
        length--;
    }

    if(hash < 0){
        hash = -1 * hash;
    }

    return hash;
}

long aux_func(int n)
{
    return n*n;
}

long position_process(HashTable_t *table,char *name)
{
    long position = hash(name)%SIZE;
    long save=position;

    int counter = 1;
    
    student_t atual;
    
    atual=clear_student(atual);
    long offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&atual, sizeof(struct student), 1, table->ref);

    //printf("READ: ID %s: Atual.ID: %s, INVALID: %d, REMOVED: %d, DONE: %d, LEFT: %d, POSITION:%ld\n", name ,atual.id, atual.invalid_position,atual.removed,atual.done,atual.left,position );


    //printf("position: %li\n,atual.id: %d,atual.removed: %d\n",position,strcmp(atual.id,name)==0, atual.removed);

    if (strcmp(atual.id,name)==0 && atual.removed && atual.invalid_position)
    {
        
        return position;
    }

    if (strcmp(atual.id,name)==0 && !atual.removed && atual.invalid_position)
    {
        return -1;
    }
    
    //printf("atual.invalid_position: %d\n",atual.invalid_position);
    while (atual.invalid_position)
    {
        
        position=(save+aux_func(counter))%SIZE;
        counter++;

        if (position<0){
            position=0-position;
        }

        atual=clear_student(atual);
        offset = sizeof(struct student)*position;
        fseek(table->ref, offset, SEEK_SET);
        fread(&atual, sizeof(struct student), 1, table->ref);

        //printf("READ AGAIN: ID %s: Atual.ID: %s, INVALID: %d, REMOVED: %d, DONE: %d, LEFT: %d, POSITION:%ld, OFFSET:%ld\n", name ,atual.id, atual.invalid_position,atual.removed,atual.done,atual.left,position, offset);
        //printf("%s %s\n",atual.id,name);
        if (strcmp(atual.id,name)==0 && atual.removed)
        {
            
            return position;
        }

        if (strcmp(atual.id,name)==0 && !atual.removed)
        {
            return -1;
        }

        
    }
    
    //printf("NO CYCLE,POSITION:%li \n",position);
    return position;
    
}

bool insert_hashtable(HashTable_t *table,student_t student) {

    long hash = position_process(table,student.id);
    
    //printf("hash: %ld\n",hash);
    //printf("%d\n",hash);
    //printf("posicao %s: %d\n", student.id, hash);
    if (hash==-1)
    {
        return false;
    }
    else
    {
        student.done=false;
        student.left=false;
        student.removed=false;
        student.invalid_position=true;

        long offset = sizeof(struct student)*hash;
        fseek(table->ref, offset, SEEK_SET);
        fwrite(&student, sizeof(struct student), 1, table->ref);
        //printf("WRITE INSERT: ID %s: INVALID: %d,REMOVED: %d, DONE: %d, LEFT: %d, POSITION:%ld\n", student.id, student.invalid_position,student.removed,student.done,student.left,hash);
        student=clear_student(student);


        return true;
    }
    return false;  
  
}

int find_apply_hashtable(HashTable_t *table,char *id, char *option, list_t *lista) //option : done,left,remove
{
    long position = hash(id)%SIZE;
    long save = position;
    //printf("position: %li\n", position);
    int hash_aux_counter = 1;
    
    student_t atual;
    
    atual=clear_student(atual);
    long offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&atual, sizeof(struct student), 1, table->ref);   

    //printf("READ: ID %s: Atual.ID: %s, INVALID: %d, REMOVED: %d, DONE: %d, LEFT: %d, POSITION:%ld\n", id ,atual.id, atual.invalid_position, atual.removed, atual.done, atual.left, position);

    while (atual.invalid_position==true)
    {   

        if (strcmp(atual.id,id)==0)
        {
            /* code */
            if (strcmp(option, "remove") == 0)
            { 
                if (atual.removed==true) //atual.done==true && atual.removed==true
                {
                    if (atual.left==true)
                    {
                    return -2; //abandonou o curso
                    }
                    if (atual.done==true) //atual.removed==true
                    {
                    return -1; //terminou o curso
                    }
                    
                    return -3;
                }
                else if (atual.left==true)
                {
                    return -2; //abandonou o curso
                }
                else if (atual.done==true) //atual.removed==true
                {
                    return -1; //terminou o curso
                }
                else
                {   
                    atual.removed = true;

                    node_t *current = list_find(lista, atual.country);
                    decrement_of(current,"active");

                    offset = sizeof(struct student)*position;
                    fseek(table->ref, offset, SEEK_SET);
                    fwrite(&atual, sizeof(struct student), 1, table->ref);  //sucesso
                    //printf("WRITE REMOVED: ID %s: INVALID: %d,REMOVED: %d, DONE: %d, LEFT: %d, POSITION:%ld\n", atual.id, atual.invalid_position,atual.removed,atual.done,atual.left,position );
                    atual=clear_student(atual);
                    return 0;
                }

                return -3;
            }
            
            if (strcmp(option, "done") == 0)
            {
                //printf("done: %d", atual.done);
                if (atual.removed==true) //atual.done==true && atual.removed==true
                {
                    if (atual.left==true)
                    {
                    return -2; //abandonou o curso
                    }
                    if (atual.done==true) //atual.removed==true
                    {
                    return -1; //terminou o curso
                    }
                    
                    return -3;
                }
                else if (atual.left==true)
                {
                    return -2; //abandonou o curso
                }
                else if (atual.done==true) //atual.removed==true
                {
                    return -1; //terminou o curso
                }
                else //if(atual.removed == true) {return -3}
                {
                    atual.done=true;

                    node_t *current = list_find(lista, atual.country);      
                    decrement_of(current,"active");
                    increment_of(current,"done");

                    offset = sizeof(struct student)*position;
                    fseek(table->ref, offset, SEEK_SET);
                    fwrite(&atual, sizeof(struct student), 1, table->ref);

                    //printf("WRITE DONE: ID %s: INVALID: %d,REMOVED: %d, DONE: %d, LEFT: %d, POSITION:%ld\n", atual.id, atual.invalid_position,atual.removed,atual.done,atual.left,position );
                    return 0;
                }
            }
            
            if (strcmp(option, "left") == 0)
            {
                if (atual.removed==true) //atual.done==true && atual.removed==true
                {
                    if (atual.left==true)
                    {
                    return -2; //abandonou o curso
                    }
                    if (atual.done==true) //atual.removed==true
                    {
                    return -1; //terminou o curso
                    }
                    
                    return -3;
                }
                else if (atual.left==true)
                {
                    return -2; //abandonou o curso
                }
                else if (atual.done==true) //atual.removed==true
                {
                    return -1; //terminou o curso
                }
                else
                {
                    atual.left=true;
                    node_t *current = list_find(lista, atual.country);
                    decrement_of(current,"active");
                    increment_of(current,"left");
                    
                    long offset = sizeof(struct student)*position;
                    fseek(table->ref, offset, SEEK_SET);
                    fwrite(&atual, sizeof(struct student), 1, table->ref);
                    //printf("WRITE LEFT: ID %s: INVALID: %d,REMOVED: %d, DONE: %d, LEFT: %d, POSITION:%ld\n", atual.id, atual.invalid_position,atual.removed,atual.done,atual.left,position );
                    
                    atual=clear_student(atual);
                    return 0;
                }
            }            
        }

        position=(save+aux_func(hash_aux_counter))%SIZE;
        hash_aux_counter++;
        
        atual=clear_student(atual);
        offset = sizeof(struct student)*position;
        fseek(table->ref, offset, SEEK_SET);
        fread(&atual, sizeof(struct student), 1, table->ref);
        
        //printf("READ AGAIN: ID %s: Atual.ID: %s, INVALID: %d, REMOVED: %d, DONE: %d, LEFT: %d, POSITION:%ld\n", id ,atual.id, atual.invalid_position, atual.removed, atual.done, atual.left, position);


        
    }
    return -3; //aluno inexistente
}


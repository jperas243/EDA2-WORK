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

//Esta funcao retorna uma struct student_t com os valores 'limpos'
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

//Gera um hash-code a partir de uma string
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

//Funcao que lida com as colisoes de forma quadratica
long aux_func(int n)
{
    return n*n;
}

//Retorna o primeiro indice onde um aluno possa ser inserido na HashTable
long position_process(HashTable_t *table,char *name)
{
    long position = hash(name)%SIZE;
    long save=position;

    int hash_aux_counter = 1;
    
    student_t atual;
    
    atual=clear_student(atual);
    long offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&atual, sizeof(struct student), 1, table->ref);

    if (strcmp(atual.id,name)==0 && atual.removed && atual.invalid_position)
    {
        
        return position;
    }

    if (strcmp(atual.id,name)==0 && !atual.removed && atual.invalid_position)
    {
        return -1;
    }
    
    while (atual.invalid_position)
    {
        
        position=(save+aux_func(hash_aux_counter))%SIZE;
        hash_aux_counter++;

        if (position<0){
            position=0-position;
        }

        atual=clear_student(atual);
        offset = sizeof(struct student)*position;
        fseek(table->ref, offset, SEEK_SET);
        fread(&atual, sizeof(struct student), 1, table->ref);

        if (strcmp(atual.id,name)==0 && atual.removed)
        {
            
            return position;
        }

        if (strcmp(atual.id,name)==0 && !atual.removed)
        {
            return -1;
        }

        
    }

    return position;
    
}

//Retorna true/false se um aluno pode ser ou nao inserido na HashTable
bool insert_hashtable(HashTable_t *table,student_t student) {

    long hash = position_process(table,student.id);
    
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
        student=clear_student(student);

        return true;
    }

    return false;  
}

/*Esta funcao e responsavel por encontrar um aluno e aplicar uma das seguintes operacoes: remover, abanonar ou terminar.
Defenidas pela string 'option': 'remove', 'left' ou 'done', respetivamente.
Retorna um inteiro de acordo com o estado do aluno e a operacao pretendida.*/
int find_apply_hashtable(HashTable_t *table,char *id, char *option, list_t *lista) 
{
    long position = hash(id)%SIZE;
    long save = position;
    int hash_aux_counter = 1;
    
    student_t atual;
    
    atual=clear_student(atual);
    long offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&atual, sizeof(struct student), 1, table->ref);   


    while (atual.invalid_position)
    {   

        if (strcmp(atual.id,id)==0)
        {
            /* code */
            if (strcmp(option, "remove") == 0)
            { 
                if (atual.removed) 
                {
                    if (atual.left)
                    {
                    return ABANDONOU; //abandonou o curso
                    }
                    if (atual.done) 
                    {
                    return TERMINOU; //terminou o curso
                    }
                    
                    return INEXISTENTE;
                }
                else if (atual.left)
                {
                    return ABANDONOU; //abandonou o curso
                }
                else if (atual.done) 
                {
                    return TERMINOU; //terminou o curso
                }
                else
                {   
                    atual.removed = true;

                    node_t *current = list_find(lista, atual.country);
                    decrement_of(current,"active");

                    offset = sizeof(struct student)*position;
                    fseek(table->ref, offset, SEEK_SET);
                    fwrite(&atual, sizeof(struct student), 1, table->ref);  //sucesso
                    atual=clear_student(atual);
                    return 0;
                }

                return INEXISTENTE;
            }
            
            if (strcmp(option, "done") == 0)
            {
               
                if (atual.removed) 
                {
                    if (atual.left)
                    {
                    return ABANDONOU; //abandonou o curso
                    }
                    if (atual.done) 
                    {
                    return TERMINOU; //terminou o curso
                    }
                    
                    return INEXISTENTE;
                }
                else if (atual.left)
                {
                    return ABANDONOU; //abandonou o curso
                }
                else if (atual.done) 
                {
                    return TERMINOU; //terminou o curso
                }
                else 
                {
                    atual.done=true;

                    node_t *current = list_find(lista, atual.country);      
                    decrement_of(current,"active");
                    increment_of(current,"done");

                    offset = sizeof(struct student)*position;
                    fseek(table->ref, offset, SEEK_SET);
                    fwrite(&atual, sizeof(struct student), 1, table->ref);

                    return 0;
                }
            }
            
            if (strcmp(option, "left") == 0)
            {
                if (atual.removed) 
                {
                    if (atual.left)
                    {
                    return ABANDONOU; //abandonou o curso
                    }
                    if (atual.done) //atual.removed==true
                    {
                    return TERMINOU; //terminou o curso
                    }
                    
                    return INEXISTENTE;
                }
                else if (atual.left)
                {
                    return ABANDONOU; //abandonou o curso
                }
                else if (atual.done) //atual.removed==true
                {
                    return TERMINOU; //terminou o curso
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
        


        
    }
    return INEXISTENTE; //aluno inexistente
}
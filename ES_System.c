#include <stdio.h>
#include <stdbool.h>
#include "HashTable.c"


void insert_student(HashTable_t students,char *id, char *country)
{
    if(insert_hashtable(id,country)!=true)
    {
        printf("+ estudante %s existe",id);
    }
    
}

void remove_student(HashTable_t students,char *id)
{
    //nada ou 
    printf("+ estudante %s inexistente",id);
    //Se não existir um estudante com o identificador dado.
    printf("+ estudante %s terminou",id);
    //Se o estudante a que o identificador corresponde já tiver terminado o curso.
    printf("+ estudante %s terminou",id);
    //Se o estudante a que o identificador corresponde tiver abandonado os estudos.
}

void set_done(HashTable_t students,char *id)
{
    //nada ou 
    printf("+ estudante %s inexistente",id);
    //Se não existir um estudante com o identificador dado.
    printf("+ estudante %s terminou",id);
    //Se o estudante a que o identificador corresponde já tiver terminado o curso.
    printf("+ estudante %s terminou",id);
    //Se o estudante a que o identificador corresponde tiver abandonado os estudos.
}

void set_leave(HashTable_t students,char *id)
{
    //nada ou 
    printf("+ estudante %s inexistente",id);
    //Se não existir um estudante com o identificador dado.
    printf("+ estudante %s terminou",id);
    //Se o estudante a que o identificador corresponde já tiver terminado o curso.
    printf("+ estudante %s terminou",id);
    //Se o estudante a que o identificador corresponde tiver abandonado os estudos.
}

void get_stats_from(HashTable_t countries,char *country)
{
    //nada ou 
    //printf("+ %s - correntes: %d, diplomados: %d, abandonaram: %d, total: %d",cod,...);
    //Se não existir um estudante com o identificador dado.

    printf("+ sem dados sobre %s",country);
    //Se não existir nenhum estudante associado ao paı́s com o código dado.
}

int main(int argc, char const *argv[])
{

    char operation;
    char id[7]; 
    char country[3];
    HashTable_t students;

    while (scanf("%c",&operation)!=EOF)
    {
        if (operation=='I')
        {
            scanf("%s %s",&id,&country);
            printf("%s %s",id,country);
            insert_student(students,id,country);

        }
        else if (operation=='R')
        {
            scanf("%s",&id);
            printf("%s",id);
            remove_student(students,id);

        }
        else if (operation=='T')
        {
            scanf("%s %s",&id);
            printf("%s",id);
            set_done(students,id);
            
        }
        else if (operation=='A')
        {
            scanf("%s",&id);
            printf("%s",id);
            set_leave(students,id);
        }
        else if (operation=='P')
        {
            scanf("%s",&country);
            printf("%s",country);
        }
        else if (operation=='X')
        {
            break;
        }
        else
        {
            printf("Invalid Operation\n");
        }
    }
    
}

#include <stdio.h>
#include <stdbool.h>
#include "HashTable.c"


void insert_student(HashTable_t *table,student_t student)
{
    printf("ola\n");
    if(insert_hashtable(table,student)!=true)
    {
        printf("+ estudante %s existe",student.id);
    }
    
}

void remove_student(HashTable_t *table,student_t student)
{
    //nada ou 
    printf("+ estudante %s inexistente",student.id);
    //Se não existir um estudante com o identificador dado.
    printf("+ estudante %s terminou",student.id);
    //Se o estudante a que o identificador corresponde já tiver terminado o curso.
    printf("+ estudante %s terminou",student.id);
    //Se o estudante a que o identificador corresponde tiver abandonado os estudos.
}

void set_done(HashTable_t *table,student_t student)
{
    //nada ou 
    printf("+ estudante %s inexistente",student.id);
    //Se não existir um estudante com o identificador dado.
    printf("+ estudante %s terminou",student.id);
    //Se o estudante a que o identificador corresponde já tiver terminado o curso.
    printf("+ estudante %s terminou",student.id);
    //Se o estudante a que o identificador corresponde tiver abandonado os estudos.
}

void set_leave(HashTable_t *table,student_t student)
{
    //nada ou 
    printf("+ estudante %s inexistente",student.id);
    //Se não existir um estudante com o identificador dado.
    printf("+ estudante %s terminou",student.id);
    //Se o estudante a que o identificador corresponde já tiver terminado o curso.
    printf("+ estudante %s terminou",student.id);
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
    HashTable_t *table = new_HashTable("alunos.dat");
    student_t current_student;

    while (scanf("%c",&operation)!=EOF)
    {
        if (operation=='I')
        {
            scanf("%s %s",&id,&country);

            strcpy(current_student.id,id);
            strcpy(current_student.id,country);

            insert_student(table,current_student);

        }
        else if (operation=='R')
        {
            scanf("%s",&id);
            printf("%s",id);

            strcpy(current_student.id,id);

            remove_student(table,current_student);

        }
        else if (operation=='T')
        {
            scanf("%s %s",&id);
            printf("%s",id);

            strcpy(current_student.id,id);

            set_done(table,current_student);
            
        }
        else if (operation=='A')
        {
            scanf("%s",&id);
            printf("%s",id);

            strcpy(current_student.id,id);

            set_leave(table,current_student);
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

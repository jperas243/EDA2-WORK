#include <stdio.h>
#include <stdbool.h>
#include "HashTable.c"


void insert_student(HashTable_t alunos,char identi[7], char cod[3])
{
    if(insert_hashtable(identi,cod)!=true)
    {
        printf("+ estudante %s existe",identi);
    }
    
}

void remove_student(HashTable_t alunos,char identi[7])
{
    //nada ou 
    printf("+ estudante %s inexistente",identi);
    //Se não existir um estudante com o identificador dado.
    printf("+ estudante %s terminou",identi);
    //Se o estudante a que o identificador corresponde já tiver terminado o curso.
    printf("+ estudante %s terminou",identi);
    //Se o estudante a que o identificador corresponde tiver abandonado os estudos.
}

void set_done(HashTable_t alunos,char identi[7])
{
    //nada ou 
    printf("+ estudante %s inexistente",identi);
    //Se não existir um estudante com o identificador dado.
    printf("+ estudante %s terminou",identi);
    //Se o estudante a que o identificador corresponde já tiver terminado o curso.
    printf("+ estudante %s terminou",identi);
    //Se o estudante a que o identificador corresponde tiver abandonado os estudos.
}

void set_leave(HashTable_t alunos,char identi[7])
{
    //nada ou 
    printf("+ estudante %s inexistente",identi);
    //Se não existir um estudante com o identificador dado.
    printf("+ estudante %s terminou",identi);
    //Se o estudante a que o identificador corresponde já tiver terminado o curso.
    printf("+ estudante %s terminou",identi);
    //Se o estudante a que o identificador corresponde tiver abandonado os estudos.
}

void get_stats_from(HashTable_t alunos,char cod[3])
{
    //nada ou 
    //printf("+ %s - correntes: %d, diplomados: %d, abandonaram: %d, total: %d",cod,...);
    //Se não existir um estudante com o identificador dado.

    printf("+ sem dados sobre %s",cod);
    //Se não existir nenhum estudante associado ao paı́s com o código dado.
}

int main(int argc, char const *argv[])
{

    char operation;
    char identi[7]; 
    char cod[3];
    HashTable_t alunos;

    while (scanf("%c",&operation)!=EOF)
    {
        if (operation=='I')
        {
            scanf("%s %s",&identi,&cod);
            printf("%s %s",identi,cod);
            insert_student(alunos,identi,cod);

        }
        else if (operation=='R')
        {
            scanf("%s",&identi);
            printf("%s",identi);
            remove_student(alunos,identi);

        }
        else if (operation=='T')
        {
            scanf("%s %s",&identi);
            printf("%s",identi);
            set_done(alunos,identi);
            
        }
        else if (operation=='A')
        {
            scanf("%s",&identi);
            printf("%s",identi);
            set_leave(alunos,identi);
        }
        else if (operation=='P')
        {
            scanf("%s",&cod);
            printf("%s",cod);
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

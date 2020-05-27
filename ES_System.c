#include <stdio.h>
#include <stdbool.h>
#include "HashTable.c"


void insert_student(HashTable_t *table,student_t student)
{
    if(insert_hashtable(table,student)!=true)
    {
        printf("+ estudante %s existe",student.id);
    }
    
}

void remove_student(HashTable_t *table,student_t student)
{
    int option = remove_hashtable(table,student.id);
    printf("%d",option);

    if (option ==1)
    {
        //sucesso
    }
    else if (option==0)
    {
        printf("+ estudante %s inexistente",student.id);
    }
    else if (option==-1)
    {
        printf("+ estudante %s terminou",student.id);
    }
    else if (option==-2)
    {
        printf("+ estudante %s abandonou",student.id);
    }

}

void set_done(HashTable_t *table,student_t student)
{

    long position = find_hashtable(table,student.id);
    student_t to_remove;

    long offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&to_remove, sizeof(struct student), 1, table->ref);

    if (position==-1)
    {
        printf("+ estudante %s inexistente",student.id);
    }
    else if (to_remove.done==true)
    {
        printf("+ estudante %s terminou",student.id);
    }
    else if (to_remove.left==true)
    {
        printf("+ estudante %s abandonou",student.id);
    }
    else
    {
        to_remove.done=true;

        fseek(table->ref, offset, SEEK_SET);
        fwrite(&to_remove, sizeof(struct student), 1, table->ref);
    }
}

void set_leave(HashTable_t *table,student_t student)
{
    long position = find_hashtable(table,student.id);
    student_t to_remove;

    int offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&to_remove, sizeof(struct student), 1, table->ref);

    if (position==-1)
    {
        printf("+ estudante %s inexistente",student.id);
    }
    else if (to_remove.done==true)
    {
        printf("+ estudante %s terminou",student.id);
    }
    else if (to_remove.left==true)
    {
        printf("+ estudante %s abandonou",student.id);
    }
    else
    {
        to_remove.left=true;

        long offset = sizeof(struct student)*position;
        fseek(table->ref, offset, SEEK_SET);
        fwrite(&to_remove, sizeof(struct student), 1, table->ref);
    }
}

void get_stats_from(HashTable_t *table,char *country)
{
    

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
            scanf("%s %s",id,country);

            strcpy(current_student.id,id);
            strcpy(current_student.country,country);

            insert_student(table,current_student);

        } 
        else if (operation=='R')
        {
            scanf("%s",id);

            strcpy(current_student.id,id);

            remove_student(table,current_student);

        }
        else if (operation=='T')
        {
            scanf("%s",id);

            strcpy(current_student.id,id);

            set_done(table,current_student);
            
        }
        else if (operation=='A')
        {
            scanf("%s",id);

            strcpy(current_student.id,id);

            set_leave(table,current_student);
        }
        else if (operation=='P')
        {
            scanf("%s",country);
            get_stats_from(table,country);

        }
        else if (operation=='X')
        {
            //guardar os paises no ficheiro
            break;
        }
    }
    
}

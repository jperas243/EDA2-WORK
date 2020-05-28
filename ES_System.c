#include <stdio.h>
#include <stdbool.h>
#include "HashTable.h"
#include "Lista.h"
#include "Lista_MEM.h"



void insert_student(HashTable_t *table,list_t *lista,student_t student)
{
    if(insert_hashtable(table,student)!=true)
    {
        printf("+ estudante %s existe\n",student.id);
    }
    else
    {
        node_t *country_node = list_find(lista,student.country);
        if (country_node == NULL)
        {
            list_insert(lista,student.country);
        }
        else
        {
            increment_of(country_node,"active");
        }
        //list_print_content(lista);
        
    }
}

void remove_student(HashTable_t *table,list_t *lista,student_t student)
{
    int option = remove_hashtable(table,student.id);
    //printf("%d",option);

    if (option ==1)
    {
        //sucesso
        node_t *country_node = list_find(lista,student.country);
        decrement_of(country_node,"active");
        //list_print_content(lista);

    }
    else if (option==0)
    {
        printf("+ estudante %s inexistente\n",student.id);
    }
    else if (option==-1)
    {
        printf("+ estudante %s terminou\n",student.id);
    }
    else if (option==-2)
    {
        printf("+ estudante %s abandonou\n",student.id);
    }

}

void set_done(HashTable_t *table,list_t *lista,student_t student)
{

    long position = find_hashtable(table,student.id);
    //printf("%d",position);
    student_t to_find;

    long offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&to_find, sizeof(struct student), 1, table->ref);

    if (position==-1)
    {
        printf("+ estudante %s inexistente\n",student.id);
    }
    else if (to_find.done==true)
    {
        printf("+ estudante %s terminou\n",student.id);
    }
    else if (to_find.left==true)
    {
        printf("+ estudante %s abandonou\n",student.id);
    }
    else
    {
        to_find.done=true;

        fseek(table->ref, offset, SEEK_SET);
        fwrite(&to_find, sizeof(struct student), 1, table->ref);

        //printf("%d\n",to_find.country);
        node_t *country_node = list_find(lista,to_find.country);
        increment_of(country_node,"done");
        decrement_of(country_node,"active");
        //list_print_content(lista);

    }
}

void set_leave(HashTable_t *table,list_t *lista,student_t student)
{
    long position = find_hashtable(table,student.id);
    student_t to_find;

    int offset = sizeof(struct student)*position;
    fseek(table->ref, offset, SEEK_SET);
    fread(&to_find, sizeof(struct student), 1, table->ref);

    if (position==-1)
    {
        printf("+ estudante %s inexistente\n",student.id);
    }
    else if (to_find.done==true)
    {
        printf("+ estudante %s terminou\n",student.id);
    }
    else if (to_find.left==true)
    {
        printf("+ estudante %s abandonou\n",student.id);
    }
    else
    {
        to_find.left=true;

        long offset = sizeof(struct student)*position;
        fseek(table->ref, offset, SEEK_SET);
        fwrite(&to_find, sizeof(struct student), 1, table->ref);

        node_t *country_node = list_find(lista,to_find.country);
        increment_of(country_node,"left");
        decrement_of(country_node,"active");
        //list_print_content(lista);
        
    }
}

void get_stats_from(list_t *lista,char *country)
{

    node_t *country_node = list_find(lista,country);
    if (country_node==NULL)
    {
        printf("+ sem dados sobre %s\n",country);
    }
    list_print(lista,country);
    
    
}

void save_countries(Lista_MEM_t *lista_MEM, list_t *lista)
{
    ListMEM_newfile(lista_MEM,"countries.dat");

    node_t *current_node = lista->header->next;
    
    while (current_node!=NULL)
    {
        ListMEM_insert(lista_MEM,current_node);
        current_node=current_node->next;
    }

    free(current_node);
}


int main(int argc, char const *argv[])
{

    char operation;
    char id[7]; 
    char country[3];

    HashTable_t *table = new_HashTable("alunos.dat");
    Lista_MEM_t *lista_MEM = new_Lista_MEM("countries.dat");

    list_t *lista = newList();
    student_t current_student;

    //load dos paises
    ListMEM_send_to(lista_MEM,lista);

    while (scanf("%c",&operation)!=EOF)
    {
        if (operation=='I')
        {
            scanf("%s %s",id,country);

            strcpy(current_student.id,id);
            strcpy(current_student.country,country);

            insert_student(table,lista,current_student);

        } 
        else if (operation=='R')
        {
            scanf("%s",id);

            strcpy(current_student.id,id);

            remove_student(table,lista,current_student);

        }
        else if (operation=='T')
        {
            scanf("%s",id);

            strcpy(current_student.id,id);

            set_done(table,lista,current_student);
            
        }
        else if (operation=='A')
        {
            scanf("%s",id);

            strcpy(current_student.id,id);

            set_leave(table,lista,current_student);
        }
        else if (operation=='P')
        {
            scanf("%s",country);
            get_stats_from(lista,country);

        }
        else if (operation=='X')
        {
            //guardar os paises no ficheiro
            save_countries(lista_MEM,lista);
            break;
        }
    }
    
}

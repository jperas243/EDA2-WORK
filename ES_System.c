#include <stdio.h>
#include <stdbool.h>

#include "Lista.h"
#include "HashTable.h"
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
    unsigned int option = find_apply_hashtable(table,student.id, "remove", lista);
    
    if (option == 0)    //sucesso
    {
    }
    else if (option == -1)
    {
        printf("+ estudante %s terminou\n",student.id);
        
    }
    else if (option == -2)
    {
        printf("+ estudante %s abandonou\n",student.id);
    }
    else if (option == -3)
    {
        printf("+ estudante %s inexistente\n",student.id);
        
    }

}

void set_done(HashTable_t *table,list_t *lista,student_t student)
{

    unsigned int option = find_apply_hashtable(table,student.id, "done", lista);

    if (option == 0)    //sucesso
    {
    }
    else if (option == -1)
    {
        printf("+ estudante %s terminou\n",student.id);
        
    }
    else if (option == -2)
    {
        printf("+ estudante %s abandonou\n",student.id);
    }
    else if (option == -3)
    {
        printf("+ estudante %s inexistente\n",student.id);
        
    }
}

void set_leave(HashTable_t *table,list_t *lista,student_t student)
{
    unsigned int option = find_apply_hashtable(table,student.id, "left", lista);

    if (option == 0)    //sucesso
    {
    }
    else if (option == -1)
    {
        printf("+ estudante %s terminou\n",student.id);
        
    }
    else if (option == -2)
    {
        printf("+ estudante %s abandonou\n",student.id);
    }
    else if (option == -3)
    {
        printf("+ estudante %s inexistente\n",student.id);
        
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
    node_t *current_node = lista->header->next;
    int i=1;

    list_print_content(lista);

    
    while (current_node!=NULL)
    {
        country_t current_country = current_node->country;
        
        int offset = sizeof(struct country)*i;
        fseek(lista_MEM->ref, offset, SEEK_SET);
        fwrite(&current_country, sizeof(struct country), 1, lista_MEM->ref);
        current_node=current_node->next;
        i++;

    }

    lista_MEM->size=lista->size--;

    ListMEM_saveSize(lista_MEM,i);
    //printf("size mem guardado:%d\n",i);
    lista_MEM->size=lista_MEM->size+1;
    ListMEM_printf(lista_MEM);

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

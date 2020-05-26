#include <stdio.h>

int main(int argc, char const *argv[])
{

    

    while (scanf("%c",&operation)!=EOF)
        {
            if (operation=='p')
            {
                scanf("%li %li",&term_1,&term_2);
                if (!searchPar(lista,term_1,term_2))
                {
                    list_insert(lista,term_1,term_2);
                }
                

            }
            else if (operation=='x')
            {
                scanf("%li %li",&term_1,&term_2);          
                list_remove(lista,term_1,term_2);

            }
            else if (operation=='q')
            {
                scanf("%li",&term_1);
                search(lista,term_1);
            }
        }
    
}

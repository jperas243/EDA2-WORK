#include <stdbool.h>
#include <stdio.h>

#define t 5 

typedef struct AutoModel  // cada variavel ocupa 48 bytes
{
    char marca[21]; //21                    //0
    char modelo[21]; //21 --                   //21
    unsigned short cilindra; //2                //42
    unsigned short ano_intro;//2               //46
    unsigned short ano_close;//2               //48
    //48 bytes totais(não ha alinhamento)

}auto_t;

typedef struct BTreeNode 
{
    short ocupation; //2 bytes
    bool folha;      //1 byte
    int filhos[2*t]; //4*2t bytes
    auto_t cars[2*t-1]; //48 * 2*t-1 bytes
    //3 bytes de alinhamento

}nodeB_t;

//grau de ramificação para uma pagina de 4KB: t=39
//2+48(2t-1)+2+4*2t+1+3(alinhamento do compilador) <=4096
//tamanho do no = 4016 bytes, 4096-4016 bytes desperdiçados

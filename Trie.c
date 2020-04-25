/* trie implementation, with arrays */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "trie.h"

#define ALPHABET_MIN 'a'
#define ALPHABET_MAX 'z'
#define ALPHABET_SIZE (ALPHABET_MAX - ALPHABET_MIN + 1)

#define POS(c)  ((c) - ALPHABET_MIN)	// character position in alphabet
#define CHAR(n) ((n) + ALPHABET_MIN)	// n-th alphabet character


/* trie node */
struct node {
  struct node *child[ALPHABET_SIZE];	// children
  bool        word;			// end-of-word mark
  
};

/* trie */
struct trie {
  struct node *root;
};


/*
  Allocates and returns a new trie node.
*/
static struct node *node_new(void)
{
  struct node *node = malloc(sizeof(*node));

  if (node != NULL)
    {
      node->word = false;

      for (int i = 0; i < ALPHABET_SIZE; ++i)
	node->child[i] = NULL;
    }

  return node;
}


/* Frees a trie NODE. */
static void node_free(struct node *node)
{
  free(node);
}


/* Destroys the sub-trie with root NODE. */
static void node_destroy(struct node *node)
{
  if (node == NULL)
    return;

  for (int i = 0; i < ALPHABET_SIZE; ++i)
    node_destroy(node->child[i]);

  node_free(node);
}


/*
  Creates and returns a new, empty trie.
*/
struct trie *trie_new(void)
{
  struct trie *trie = malloc(sizeof(struct trie));

  if (trie != NULL)
    trie->root = NULL;

  return trie;
}


/* Destroys trie T, freeing the memory it occupies. */
void trie_destroy(struct trie *t)
{
  node_destroy(t->root);

  free(t);
}


/* Checks whether trie T is empty. */
bool trie_empty(struct trie *t)
{
  return t->root == NULL;
}


/*
  Inserts word P into trie T.

  Returns true if the word was successfully inserted (or was already
  in the trie), false otherwise.
*/
bool trie_insert(struct trie *t, char p[])
{
  struct node *n;
  int i = 0;

  if (t->root == NULL)
    t->root = node_new();	// new, empty root node

  if (t->root == NULL)
    return false;

  n = t->root;

  // follow the word down the trie as long as possible,
  // taking care not to go to a nonexisting node
  while (p[i] != '\0' && n->child[POS(p[i])] != NULL)
    {
      n = n->child[POS(p[i])];
      i++;
    }

  // insert the new suffix into the trie
  while (p[i] != '\0')
    {
      n->child[POS(p[i])] = node_new();

      if (n->child[POS(p[i])] == NULL)
	return false;

      n = n->child[POS(p[i])];

      i++;
    }

  n->word = true;

  return true;
}

bool trie_find(struct trie *arv,char word[])
{
  int counter=0;
  struct node *Atual = arv->root;

  if (Atual==NULL)
  {
    return false;
  }
  

  while (word[counter]!='\0')
  {
    int indice = (int)word[counter]-(int)'a';
    
    if (Atual->child[indice]!=NULL)
    {
      Atual = Atual->child[indice];
    }
    else
    {
      return false;
    }
    counter++;
  }

  if (Atual->word==true)
  {
    return true;
  }
  
  return false;
}

int trie_count_node(struct node *nod)
{
  int result=0;
  
  if (nod->word==true)
  {
    result++;
  }

  for (int i = 0; i < 26; i++)
  {
    if (nod->child[i] != NULL)
    {
      result += trie_count_node(nod->child[i]);
    }
  }

  return result;
  
}

int trie_count(struct trie *arv)
{
  int result=0;
  if (arv->root!=NULL)
  {
    result = trie_count_node(arv->root);
  }
  return result;
}

void trie_print_node(struct node *nod,char word[],int index)
{
  if (nod->word==true)
  {
    for (int i = 0;i<index;i++)
    {
      printf("%c",word[i]);
    }
    printf("\n");
  }

  for (int i = 0; i < 26; i++)
  {
    if (nod->child[i] != NULL)
    {
      char c = i + 'a';
      word[index] = c;
      index++;
      trie_print_node(nod->child[i],word,index);
      index--;
    }
  }
}

void trie_print(struct trie *arv)
{
  int index = 0;
  char word[65];
  trie_print_node(arv->root,word,index);
}

void trie_print_completions(struct trie *arv,char prefix[])
{
  int counter=0;
  bool valid = true;
  struct node *Atual = arv->root;

  if (Atual==NULL)
  {
    valid=false;
  }

  while (prefix[counter]!='\0' && valid)
  {
    int indice = (int)prefix[counter]-(int)'a';
    
    if (Atual->child[indice]!=NULL)
    {
      Atual = Atual->child[indice];
    }
    else
    {
      valid=false;
      break;
    }
        
    counter++;
  }

  if (valid)
  {
    trie_print_node(Atual,prefix,counter);
  }
}

bool childless(struct node *nod)
{
  for (int i = 0; i < 26; i++)
  {
    if (nod->child[i] != NULL)
    {
      return false;
    }
  }

  return true;
}

void trie_delete(struct trie *arv,char word[])
{
  int counter=0;
  bool valid = true;
  struct node *save[65];
  struct node *Atual = arv->root;

  if (Atual == NULL)
  {
    valid=false;
  }
  

  while (word[counter]!='\0' && valid)
  {
    int indice = (int)word[counter]-(int)'a';
    
    if (Atual->child[indice]!=NULL)
    {
      save[counter]=Atual;
      Atual = Atual->child[indice];
    }
    else
    {
      valid=false;
      break;
    }
    counter++;
  }
  
  if (Atual!=NULL && Atual->word && valid)
  {
    Atual->word = false;
    while (Atual!=NULL && childless(Atual) && Atual->word!=true)
    {
      counter--;
      if (Atual!=arv->root)
      {
        int indice = (int)word[counter]-(int)'a';
        save[counter]->child[indice]=NULL;
        Atual=save[counter];
      }
      else
      {
        arv->root=NULL;
        break;
      }      
    }
  }
  

  
}

int main(int argc, char const *argv[])
{
  char operation;
  char word[65];

  struct trie *arv = trie_new();

  while (scanf("%c",&operation)!=EOF)
  {
    //printf("oi\n");
    if (operation=='i')
    {
      scanf("%s",word);
      trie_insert(arv,word);
    }
    else if (operation=='r')
    {
      scanf("%s",word);
      trie_delete(arv,word);
    }
    else if (operation=='e')
    {
      scanf("%s",word);
      
      if (trie_find(arv,word))
      {
        printf("\"%s\" conhecida\n",word);
      }
      else
      {
        printf("\"%s\" desconhecida\n",word);        
      }
      
    }
    else if (operation=='q')
    {
      printf("palavras conhecidas: %d\n", trie_count(arv));    
    }    
    else if (operation=='c')
    {
      scanf("%s",word);
      printf("palavras com prefixo \"%s\":\n",word);
      trie_print_completions(arv,word);
    } 
  }
}

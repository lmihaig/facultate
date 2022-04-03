/*
programul genereaza o lista dublu legata si foloseste
doua functii pentru controlul elementelor: una pentru
adaugarea unui element nou si alta pentru eliminarea unui
element deja existent

accepta urmatorii parametrii in linia de comanda:
numarul total de elemente, numarul elementului care trebuie
eliminat, numarul elementului dupa care urmeaza sa introduca noul
element si valoarea elementului care trebuie adaugat

se compileaza ca: gcc -o linked_list linked_list.c
se ruleaza ca:  ./linked_list 10 3 4 50
(lista cu 10 elemente, scoate el. 3, introduce un element dupa el. 4
care va avea nr. 50
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// structura pentru lista dublu legata
struct nnode
{
  int value;
  struct nnode *next;
  struct nnode *previous;
};

typedef struct nnode node;

void rem(node *item);             /// functia de eliminare a unui element
void create(node *item, int val); /// functia de creare a unui element

int main(int argc, char **argv)
{
  int i;
  int n = atoi(argv[1]); // list size
  node *item, *start, *interm;

  interm = NULL;

  /// alocarea memoriei si initializarea listei
  for (i = 0; i < n; i++)
  {
    if ((item = malloc(sizeof(node))) == NULL)
      printf("maloc err\n");
    if (i == 0)
      start = item;
    if (i != 0)
      interm->next = item;
    item->value = i;
    item->previous = interm;
    item->next = NULL;
    interm = item;
  }

  /// afisarea listei
  printf("this is the list:\n");
  item = start;
  i = 0;
  do
  {
    printf("item %i value %i\n", i, item->value);
    item = item->next;
    i += 1;
  } while (item != NULL);
  printf("\n\n");

  /// eliminarea elementului selectat
  item = start;
  for (i = 0; i < atoi(argv[2]); i++)
  {
    item = item->next;
  }
  rem(item); /// aici are loc eliminare

  /// afisarea listei
  printf("this is the list after eliminating an element\n");
  item = start;
  i = 0;
  do
  {
    printf("item %i value %i\n", i, item->value);
    item = item->next;
    i += 1;
  } while (item != NULL);
  printf("\n\n");

  /// adaugarea unui element nou
  item = start;
  for (i = 0; i < atoi(argv[3]) - 1; i++)
  {
    item = item->next;
  }
  create(item, atoi(argv[4]));

  /// afisara listei
  printf("this is the list after adding an element\n");
  item = start;
  i = 0;
  do
  {
    printf("item %i value %i\n", i, item->value);
    item = item->next;
    i += 1;
  } while (item != NULL);
  printf("\n\n");

  /// eliberarea memoriei
  item = start;
  do
  {
    interm = item->next;
    free(item);
    item = interm;
  } while (item != NULL);

  return 0;
}

/// elimina elementul "item"
void rem(node *item)
{
  node *previous, *next;
  previous = item->previous;
  next = item->next;
  free(item);
  next->previous = previous;
  previous->next = next;
}

/// primeste elementul dupa care sa adauge elementul nou
void create(node *item, int val)
{
  node *new = malloc(sizeof(node));
  new->value = val;
  new->previous = item;
  if (item->next == NULL)
    new->next = NULL; /// if item is last element
  else
    new->next = item->next;
  item->next = new;
  (item->next)->previous = new;
}
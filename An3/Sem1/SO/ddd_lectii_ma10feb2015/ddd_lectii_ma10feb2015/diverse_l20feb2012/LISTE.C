/*
Program demonstrativ cu liste in limbajul C
Dragulici Daniel
26 aprilie 2006
*/

#include <stdio.h>
#include <stdlib.h>

struct nod
{
  int inf;
  struct nod *leg;
};

struct nod *nodnou()
{
  struct nod *aux;
  if (!(aux = (struct nod *)malloc(sizeof(struct nod))))
  {
    printf("Eroare la alocare\n");
    exit(1);
  }
  return aux;
}

/* returneaza pozitia celei de-a n-a aparitii (numarand de la 1) a lui x */
int cauta(struct nod *l, int x, int n)
{
  int poz, i;
  if (n <= 0)
    return -1;
  i = 0;
  while (l && n > 0)
  {
    if (l->inf == x)
    {
      poz = i;
      --n;
    }
    l = l->leg;
    ++i;
  }
  if (n == 0)
    return poz;
  else
    return -1;
}

/* inserare pe pozitia n */
struct nod *inserare(struct nod *l, int x, int n)
{
  struct nod *aux1, *aux2;
  if (n < 0)
    return NULL;
  if (n == 0)
  {
    aux1 = nodnou();
    aux1->inf = x;
    aux1->leg = l;
    return aux1;
  }
  if (!l)
    return NULL;
  for (aux2 = l; aux2->leg && n > 1; aux2 = aux2->leg, --n)
    ;
  if (n > 1)
    return NULL;
  aux1 = nodnou();
  aux1->inf = x;
  aux1->leg = aux2->leg;
  aux2->leg = aux1;
  return l;
}

/* eliminare de pe pozitia n */
/* valoarea returnata NULL nu ne permite sa distingem daca pozitia n nu
   exista sau s-a scos ultimul element */
struct nod *eliminare(struct nod *l, int n)
{
  struct nod *aux1, *aux2;
  if (n < 0)
    return NULL;
  if (!l)
    return NULL;
  if (n == 0)
  {
    aux1 = l;
    l = l->leg;
    free(aux1);
    return l;
  }
  for (aux2 = l; aux2->leg && n > 1; aux2 = aux2->leg, --n)
    ;
  if (n > 1)
    return NULL;
  aux1 = aux2->leg;
  if (aux1)
    aux2->leg = aux1->leg;
  free(aux1);
  return l;
}

/* inserare x inainte/dupa un element dat y */
struct nod *inserare1(struct nod *l, int x, int y, int op)
{
  struct nod *aux1, *aux2;
  if (!l)
    return NULL;
  if (op == 1)
  { /* inserare inainte de y */
    if (l->inf == y)
    {
      aux1 = nodnou();
      aux1->inf = x;
      aux1->leg = l;
      return aux1;
    }
    for (aux2 = l; aux2->leg; aux2 = aux2->leg)
      if (aux2->leg->inf == y)
        break;
    if (!aux2->leg)
      return NULL;
    aux1 = nodnou();
    aux1->inf = x;
    aux1->leg = aux2->leg;
    aux2->leg = aux1;
    return l;
  }
  else if (op == 2)
  { /* inserare dupa y */
    for (aux2 = l; aux2; aux2 = aux2->leg)
      if (aux2->inf == y)
        break;
    if (!aux2)
      return NULL;
    aux1 = nodnou();
    aux1->inf = x;
    aux1->leg = aux2->leg;
    aux2->leg = aux1;
    return l;
  }
  else
    return NULL; /* optiune gresita */
}

/* varianta scrisa deasupra primitivelor cu n */
struct nod *inserare2(struct nod *l, int x, int y, int op)
{
  int n;
  struct nod *aux;
  n = cauta(l, y, 1);
  /*  if(n==-1)return NULL; */
  switch (op)
  {
  case 1:
    aux = inserare(l, x, n);
    break; /* inserare inainte de y */
  case 2:
    aux = inserare(l, x, n + 1);
    break; /* inserare dupa y */
  default:
    aux = NULL;
  }
  return aux;
}

/* tema: funtie de eliminarea elementului de dinainte/de dupa y,
   varianta directa si varianta deasupra primitivelor cu n */

/* stive cu 4 primitive */

typedef struct nod *stiva;

void init(stiva *s) { *s = NULL; }

int vida(stiva *s) { return *s == NULL; }

void push(stiva *s, int x)
{
  struct nod *aux;
  aux = nodnou();
  aux->inf = x;
  aux->leg = *s;
  *s = aux;
}

int pop(stiva *s)
{
  struct nod *aux;
  int x;
  x = (*s)->inf;
  aux = *s;
  *s = (*s)->leg;
  free(aux);
  return x;
}

/* golire stiva */
void golire(stiva *s)
{
  while (!vida(s))
    pop(s);
}

/* citire stiva */
void cit(stiva *s)
{
  int x;
  golire(s);
  for (scanf("%d", &x); x != -1; scanf("%d", &x))
    push(s, x);
}

/* afisare stiva */
void scr(stiva *s)
{
  stiva s1;
  int x;
  init(&s1);
  while (!vida(s))
  {
    x = pop(s);
    push(s1, x);
  }
  while (!vida(s1))
  {
    x = pop(s1);
    push(s, x);
    printf("%d ", x);
  }
  printf("\n");
}

/* copiere stive */
void cop(stiva *d, stiva *s)
{
  stiva s1;
  int x;
  init(&s1);
  golire(d);
  while (!vida(s))
  {
    x = pop(s);
    push(s1, x);
  }
  while (!vida(s1))
  {
    x = pop(s1);
    push(s, x);
    push(d, x);
  }
}

/* tema: cozi cu aceleasi 4 primitive si functii deasupra lor */

int main()
{

  /* liste */
  struct nod *l1, *l2, *l3;

  /* stive */
  stiva s1, s2;

  /* variabile auxiliare */
  int n, i, x, y;
  struct nod *aux1, *aux2;

  /*** prelucrari fara functii ***/

  /* citire in sens direct */
  printf("Nr. elementelor: ");
  scanf("%d", &n);
  if (n == 0)
    l1 = NULL;
  else
  {
    if ((l1 = (struct nod *)malloc(sizeof(struct nod))) == NULL)
    {
      printf("Eroare la alocare\n");
      exit(1);
    }
    printf("Elementul nr. 1: ");
    scanf("%d", &l1->inf);
    l1->leg = NULL;
    aux1 = l1;
    for (i = 1; i < n; ++i)
    {
      if ((aux1->leg = (struct nod *)malloc(sizeof(struct nod))) == NULL)
      {
        printf("Eroare la alocare\n");
        exit(1);
      }
      printf("Elementul nr. %d: ", i + 1);
      scanf("%d", &aux1->leg->inf);
      aux1->leg->leg = NULL;
      aux1 = aux1->leg;
    }
  }

  /* citire in sens invers */
  printf("Nr. elementelor: ");
  scanf("%d", &n);
  l2 = NULL;
  for (i = 0; i < n; ++i)
  {
    if ((aux1 = (struct nod *)malloc(sizeof(struct nod))) == NULL)
    {
      printf("Eroare la alocare\n");
      exit(1);
    }
    printf("Elementul nr. %d: ", i + 1);
    scanf("%d", &aux1->inf);
    aux1->leg = l2;
    l2 = aux1;
  }

  /* citire in sens invers pana la -1 exclusiv */
  printf("Dati elementele: ");
  l3 = NULL;
  for (scanf("%d", &x); x != -1; scanf("%d", &x))
  {
    if ((aux1 = (struct nod *)malloc(sizeof(struct nod))) == NULL)
    {
      printf("Eroare la alocare\n");
      exit(1);
    }
    aux1->inf = x;
    aux1->leg = l3;
    l3 = aux1;
  }

  /* afisare */
  for (aux1 = l1; aux1; aux1 = aux1->leg)
    printf("%d ", aux1->inf);
  printf("\n");
  for (aux1 = l2; aux1; aux1 = aux1->leg)
    printf("%d ", aux1->inf);
  printf("\n");
  for (aux1 = l3; aux1; aux1 = aux1->leg)
    printf("%d ", aux1->inf);
  printf("\n");

  /* stergere */
  while (l3)
  {
    aux1 = l3;
    l3 = l3->leg;
    free(aux1);
  }

  /*** prelucrari cu functii ***/

  /* cautarea tuturor aparitiilor */
  printf("Nr. cautat: ");
  scanf("%d", &x);
  printf("El apare pe pozitiile: ");
  for (n = 1;; ++n)
  {
    i = cauta(l1, x, n);
    if (i == -1)
      break;
    printf("%d ", i);
  }
  printf("\n");

  /* inserare pe pozitiile pare */
  for (n = 0;; n += 2)
  {
    aux1 = inserare(l1, 1000, n);
    if (!aux1)
      break;
    l1 = aux1;
  }
  for (aux1 = l1; aux1; aux1 = aux1->leg)
    printf("%d ", aux1->inf);
  printf("\n");

  /* eliminare de pe pozitiile pare (merge doar daca lista are >= 2 elem.) */
  for (n = 0;; ++n)
  {
    aux1 = eliminare(l1, n);
    if (!aux1)
      break;
    l1 = aux1;
  }
  for (aux1 = l1; aux1; aux1 = aux1->leg)
    printf("%d ", aux1->inf);
  printf("\n");

  /* inserari inainte/dupa un y */
  printf("Elementul inainte/dupa care se insereaza: ");
  scanf("%d", &y);
  printf("Elementul inserat: ");
  scanf("%d", &x);
  aux1 = inserare1(l1, x, y, 1);
  if (aux1)
    l1 = aux1;
  aux1 = inserare1(l1, x, y, 2);
  if (aux1)
    l1 = aux1;
  for (aux1 = l1; aux1; aux1 = aux1->leg)
    printf("%d ", aux1->inf);
  printf("\n");
  printf("Elementul inainte/dupa care se insereaza: ");
  scanf("%d", &y);
  printf("Elementul inserat: ");
  scanf("%d", &x);
  aux1 = inserare2(l1, x, y, 1);
  if (aux1)
    l1 = aux1;
  aux1 = inserare2(l1, x, y, 2);
  if (aux1)
    l1 = aux1;
  for (aux1 = l1; aux1; aux1 = aux1->leg)
    printf("%d ", aux1->inf);
  printf("\n");

  /* operatii cu stive */
  init(&s1);
  init(&s2);

  printf("Dati elementele stivei (se vor insera pana la -1 exclusiv): ");
  cit(&s1);

  printf("Stiva citita este: ");
  scr(&s1);
  printf("\n");
  printf("Stiva citita este: ");
  scr(&s1);
  printf("\n");

  cop(&s2, &s1);

  printf("Stiva copie este: ");
  scr(&s2);
  printf("\n");
  printf("Stiva initiala este: ");
  scr(&s1);
  printf("\n");

  golire(&s1);

  printf("Stiva initiala dupa golire este: ");
  scr(&s1);
  printf("\n");

  return 0;
}

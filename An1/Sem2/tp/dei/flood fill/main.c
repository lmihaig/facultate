#include <stdio.h>
#include <stdlib.h>

// structura nodurilor
struct Node
{
    int x, y;
    struct Node *next;
};
// structura cozii
struct Queue
{
    struct Node *head, *tail;
};

// adauga nod nou la finalul cozii
void push(struct Queue *q, int x, int y)
{
    // noul nod

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->x = x;
    temp->y = y;
    temp->next = NULL;
    // daca nu exista noduri atunci noul nod devine si capul si finalul cozii
    if (q->tail == NULL)
    {
        q->head = q->tail = temp;
        return;
    }

    // noul nod devine finalul cozii

    q->tail->next = temp;
    q->tail = temp;
}

// scoate primul nod din coada
void pop(struct Queue *q)
{
    // daca coada e goala deja se opreste
    if (q->head == NULL)
        return;

    struct Node *temp = q->head;
    q->head = q->head->next;

    if (q->head == NULL)
        q->tail = NULL;

    // elibereaza memoria nodului
    free(temp);
}

// citirea matricei din fisier
int **read_array(FILE *file, int n, int m)
{
    int i, j;
    int **array = (int **)malloc(m * sizeof(int *));
    for (i = 0; i < n; i++)
        array[i] = (int *)malloc(m * sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            fscanf(file, "%d", &array[i][j]);

    return array;
}

// scrierea matricei in fisier
void write_array(FILE *file, int n, int m, int **array)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            fprintf(file, "%d ", array[i][j]);
        fputs("\n", file);
    }
}

void flood_fill(int x0, int y0, int **array, int n, int m, int fill)
{
    x0--;
    y0--;
    int color = array[x0][y0]; // elementul care trebuie sa fie inlocuit (in problema 0)
    int x, y;

    if (color == fill) // daca deja sunt egale nu avem ce umple
        return;
    else
        array[x0][y0] = fill; // se schimba elementul de pe pozitia (x0,y0)

    // initializarea cozii goale
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->head = q->tail = NULL;

    // adaugarea primului nod de plecare in coada
    push(q, x0, y0);

    // efectuam algoritmu pentru vecinii fiecarui nod din coada cat timp sunt noduri in coada
    while (q->head != NULL)
    {
        // se preiau coordonatele pentru a gasii vecinii si se elimina nodul din coada
        x = q->head->x;
        y = q->head->y;
        pop(q);

        // fiecare vecin isi va avea culoarea schimbata inainte de a fi introdus in coada pentru a nu cumva fi adaugat de mai multe ori
        // vecinul din N
        if (x != 0)
            if (array[x - 1][y] == color)
            {
                array[x - 1][y] = fill;
                push(q, x - 1, y);
            }
        // vecinul din E
        if (y != m - 1)
            if (array[x][y + 1] == color)
            {
                array[x][y + 1] = fill;
                push(q, x, y + 1);
            }
        // vecinul din S
        if (x != n - 1)
            if (array[x + 1][y] == color)
            {
                array[x + 1][y] = fill;
                push(q, x + 1, y);
            }
        // vecinul din V
        if (y != 0)
            if (array[x][y - 1] == color)
            {
                array[x][y - 1] = fill;
                push(q, x, y - 1);
            }
    }
}

int main()
{
    int m, n, x0, y0;
    int **array;
    FILE *fin = fopen("date.in", "r");
    FILE *fout = fopen("date.out", "w");

    if (fin == NULL)
    {
        printf("fisierul nu exista");
        return 1;
    }

    fscanf(fin, "%d %d", &n, &m);
    array = read_array(fin, n, m);
    fscanf(fin, "%d %d", &x0, &y0);
    flood_fill(x0, y0, array, n, m, 1);
    write_array(fout, n, m, array);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct Node

{
    int x, y;
    struct Node *next;
};

struct Queue
{
    struct Node *head, *tail;
};

void push(struct Queue *q, int x, int y)
{

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->x = x;
    temp->y = y;
    temp->next = NULL;

    if (q->tail == NULL)
    {
        q->head = q->tail = temp;
        return;
    }

    q->tail->next = temp;
    q->tail = temp;
}

void pop(struct Queue *q)
{

    if (q->head == NULL)
        return;

    struct Node *temp = q->head;
    q->head = q->head->next;

    if (q->head == NULL)
        q->tail = NULL;

    free(temp);
}

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

int obj_iden(int **array, int n, int m)
{
    int i, j, x, y, color, num = 0;
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->head = q->tail = NULL;

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            if (array[i][j] == 1)
            {
                num++;
                array[i][j] = 2;
                push(q, i, j);
                while (q->head != NULL)
                {

                    x = q->head->x;
                    y = q->head->y;
                    pop(q);

                    if (x != 0)
                        if (array[x - 1][y] == 1)
                        {
                            array[x - 1][y] = 2;
                            push(q, x - 1, y);
                        }

                    if (y != m - 1)
                        if (array[x][y + 1] == 1)
                        {
                            array[x][y + 1] = 2;
                            push(q, x, y + 1);
                        }

                    if (x != n - 1)
                        if (array[x + 1][y] == 1)
                        {
                            array[x + 1][y] = 2;
                            push(q, x + 1, y);
                        }

                    if (y != 0)
                        if (array[x][y - 1] == 1)
                        {
                            array[x][y - 1] = 2;
                            push(q, x, y - 1);
                        }
                }
            }
        }

    return num;
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
    fprintf(fout, "%d", obj_iden(array, n, m));

    return 0;
}
#include <stdio.h>

int cautareBinara(int *v, int x, int st, int dr)
{
    if(st > dr)     return -1;
    if(v[st] == x)  return st;
    if(v[dr] == x)  return dr;

    int mijloc = (st + dr) / 2;
    if(v[mijloc] == x)
        return mijloc;
    else if(v[mijloc] > x &&  v[mijloc-1] < x)
        return mijloc;
    else if(v[mijloc] < x &&  v[mijloc+1] > x)
        return mijloc+1;
    else if(x < v[mijloc])
        return cautareBinara(v, x, st, mijloc - 1);  // caut doar in stanga
    else
        return cautareBinara(v, x, mijloc + 1, dr);  // caut doar in dreapta
}

int main()
{
    FILE *pfile;
    pfile = fopen("prob2.txt", "r");

    int x, y, n, i, start;

    scanf("%d %d", &x, &y);
    fscanf(pfile, "%d", &n);
    
    int v[n];

    for(i = 0 ; i < n; i++)
        fscanf(pfile, "%d", &v[i]);

    start = cautareBinara(v, x, 0, n);
    for(i = start; v[i] <= y; i++)
        printf("%d ", v[i]);
}
#include <stdio.h>

int main()
{
    int n, c, k;
    scanf("%d", &n);

    for (c = 31; c >= 0; c--)
  {

    k = n >> c;

    if (k & 1)
      printf("1");
    else
      printf("0");

  }

  return 0;

}
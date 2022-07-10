#include <stdio.h>
#include <stdlib.h>

int busca_binaria(int *v, int len, int o);

int busca_binaria(int *v, int len, int o)
{
    int inicio = 0, fim = len-1;
    while (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        if (v[meio] == o)
            return meio;
        else if (v[meio] < o)
            inicio = meio + 1;
        else
            fim = meio;
    }
    return 0;
}
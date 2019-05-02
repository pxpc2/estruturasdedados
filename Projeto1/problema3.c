#include <stdio.h>

void moverDiscos(int n, char atual, char dest, char aux)
{
	if (n == 1)
		printf("Mover disco 1 da torre %c para %c\n", atual, dest);
	else
	{
		moverDiscos(n-1, atual, aux, dest); 
		printf("Mover disco %d da torre %c para %c\n", n, atual, dest);
		moverDiscos(n-1, aux, dest, atual);
	}
}

int main()
{
	int n = 0;
	printf("TORRE DE HANOI\nEntre com a quantidade de discos (maior que zero) a serem movidos de A para C\n");
	while (n < 1) scanf("%d", &n);
	moverDiscos(n, 'A', 'C', 'B');
	return 0;
}




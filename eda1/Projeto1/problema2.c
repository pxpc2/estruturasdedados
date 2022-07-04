#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void recebe_notas(float *, int *, int);
void conta_notas(int *, int *, int);
int percent_aprov(int *, float *);

int main(){
	
	float NOTAS[MAX], n;
	int APR[MAX], qtd_aprov[2], p;
	float perc_apr[2]; 

	for(int i = 0; i < MAX; i++){
		printf("insira a nota do aluno %d:", i+1);
		scanf("%f", &n);
		NOTAS[i] = n;
		printf("\n");
	}

	recebe_notas(NOTAS, APR, MAX);
	conta_notas(APR, qtd_aprov, MAX);
	p = percent_aprov(qtd_aprov, perc_apr);

	printf("Quantidade de alunos aprovados: %d\n", qtd_aprov[0]);	
	printf("Quantidade de alunos reprovados: %d\n", qtd_aprov[1]);
	printf("Percentual de alunos aprovados: %.f%%\n", perc_apr[0]);
	printf("Percentual de alunos reprovados: %.f%%\n", perc_apr[1]);
	printf("Mais da metade da turma foi aprovada?");
	if(p == 1)
		printf("Sim!");
	else
		printf("Nao!");
	printf("\n");
		

return 0;
}

void recebe_notas(float *notas, int *APR, int N){

	for(int i = 0; i < N; i++){
		if(notas[i] >= 6.0){
			*(APR + i) = 1;
		}else{
			*(APR + i) = 0;
		}
	}
}

void conta_notas(int *aprov, int *num_aprov, int N){
	
	for(int i = 0; i < N; i++){
		if ( *(aprov + i) == 1 ){
			num_aprov[0] += 1;
		}else{
			num_aprov[1] += 1;
		}
	}	
}

int percent_aprov(int *num_apr, float *perc_apr){
	
	*perc_apr = ((float)*num_apr / 10) * 100;
	*(perc_apr + 1) = 100 - *perc_apr;

	if(*perc_apr > 50.0)
		return 1;
	else 
		return 0;

}

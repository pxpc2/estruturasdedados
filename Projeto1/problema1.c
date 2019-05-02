#include <stdio.h>
#include <stdlib.h>

int main() {
  float ENTRADAS[10];
  float PESOS[10]; 
  float T;
  int i; 
  float x;
  
  printf("Digite 10 valores de entrada: \n");
  for(i=0; i<10; i++){
  printf("Entrada %d: ", i);
  scanf("%f", &ENTRADAS[i]);
  }

  printf("Digite 10 valores referentes aos pesos: \n");
  for(i=0; i<10; i++){
  printf("Peso %d: ", i);
  scanf("%f", &PESOS[i]);
  }

  printf("Digite um valor para o limiar T: \n");
  scanf("%f", &T);


  void fneuronio(float *ENTRADAS, float *PESOS, float T, float *x);

  fneuronio(ENTRADAS, PESOS, T, &x);

  if(x==1){
    printf("Neuronio ativado!\n");
  }
  else{
    printf("Neuronio inibido!\n");
  }
}

void fneuronio(float *ENTRADAS, float *PESOS, float T, float *x){
  int i;
  float eq;

  for(i=0; i<10; i++)
  eq+=*(ENTRADAS+i) * *(PESOS+i);

  if(eq>T){
    *x = 1;
  }
  else{
    *x = 0;
  }
}

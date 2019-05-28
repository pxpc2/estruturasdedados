#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto3.h"

int main() {
    carregarContatos();
    int flag = 1;
    while (flag)
    {
        int opcao = exibirMenu();
        switch (opcao) {
            case 1: {
                adicionarNo();
            }
                break;
            case 2: {
                char filtro[101];
                printf("Entre com a sequência de caracteres de filtro para remover os registros\n");
                getchar();
                fgets(filtro, 101, stdin);
                strtok(filtro, "\n");
                printf("Removendo registros\n");
                removerRegistros(filtro);
            }
                break;
            case 3: {
                char filtro[101];
                printf("Entre com a sequência de caracteres de filtro para buscar os registros\n");
                getchar();
                fgets(filtro, 101, stdin);
                strtok(filtro, "\n");
                exibirRegistros(filtro);
            }
                break;
            case 4:
                exibirLista();
                break;
            case 5:
                printf("Finalizando e salvando os novos dados da lista no arquivo txt...\n");
                escreverArquivo();
                flag = 0;
                break;
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

#define MAX 999

No* raiz = NULL;

No* loadTreeFromFile(char*);
void printExampleFormat();
void showMenu();

int main() {
    showMenu();
    return 0;
}

void showMenu()
{
    int opcao = -1;
    while (opcao != 0)
    {
        printf("------\nEscolha uma opcao:\n"
               "1 - carregar arvore de um arquivo\n"
               "2 - exibir arvore\n"
               "3 - arvore esta cheia?\n"
               "4 - buscar valor na arvore\n"
               "5 - altura da arvore\n"
               "6 - remover valor da arvore\n"
               "7 - print in order\n"
               "8 - print pre order\n"
               "9 - print post order\n"
               "10 - balancear a arvore\n"
               "0 - encerrar\n------\n");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            char nome[9];
            int op;
            printf("Entre com a opcao de um dos arquivos:\n"
                   "1 - bst1.txt\n"
                   "2 - bst2.txt\n"
                   "3 - bst3.txt\n"
                   "4 - bst4.txt\n"
                   "5 - bst5.txt\n"
                   "6 - bst6.txt\n");
            scanf("%d", &op);
            sprintf(nome, "bst%d.txt", op);
            raiz  = loadTreeFromFile(nome);
            printf("Arquivo carregado.\n");
        }
        else if (opcao == 2)
        {
            printExampleFormat();
            showTree(raiz);
            printf("\n\n");
        }
        else if (opcao == 3)
        {
            printf("%s\n", (isFull(raiz) == 1 ? "arvore cheia.\n" : "arvore nao e cheia.\n"));
        }
        else if (opcao == 4)
        {
            printf("Valor para buscar:\n");
            int v;
            scanf("%d", &v);
            if (searchValue(raiz, v) == 0)
                printf("Valor nao encontrado.\n");
        }
        else if (opcao == 5)
        {
            int altura = getHeight(raiz);
            printf("Altura da arvore = %d\n", altura);
        }
        else if (opcao == 6)
        {
            int v;
            printf("Entre com o valor a ser removido:\n");
            scanf("%d", &v);
            removeValue(raiz, v);
        }
        else if (opcao == 7)
        {
            printf("Imprimindo in-order\n");
            printEmOrdem(raiz);
            printf("\n");
        }
        else if (opcao == 8)
        {
            printf("Imprimindo pre-order\n");
            printPreOrdem(raiz);
            printf("\n");
        }
        else if (opcao == 9)
        {
            printf("Imprimindo post-order\n");
            printPosOrdem(raiz);
            printf("\n");
        }
        else if (opcao == 10)
        {
            balanceTree(raiz);
        }
    }
}

void printExampleFormat()
{
    printf("EXEMPLO DO FORMATO DA ARVORE EXIBIDA (HORIZONTAL):\n\n");
    char* path = (char*) calloc(16, sizeof(char));
    path = strcat(path, "TREE_FORMAT.txt");
    FILE* arq = fopen(path, "r");
    if (arq == NULL)
    {
        printf("Nao foi encontrado o arquivo TREE_FORMAT.txt que contem o exemplo do formato da arvore.\n"
               "Ao solicitar que imprima a arvore na tela, ela sera exibida de forma DEITADA.");
        return;
    }
    int c;
    while ((c = getc(arq)) != EOF)
        putchar(c);
    fclose(arq);
    printf("\n\n\n\n");
}

No* loadTreeFromFile(char* nome)
{
    if (raiz != NULL)
        liberarArvore(raiz); // se já tinha arvore antes, liberamos ela da memória para a nova
    raiz = NULL;
    char* path = (char*) calloc(14, sizeof(char));
    path = strcat(path, "BSTs/");
    path = strcat(path, nome);
    FILE* arq = fopen(path, "r");
    if (arq == NULL)
    {
        printf("Erro carregando arquivo.\n");
        return NULL;
    }
    fgets(path, MAX, arq);
    char* tok = strtok(path, " ");
    while (tok)
    {
        int data = atoi(tok);
        raiz = inserir(raiz, data);
        tok = strtok(NULL, " ");
    }
    return raiz;
}

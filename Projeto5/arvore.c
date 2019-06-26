#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"


/*
 * TODO: void removeValue(No*, int), void balance(No*)
 */


int cont = 1;
int qtNos = 0;

No* criarNo(int data)
{
    No* n = (No*) malloc(sizeof(No));
    n->data = data;
    n->dir = NULL;
    n->esq = NULL;
    qtNos++;
    return n;
}

No* inserir(No* n, int data)
{
    if (n == NULL)
    {
        // árvore/sub-árvore atual tá vazia então criamos o nó
        n = criarNo(data);
        return n;
    }
    else if (data <= n->data)
        n->esq = inserir(n->esq, data);
    else
        n->dir = inserir(n->dir, data);
    return n;
}

int listarDetalhes(No* raiz, No* n)
{
    printf("Nivel do no: %d\nValor do pai: %d\n", (raiz == NULL) ? 1 : cont,
           (raiz == NULL) ?  -1 : raiz->data);
    cont = 1;
    if (raiz == NULL)
        return 1;
    if (raiz->dir != NULL && raiz->dir->data == n->data && raiz->esq != NULL)
        printf("Valor do irmão: %d\n", raiz->esq->data);
    else if (raiz->esq != NULL && raiz->esq->data == n->data && raiz->dir != NULL)
        printf("Valor do irmão: %d\n", raiz->dir->data);
    return 1;
}

/*
 * Recebe o nó raiz e o valor que quer procurar
 * imprime na tela o valor do pai, dos irmãos e o nível do nó encontrado
 * retorna 1 se encontrou, 0 se não
 */
int search(No* pai, No* n, int data, int shouldPrint)
{
    if (n == NULL)
        return 0;
    //printf("NO: %d\n", n->data);
    if (n->data == data)
    {
        return (shouldPrint == 1? listarDetalhes(pai, n) : 1);
    }
    cont++;
    if (data < n->data)
        return search(n, n->esq, data, shouldPrint);
    else
        return search(n, n->dir, data, shouldPrint);
}

int searchValue(No* raiz, int v)
{
    return search(NULL, raiz, v, 1);
}

int getHeight(No* raiz)
{
    if (raiz == NULL)
        return 0;
    int alturaDir =  1 + getHeight(raiz->dir);
    int alturaEsq = 1 + getHeight(raiz->esq);
    return (alturaDir >= alturaEsq? alturaDir : alturaEsq);
}

// ou é folha, ou tem 2 nós
int isFull(No* raiz)
{
    if (raiz == NULL) // árvore/sub vázia, é completa
        return 1;
    if (raiz->esq == NULL && raiz->dir == NULL) // NÓ FOLHA
        return 1;
    if (raiz->esq != NULL && raiz->dir != NULL)
        return (isFull(raiz->dir) == 1 && isFull(raiz->esq) == 1? 1 : 0);
    return 0;
}

void printEmOrdem(No* raiz)
{
    if (raiz == NULL)
        return;
    printEmOrdem(raiz->esq);
    printf("%d ", raiz->data);
    printEmOrdem(raiz->dir);
}

No* getMenor(No* raiz)
{
    No* curr = raiz;
    while (curr->esq != NULL)
        curr = curr->esq;
    return curr;
}

void printPosOrdem(No* raiz)
{
    if (raiz == NULL)
        return;
    printPosOrdem(raiz->esq);
    printPosOrdem(raiz->dir);
    printf("%d ", raiz->data);
}

void printPreOrdem(No* raiz)
{
    if (raiz == NULL)
        return;
    printf("%d ", raiz->data);
    printPreOrdem(raiz->esq);
    printPreOrdem(raiz->dir);
}

void showTree(No* raiz)
{
    print("", raiz);
}

void print(char* s, No* n)
{
    char c[999] = "", c2[999] = "";
    strcat(c, s);
    strcat(c2, s);
    if (n == NULL)
        return;
    strcat(c, "     ");
    print(c, n->dir);
    printf("%s%s%d\n", c2, "|-- ", n->data);
    print(c, n->esq);
}

int getLevel(No* raiz, int value)
{
    if (raiz == NULL)
        return -999;
    if (raiz->data == value)
        return 1;

    int x = 1 + getLevel(raiz->dir, value);
    int y = 1 + getLevel(raiz->esq, value);

    return (x > y) ? x : y;
}

int getQtNos()
{
    return qtNos;
}

void liberarArvore(No* raiz)
{ // POS ORDEM, POIS VISITAMOS TODOS PRA DEPOIS DAR FREE
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
    qtNos = 0;
}


void removeValue(No *raiz, int v)
{
    if (raiz == NULL) return;
    if (search(NULL, raiz, v, 0) == 0)
    {
        printf("O valor nao esta presente na arvore.\n");
        return;
    }
    raiz = remover(raiz, v);
}

No* remover(No* n, int v)
{
    if (v < n->data)
        n->esq = remover(n->esq, v);
    else if (v > n->data)
        n->dir = remover(n->dir, v);
    else
    {
        // chegamos no Nó para remover
        if (n->esq == NULL)
            return doRemove(n, n->dir);
        else if (n->dir == NULL)
            return doRemove(n, n->esq);
        else
        {
            // Nó com duas sub-arvores
            No* curr = getMenor(n->dir); // pega o valor do sucessor inorder
            n->data = curr->data; // troca de valor o no raiz pelo valor do sucessor
            n->dir = remover(n->dir, curr->data); // e agora remove o sucessor
            // se o sucessor for caso basico fica trivial, se nao, faz isso recursivamente de novo
            // ate chegar no caso basico
        }
    }
    return n;
}

No* doRemove(No* n, No* child)
{
    No* curr = child;
    free(n);
    return curr;
}

void balanceTree(No* raiz)
{
    if (isBalanced(raiz))
        return;
}

int isBalanced(No* raiz) // diferença de altura das duas subarvores de qualquer nó é menor ou igual a 1
{
    if (raiz == NULL)
        return 1;
    int height_esq = 0, height_dir = 0;
    if (raiz->esq != NULL)
        height_esq = getHeight(raiz->esq);
    if (raiz->dir != NULL)
        height_dir = getHeight(raiz->dir);
    if (abs(height_dir-height_esq) <= 1 && isBalanced(raiz->dir) && isBalanced(raiz->esq))
        return 1;
    return 0;
}
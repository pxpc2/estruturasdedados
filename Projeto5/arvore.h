#ifndef PROJETO5_ARVORE_H
#define PROJETO5_ARVORE_H

// AQUI VAI AS STRUCTS DE ARVORE E OS CABECALHOS DAS FUNCOES

typedef struct no
{
    int data;
    struct no* esq;
    struct no* dir;
} No;

No* inserir(No*, int);
No* criarNo(int);
int search(No *, No *, int, int);
int searchValue(No *, int);
int getHeight(No*);
void showTree(No*);
void print(char*, No*);
void printEmOrdem(No*);
void printPosOrdem(No*);
void printPreOrdem(No*);
int isFull(No*);
void liberarArvore(No*);
void removeValue(No*,int);
No* remover(No*, int);
No* doRemove(No*,No*);
int getLevel(No*, int);
No* getMenor(No*);
void balanceTree(No*);
int isBalanced(No*);

#endif //PROJETO5_ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto3.h"

struct dados
{
    char nome[101], telefone[100], endereco[101], cep[100], nascimento[100];
};

struct no
{
    Data dados;
    No* prox;
    No* ant;
};

No* inicio = NULL;
No* fim = NULL;

int exibirMenu()
{
    int opcao = 5;
    printf("Digite uma opção:\n"
           "1 - Inserir novo registro\n"
           "2 - Remover registros que contém certa string no nome\n"
           "3 - Visualizar registros que contém palavra específica no nome\n"
           "4 - Visualizar todos registros\n"
           "5 - Salvar e sair\n");
    scanf("%d", &opcao);
    return opcao;
}

Data getDados()
{
    Data d;
    printf("Entre com o nome\n");
    getchar();
    fgets(d.nome, 101, stdin);
    strtok(d.nome, "\n");
    printf("Entre com o telefone no formato XXXXX-XXXX\n");
    while (1)
    {
        scanf("%s", d.telefone);
        if (strlen(d.telefone) < 9 || d.telefone[5] != '-') {
            printf("Entre com um formato válido. (XXXXX-XXXX)\n");
            continue;
        }
        break;
    }
    getchar();
    printf("Entre com o endereço\n");
    fgets(d.endereco, 101, stdin);
    strtok(d.endereco, "\n");
    printf("Entre com o CEP\n");
    scanf("%s", d.cep);
    printf("Entre com a data de nascimento, no formato DD/MM/AAAA\n");
    while (1)
    {
        scanf("%s", d.nascimento);
        if (d.nascimento[2] != '/' && d.nascimento[5] != '/') {
            printf("Entre com um formato válido\n");
            continue;
        }
        break;
    }
    return d;
}

void ordenarLista()
{
    No* curr = NULL;
    No* prox = NULL;
    if (inicio == NULL)
        return; // lista vazia, nada para ordenar
    for (curr = inicio; curr->prox != NULL; curr = curr->prox)
    {
        for (prox = curr->prox; prox != NULL; prox = prox->prox)
        {
            if (comparar(curr, prox) >= 0)
            {
                Data t = curr->dados;
                curr->dados = prox->dados;
                prox->dados = t;
            }
        }
    }
}

void adicionarContato(Data dados)
{
    No* n = (No*) malloc(sizeof(No));
    n->dados = dados;
    if (inicio == NULL)
    {
        // lista vazia
        inicio = n;
        fim = n;
        inicio->ant = NULL;
        fim->prox = NULL;
    }
    else
    {
        fim->prox = n;
        n->ant = fim;
        fim = n;
        fim->prox = NULL;
    }
}

void adicionarNo()
{
    Data dados = getDados();
    No* n = (No*) malloc(sizeof(No));
    n->dados = dados;
    if (inicio == NULL)
    {
        // lista vazia
        inicio = n;
        fim = n;
        inicio->ant = NULL;
        fim->prox = NULL;
    }
    else
    {
        fim->prox = n;
        n->ant = fim;
        fim = n;
        fim->prox = NULL;
    }
    ordenarLista();
}

/*
 * < 0 se A vem antes de B
 * > 0 se B vem antes de A
 */
int comparar(No* a, No* b)
{
    return strcmp(a->dados.nome, b->dados.nome);
}

void carregarContatos()
{
    printf("Carregando registros já salvos em contatos.txt.\n");
    int qt = 0;
    FILE *arq = fopen("contatos.txt", "r");
    if (arq == NULL)
    {
        printf("Erro ao carregar/criar \"contatos.txt\"");
        return;
    }
    char texto[255];
    int contador = 0;
    Data d;
    while (fgets(texto, 255, arq) != NULL)
    {
        if (strcmp(texto, "\n") == 0) continue;
        if (contador == 5)
        {
            contador = 0;
            qt++;
            adicionarContato(d);
            continue;
        }
        switch (contador)
        {
            case 0:
                strtok(texto, "\n");
                strcpy(d.nome, texto);
                break;
            case 1:
                strtok(texto, "\n");
                strcpy(d.telefone, texto);
                break;
            case 2:
                strtok(texto, "\n");
                strcpy(d.endereco, texto);
                break;
            case 3:
                strtok(texto, "\n");
                strcpy(d.cep, texto);
                break;
            case 4:
                strtok(texto, "\n");
                strcpy(d.nascimento, texto);
                break;
            default:
                break;
        }
        contador++;
    }
    printf("Total de %d registros carregados.\n\n", qt);
    printf("---------------\n");
    fclose(arq);
    ordenarLista();
}

void removerNo(No* n)
{
    printf("Removendo registro de nome: %s\n", n->dados.nome);
    if (n == fim)
    {
        fim = fim->ant;
        if (fim != NULL)
            fim->prox = NULL;
    }
    else if (n == inicio)
    {
        inicio = inicio->prox;
        if (inicio != NULL)
            inicio->ant = NULL;
    }
    else
    {
        n->ant->prox = n->prox;
        n->prox->ant = n->ant;
    }
    free(n);
}

void removerRegistros(char* filtro)
{
    if (inicio == NULL)
        return;
    No* curr = inicio;
    No* prox = NULL;
    while (curr != NULL)
    {
        if (strstr(curr->dados.nome, filtro) != NULL)
        {
            prox = curr->prox;
            removerNo(curr);
            curr = prox;
        }
        else
            curr = curr->prox;
    }
    free(curr);
    free(prox);
    ordenarLista();
}

void exibirLista()
{
    No* curr = inicio;
    printf("Exibindo lista\n");
    while (curr != NULL)
    {
        printNo(curr->dados);
        curr = curr->prox;
    }
    free(curr);
}

void printNo(Data d)
{
    printf("Nome: %s\n", d.nome);
    printf("Telefone: %s\n", d.telefone);
    printf("Endereço: %s\n", d.endereco);
    printf("CEP: %s\n", d.cep);
    printf("Nascimento: %s\n---------------\n", d.nascimento);
}

void exibirRegistros(char* filtro)
{
    No* curr = inicio;
    while (curr != NULL)
    {
        if (strstr(curr->dados.nome, filtro) != NULL)
            printNo(curr->dados);
        curr = curr->prox;
    }
    free(curr);
}

void escreverArquivo()
{
    FILE *arq = fopen("contatos.txt", "w");
    No* n = inicio;
    while (n != NULL)
    {
        Data d = n->dados;
        fprintf(arq, "%s\n%s\n%s\n%s\n%s\n$\n", d.nome, d.telefone,
                d.endereco, d.cep, d.nascimento);
        n = n->prox;
    }
    fclose(arq);
}

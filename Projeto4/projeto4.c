#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/*
 * ED1 - Mendelson - Projeto 4
 * Pedro Daia Cardoso - 180067265
 * João Bisnotti - 170069991
 * Luiz Gustavo Dias - 140169784
 */

// Início
int totalVoos = 0, totalAproximacao = 0, totalDecolagem = 0, totalPrioridade = 0;
double tempoCombustivel = 10.0;
int tempoAtual_s = 0, tempoInicial = 0;
int controle[65] = {};
char codigos[64][8] = { "VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008",
                        "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012",
                        "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002",
                        "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001",
                        "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601",
                        "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392",
                        "GF4681","GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065",
                        "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510",
                        "TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609",
                        "KL5610","KL5611" };

// Structs
typedef struct voo
{
    char *codigo;
    char modo;
    int combust;
    int prioridade;
} Voo;
typedef struct lista
{
    Voo *data;
    struct lista *prox;
} Lista;
typedef struct fila
{
    int tamanho;
    Lista *ini;
    Lista *fim;
} Fila;
typedef struct pista
{
    int num;
    double tempo_pra_liberar;
} Pista;

Pista **pistas;
Fila *fila;

// simulação
void reduzirCombustivel();
void atualizarAeronaves();
void atualizarTempos();
int pousar(Voo*,Pista*);
int decolar(Voo*,Pista*);

// Inicio
void gerarTotais();
int getCombustivelRand();
int getRandIndex();
void gerarVoos();

// Utilidades
int repete(int);

// Tempo
char *getData();
char *getHora();
int getTempoAtual();
void printarHora(int);
char tempo[9];
char t[3][2] = {};

// Fila
void printarFila();
void inicializarFila();
void enqueue(Voo*);
Lista *dequeue();
void enqueuePrioridade(Voo*);
void liberarAeronave(Voo*,int);
void freeAll();

// -----------------------------------------------------------------------------

int main()
{
    printf("Aeroporto Internacional de Brasília\n");

    printf("Hora Inicial: %s\n", getData());
    tempoInicial = getTempoAtual();
    tempoAtual_s = tempoInicial;

    gerarTotais();
    inicializarFila();
    gerarVoos();

    printarFila();
    printf("Número de voôs: %d\nNúmero de aproximações: %d\nNúmero de decolagens: %d\n--------------------\n",
           totalVoos, totalAproximacao, totalDecolagem);

    printf("\nListagem de eventos:\n\n");

    pistas = (Pista**) calloc(3, sizeof(Pista*));
    for (int i = 0; i < 3; i++)
    {
        pistas[i] = (Pista *) malloc(sizeof(Pista));
        if (pistas[i] == NULL)
        {
            printf("SEM MEMORIA\n");
            return 0;
        }

        pistas[i]->num = i+1;
        pistas[i]->tempo_pra_liberar = 0.0;
    }

    while (fila->tamanho > 0)
        atualizarAeronaves();

    freeAll();

    printf("\nTodos os procedimentos foram finalizados.\n");

    return 0;
}

// Simulação
void atualizarTempos() // CADA VEZ QUE ATUALIZAR TEMPOS É CHAMADA, PASSA-SE 1 UNIDADE DE TEMPO
{
    for (int i = 0; i < 3; i++)
    {
        if (pistas[i]->tempo_pra_liberar > 0.0)
        {
            pistas[i]->tempo_pra_liberar--;
        }
    }
    if (tempoCombustivel > 0.0)
    {
        tempoCombustivel--;
    }
    tempoAtual_s += 300; // 1 unidade de tempo = 5 min
}



void reduzirCombustivel()
{
    if (tempoCombustivel > 0.0)
        return;
    Lista *it = fila->ini;
    while (it != NULL)
    {
        if (it->data == NULL)
            return;
        it->data->combust--;
        it = it->prox;
    }
    tempoCombustivel = 10.0;
}
void atualizarAeronaves()
{
    if (fila->tamanho <= 0)
        return;
    Lista *it;
    while (fila->tamanho > 0)
    {
        it = dequeue();
        if (it->data == NULL) return;
        Voo *v = it->data;
        if (v == NULL)
            break;
        int res = 0;
        if (v->combust < 0 && v->modo == 'P')
        {
            printf("\nALERTA CRITICO, AERONAVE %s IRA CAIR\n", it->data->codigo); // NÃO DEVOLVE PRA LISTA.
            continue;
        }
        if (v->combust == 0) totalPrioridade--;
        for (int i = 0; i < 3; i++)
        {
            if (pistas[i] == NULL) return;
            if (v->modo == 'P')
                res = pousar(v,pistas[i]);
            else
                res = decolar(v,pistas[i]);
            if (res == 1) break; // conseguiu em uma pista, não precisa tentar nas outras.
        }
        if (res == 0) // não conseguiu pousar em nenhuma das pistas, coloca no final.
        {
            if (v->combust == 0)
            {
                totalPrioridade++;
                if (totalPrioridade >= 3)
                    printf("ALERTA GERAL DE DESVIO DE AERONAVE\n");
                enqueuePrioridade(v);
            }
            else enqueue(v);
        }

        atualizarTempos();

        reduzirCombustivel();

    }

}
void liberarAeronave(Voo* v, int id)
{
    if (v == NULL ) return;
    printf("\nCódigo do voo: %s\n", v->codigo);
    printf("Status: [aeronave %s]\n", (v->modo == 'P' ? "pousou" : "decolou"));
    printf("Horário de início do procedimento: ");
    printarHora(tempoAtual_s);
    printf("\nNúmero da pista: %d\n", id);
    printf("-----------------------------------------\n");
    //printarFila();
    //printf("\nQuantidade de aeronaves na fila: %d\n", fila->tamanho);
}

void freeAll()
{
    free(fila);
    for (int i = 0; i < 3; i++)
        free(pistas[i]);
    free(pistas);
}

int pousar(Voo *v, Pista *p)
{
    if (v == NULL || p == NULL) return 0;
    if (p->tempo_pra_liberar > 0.0)
        return 0;
    if (p->num == 3 && totalPrioridade < 3) // só pousamos na pista 3 se tiver em emergência
        return 0;
    p->tempo_pra_liberar = 4.0; // 3 + 1
    liberarAeronave(v, p->num);
    return 1;
}
int decolar(Voo *v, Pista *p)
{
    if (v == NULL || p == NULL) return 0;
    if (p->tempo_pra_liberar > 0.0)
        return 0;
    p->tempo_pra_liberar = 3.0;
    liberarAeronave(v, p->num);
    return 1;
}

// Inicialização
void gerarTotais()
{
    srand(time(0));
    totalVoos = 20 + rand() % (64 + 1 - 20);
    if (totalVoos > 32)
        totalAproximacao = totalVoos - 32 + rand() % (32 + 1 - (totalVoos - 32 ));
    else
        totalAproximacao = 10 + rand() % (totalVoos - 10);
    totalDecolagem = totalVoos - totalAproximacao;
}
int getRandIndex()
{
    return rand() % 65;
}
int getCombustivelRand()
{
    return rand() % 13;
}
void gerarVoos()
{
    int td = 0, ta = 0, index = 0;
    // gerar primeiro os de decolagem
    for (int i = 0; i < totalDecolagem; i++)
    {
        Voo *v = (Voo *) malloc(sizeof(Voo));
        index = getRandIndex();
        while (repete(index))
        {
            index = getRandIndex();
        }
        controle[i] = index;
        v->codigo = codigos[index-1];
        v->combust = 12;
        v->modo = 'D';
        v->prioridade = 0;
        enqueue(v);
        td++;
    }
    for (int j = totalDecolagem; j < totalVoos; j++)
    {
        Voo *v = (Voo *) malloc(sizeof(Voo));
        index = getRandIndex();
        while (repete(index))
        {
            index = getRandIndex();
        }
        controle[j] = index;
        v->codigo = codigos[index-1];
        v->combust = getCombustivelRand();
        v->modo = 'P';
        v->prioridade = 0;
        if (v->combust == 0)
        {
            v->prioridade = 1;
            enqueuePrioridade(v);
        }
        else
            enqueue(v);
        ta++;
    }
}

// Utilidades
int repete(int index)
{
    for (int i = 0; i < 64; i++)
    {
        if (controle[i] == index)
            return 1;
    }
    return 0;
}

// Métodos de tempo
char *getData()
{
    time_t mytime = time(NULL);
    char *time_str = ctime(&mytime);
    time_str[strlen(time_str) - 1] = '\0';
    return time_str;
}
char * inverte(char *d)
{
    int length = strlen(d) ;
    int c, i, j;

    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        c = d[i];
        d[i] = d[j];
        d[j] = c;
    }

    return d;
}
char *formataHora(){
    char *s, *t2;
    s = getData();
    t2 = inverte(s);

    for(int i = 0; i < 6; i++){

        if(i >= 4){
            strncpy(tempo, t2 + i, 8);
        }
    }

    char *p;
    p = tempo;
    p = inverte(p);
    return p;
}
void setHora(){
    char *s;
    s = formataHora();
    char *token = NULL;
    token = strtok(s, ":");
    int i = 0;
    while (token != NULL)
    {
        for (int j = 0; j < 2; j++)
        {
            t[i][j] = token[j];
        }
        i++;
        token = strtok(NULL, ":");
    }
}
int getTempoAtual()
{
    setHora();
    char aux[2];
    int hora_em_segundos =0, min_em_segundos=0, segundos=0;
    for (int i = 0; i < 3; i++)
    {
        aux[0] = t[i][0];
        aux[1] = t[i][1];
        if (i == 0)
            hora_em_segundos = atoi(aux);
        else if (i == 1)
            min_em_segundos = atoi(aux);
        else if (i == 2)
            segundos = atoi(aux);
    }
    int totalSegundos = hora_em_segundos * 3600 + min_em_segundos * 60 + segundos;
    return totalSegundos;
}
void printarHora(int segundos)
{
    int hora = segundos / 3600;
    int min = (segundos % 3600) / 60;
    int seg = (segundos % 3600) % 60;
    if (hora < 10)
        printf("0");
    printf("%d:",hora);
    if (min < 10)
        printf("0");
    printf("%d:",min);
    if (seg < 10)
        printf("0");
    printf("%d\n",seg);
}

// Métodos fila
void inicializarFila()
{
    fila = (Fila*) malloc(sizeof(Fila));
    if (fila == NULL)
    {
        printf("sem memória!\n");
        return;
    }
    fila->fim = NULL;
    fila->ini = NULL;
    fila->tamanho = 0;
}
void printarFila()
{
    if (fila->tamanho == 0)
    {
        printf("\nProcedimentos encerrados.\n");
        return;
    }
    printf("Fila de pedidos: %d\n", fila->tamanho);
    Lista *temp = fila->ini;
    while (temp != NULL)
    {
        Voo *v = temp->data;
        printf("[%s - %c - %d] (COMBUSTÍVEL = %d)\n", v->codigo, v->modo, v->prioridade, v->combust);
        temp = temp->prox;
    }
}
void enqueue(Voo *v)
{
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    if (novo == NULL )
        return;
    novo->data = v;
    novo->prox = NULL;
    if (fila->ini == NULL)
    {
        // tá vazia
        fila->ini = novo;
        fila->fim = novo;
    }
    else
    {
        Lista *temp = fila->ini;
        while (temp->prox != NULL)
            temp = temp->prox;
        temp->prox = novo;
        fila->fim = novo;
    }
    fila->tamanho++;
}
void enqueuePrioridade(Voo *v)
{
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    if (novo == NULL ) return;
    novo->data = v;
    novo->prox = fila->ini;
    fila->ini = novo;
    fila->tamanho++;
}
Lista* dequeue()
{
    Lista *el = fila->ini;
    if (el == NULL) return NULL;
    if (fila->ini->data->modo == 'D')
        totalDecolagem--;
    else
        totalAproximacao--;
    fila->ini = fila->ini->prox;
    if (fila->ini == NULL)
        fila->fim = NULL;
    fila->tamanho--;
    totalVoos--;
    return el;
}

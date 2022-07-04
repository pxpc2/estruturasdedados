#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rede.h"

#define QT_ENTRADA 536 // quantidade de neurônios na camada entrada

#define LEARNING_RATE 0.3 // definida aleatoriamente

Rede* rede;

/**
 * Aloca memoria e inicializa as camadas e seus respectivos neuronios,
 * atribuindo já os pesos e bias aleatorios pras entradas dos neuronios.
 *
 * @param qt_oculta quantidade de neuronios na camada oculta (definida runtime)
 */
void initRede(int qt_oculta)
{
    rede = (Rede*) malloc(sizeof(Rede));
    rede->entrada = (Camada*) malloc(sizeof(Camada));
    rede->entrada->neuronios = (Neuronio**) malloc(sizeof(Neuronio*) * QT_ENTRADA);
    rede->entrada->qt_neuronios = QT_ENTRADA;
    rede->entrada->qt_entradas = QT_ENTRADA;
    rede->entrada->def = 0;
    rede->entrada->sinal_saida = (double*) malloc(sizeof(double) * QT_ENTRADA);
    initNeuronios(rede->entrada, qt_oculta);

    rede->oculta = (Camada*) malloc(sizeof(Camada));
    rede->oculta->neuronios = (Neuronio**) malloc(sizeof(Neuronio*) * qt_oculta);
    rede->oculta->qt_neuronios = qt_oculta;
    rede->oculta->qt_entradas = QT_ENTRADA;
    rede->oculta->def = 1;
    rede->oculta->sinal_saida = (double*) malloc(sizeof(double) * qt_oculta);
    initNeuronios(rede->oculta, qt_oculta);

    rede->saida = (Camada*) malloc(sizeof(Camada));
    rede->saida->neuronios = (Neuronio**) malloc(sizeof(Neuronio*));
    rede->saida->qt_neuronios = 1;
    rede->saida->def = 2;
    rede->saida->qt_entradas = qt_oculta;
    rede->saida->sinal_saida = (double*) malloc(sizeof(double) * 1);
    initNeuronios(rede->saida, qt_oculta);

}

/**
 *
 * Inicializa os neuronios
 *
 * @param camada camada da qual inicializar os neuronios
 * @param qt_oculta quantidade de neuronios na camada oculta da rede
 */
void initNeuronios(Camada* camada, int qt_oculta)
{
    if (camada == NULL)
        return;
    for (int i = 0; i < camada->qt_neuronios; i++)
    {
        // trocamos a seed a cada iteração pra não repetir os mesmos pesos e bias
        srand(i);
        double* pesos = gerarPesos(camada->qt_entradas);

        camada->neuronios[i] = (Neuronio*) malloc(sizeof(Neuronio));

        // se for da camada oculta ou entrada, teremos 536 pesos e 536 entradas
        // se for da camada saída, teremos "qt_oculta" pesos e entradas
        int size = (camada->qt_neuronios == 1? qt_oculta : QT_ENTRADA);

        camada->neuronios[i]->p = (double*) malloc(sizeof(double) * size);
        camada->neuronios[i]->w = (double*) malloc(sizeof(double) * size);
        camada->neuronios[i]->p_length = size;

        for (int j = 0; j < camada->qt_entradas; j++)
            camada->neuronios[i]->w[j] = pesos[j];
        camada->neuronios[i]->b = gerarBias();
    }
}

/**
 * Gera um vetor de pesos aleatorios
 * @param quantidade quantidade de pesos pra gerar (igual a quantidade de entradas que neuronio recebe)
 * @return vetor de pesos gerados
 */
double* gerarPesos(int quantidade)
{
    double* pesos = (double*) malloc(sizeof(double) * quantidade);
    for (int i = 0; i < quantidade; i++)
    {
        pesos[i] = rand() % 15000 + 1;
    }
    return pesos;
}

/**
 * Gera um escalar aleatorio, bias.
 * @return o bias
 */
double gerarBias()
{
    return rand() % 15000 + 1;
}

/**
 * Calcula o somatorio do produto dos pesos pelas entradas, e adiciona o bias
 * @param n neuronio pra calcular o somatorio dele
 * @return o valor que vai na funcao logistica
 */
double getSomatorio(Neuronio* n)
{
    double sum = 0.0;
    if (n == NULL)
        return -1;
    for (int i = 0; i < n->p_length; i++)
        sum += (n->p[i]*n->w[i]);
    return (n->b + sum);
}

/**
 * Aplica a funcao logistica ao somatorio
 * @param somatorio somatorio do produto dos pesos pelas entradas e o bias
 * @return resultado da funcao logistica (sigmoid)
 */
double funcaoLogistica(double somatorio)
{
    return 1 / (1 + exp(-somatorio));
}

/**
 * Aplica a derivada da função sigmoide
 * @param input entrada
 * @return resultado da função sigmoide derivada pra este input
 */
double derivadaSigmoide(double input)
{
    double r = funcaoLogistica(input);
    return (r * (1 - r));
}

/**
 * Aplica o processo de feedforward com os inputs especificados
 * @param input entrada pro feedforward
 * @return saída gerada pela rede após propagar pelas camadas
 */
double feedForward(double* input)
{
    double* output_entrada = feed(rede->entrada, input);
    double* output_oculta = feed(rede->oculta, output_entrada);
    return feed(rede->saida, output_oculta)[0];
}

/**
 * Faz o processo de feedforward pra camada utilizando as features de entrada
 * @param camada ponteiro pra camada a qual fazer o processo
 * @param features entrada do feedforward
 * @return o vetor de saída do feedforward dado a entrada, pra esta camada
 */
double* feed(Camada* camada, double* features)
{
    double* out = (double*) malloc(sizeof(double) * camada->qt_neuronios);
    if (features == NULL)
        return NULL;
    for (int i = 0; i < camada->qt_neuronios; i++)
    {
        // para cada neuronio desta camada
        for (int j = 0; j < camada->qt_entradas; j++)
        {
            // para cada entrada deste neuronio, atribuimos ela a feature
            camada->neuronios[i]->p[j] = features[j];
        }
        double somatorio = getSomatorio(camada->neuronios[i]);
        double logistic = funcaoLogistica(somatorio);
        camada->neuronios[i]->s = logistic;
        out[i] = logistic;
    }
    camada->sinal_saida = out;
    return out;
}

/**
 * Realiza o cálculo do custo, somatorio do resultado (esperado - saída)^2 pra cada
 * neuronio de cada camada, e seta os erros pra cada neuronio
 * @param expected resultado esperado
 */
void setCusto(int expected)
{
    double custo = 0.0, error;
    for (int i = 0; i < rede->entrada->qt_neuronios; i++)
    {
        error = expected - rede->entrada->neuronios[i]->s;
        rede->entrada->neuronios[i]->erro = error;
        custo += pow(error, 2);
    }
    for (int i = 0; i < rede->oculta->qt_neuronios; i++)
    {
        error = expected - rede->oculta->neuronios[i]->s;
        rede->oculta->neuronios[i]->erro = error;
        custo += pow(error, 2);
    }
    error = expected - rede->saida->neuronios[0]->s;
    rede->saida->neuronios[0]->erro = error;
    custo += pow(error, 2);
    rede->custo = custo;
}
/**
 * Realiza o cálculo dos gradientes de acordo com o referêncial bibliográfico
 * Como o gradiente de cada neuronio da camada oculta depende dos gradientes da saída
 * utilizamos recurssão
 * @param c camada pra calcular os gradientes
 * @return vetor de gradientes da camada c
 */
double* getGradiente(Camada* c)
{
    double* gradientes = (double*) malloc(sizeof(double) * c->qt_neuronios);
    if (c->def == 1 || c->def == 0)
    {
        for (int i = 0; i < c->qt_neuronios; i++)
        {
            // usamos recurssividade pra calcular os gradientes da camada oculta
            for (int j = 0; j < (c->def == 1? rede->saida->qt_neuronios : rede->oculta->qt_neuronios); j++)
                gradientes[i] += getGradiente((c->def == 1? rede->saida : rede->oculta))[j]*
                        c->def == 1? rede->saida->neuronios[j]->s : rede->oculta->neuronios[j]->w[j];
            gradientes[i] *= derivadaSigmoide(c->neuronios[i]->s);
            c->neuronios[i]->gradiente = gradientes[i];
        }
    }
    else if (c->def == 2)
    {
        for (int i = 0; i < c->qt_neuronios; i++)
        {
            gradientes[i] = derivadaSigmoide(c->neuronios[i]->s) * c->neuronios[i]->erro;
            rede->saida->neuronios[i]->gradiente = gradientes[i];
        }
        return gradientes;
    }
    return gradientes;
}

void setGradientes()
{
    getGradiente(rede->entrada);
    getGradiente(rede->oculta);
    getGradiente(rede->saida);
}

/**
 * Realiza o ajuste dos pesos após realizar o calculo dos gradientes
 * @param camada camada dos pesos pra ajustar
 */
void ajustarPesos(Camada* camada)
{
    if (camada->def == 0)
        return; // não fazemos operações com a camada de entrada
    for (int i = 0; i < camada->qt_neuronios; i++)
    {
        for (int j = 0; j < camada->neuronios[i]->p_length; j++)
        {
            double saida_anterior = 0.0;
            if (camada->def == 1)
                saida_anterior = rede->entrada->neuronios[j]->s;
            else if (camada->def == 2)
                saida_anterior = rede->oculta->neuronios[j]->s;
            camada->neuronios[i]->w[j] = (camada->neuronios[i]->w[j]) +
                    (LEARNING_RATE * saida_anterior * camada->neuronios[i]->gradiente);
        }
    }
}

/**
 * Realiza o ajuste do bias de cada neuronio
 * @param camada  camada pra ajustar
 */
void ajustarBias(Camada* camada)
{
    if (camada->def == 0)
        return; // não fazemos com a entrada
    for (int i = 0; i < camada->qt_neuronios; i++)
        camada->neuronios[i]->b = camada->neuronios[i]->b + (LEARNING_RATE * camada->neuronios[i]->gradiente);
}

void backPropagate(int type)
{
    setCusto(type);
    setGradientes();
    ajustarPesos(rede->oculta);
    ajustarPesos(rede->saida);
    ajustarBias(rede->oculta);
    ajustarBias(rede->saida);
}

/**
 * Libera da memoria os neuronios da camada
 * @param c camada pra liberar os seus neuronios
 */
void freeNeuronios(Camada* c)
{
    for (int i = 0; i < c->qt_neuronios; i++)
    {
        free(c->neuronios[i]->p);
        free(c->neuronios[i]->w);
        free(c->neuronios[i]);
    }
    free(c->neuronios);
}

/**
 * Libera todos os ponteiros alocados dinamicamente na memoria
 */
void freeTodos()
{
    freeNeuronios(rede->entrada);
    freeNeuronios(rede->oculta);
    freeNeuronios(rede->saida);
    free(rede->entrada->sinal_saida);
    free(rede->oculta->sinal_saida);
    free(rede->saida->sinal_saida);
    free(rede->entrada);
    free(rede->oculta);
    free(rede->saida);
    free(rede);
}

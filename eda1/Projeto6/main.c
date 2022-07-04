#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rede.h"
#include "glcm.h"

int main(int argc, char* argv[])
{
    // gera os 50 numeros das imagens, onde os 25 primeiros sao pro treinamento e os ultimos pro teste.
    int* nums = gerarNumerosAleatorio();

    // pega o valor definido pra qt de neuronios em runtime, se nada for definido o padrao serão 10 neuronios
    int qt_oculta = (argc < 2? 10 : atoi(argv[1]));

    // inicializa as camadas e seus neuronios
    initRede(qt_oculta);

    srand(time(NULL));
    double taxa_acerto = 0.0, taxa_falsa_rejeicao = 0.0, taxa_falsa_aceitacao = 0.0;

    printf("Calculando...\n");

    int epoca = 0;

    while (epoca < 1000)
    {
        printf("Iniciando epoca #%d\n", epoca+1);
        epoca++;
        double mse = 0.0;
        for (int i = 0; i < 25; i++) // conjunto treinamento
        {
            int type = rand() % 2; // aleatoriamente escolhe se vai ser grass ou asphalt
            if (type % 2)
                type = 1;
            else
                type = 0;
            double *feature = getFeaturesImg(nums[i], type); // 1 = grass, 0 = asphalt

            double output_saida = feedForward(feature);

            mse += pow(type - output_saida, 2);

            backPropagate(type); // faz os ajustes dos pesos e biases

            printf("...\n");
        }
        printf("Fim epoca\n");
        mse /= 25;
        if (mse < 0.2)
            break;
    }

    printf("Iniciando o teste\n");
    for (int i = 25; i < 50; i++) // TESTE
    {
        int type = rand() % 2; // aleatoriamente escolhe se vai ser grass ou asphalt

        if (type % 2)
            type = 1;
        else
            type = 0;

        double *feature = getFeaturesImg(nums[i], type); // 1 = grass, 0 = asphalt

        double output_saida = feedForward(feature);

        if ((output_saida > 0.5 && type == 1) || (output_saida < 0.5 && type == 0))
            taxa_acerto++;
        else if (output_saida > 0.5 && type == 0)
            taxa_falsa_aceitacao++;
        else if (output_saida < 0.5 && type == 1)
            taxa_falsa_rejeicao++;
    }

    freeTodos(); // libera todos os ponteiros alocados da memoria

    printf("Taxa acerto = %.1lf%%\n", (taxa_acerto / 25.0) * 100.0);
    printf("Taxa falsa aceitacao = %.1lf%%\n", (taxa_falsa_aceitacao / 25.0) * 100.0);
    printf("Taxa falsa rejeicao = %.1lf%%\n", (taxa_falsa_rejeicao / 25.0) * 100.0);

    return 0;
}
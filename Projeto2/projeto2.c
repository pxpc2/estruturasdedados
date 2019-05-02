#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX 1025*1025

/**
 * Universidade de Brasília
 *
 * Projeto 02 da disciplina Estruturas de Dados 1, professor Mendelson
 *
 *      Pedro Daia Cardoso - 180067265
 *      João Bisnotti      - 170069991
 *      Luiz Gustavo Dias  - 140169784
 */

int* getMatriz(int, int);
int* getVetorILBP(int*);
int repete(int*, int);
int* gerarNumerosAleatorio();
double* getMatrizGLCM(int*, int, int);
double* getMetricas(double*, int*, int, int);
double* getFeaturesImg(int, int);
void normalizar(double*);
int compararImagem(double*, double*, double*);

int main()
{
    int* nums = gerarNumerosAleatorio();
    
    double* media_grass = (double *) calloc(536, sizeof(double));
    double* media_asphalt = (double *) calloc(536, sizeof(double));
    
    double* features_grass = (double *) calloc(536, sizeof(double));
    double* features_asphalt = (double *) calloc(536, sizeof(double));
    
    // Pra cada imagem
    for (int i = 0; i < 25; i++)
    {
        features_grass = getFeaturesImg(nums[i], 0);
        features_asphalt = getFeaturesImg(nums[i], 1);
        
        normalizar(features_grass);
        normalizar(features_asphalt);
        
        for (int j = 0; j < 536; j++)
        {
            *(media_grass + j) += (*(features_grass + j) / 25.0);
            *(media_asphalt + j) += (*(features_asphalt + j) / 25.0);
        }
        
    }
    
    double taxa_acerto = 0.0, taxa_Faceitacao = 0.0, taxa_Frejeicao = 0.0;
    
    for (int i = 25; i < 50; i++)
    {
        features_grass = getFeaturesImg(*(nums + i), 0);
        features_asphalt = getFeaturesImg(*(nums + i), 1);
        
        normalizar(features_grass);
        normalizar(features_asphalt);
        
        // comparar com as médias calculadas no treinamento
        int dist_grass = compararImagem(media_grass, media_asphalt, features_grass);
        
        if (dist_grass == 1) taxa_acerto++;
        else if (dist_grass == 0) taxa_Frejeicao++;
            
        int dist_asphalt = compararImagem(media_grass, media_asphalt, features_asphalt);
        
        if (dist_asphalt == 1) taxa_Faceitacao++;
        else if (dist_asphalt == 0) taxa_acerto++;
        
    }
    
    free(features_grass);
    free(features_asphalt);
    free(media_grass);
    free(media_asphalt);
    free(nums);
    
    double acerto = (double) (taxa_acerto / 50.0) * 100.0;
    double f_aceitacao = (double) (taxa_Faceitacao / 50.0) * 100.0;
    double f_rejeicao = (double) (taxa_Frejeicao / 50.0) * 100.0;
    
    printf("TAXA DE ACERTO = %.1lf%%\n", acerto);
    printf("TAXA DE FALSA ACEITAÇÃO = %.1lf%%\n", f_aceitacao);
    printf("TAXA DE FALSA REJEIÇÃO = %.1lf%%\n", f_rejeicao);
    
    return 0;
    
}

/**
 type 0 = grass
 type 1 = asphalt
 */
int* getMatriz(int num, int type)
{
    int tamRota;
    char* rota = (char *) calloc(tamRota, sizeof(char));
    if (type == 0)
    {
        tamRota = 28;
        strcpy(rota, "DataSet/grass/grass_");
    }
    else if (type == 1)
    {
        tamRota = 32;
        strcpy(rota, "DataSet/asphalt/asphalt_");
    }
    
    char buffer[3];
    sprintf(buffer, "%02d", num);
    
    strcat(rota, buffer);
    strcat(rota, ".txt");
    
    FILE *arq;
    arq = fopen(rota, "r"); // r = somente leitura
    
    char texto[1025*4];
    
    int i = 0, j = 0;
    
    int* matriz = (int *) calloc(2000*2000, sizeof(int));
    
    int count = 0;
    
    while (fgets(texto, 1025*4, arq) != NULL)
    {
        j = 0;
        const char remover[2] = ";";
        char *token;
        token = strtok(texto, remover);
        int pixel = atoi(token);
        matriz[i * 1025 + j] = pixel;
        count++;
        while (token != NULL)
        {
            token = strtok(NULL, remover);
            if (token == NULL) continue;
            j++;
            pixel = atoi(token);
            matriz[i * 1025 + j] = pixel;
            count++;
        }
        i++;
    }
    
    fclose(arq);
    
    return matriz;
}


int* getVetorILBP(int* matriz)
{
    const int size = 1025; // tamanho da matriz do arquivo
    
    int* vetorILBP = (int *) calloc(512, sizeof(int));
    
    for(int s = 0; s < size*size; s++) // a ideia é passar por todos os pixels e pegar seus vizinhos
    {
        int mat[3][3] = {};
        int soma = 0;
        int matBin[3][3]={};
        double media = 0.0;
        
        int x_pixel, y_pixel; // posicao do pixel atual na matriz
        
        if (s < size)
        {
            x_pixel = 0;
            y_pixel = s;
        }
        else
        {
            x_pixel = s / size;
            y_pixel = s % size;
        }
        
        if (x_pixel == 0 || y_pixel == 0 || x_pixel == 1024 || y_pixel == 1024)
            continue; // não queremos trabalhar com os pixels das bordas
        
        // cálculo dos vizinhos do pixel atual, jogando em mat[x][y] 3x3
        
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                int dx,dy;
                dx = x_pixel + i, dy = y_pixel + j;
                
                mat[i+1][j+1] = *(matriz + dx * 1025 + dy);
                
                soma += mat[i+1][j+1];
            }
        }
        
        int palavraBin[9];
        media = (double) soma / 9.0;
        
        int d = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (mat[i][j] < media)
                    matBin[i][j] = 0;
                else
                    matBin[i][j] = 1;
                
                palavraBin[d] = matBin[i][j];
                d++;
            }
        }
        
        // pegar o menor valor das rotações da palavra binária, o código ILBP
        
        int menor = 9999999, j = 9;
        int aux[9];
        while (j--)
        {
            // 9 rotações possíveis
            for (int i = 0; i < 9; i++)
            {
                int auxx = palavraBin[i];
                if (i == 0)
                    aux[i] = palavraBin[8];
                else
                    aux[i] = palavraBin[i-1];
                
                if (i == 8)
                    aux[0] = auxx;
                else
                    aux[i+1] = auxx;
            }
            // calcular valor decimal
            int decimal = 0;
            for (int i = 0; i < 9; i++)
                decimal += aux[i] * pow(2, 8-i);
            
            for (int i =0; i < 9; i++)
                palavraBin[i] = aux[i];
            
            if (decimal < menor) menor = decimal;
        }
        *(vetorILBP + menor) += 1; // faz a contabilidade do vetor ILBP
    }
    
    return vetorILBP;
    
}

int repete(int* vetor, int num)
{
    for (int i = 0; i < 50; i++)
        if (vetor[i] == num)
            return 1;
    return 0;
}

/**
 Gerar 25 números aleatórios e preencher o resto com o que falta, pra
 compor os conjuntos TESTE  e TREINAMENTO
 */
int* gerarNumerosAleatorio()
{
    int* nums = (int*) calloc(50, sizeof(int));
    
    srand(time(0));
    
    for (int i = 0; i < 25; i++)
    {
        int n = rand() % 50 + 1;
        if (repete(nums, n) == 1)
        {
            i--; // repetir essa iteração
            continue;
        }
        *(nums + i) = n;
    }
    
    int j = 25;
    
    for (int i = 1; i <= 50; i++)
    {
        if (repete(nums, i) == 1) continue;
        nums[j] = i;
        j++;
    }
    
    return nums;
}

/**
 (dx, dy)
 (0, 0) = pixel inicial
 (0, 1) = acima
 (0, -1) = abaixo
 (1, 0) = direita
 (1, 1) = diagonal direita cima
 (1, -1) = diagonal direita baixo
 (-1, 0) = esquerda
 (-1, 1) = diagonal esquerda cima
 (-1, -1) = diagonal esquerda baixo
 */
double* getMatrizGLCM(int* matriz, int dx, int dy)
{
    double* glcm = (double *) calloc(256*256, sizeof(double));
    
    int size = 1025, x1, y1, x2, y2;
    
    for (int s = 0; s < size*size; s++) // passar por todos os pixels
    {
        if (s < size)
        {
            x1 = 0;
            y1 = s;
        }
        else
        {
            x1 = s / size;
            y1 = s % size;
        }
        
        x2 = x1 + dx;
        y2 = y1 + dy;
        
        if (x2 < 0 || y2 < 0 || x2 > 1024 || y2 > 1024)
            continue; // pular esta iteração pois não há pixel nessa direção
        
        int indice1 = matriz[x1 * 1025 + y1];
        int indice2 = matriz[x2 * 1025 + y2];
        
        *(glcm + (indice1 * 256) + indice2) += 1;
    }
    
    return glcm;
}

double* getMetricas(double* glcm, int* matriz, int dx, int dy)
{
    
    double contraste = 0.0, homog = 0.0, energia = 0.0;
    
    double* metricas = (double *) calloc(3, sizeof(double));
    
    int size = 1025, x1, y1, x2, y2;
    
    for (int s = 0; s < size*size; s++) // passar por todos os pixels
    {
        if (s < size)
        {
            x1 = 0;
            y1 = s;
        }
        else
        {
            x1 = s / size;
            y1 = s % size;
        }
        
        x2 = x1 + dx;
        y2 = y1 + dy;
        
        if (x2 < 0 || y2 < 0 || x2 > 1024 || y2 > 1024)
            continue; // pular esta iteração pois não há pixel nessa direção
        
        int indice1 = *(matriz + x1 * 1025 + y1);
        int indice2 = *(matriz + x2 * 1025 + y2);
        
        double prob_glcm = (double) (*(glcm + indice1 * 256) + indice2) / MAX;
        
        int mod = abs(indice1-indice2);
        
        contraste += prob_glcm * pow(mod, 2);
        
        homog += prob_glcm / (1 + mod);
        
        energia += pow(prob_glcm, 2);
        
    }
    
    *(metricas + 0) = contraste;
    *(metricas + 1) = homog;
    *(metricas + 2) = energia;
    
    return metricas;
}

double* getFeaturesImg(int num, int type)
{
    double* features = (double *) calloc(536, sizeof(double));
    
    int* matriz;
    int* ilbp;
    double* glcm[8];
    
    // Pegar a matriz da imagem atual
    matriz = getMatriz(num, type);
    
    // Realizar o ILBP da imagem atual
    ilbp = getVetorILBP(matriz); // vetor de 512 posições
    
    
    // Pegar os 8 GLCMs da imagem atual
    // Cada métrica pra cada uma das 8 GLCMs
    double* contraste = (double *) calloc(8, sizeof(double));
    double* homog = (double *) calloc(8, sizeof(double));
    double* energia = (double *) calloc(8, sizeof(double));
    
    int cont = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0) continue; // não precisa fazer GLCM pro próprio pixel atual
            // faz o GLCM da direção atual i,j
            glcm[cont] = getMatrizGLCM(matriz, i, j);
            
            double* metricas = getMetricas(glcm[cont], matriz, i, j);
            
            *(contraste + cont) = *(metricas + 0);
            *(homog + cont) = *(metricas + 1);
            *(energia + cont) = *(metricas + 2);
            
            cont++;
        }
    }
    
    int i = 0;
    for (i = 0; i < 512; i++)
        *(features + i) = (double) *(ilbp + i);
    for (i = 512; i < 520; i++)
        *(features + i) = (double) *(contraste + (i-512));
    for (i = 520; i < 528; i++)
        *(features + i) = (double) *(homog + (i-520));
    for (i = 528; i < 536; i++)
        *(features + i) = (double) *(energia + (i-528));
    
    return features;
}

void normalizar(double* vetor)
{
    int maior = 0, menor = 9999999;
    for (int i = 0; i < 536; i++)
    {
        double element = *(vetor + i);
        
        if (element == 0.0) continue;
        
        if (element < menor)
            menor = element;
        
        if (element > maior)
            maior = element;
        
    }
    for (int i = 0; i < 536; i++)
    {
        double element = *(vetor + i);
        *(vetor + i) = (double) (element - menor) / (maior - menor);
    }
}

/**
 * return 1 -> parece mais com grama
 * return 0 -> parece mais com asfalto
 */
int compararImagem(double* media_grass, double* media_asphalt, double* vetor)
{
    int result_grass = 0, result_asphalt = 0;
    for (int i = 0; i < 536; i++)
    {
        result_grass += pow(*(vetor + i) - *(media_grass + i), 2);
        result_asphalt += pow(*(vetor + i) - *(media_asphalt + i), 2);
    }
    result_grass = sqrt(result_grass);
    result_asphalt = sqrt(result_asphalt);
    return (result_grass < result_asphalt) ? 1 : 0;
}

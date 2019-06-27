typedef struct neuronio
{
    double* p; // conjunto de entradas deste neuronio
    double* w; // conjunto de pesos deste neuronio
    double b; // bias deste neuronio
    double s; // saida deste neuronio
    int p_length; // quantidade de entradas
    double erro; // erro para propagar deste neuronio
    double gradiente; // gradiente deste neuronio para o backpropagation

} Neuronio;
typedef struct camada
{
    int def;
    Neuronio** neuronios; // conjunto de ponteiros dos neuronios dessa camada
    int qt_neuronios; // quantidade de neuronios presente na camada
    int qt_entradas; // quantidade de entradas por neuronio da camada
    double* sinal_saida;
} Camada;
typedef struct rede
{
    Camada* entrada; // primeira camada da rede, com 536 neuronios
    Camada* oculta; // camada oculta, quantidade de neuronios definida runtime
    Camada* saida; // ultima camada, com somente 1 neuronio
    double custo; // custo da rede com pesos e bias atuais
} Rede;

// inicializa a rede e suas camadas
void initRede(int);
// inicializa cada neuronio de uma camada (gerando os pesos e bias aleatorios)
void initNeuronios(Camada*,int);
// gera pesos aleatorios
double* gerarPesos(int);
// gera um bias aleatorio
double gerarBias();
// pega o somatorio do produto pesos por entradas, somando com o bias
double getSomatorio(Neuronio*);
// pega a saída de um neuronio usando a funcao logistica sigmoid
double funcaoLogistica(double);
// faz o processo de feedforward chamando a funcao feed
double feedForward(double*);
// realiza o processo de atribuir entradas ao neuronio e calcular sua saída
double* feed(Camada*,double*);
// faz o calculo do somatorio do custo de cada neuronio
void setCusto(int);
// joga o valor na derivada da fç sigmoide, para calculo do gradiente do neuronio
double derivadaSigmoide(double);
// chama as funcoes do backpropagation
void backPropagate(int);
// faz o processo de calcular os gradientes pra cada camada
void setGradientes();
// realiza os calculos para pegar o gradiente de cada neuronio
double* getGradiente(Camada*);
// realiza o ajuste dos pesos com os novos gradientes
void ajustarPesos(Camada*);
// realiza o ajuste de cada bias com os novos gradientes
void ajustarBias(Camada*);
// libera da memoria todos os neuronios
void freeNeuronios(Camada*);
// libera da memoria o resto dos ponteiros
void freeTodos();

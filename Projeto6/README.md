# EDA1 2019.1 UnB-FGA Projeto 06 #

---

Pedro Daia Cardoso - 18/0067265
<br>João Victor Max Bisnotti de Oliveira - 17/0069991
<br>Luiz Gustavo Dias Paes Pinheiro - 14/0169784

---

## Sobre o Projeto
O programa consiste em um sistema para classificação de imagens utilizando os métodos ILBP e GLCM, para pouso de um drone.
Nesta implementação, utiliza-se uma rede neural feedforward para treinamento do sistema, pelo método backpropagation.


## Observações Importantes
Para compilar, vá até a pasta raiz do projeto e insira o seguinte comando pelo terminal: gcc main.c rede.c glcm.c -lm -o executavel

Para executar, após realizar a compilação, insira o seguinte comando: ./executavel X
onde X é a quantidade de neurônios na camada oculta da rede neural. Caso não especificada, o padrão serão 10 neurônios.

É necessário ter a pasta DataSet com o conjunto de imagens junto da raiz do projeto (mesmo nível do executavel)!

## Output
Ao executar o programa, o processo de treinamento irá iniciar, até que seja realizado 1000 vezes ou a média quadrática do erro seja menor que 0,2.
Após isso, iniciará o teste do conjunto, pegando as 25 imagens restantes. Durante o teste, as métricas serão calculadas e as irá imprimir na tela:

- Taxa de acerto: indica, em porcentagem, quantas vezes uma imagem do conjunto treinamento concordou com o teste, isto é, uma imagem de asfalto no treinamento deu uma distância euclidiana menor para asfalto do que para grama no teste, ou seja, permitiu pouso na grama ou rejeitou pouso no asfalto.

- Taxa de falsa aceitação: indica, em porcentagem, quantas vezes uma imagem de asfalto do conjunto treinamento resultou em uma distância euclidiana menor para grama no teste, isto é, permitiu pouso em terreno de asfalto.

- Taxa de falsa rejeição: indica, em porcentagem, quantas vezes uma imagem de grama do conjunto treinamento resultou em uma distância euclidiana menor para asfalto no teste, isto é, rejeitou um pouco em grama.


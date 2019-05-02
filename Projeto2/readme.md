# EDA1 2019.1 UnB-FGA Projeto 02

---

## Projeto 2    

### Instruções de compilação
A pasta DataSet, que contém as pastas com imagens utilizadas no projeto, em formato txt, se encontra no mesmo nível do arquivo que contém o código fonte.

Exemplo de rota: "DataSet/asphalt/asphalt_01.txt"

Para compilar, vá até a pasta raiz do projeto e insira o seguinte comando pelo terminal: gcc projeto2.c -o executavel

Para executar, após realizar a compilação, insira o seguinte comando: ./executavel

### Output
Taxa de acerto: indica, em porcentagem, quantas vezes uma imagem do conjunto treinamento concordou com o teste, isto é, uma imagem de asfalto no treinamento deu uma distância euclidiana menor para asfalto do que para grama no teste, ou seja, permitiu pouso na grama ou rejeitou pouso no asfalto.

Taxa de falsa aceitação: indica, em porcentagem, quantas vezes uma imagem de asfalto do conjunto treinamento resultou em uma distância euclidiana menor para grama no teste, isto é, permitiu pouso em terreno de asfalto.

Taxa de falsa rejeição: indica, em porcentagem, quantas vezes uma imagem de grama do conjunto treinamento resultou em uma distância euclidiana menor para asfalto no teste, isto é, rejeitou um pouco em grama.

 *      Pedro Daia Cardoso - 180067265
 *      João Bisnotti      - 170069991
 *      Luiz Gustavo Dias  - 140169784

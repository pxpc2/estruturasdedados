# EDA1 2019.1 UnB-FGA Projeto 05 #

---

Pedro Daia Cardoso - 18/0067265
<br>João Victor Max Bisnotti de Oliveira - 17/0069991
<br>Luiz Gustavo Dias Paes Pinheiro - 14/0169784

---

## Sobre o Projeto
O programa consiste em um menu para realizar operações em uma árvore de busca binária.


## Observações Importantes
Para compilar, vá até a pasta raiz do projeto e insira o seguinte comando pelo terminal: gcc main.c arvore.c -o executavel

Para executar, após realizar a compilação, insira o seguinte comando: ./executavel

## Output
Ao iniciar o programa deverá ser exibido o menu, que consiste das opções:

1. carregar o arquivo da árvore.
	OBS: cada arquivo está localizado dentro da pasta BSTs, localizada na raiz do projeto.

2. exibir árvore
	OBS: a exibição da árvore é de forma HORIZONTAL, deitada. Ao executar esta função, será exibido na tela o exemplo.
	OBS2: para exibir o exemplo, é necessário ter o arquivo TREE_FORMAT.txt na raiz do projeto.

3. imprime na tela caso a árvore é cheia (para qualquer nó, ou ele é folha, ou tem dois filhos) ou não.

4. realiza a busca de um valor na árvore, imprime seu nível, valor de seu pai e caso exista, valor do irmão.

5. imprime a altura da árvore na tela (maior nível de um nó).

6. Remove um valor da árvore. No caso de dois filhos, remove trocando pelo seu sucessor em ordem.

7. imprime na tela a árvore em ordem.

8. imprime na tela a árvore em pré-ordem.

9. imprime na tela a árvore em pós-ordem.

10. realiza o balanceamento da árvore caso não esteja balanceada.

0. encerra a execução do programa.


# EDA1 2019.1 UnB-FGA Projeto 04 #

---

Pedro Daia Cardoso - 18/0067265
<br>João Victor Max Bisnotti de Oliveira - 17/0069991
<br>Luiz Gustavo Dias Paes Pinheiro - 14/0169784

---

## Sobre o Projeto
O programa consiste em ordenar pousos e decolagens nas três pistas do Aeroporto Internacional de Brasília, sendo que, em uma das pistas apenas a decolagem é permitida, exceto em emergências(três ou mais aeronaves se aproximando com combustível em zero), quando o pouso é permitido.

## Observações Importantes
Para compilar, vá até a pasta raiz do projeto e insira o seguinte comando pelo terminal: gcc projeto4.c -o executavel -lm

Para executar, após realizar a compilação, insira o seguinte comando: ./executavel

## Output
Ao iniciar o programa será mostrado na tela o terminal do aeroporto, que consiste de: hora incial, fila de pedidos, número de voos, número de aproximações e número de decolagens. Em seguida será mostrada a listagem de eventos, onde cada evento consiste de: código do voo, status(aeronave decolou ou aeronave pousou), horário de início do procedimento e número da pista. No caso de o combustível de uma aeronave acabar, será apresentada na tela a mensagem "ALERTA CRITICO, AERONAVE #XX0000 IRA CAIR". No caso de ter três ou mais aeronaves se aproximando com o combustível em zero, será apresentada na tela a mensagem "ALERTA GERAL DE DESVIO DE AERONAVE".


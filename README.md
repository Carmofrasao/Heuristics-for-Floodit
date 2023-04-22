# Heuristica para jogo Floodit

Feito por Anderson Frasão

Algoritmo implementado para a matéria de Inteligencia artificial, do curso de Ciência da Computação.

Esse código implementa uma heuristica para resolver o jogo Floodit no menor numero de passos possiveis.

## Heuristica

A heuristica é baseada em duas buscas em profundidade.

* Primeira BFS:

    * A primeira busca é para preencher um dos cantos com uma cor escolhida;
    
* Segunda BFS:

    * A segunda busca é para contar quantas posições ficaram com a cor escolhida, considerando o que foi pintado na primeira BFS e o que ja estava com a cor escolhida.

## Aplicando a heuristica

* Essa heuristica é aplicada para os 4 cantos testando todas as cores possiveis para cada canto;

* Cada iteração verifica se a profundidade (numero de posições preenchidas) encontrada é maior que a profundidade anterior, se for, salva a profundidade dessa busca;

* Após testar todas as possibilidades, ultilizando o canto e a cor salva, é aplicada novamente as duas BFS na matriz, e o resultado é aplicado novamente ao algoritmo, até que a matriz esteja com uma só cor.
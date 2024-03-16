#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "Funcoes.c"

int main(){
    limparTela();
    srand(time(NULL)); //Concerta o bug do randômico ser sempre o mesmo
    Baralho *baralho = pegaBaralhoNovo();
    Descarte *descarte = criaDescarte();
    inicializaBaralho(baralho);
    inicializaDescarte(descarte, baralho);

    Jogador *jog = registraJogador();
    Carta carta[7];

    for(int i = 0; i < 7; i++){
        carta[i] = popBaralho(baralho);
        insereCartasNoJogador(jog, &carta[i]);
    }
    imprimeMaoDoJogador(jog);

for(int cont = 0; cont < 9; cont++){
    int posicao;
    printf("Qual a posicao a ser jogada? ");
    scanf("%d", &posicao);
    imprimeCarta(retiraCartaDoJogador(jog, posicao));
    imprimeMaoDoJogador(jog);
}

/*    delayNaTela(5);
    Pessoas *pessoas = criaPessoa();
    inicializaPessoas(pessoas);
    reparteAsCartas(baralho, pessoas);
    imprimePessoas(pessoas);*/
}

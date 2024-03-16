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
    
    delayNaTela(5);
    Pessoas *pessoas = criaPessoa();
    inicializaPessoas(pessoas);
    reparteAsCartas(baralho, pessoas);
    imprimePessoas(pessoas);
}

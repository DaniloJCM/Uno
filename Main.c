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

    Pessoas *pessoas = criaPessoa();
    inicializaPessoas(pessoas);
    reparteAsCartas(baralho, pessoas);
    delayNaTela(2);
//    imprimePessoas(pessoas);

    PessoasNo *p = pessoas->prim;
    while(!alguemGanhou(pessoas)){
        jogadaDe(baralho, descarte, p->jogador);
        if(!alguemGanhou(pessoas)){
            if(inversao) p = p->prox;
            else p = p->ant;
        }
        delayNaTela(3);
    }

    printf("%s ganhou!\n", p->jogador->nome);
}

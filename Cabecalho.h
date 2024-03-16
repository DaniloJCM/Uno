#define white "\e[0;37m"
#define blue "\e[0;34m"
#define red "\e[0;31m"
#define green "\e[0;32m"
#define yellow "\e[0;33m"
#define black "\e[0;30m"

typedef struct carta{
    char cor;//pode receber -> 'r': (red)vermelho, 'g': (green)verde, 'b': (blue)azul, 'y': (yellow)amarelo, 'p': preta
    char simbolo;//pode receber -> 0 a 9: números, 'b': bloqueio, 'i': inverte, 'd': +2, 'q': +4, 't': trocar a cor
    struct carta *prox;
} Carta;

//1ª Pilha
typedef struct descarte{
    Carta *topo;
} Descarte;

//2ª Pilha
typedef struct baralho{
    Carta *topo;
} Baralho;

typedef struct maoNo{
    Carta *carta;
    struct maoNo *prox;
} MaoNo;

typedef struct mao{
    MaoNo *prim;
} MaoDoJogador;


typedef struct jogador{
    char nome[30];
    int qtasCartas;
    int estaEmUno;
    MaoDoJogador *mao;
} Jogador; 

typedef struct pessoasNo{
    Jogador *jogador;
    struct pessoasNo *prox;
    struct pessoasNo *ant;
} PessoasNo;

typedef struct pessoas{
    PessoasNo *prim;
} Pessoas;

//Protótipos funções
Baralho* pegaBaralhoNovo();

Descarte* criaDescarte();

void inserirCartaNoBaralho(Baralho *b, Carta *c);

void inicializaBaralho(Baralho *b);

Carta popBaralho(Baralho *esse);

void inicializaDescarte(Descarte *d, Baralho *b);

Jogador* registraJogador();

void imprimeMaoDoJogador(Jogador *jogador);

void insereCartasNoJogador(Jogador *jogador, Carta *carta);

//Carta *retiraCartaDoJogador(Jogador *jogador, int posicao);

// PESSOAS //

Pessoas *criaPessoa();

void inserePessoas(Pessoas *pessoa, Jogador *jogador);

Pessoas *inverte(Pessoas *pessoas);

void imprimePessoas(Pessoas *pessoas);

void inicializaPessoas(Pessoas *pessoas);

void reparteAsCartas(Baralho *baralho, Pessoas *pessoa);

//DOM-GGMS-Model.cpp - Projeto Domino - Etapa 6
//03/09/24 - Grupo: GGMS
//Gabriel Azevedo Cruz 
//Giulia Meninel Mattedi
//Matheus Gomes Costa Castanho Giacomini
//Sthefany Viveiros Cordeiro

#include "DOM_GGMS_Model.h"
#include <stdlib.h>
#include <stdbool.h>

// Variável global para identificar se o jogador 2 é o computador
bool jogador2EhComputador = false;

char jvez;
char escolha;
char ladoEscolhido;
Mesa mesa;
tipopeca pecas[28];
tipopeca jogador1[21];
tipopeca jogador2[21];
tipopeca monte[14]; // monte pecas disponiveis
int numeroPecasNoMonte = 14;
int numeroPecasDoJogador1 = 7;
int numeroPecasDoJogador2 = 7;
int jogoEmAndamento = 0;
int podeJogarJogador1 = 0;
int podeJogarJogador2 = 0;

void fCriar(tipopeca pecas[]) {
    int k = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            pecas[k].lado1 = i;
            pecas[k].lado2 = j;
            pecas[k].status = 'D';
            k++;
        }
    }
}

void distribuiPecas(tipopeca pecas[28]) {
    
    for (int i = 0; i < 7; i++) {
        jogador1[i] = pecas[i];
        jogador1[i].status = 'J'; // status jogador 1
    }
    for (int i = 7; i < 14; i++) {
        jogador2[i - 7] = pecas[i];
        jogador2[i - 7].status = 'j'; // status jogador 2
    }
    for (int i = 14; i < 28; i++) {
        monte[i - 14] = pecas[i];
        monte[i - 14].status = 'C'; // status monte
    }
    numeroPecasDoJogador1;
    numeroPecasDoJogador2;
    numeroPecasNoMonte;

}


struct Jogo {
    char jogadorJogo;     // Jogador atual (J = jogador 1 ; j = jogador 2)
    int qtMesaJogo;      // Quantidade de peças na mesa
    bool jogadorComp;     // Se o jogador 2 é o computador (0: não, 1: sim)
    int mesaDJogo;       // Extremidade direita da mesa
    int mesaEJogo;       // Extremidade esquerda da mesa
    int qtPecasJ1; // Quantidade de peças do jogador 1 
    int qtPecasJ2; // Quantidade de peças do jogador 2 
    int qtPecasMonte;
    tipopeca pecasMonte[14];
    tipopeca pecasJ1[21]; // Peças do jogador 1 *deletar
    tipopeca pecasJ2[21]; // Peças do jogador 2 *deletar
} sitJogo;               // Variável global da situação do jogo



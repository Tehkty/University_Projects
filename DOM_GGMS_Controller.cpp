//DOM-GGMS-Controller.cpp - Projeto Domino - Etapa 6
//03/09/24 - Grupo: GGMS
//Gabriel Azevedo Cruz 
//Giulia Meninel Mattedi
//Matheus Gomes Costa Castanho Giacomini
//Sthefany Viveiros Cordeiro
 
#include "DOM_GGMS_Controller.h"
#include "DOM_GGMS_View.cpp"
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
void jogo(){
	menuGeral();
	iniciarJogo();   
}
 
void fEmbaralha(tipopeca pecas[28]) {
    srand(time(NULL));
    for (int i = 0; i < 28; i++) {
        int j = rand() % 28;
        tipopeca temp = pecas[i];
        pecas[i] = pecas[j];
        pecas[j] = temp;
    }
}
 
void iniciarJogo() {
	mesa.posicaoLivreMesa = 0;
    for (int i = 0; i < 28; i++) {
        mesa.pecasNaMesa[i].lado1 = -1;
        mesa.pecasNaMesa[i].lado2 = -1;
	}
    fEmbaralha(pecas);
    distribuiPecas(pecas);
    primeiroLance();
    jogoEmAndamento = 1;
}
 
void colocarPecaNaMesa(tipopeca peca) {
    if (mesa.posicaoLivreMesa < 28) { //A mesa so pode ter 28 pecas, entao mesa.posicaoLivreMesa avalia se ha espaco para novas pecas
        peca.status = 'M';
		mesa.pecasNaMesa[mesa.posicaoLivreMesa] = peca; //pecasNaMesa e' uma array de 28 slots (pecas). Se houver espaco, 'peca' e' adicionada a posicao de mesa.posicaoLivreMesa
        mesa.posicaoLivreMesa++; //Depois de alocar espaco para uma peca, mesa.posicaoLivreMesa e' incrementada para disponibilizar uma proxima posicao 
    }
}

 
void primeiroLance() {
    int i, pj, dupla;
    pj = -1;
    dupla = -1;
    tipopeca pecaJogada;
 
    // Procurar a maior dupla:
/* Se os lados da peca escolhida forem iguais, pj recebe o indice da peca e dupla, seu valor. A comparacao com -1 e' realizada para determinar se a dupla
existe; caso nao exista, pj == -1, e o algoritmo passa a procurar a peca com a maior soma disponivel.
*/
    for (i = 0; i < 7; i++) {
        if (jogador1[i].lado1 == jogador1[i].lado2 && jogador1[i].lado1 > dupla) {
            dupla = jogador1[i].lado1;
            pj = i;
            jvez = 'J';
        }
        if (jogador2[i].lado1 == jogador2[i].lado2 && jogador2[i].lado1 > dupla) {
            dupla = jogador2[i].lado1;
            pj = i;
            jvez = 'j';
        }
    }
 
    // Se nao tiver dupla, procurar a peca com a maior soma
    if (pj == -1) {
        dupla = 0;
        for (i = 0; i < 7; i++) {
            if (jogador1[i].lado1 + jogador1[i].lado2 > dupla) {
                dupla = jogador1[i].lado1 + jogador1[i].lado2;
                pj = i;
                jvez = 'J';
            }
            if (jogador2[i].lado1 + jogador2[i].lado2 > dupla) {
                dupla = jogador2[i].lado1 + jogador2[i].lado2;
                pj = i;
                jvez = 'j';
            }
        }
    }
 
 /* Se jvez = 'J', pecaJogada (tipopeca) torna-se a peca de maior dupla/soma, e o numero de pecas do jogador 1 reduz em uma unidade. E vice-versa.
 */
    if (jvez == 'J') {
        pecaJogada = jogador1[pj];
        jogador1[pj] = jogador1[numeroPecasDoJogador1 - 1]; // -1 peca do jogador
        numeroPecasDoJogador1--;
    } else {
        pecaJogada = jogador2[pj];
        jogador2[pj] = jogador2[numeroPecasDoJogador2 - 1]; 
        numeroPecasDoJogador2--;
    }
 
    colocarPecaNaMesa(pecaJogada);
    //apresentarMesa();
 
    //necessario para alternar as vezes dos jogadores.
    if (jvez == 'J') {
    	apresentarMensagem("-> Jogador 1 jogou. ");
    	apresentarMensagem("-> Vez do Jogador 2! \n");
    	apresentarMesa();
        jvez = 'j';
        
        
        
        
    } else {
    	apresentarMensagem("-> Jogador 2 jogou. ");
    	apresentarMensagem("-> Vez do Jogador 1! \n");
    	apresentarMesa();
        jvez = 'J';
		
        
        
    }
 
    atualizaPecas(jvez); // pecas de quem jogou
    subMenu();
    system("cls");
}


void atualizaPecas(char jvez) {
    char indice;
    tipopeca pecaAtual;
    int i, j;
    
    if (jvez == 'J') {
        indice = 'a'; // inicializa a ordem de rotulacao das pecas em letras alfabeticas para o jogador 1
        apresentarMensagem("\n -> Pecas do jogador 1:\n");
        for (i = 0; i < numeroPecasDoJogador1; i++) { // pecas do jogador 1
            pecaAtual = jogador1[i];
            // Exibir peça, se não for [0|0] ou se já não houver outra peça [0|0] exibida
            if (pecaAtual.lado1 != 0 || pecaAtual.lado2 != 0) {
                apresentarPeca(indice, pecaAtual.lado1, pecaAtual.lado2);
            } else {
                int mostra = 1;
                for (j = 0; j < i; j++) {
                    if (jogador1[j].lado1 == 0 && jogador1[j].lado2 == 0) {
                        mostra = 0;
                        break;
                    }
                }
                if (mostra) {
                    apresentarPeca(indice, pecaAtual.lado1, pecaAtual.lado2);
                }
            }
            jogador1[i].status = 'J';
            indice++;
        }
        apresentarMensagem("\n");
    } else {
        indice = 'a'; // inicializa a ordem de rotulacao das pecas em letras alfabeticas para o jogador 2
        apresentarMensagem("\n -> Pecas do jogador 2:\n");
        for (i = 0; i < numeroPecasDoJogador2; i++) { // pecas do jogador 2
            pecaAtual = jogador2[i];
            // Exibir peça, se não for [0|0] ou se já não houver outra peça [0|0] exibida
            if (pecaAtual.lado1 != 0 || pecaAtual.lado2 != 0) {
                apresentarPeca(indice, pecaAtual.lado1, pecaAtual.lado2);
            } else {
                int mostra = 1;
                for (j = 0; j < i; j++) {
                    if (jogador2[j].lado1 == 0 && jogador2[j].lado2 == 0) {
                        mostra = 0;
                        break;
                    }
                }
                if (mostra) {
                    apresentarPeca(indice, pecaAtual.lado1, pecaAtual.lado2);
                }
            }
            jogador2[i].status = 'j';
            indice++;
        }
        apresentarMensagem("\n");
    }
}

void fComprar(tipopeca monte[], int &numeroPecasNoMonte, tipopeca jogador1[], tipopeca jogador2[], int &numeroPecasDoJogador1, int &numeroPecasDoJogador2) {
    if (numeroPecasNoMonte > 0) {
        tipopeca pecaComprada = monte[numeroPecasNoMonte - 1];
        if (jvez == 'J') {
            jogador1[numeroPecasDoJogador1] = pecaComprada; 
            jogador1[numeroPecasDoJogador1].status = 'J';
            numeroPecasDoJogador1++; 
        } else {
            jogador2[numeroPecasDoJogador2] = pecaComprada;
            jogador2[numeroPecasDoJogador2].status = 'j';
            numeroPecasDoJogador2++; 
        }
        numeroPecasNoMonte--; 

        system("cls");
        apresentarMensagem("-> Compra efetuada! \n");
        apresentarMesa(); 
		
        if (jvez == 'J') {
            printf("-> Peca comprada pelo Jogador 1: [%d|%d]\n", jogador1[numeroPecasDoJogador1 - 1].lado1, jogador1[numeroPecasDoJogador1 - 1].lado2);
        } else {
            printf("-> Peca comprada pelo Jogador 2: [%d|%d]\n", jogador2[numeroPecasDoJogador2 - 1].lado1, jogador2[numeroPecasDoJogador2 - 1].lado2);
        }
    } else {
        system("cls");
        apresentarMesa();
    }
}

void menuGeral() {
    int op;

    do {
        op = apresentarMenuGeral();


        if (jogador2EhComputador && jvez == 'j') {
            Computador(); 
        }

        switch (op) {
            case 0:
                mensagemSair();
                exit(0);
            case 1:
                jogoEmAndamento = 1;
                iniciarJogo();
                subMenu();
                break;
            case 2:
                jogador2EhComputador = true;
                iniciarJogo();
                subMenu();
                continue;
            case 3:
            	if (jogoEmAndamento = 1) { 
                    apresentarMensagem("\n-> Retornando ao jogo interrompido.\n");
                    apresentarMesa();
                    atualizaPecas(jvez);
                    subMenu(); 
                } else {
                    apresentarMensagem("\n-> Nenhum jogo em andamento para retornar.\n");
                }
                break;
            case 4:
            	if (mesa.posicaoLivreMesa == 0) {
                    apresentarMensagem("\n-> Nenhum jogo esta disponivel para salvar.\n");
                } else {
                    gravaCadastro();
                }
                break;
            case 5:
                recuperaCadastro();
                break;
            case 6:
            	regrasGerais();
            	break;
            default:
                mensagemOpInvalida();
                break;
        }
    } while (op != 0);
}

 
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void podeJogarOuNao() { 
    podeJogarJogador1 = 0; 
    podeJogarJogador2 = 0;
    
    if (mesa.posicaoLivreMesa > 0) {
        int ladoMesaEsquerda = mesa.pecasNaMesa[0].lado1;
        int ladoMesaDireita = mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2;

        for (int i = 0; i < numeroPecasDoJogador1; i++) {
            if (jogador1[i].lado1 == ladoMesaEsquerda || jogador1[i].lado2 == ladoMesaEsquerda ||
                jogador1[i].lado1 == ladoMesaDireita || jogador1[i].lado2 == ladoMesaDireita) {
                podeJogarJogador1 = 1;
                break;
            }
        }

        for (int i = 0; i < numeroPecasDoJogador2; i++) {
            if (jogador2[i].lado1 == ladoMesaEsquerda || jogador2[i].lado2 == ladoMesaEsquerda ||
                jogador2[i].lado1 == ladoMesaDireita || jogador2[i].lado2 == ladoMesaDireita) {
                podeJogarJogador2 = 1;
                break;
            }
        }

    if (podeJogarJogador1 == 0 && podeJogarJogador2 == 0 && numeroPecasNoMonte == 0) {
        if (numeroPecasDoJogador1 < numeroPecasDoJogador2) {
            apresentarMensagem("-> Nenhum Jogador pode jogar. Jogador 1 Venceu com menos Pecas!");
        } else if (numeroPecasDoJogador2 < numeroPecasDoJogador1) {
            apresentarMensagem("-> Nenhum Jogador pode jogar. Jogador 2 Venceu com menos Pecas!");
        } else {
            apresentarMensagem("-> Nenhum Jogador pode jogar. O Jogo terminou empatado. :D");
        }
        exit(0);
    }
}
}

void subMenu() {
    char op2;

    do {
        if (jogador2EhComputador && jvez == 'j') { 
            Computador();
            jvez = 'J';
            continue; 
        }

        op2 = apresentarSubMenu();
        switch (op2) {
            case 'j':
                jogada();
                break;
            case 'c':
                fComprar(monte, numeroPecasNoMonte, jogador1, jogador2, numeroPecasDoJogador1, numeroPecasDoJogador2);
                atualizaPecas(jvez);
                break;
            case 'p':
            	
                int ladoMesaEsquerda, ladoMesaDireita;

                if (mesa.posicaoLivreMesa > 0) { 
                    ladoMesaEsquerda = mesa.pecasNaMesa[0].lado1; 
                    ladoMesaDireita = mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2;
                } else {
                    ladoMesaEsquerda = -1; 
                    ladoMesaDireita = -1; 
                }

                podeJogarOuNao(); 

                if (jvez == 'J') {
                    if (podeJogarJogador1 == 0) {
                        if (numeroPecasNoMonte > 0) {
                            fComprar(monte, numeroPecasNoMonte, jogador1, jogador2, numeroPecasDoJogador1, numeroPecasDoJogador2);
                            if (jogador1[numeroPecasDoJogador1 - 1].lado1 != ladoMesaDireita && jogador1[numeroPecasDoJogador1 - 1].lado2 != ladoMesaDireita &&
                                jogador1[numeroPecasDoJogador1 - 1].lado1 != ladoMesaEsquerda && jogador1[numeroPecasDoJogador1 - 1].lado2 != ladoMesaEsquerda) {
                                	system("cls");
                                apresentarMensagem("-> Jogador 1 nao pode jogar. Passa a vez para o Jogador 2\n");
                                jvez = 'j'; 
                            } else {
                            	system("cls");
                                apresentarMensagem("-> Voce pode jogar a peca comprada ou passar a vez.");
                                apresentarMesa();
                                atualizaPecas(jvez);
                                subMenu();
                            }
                        } else {
                        	system("cls");
                            apresentarMensagem("-> Jogador 1 nao pode comprar. Passa a vez para o Jogador 2\n");
                            jvez = 'j'; 
                        }
                    } else {
                    	system("cls");
                        apresentarMensagem("-> Voce tem pecas jogaveis, nao pode passar a vez.");
                        apresentarMesa();
                        atualizaPecas(jvez);
                        subMenu();
                    }
                } else {
                    if (podeJogarJogador2 == 0) {
                        if (numeroPecasNoMonte > 0) {
                            fComprar(monte, numeroPecasNoMonte, jogador1, jogador2, numeroPecasDoJogador1, numeroPecasDoJogador2);
                            
                            if (jogador2[numeroPecasDoJogador2 - 1].lado1 != ladoMesaDireita && jogador2[numeroPecasDoJogador2 - 1].lado2 != ladoMesaDireita &&
                                jogador2[numeroPecasDoJogador2 - 1].lado1 != ladoMesaEsquerda && jogador2[numeroPecasDoJogador2 - 1].lado2 != ladoMesaEsquerda) {
                                system("cls");
                                apresentarMensagem("-> Jogador 2 nao pode jogar. Passa a vez para o Jogador 1\n");
                                jvez = 'J';
                            } else {
                            	system("cls");
                                apresentarMensagem("-> Voce pode jogar a peca comprada ou passar a vez.");
                                apresentarMesa();
                                atualizaPecas(jvez);
                                subMenu(); 
                            }
                        } else {
                        	system("cls");
                            apresentarMensagem("-> Jogador 2 nao pode comprar. Passa a vez para o Jogador 1\n");
                            jvez = 'J';
                        }
                    } else {
                    	system("cls");
                        apresentarMensagem("-> Voce tem pecas jogaveis, nao pode passar a vez.");
                        apresentarMesa();
                        atualizaPecas(jvez);
                        subMenu();
                    }
                }
                break;
            case 's':
                system("cls");
                menuGeral();
                break;
            default:
                mensagemOpInvalida();
                break;
        }
    } while (op2 != 's');
}

void inverterPeca(tipopeca &peca) {
    int temp = peca.lado1;
    peca.lado1 = peca.lado2;
    peca.lado2 = temp;
}

void mostrarPecasPossiveis(tipopeca jogador1[], tipopeca jogador2[], char jvez) {
    int mesaE, mesaD;
    int jogadaValida = 0; //nenhuma peca jogavel encontrada ainda
    char indice;

    if (mesa.posicaoLivreMesa > 0) {
        mesaE = mesa.pecasNaMesa[0].lado1;
        mesaD = mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2;
    } else {
        mesaE = mesaD = -1; // mesa vazia
    }

    if (jvez == 'J') {
        indice = 'a';
        for (int i = 0; i < numeroPecasDoJogador1; i++) {
            if (jogador1[i].lado1 == mesaE || jogador1[i].lado2 == mesaE || 
                jogador1[i].lado1 == mesaD || jogador1[i].lado2 == mesaD) {
                if (!jogadaValida) //se uma peca valida for encontrada, if (!jogadaValida) é verdadeiro pois !0 = 1 (verdadeiro)
				{
                    apresentarMensagem("\n -> Pecas Possiveis do Jogador 1: \n");
                }
                apresentarPeca(indice, jogador1[i].lado1, jogador1[i].lado2);
                jogadaValida = 1;
            }
            indice++;
        }
    } else {
        indice = 'a';
        for (int i = 0; i < numeroPecasDoJogador2; i++) {
            if (jogador2[i].lado1 == mesaE || jogador2[i].lado2 == mesaE || 
                jogador2[i].lado1 == mesaD || jogador2[i].lado2 == mesaD) {
                if (!jogadaValida) {
                    apresentarMensagem("\n -> Pecas Possiveis do Jogador 2: \n");
                }
                apresentarPeca(indice, jogador2[i].lado1, jogador2[i].lado2);
                jogadaValida = 1;
            }
            indice++;
        }
    } 
    
    if (!jogadaValida) {
        apresentarMensagem("\n -> Nao possui Pecas Jogaveis, compre pecas.\n");
        subMenu();
    }
    apresentarMensagem("\n");
}

void vencedor() {
    if (numeroPecasDoJogador1 == 0) {
    	apresentarMesa();
        apresentarMensagem("---> FIM: Jogador 1 Venceu! ;D ");
        exit(0);
    } else if (numeroPecasDoJogador2 == 0) {
    	apresentarMesa();
        apresentarMensagem("---> FIM: Jogador 2 Venceu! ;D ");
        exit(0);
    }
}


void jogada() {
    tipopeca pecaEscolhida;
    int indicePecaEscolhida;

    mostrarPecasPossiveis(jogador1, jogador2, jvez);

    apresentarMensagem("\n-> Escolha a peca (digite a letra): \n");
    escanearEscolha();

    if (jvez == 'J') {
        indicePecaEscolhida = escolha - 'a'; 
        if (indicePecaEscolhida >= 0 && indicePecaEscolhida < numeroPecasDoJogador1) {
            pecaEscolhida = jogador1[indicePecaEscolhida];

            // tira peca do j1
            for (int i = indicePecaEscolhida; i < numeroPecasDoJogador1 - 1; i++) {
                jogador1[i] = jogador1[i + 1];
            }
            numeroPecasDoJogador1--;

        } else {
            apresentarMensagem("\n-> Jogada Invalida!\n");
            return;
        }
    } else {
        indicePecaEscolhida = escolha - 'a';
        if (indicePecaEscolhida >= 0 && indicePecaEscolhida < numeroPecasDoJogador2) {
            pecaEscolhida = jogador2[indicePecaEscolhida];

            // tira peca do j2
            for (int i = indicePecaEscolhida; i < numeroPecasDoJogador2 - 1; i++) {
                jogador2[i] = jogador2[i + 1];
            }
            numeroPecasDoJogador2--;

        } else {
            apresentarMensagem("\n-> Jogada Invalida!");
            return;
        }
    }
    
    
    int ladoMesaEsquerda = mesa.pecasNaMesa[0].lado1; 
    int ladoMesaDireita = mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2; 

    if ((pecaEscolhida.lado1 == ladoMesaEsquerda || pecaEscolhida.lado2 == ladoMesaEsquerda) && 
        (pecaEscolhida.lado1 == ladoMesaDireita || pecaEscolhida.lado2 == ladoMesaDireita)) {

        apresentarMensagem("\n-> Escolha: 'e' Para jogar na esquerda da mesa, ou 'd' Para jogar na direita da mesa: \n");
        limparBuffer();
        escanearLadoEscolhido();

        if (ladoEscolhido == 'e') {
            if (pecaEscolhida.lado1 == ladoMesaEsquerda) { 
                inverterPeca(pecaEscolhida);
            }

            // peca vai pra direita pra abrir espaco pra outras pecas
            for (int i = mesa.posicaoLivreMesa; i > 0; i--) { 
                mesa.pecasNaMesa[i] = mesa.pecasNaMesa[i - 1];
            }
            mesa.pecasNaMesa[0] = pecaEscolhida;
            mesa.posicaoLivreMesa++;
            
        } else if (ladoEscolhido == 'd') {
            if (pecaEscolhida.lado2 == ladoMesaDireita) { 
                inverterPeca(pecaEscolhida);
            }

            mesa.pecasNaMesa[mesa.posicaoLivreMesa] = pecaEscolhida; 
            mesa.posicaoLivreMesa++;
        } else {
            apresentarMensagem("\n-> Jogada Invalida!");
            return;
        }
    } else if (pecaEscolhida.lado1 == ladoMesaEsquerda || pecaEscolhida.lado2 == ladoMesaEsquerda) { 
        if (pecaEscolhida.lado1 == ladoMesaEsquerda) {
            inverterPeca(pecaEscolhida);
        }

        // peca vai pra direita pra abrir espaco pra outras pecas
        for (int i = mesa.posicaoLivreMesa; i > 0; i--) {
            mesa.pecasNaMesa[i] = mesa.pecasNaMesa[i - 1];
        }
        mesa.pecasNaMesa[0] = pecaEscolhida;
        mesa.posicaoLivreMesa++;
    } else if (pecaEscolhida.lado1 == ladoMesaDireita || pecaEscolhida.lado2 == ladoMesaDireita) {  
        if (pecaEscolhida.lado2 == ladoMesaDireita) {
            inverterPeca(pecaEscolhida);
        }

        mesa.pecasNaMesa[mesa.posicaoLivreMesa] = pecaEscolhida;
        mesa.posicaoLivreMesa++;
    } else {
        apresentarMensagem("\n-> Jogada Invalida!");
        return;
    }
    
    system("cls");
    //apresentarMesa();

    vencedor();
    podeJogarOuNao();

    // troca vez
    if (jvez == 'J') {
        jvez = 'j';
        apresentarMensagem("\n-> Jogador 1 jogou!\n-> Vez do Jogador 2\n");
        apresentarMesa();
    } else {
        jvez = 'J';
        apresentarMensagem("\n-> Jogador 2 jogou!\n-> Vez do Jogador 1\n");
        apresentarMesa();
    }

    atualizaPecas(jvez);
}



void gravaCadastro() { 
    int i;
    FILE *fp, *fpm, *fps;
    
    fp = fopen("CAD_DOMINO", "wb");
    fpm = fopen("CAD_MESA", "wb");
    fps = fopen("CAD_JOGO", "wb");

    if (fp == NULL || fpm == NULL || fps == NULL) {
        apresentarMensagem("Erro ao ler arquivos");
        return;
    }

    
    for (i = 0; i < 28; i++) {
        if (fwrite(&pecas[i], sizeof(tipopeca), 1, fp) != 1) {
            apresentarMensagem("Erro na cad domino gravaCadastro");
            fclose(fp);
            fclose(fpm);
            fclose(fps);
            return;
        }
    }

    
    sitJogo.qtMesaJogo = mesa.posicaoLivreMesa;
    for (i = 0; i < sitJogo.qtMesaJogo; i++) {
        if (fwrite(&mesa.pecasNaMesa[i], sizeof(tipopeca), 1, fpm) != 1) {
            apresentarMensagem("Erro na cad mesa gravaCadastro");
            fclose(fp);
            fclose(fpm);
            fclose(fps);
            return;
        }
    }
    
    sitJogo.jogadorJogo = jvez;
    sitJogo.mesaDJogo = mesa.mesaD;
    sitJogo.mesaEJogo = mesa.mesaE;
    sitJogo.qtPecasJ1 = numeroPecasDoJogador1;
    sitJogo.qtPecasJ2 = numeroPecasDoJogador2;
    sitJogo.qtPecasMonte = numeroPecasNoMonte;
  
    for (i = 0; i < numeroPecasDoJogador1; i++) {
        sitJogo.pecasJ1[i] = jogador1[i];
        jogador1[i].status = 'J';
    }
    for (i = 0; i < numeroPecasDoJogador2; i++) {
        sitJogo.pecasJ2[i] = jogador2[i];
        jogador2[i].status = 'j';
    }
    for (i = 0; i < numeroPecasNoMonte; i++) {
        sitJogo.pecasMonte[i] = monte[i];
        sitJogo.pecasMonte[i].status = 'C';
    }

    if (fwrite(&sitJogo, sizeof(Jogo), 1, fps) != 1) {
        apresentarMensagem("Erro no cad jogo gravaCadastro");
        fclose(fp);
        fclose(fpm);
        fclose(fps);
        return;
    }

    fclose(fp);
    fclose(fpm);
    fclose(fps);

    apresentarMensagem("Cadastro gravado com sucesso!\n");
}


void recuperaCadastro() { 
    int i;
    FILE *fp, *fpm, *fps;
	
    fp = fopen("CAD_DOMINO", "rb");
    if (fp == NULL) {
        apresentarMensagem("Erro CAD_DOMINO ");
        return;
    }

    fpm = fopen("CAD_MESA", "rb");
    if (fpm == NULL) {
        apresentarMensagem("Erro CAD_MESA ");
        fclose(fp);
        return;
    }

    fps = fopen("CAD_JOGO", "rb");
    if (fps == NULL) {
        apresentarMensagem("Erro CAD_JOGO ");
        fclose(fp);
        fclose(fpm);
        return;
    }

    
    for (i = 0; i < 28; i++) {
        if (fread(&pecas[i], sizeof(tipopeca), 1, fp) != 1) {
            apresentarMensagem("Erro pecas CAD_DOMINO recuperaCadastro");
            fclose(fp);
            fclose(fpm);
            fclose(fps);
            return;
        }
    }

    
    if (fread(&sitJogo, sizeof(Jogo), 1, fps) != 1) {
        apresentarMensagem("Erro jogo CAD_JOGO recuperaCadastro");
        fclose(fp);
        fclose(fpm);
        fclose(fps);
        return;
    }

   
    mesa.posicaoLivreMesa = sitJogo.qtMesaJogo;
    for (i = 0; i < mesa.posicaoLivreMesa; i++) {
        if (fread(&mesa.pecasNaMesa[i], sizeof(tipopeca), 1, fpm) != 1) {
            apresentarMensagem("Erro jogo CAD_MESA recuperaCadastro");
            fclose(fp);
            fclose(fpm);
            fclose(fps);
            return;
        }
    }

    
    mesa.mesaD = sitJogo.mesaDJogo;
    mesa.mesaE = sitJogo.mesaEJogo;
    numeroPecasDoJogador1 = sitJogo.qtPecasJ1;
    numeroPecasDoJogador2 = sitJogo.qtPecasJ2;
    numeroPecasNoMonte = sitJogo.qtPecasMonte;

    
    for (i = 0; i < numeroPecasDoJogador1; i++) {
        jogador1[i] = sitJogo.pecasJ1[i];
        jogador1[i].status = 'J';
    }
    for (i = 0; i < numeroPecasDoJogador2; i++) {
        jogador2[i] = sitJogo.pecasJ2[i];
        jogador2[i].status = 'j';
    }
    for (i = 0; i < numeroPecasNoMonte; i++) {
        monte[i] = sitJogo.pecasMonte[i];
    }

    jvez = sitJogo.jogadorJogo;

    fclose(fp);
    fclose(fpm);
    fclose(fps);

    apresentarMensagem("Cadastro recuperado com sucesso!\n");
    apresentarMesa();
    atualizaPecas(jvez);
    subMenu();
}

/*int Computador() {
    int jogou = 0;  // Variável para verificar se o computador já jogou
    do {
        podeJogarOuNao();

        // Condições para passar o turno ou comprar
        if ((numeroPecasDoJogador2 == 0) && (numeroPecasNoMonte == 0)) {
            jvez = (jvez == 'J') ? 'j' : 'J';
            apresentarMensagem("\n-> Jogador passou o turno.\n");
            system("cls");
            apresentarMesa();
            atualizaPecas('J');
            subMenu();
            return 0;
        }

        if ((numeroPecasDoJogador2 == 0) && (numeroPecasNoMonte != 0)) {
            fComprar(monte, numeroPecasNoMonte, jogador1, jogador2, numeroPecasDoJogador1, numeroPecasDoJogador2);
            apresentarMesa();
            atualizaPecas('J');
            subMenu();
            return 0;
        }

        // Tentativa de jogar uma peça
        for (int i = 0; i < numeroPecasDoJogador2; i++) {
            if (jogador2[i].status == 'j') { // Verifica se a peça está disponível

                // Verifica o lado direito da mesa
                if ((jogador2[i].lado1 == mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2) || 
                    (jogador2[i].lado2 == mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2)) {

                    // Inverte a peça se necessário
                    if (jogador2[i].lado2 == mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2) {
                        int temp = jogador2[i].lado1;
                        jogador2[i].lado1 = jogador2[i].lado2;
                        jogador2[i].lado2 = temp;
                    }

                    // Joga a peça na mesa
                    mesa.pecasNaMesa[mesa.posicaoLivreMesa] = jogador2[i];
                    mesa.pecasNaMesa[mesa.posicaoLivreMesa].status = 'M'; // Marca como jogada
                    jogador2[i].status = 'M'; // Atualiza status da peça
                    mesa.posicaoLivreMesa++;
                    numeroPecasDoJogador2--; // Atualiza o número de peças do jogador
                    jogou = 1;  // Indica que o computador jogou
                    break;  // Sai do loop
                }

                // Verifica o lado esquerdo da mesa
                else if ((jogador2[i].lado1 == mesa.pecasNaMesa[0].lado1) || 
                         (jogador2[i].lado2 == mesa.pecasNaMesa[0].lado1)) {

                    // Inverte a peça se necessário
                    if (jogador2[i].lado1 == mesa.pecasNaMesa[0].lado1) {
                        int temp = jogador2[i].lado1;
                        jogador2[i].lado1 = jogador2[i].lado2;
                        jogador2[i].lado2 = temp;
                    }

                    // Move as peças para a direita antes de jogar
                    for (int j = mesa.posicaoLivreMesa; j > 0; j--) {
                        mesa.pecasNaMesa[j] = mesa.pecasNaMesa[j - 1];
                    }

                    // Joga a peça na mesa
                    mesa.pecasNaMesa[0] = jogador2[i];
                    mesa.pecasNaMesa[0].status = 'M'; // Marca como jogada
                    jogador2[i].status = 'M'; // Atualiza status da peça
                    mesa.posicaoLivreMesa++;
                    numeroPecasDoJogador2--; // Atualiza o número de peças
                    jogou = 1;  // Indica que o computador jogou
                    break;  // Sai do loop
                }
            }
        }

        // Se o computador jogou, atualiza o status e passa a vez
        if (jogou) {
            jvez = 'J';  // Passa a vez para o jogador 1
            system("cls");
            apresentarMensagem("-> O computador jogou a peca: \n", );
            apresentarMesa();
            atualizaPecas('J');
            subMenu();
            return 0;  // Sai após a jogada
        }

        // Se não houver peça para jogar, pode comprar do monte ou passar a vez
        if (!jogou && numeroPecasNoMonte > 0) {
            apresentarMensagem("-> O computador esta comprando uma peça do monte!\n");
            fComprar(monte, numeroPecasNoMonte, jogador1, jogador2, numeroPecasDoJogador1, numeroPecasDoJogador2);
        } else {
            apresentarMensagem("-> O computador nao pode jogar e passou a vez!\n");
            jvez = 'J';  // Passa a vez
            subMenu();
            return 0;
        }
    } while (1);
}
*/

int Computador() {
    int jogou = 0;  // Variável para verificar se o computador já jogou
    do {
        podeJogarOuNao();

        // Condições para passar o turno ou comprar
        if ((numeroPecasDoJogador2 == 0) && (numeroPecasNoMonte == 0)) {
            jvez = (jvez == 'J') ? 'j' : 'J';
            apresentarMensagem("\n-> Jogador passou o turno.\n");
            system("cls");
            apresentarMesa();
            atualizaPecas('J');
            subMenu();
            return 0;
        }

        if ((numeroPecasDoJogador2 == 0) && (numeroPecasNoMonte != 0)) {
            fComprar(monte, numeroPecasNoMonte, jogador1, jogador2, numeroPecasDoJogador1, numeroPecasDoJogador2);
            apresentarMesa();
            atualizaPecas('J');
            subMenu();
            return 0;
        }

        // Tentativa de jogar uma peça
        for (int i = 0; i < numeroPecasDoJogador2; i++) {
            if (jogador2[i].status == 'j') { // Verifica se a peça está disponível

                // Verifica o lado direito da mesa
                if ((jogador2[i].lado1 == mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2) || 
                    (jogador2[i].lado2 == mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2)) {

                    // Inverte a peça se necessário
                    if (jogador2[i].lado2 == mesa.pecasNaMesa[mesa.posicaoLivreMesa - 1].lado2) {
                        int temp = jogador2[i].lado1;
                        jogador2[i].lado1 = jogador2[i].lado2;
                        jogador2[i].lado2 = temp;
                    }

                    // Verificação extra para evitar jogar a mesma peça (considerando lados invertidos)
                    bool ja_jogada = false;
                    for (int k = 0; k < mesa.posicaoLivreMesa; k++) {
                        if ((mesa.pecasNaMesa[k].lado1 == jogador2[i].lado1 && 
                             mesa.pecasNaMesa[k].lado2 == jogador2[i].lado2) || 
                            (mesa.pecasNaMesa[k].lado1 == jogador2[i].lado2 && 
                             mesa.pecasNaMesa[k].lado2 == jogador2[i].lado1)) {
                            ja_jogada = true;
                            break;
                        }
                    }

                    // Se a peça já foi jogada, continua o loop
                    if (ja_jogada) {
                        continue;
                    }

                    // Joga a peça na mesa
                    mesa.pecasNaMesa[mesa.posicaoLivreMesa] = jogador2[i];
                    mesa.pecasNaMesa[mesa.posicaoLivreMesa].status = 'M'; // Marca como jogada
                    jogador2[i].status = 'M'; // Atualiza status da peça
                    mesa.posicaoLivreMesa++;
                    numeroPecasDoJogador2--; // Atualiza o número de peças do jogador
                    jogou = 1;  // Indica que o computador jogou
                    break;  // Sai do loop
                }

                // Verifica o lado esquerdo da mesa
                else if ((jogador2[i].lado1 == mesa.pecasNaMesa[0].lado1) || 
                         (jogador2[i].lado2 == mesa.pecasNaMesa[0].lado1)) {

                    // Inverte a peça se necessário
                    if (jogador2[i].lado1 == mesa.pecasNaMesa[0].lado1) {
                        int temp = jogador2[i].lado1;
                        jogador2[i].lado1 = jogador2[i].lado2;
                        jogador2[i].lado2 = temp;
                    }

                    // Verificação extra para evitar jogar a mesma peça (considerando lados invertidos)
                    bool ja_jogada = false;
                    for (int k = 0; k < mesa.posicaoLivreMesa; k++) {
                        if ((mesa.pecasNaMesa[k].lado1 == jogador2[i].lado1 && 
                             mesa.pecasNaMesa[k].lado2 == jogador2[i].lado2) || 
                            (mesa.pecasNaMesa[k].lado1 == jogador2[i].lado2 && 
                             mesa.pecasNaMesa[k].lado2 == jogador2[i].lado1)) {
                            ja_jogada = true;
                            break;
                        }
                    }

                    // Se a peça já foi jogada, continua o loop
                    if (ja_jogada) {
                        continue;
                    }

                    // Move as peças para a direita antes de jogar
                    for (int j = mesa.posicaoLivreMesa; j > 0; j--) {
                        mesa.pecasNaMesa[j] = mesa.pecasNaMesa[j - 1];
                    }

                    // Joga a peça na mesa
                    mesa.pecasNaMesa[0] = jogador2[i];
                    mesa.pecasNaMesa[0].status = 'M'; // Marca como jogada
                    jogador2[i].status = 'M'; // Atualiza status da peça
                    mesa.posicaoLivreMesa++;
                    numeroPecasDoJogador2--; // Atualiza o número de peças
                    jogou = 1;  // Indica que o computador jogou
                    break;  // Sai do loop
                }
            }
        }

        // Se o computador jogou, atualiza o status e passa a vez
        if (jogou) {
            jvez = 'J';  // Passa a vez para o jogador 1
            system("cls");
            apresentarMensagem("-> O computador jogou uma peca. \n");
            apresentarMesa(); 
            atualizaPecas('J');
            subMenu();
            return 0;  // Sai após a jogada
        }

        // Se não houver peça para jogar, pode comprar do monte ou passar a vez
        if (!jogou && numeroPecasNoMonte > 0) {
            apresentarMensagem("-> O computador está comprando uma peça do monte!\n");
            fComprar(monte, numeroPecasNoMonte, jogador1, jogador2, numeroPecasDoJogador1, numeroPecasDoJogador2);
        } else {
            apresentarMensagem("-> O computador não pode jogar e passou a vez!\n");
            jvez = 'J';  // Passa a vez
            subMenu();
            return 0;
        }
    } while (1);
}








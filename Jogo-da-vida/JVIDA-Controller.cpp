#include "JVIDA-Controller.h"
#include "JVIDA-View.cpp"
#include <stdio.h>

void menu() {
    int op;
    do {
        op = apresentarMenuGeral();

        switch(op) {
            case 1:
                apresentaMapa();
                break;
            case 2:
                limparMapa();
                break;
            case 3:
                colocarCelula();
                break;
            case 4:
                perguntarMostrarMortosVizinhos();
                break;
            case 5:
                iniciarProcesso();
                break;
            case 6:
                // apresenta lista
                break;
            case 7:
                // grava uma geracao inicial
                break;
            case 8:
                // recupera uma geracao inicial cadastrada
                break;
            case 9:
                // limpa cadastro
                break;
            case 10:
                // regras gerais
                break;
            case 0:
                apresentarMensagem("Saindo...");
                exit(0);
            default:
                apresentarMensagem("Opcao invalida.");
                break;        
        }

    } while(op != 0);
}

void matrizAux() {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int vizinhosVivos = calcVizinhos(i, j);

            if (matriz[i][j] == 'O') {
                // Verifica se a célula viva deve morrer
                if (vizinhosVivos < 2 || vizinhosVivos > 3) {
                    aux[i][j] = '.';
                    excluiLVivo(i, j); // Remove da lista de vivas
                } else {
                    aux[i][j] = 'O';
                }
            } else {
                // Verifica se uma célula morta deve nascer
                if (vizinhosVivos == 3) {
                    aux[i][j] = 'O';
                    carregaVivo(i, j); // Adiciona à lista de vivas
                } else {
                    aux[i][j] = '.';
                }
            }
        }    
    }
    atualizarMatriz(); // Atualiza a matriz com o novo estado
}

void atualizarMatriz() {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = aux[i][j];
        }
    }
}

void celulavivamorta() {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (matriz[i][j] == '+') {
                matriz[i][j] = '.';  // tira os + antigos
            }
        }
    }

    if (mostrarMortosVizinhos) {
        vizinhosMortos();
    }
    apresentaMapa();
} 

void vizinhosMortos() {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (matriz[i][j] == 'O') {
                if (i > 0 && matriz[i-1][j] != 'O') matriz[i-1][j] = '+';
                if (i < dim-1 && matriz[i+1][j] != 'O') matriz[i+1][j] = '+';
                if (j > 0 && matriz[i][j-1] != 'O') matriz[i][j-1] = '+';
                if (j < dim-1 && matriz[i][j+1] != 'O') matriz[i][j+1] = '+';
                if (i > 0 && j > 0 && matriz[i-1][j-1] != 'O') matriz[i-1][j-1] = '+';
                if (i > 0 && j < dim-1 && matriz[i-1][j+1] != 'O') matriz[i-1][j+1] = '+';
                if (i < dim-1 && j > 0 && matriz[i+1][j-1] != 'O') matriz[i+1][j-1] = '+';
                if (i < dim-1 && j < dim-1 && matriz[i+1][j+1] != 'O') matriz[i+1][j+1] = '+';
            }
        }
    }
}

void limparMapa() {
    // Limpa a matriz
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = '.';
        }
    }

    // Esvazia a lista de células vivas
    TipoCel *aux;
    while (pvivo != NULL) {
        aux = pvivo;
        pvivo = pvivo->next;
        free(aux); // Libera a memória da célula
    }
    totvivo = 0; // Zera o contador de células vivas

    atualizarMatriz();  // Atualiza a matriz após a limpeza
    apresentaMapa();    // Atualiza o mapa na visualização
}


int calcVizinhos(int i, int j) {    
    int qt = 0;
    // os 3 vizinhos superiores
    if (i-1 >= 0 && j-1 >= 0 && matriz[i-1][j-1] == 'O') qt++;
    if (i-1 >= 0 && matriz[i-1][j] == 'O') qt++;
    if (i-1 >= 0 && j+1 < dim && matriz[i-1][j+1] == 'O') qt++;
    // os 2 vizinhos laterais
    if (j-1 >= 0 && matriz[i][j-1] == 'O') qt++;
    if (j+1 < dim && matriz[i][j+1] == 'O') qt++;
    // os 3 vizinhos inferiores
    if (i+1 < dim && j-1 >= 0 && matriz[i+1][j-1] == 'O') qt++;
    if (i+1 < dim && matriz[i+1][j] == 'O') qt++;
    if (i+1 < dim && j+1 < dim && matriz[i+1][j+1] == 'O') qt++;
    return qt;
}

bool verificarMatrizVazia() {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (matriz[i][j] == 'O') {
                return false;  
            }
        }
    }
    return true;  
}

void carregaVivo(int ii, int jj) {
    TipoCel *aux = (TipoCel *) malloc(sizeof(TipoCel));

    if (aux == NULL) {
        apresentarMensagem("Sem espaço na memoria para inclusao de celula viva\n");
        return;
    }
    aux->lin = ii;
    aux->col = jj;

    if (totvivo == 0) {
        pvivo = aux;
        pvivo->next = NULL;
    } else {
        aux->next = pvivo;
        pvivo = aux;
    }
    totvivo++;
}

void excluiLVivo(int ii, int jj) {
    TipoCel *aux = pvivo, *aux2 = aux;

    if (totvivo > 0) {
        while (aux->lin != ii || aux->col != jj) {
            aux2 = aux;
            aux = aux->next;
        }
        if (aux->lin == ii && aux->col == jj) {
            if (aux2 == aux)
                pvivo = aux->next;
            else
                aux2->next = aux->next;
            free(aux);
            totvivo--;
        }
    }
}

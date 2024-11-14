#include "JVIDA-View.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void apresentarMensagem(const char mens[100]){
	printf("%s\n",mens);
}

void mapaInicial() {
    printf("Digite a dimensao da matriz desejada (10 a 60): ");
    scanf("%d", &dim);

    if (dim < 10 || dim > 60) {
        printf("Tamanho invalido, digite de novo.");
        return;
    }
    
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = '.';
        }
    }
    
    apresentaMapa();
}

void apresentaMapa() {
    printf("\n   ");
    for (int j = 0; j < dim; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < dim; i++) {
        printf("%2d ", i);
        for (int j = 0; j < dim; j++) {
            printf(" %c ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    mostraLvivo();           // Exibe células vivas
    mostraLvizinhasMortas();  // Exibe células vizinhas mortas
}

void iniciarProcesso(){
	int numGeracoes, atraso;
	printf("Informe o numero de geracoes a serem simuladas: ");
	scanf("%d", &numGeracoes);
	printf("Informe o atraso entre as geracoes (em segundos, 0 para modo passo a passo): ");
	scanf("%d", &atraso);
	getchar();
	evoluirJogo(numGeracoes, atraso);	
}

void evoluirJogo(int numGeracoes, int atraso) {
    time_t lt1, lt2;
    int geracaoAtual = 1;

    while (geracaoAtual <= numGeracoes) {
        printf("\nGeracao %d:", geracaoAtual);         
        matrizAux();        
        atualizarMatriz();
		if (mostrarMortosVizinhos) { //continua mostrando geracao caso o flag de mostrar vizinhos mortos esteja ativado
			vizinhosMortos();
		}        
        apresentaMapa();   
		
		if (verificarMatrizVazia()) { 
            printf("Nenhuma celula sobreviveu.\n");
            break;
        }
		     
        if (atraso > 0) { //funcao de controle de tempo - dica do eli
            lt1 = time(NULL);
            lt2 = lt1;
            while (difftime(lt2, lt1) < atraso) {
                lt2 = time(NULL); 
            }
        } 
        geracaoAtual++; 
    }
}

void perguntarMostrarMortosVizinhos(){
	
	char resposta;
    printf("Deseja mostrar as celulas vizinhas-mortas? (S/N): ");
    scanf(" %c", &resposta);

    if (resposta == 'S' || resposta == 's') {
        mostrarMortosVizinhos = true;
        apresentarMensagem("Os vizinhos mortos serao mostrados.");
    } else if (resposta == 'N' || resposta == 'n') {
        mostrarMortosVizinhos = false;
        apresentarMensagem("Os vizinhos mortos nao serao mostrados.");
    } else {
        apresentarMensagem("Resposta invalida. Escolha S ou N.");
        perguntarMostrarMortosVizinhos();
    }
    
    celulavivamorta();
}

void colocarCelula() {
    int i, j;
    char op2;
//	apresentaMapa();
    do {
        
        system("cls");
        apresentaMapa();
        
        printf("Digite as coordenadas (linha coluna) ou (-1 -1 para voltar ao menu): ");
        scanf("%d %d", &i, &j);

        if (i == -1 && j == -1) {
            break; 
        }

        if (i < 0 || i >= dim || j < 0 || j >= dim) {
            printf("\nCoordenada invalida! Por favor, digite coordenadas entre 0 e %d.\n", dim - 1);
            continue;
        }
		
        //para incluir ou excluir celula
        if (matriz[i][j] == 'O') {
            printf("Celula viva. Deseja remove-la? (S para sim, N para nao): ");
            scanf(" %c", &op2); 

            if (op2 == 'S' || op2 == 's') {
                matriz[i][j] = '.';
                excluiLVivo(i, j);
                printf("Celula removida com sucesso!\n");
            } else {
                printf("Celula mantida.\n");
            }
        } else { //Se ta morta
            printf("Colocando celula viva.\n");
            matriz[i][j] = 'O';
            carregaVivo( i, j);
        }
		
        celulavivamorta();
        

    } while (true);
}

void mostraLvivo() {
    TipoCel *aux = pvivo; // Define um ponteiro auxiliar para percorrer a lista
    printf("Celulas vivas: ");
    
    if (totvivo > 0) {
        while (aux != NULL) {
            printf("( %d, %d ) ", aux->lin, aux->col);
            aux = aux->next; // Caminha para o próximo nó na lista
        }
    } else {
        printf("Nenhuma celula viva.");
    }
    printf("\n");
}

void mostraLvizinhasMortas() {
    printf("Celulas vizinhas mortas: ");
    bool encontrou = false; // Flag para verificar se há células vizinhas mortas
    
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (matriz[i][j] == '+') {
                printf("( %d, %d ) ", i, j);
                encontrou = true;
            }
        }
    }
    
    if (!encontrou) {
        printf("Nenhuma celula vizinha morta.\n");
    }
    printf("\n");
}

int apresentarMenuGeral(){ 
	int op;
	printf("\n                \n");
	printf("\t\t\t\tMENU\n");
	printf("=====================================================================");
    printf("\n1 - Apresentar o Mapa\n");
    printf("2 - Limpar o Mapa\n");
    printf("3 - Incluir/excluir celulas vivas\n"); 
    printf("4 - Mostrar/Esconder os mortos-vizinhos\n");
    printf("5 - Iniciar o processo\n");
    printf("6 - Apresentar as Listas\n");
    printf("7 - Gravar uma geracao inicial\n");
    printf("8 - Recuperar uma geracao inicial cadastrada\n");
	printf("9 - Limpar o cadastro de geracoes iniciais cadastradas (n geracoes)\n");
	printf("10 - Regras de evolucao das celulas\n");
	printf("0 - Sair\n");
    printf("Opcao selecionada: ");
    scanf("%d", &op);
    system("cls");
    return op;
}

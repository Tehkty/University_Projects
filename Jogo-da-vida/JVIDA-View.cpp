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
        printf("Tamanho invalido, digite de novo.\n");
        return;
    }
    
	criarMatriz();
    
    int geracao = 0; // Inicializa a variável geracao

    apresentaMapa(); // Passa o parâmetro geracao
}

void criarMatriz(){
	for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = '.';
        }
    }
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
	
	printf("Geracao: %d\n", geracaoAtual);
	
    mostraLvivo();           // Exibe células vivas
    mostraLvizinhasMortas();  // Exibe células vizinhas mortas
}

void iniciarProcesso() {
    if (totvivo == 0) {
        apresentarMensagem("Nenhuma célula viva presente no mapa. Adicione células antes de iniciar o processo.");
        return;
    }

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

    while (geracaoAtual <= numGeracoes) {
        printf("\nGeracao %d:", geracaoAtual);

        // Avança a geração
        Evolucao();  // Chama a função Evolucao para processar a evolução das células


        // Se o flag de mostrar vizinhos mortos estiver ativado, chama a função
        if (mostrarMortosVizinhos) {
            vizinhosMortos();
        }

        // Exibe o mapa após a evolução da geração
        apresentaMapa();  

        // Verifica se a matriz está vazia, ou seja, não há células vivas restantes
        if (verificarMatrizVazia()) { 
            printf("Nenhuma celula sobreviveu.\n");
            break;
        }

        // Controle de tempo (atraso entre gerações)
        if (atraso > 0) {
            lt1 = time(NULL);
            lt2 = lt1;
            while (difftime(lt2, lt1) < atraso) {
                lt2 = time(NULL);  // Aguarda o tempo de atraso
            }
        }

        geracaoAtual++;  // Incrementa a geração atual
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

        if (matriz[i][j] == 'O') {
            printf("Celula viva. Deseja remove-la? (S para sim, N para nao): ");
            scanf(" %c", &op2); 

            if (op2 == 'S' || op2 == 's') {
                excluiLVivo(i, j);
                matriz[i][j] = '.';
                printf("Celula removida com sucesso!\n");
            } else {
                printf("Celula mantida.\n");
            }
        } else { // Se a célula está morta
            printf("Colocando celula viva.\n");
            matriz[i][j] = 'O';
            carregaVivo(i, j);
        }

        celulavivamorta();

    } while (true);

    vivosAtuais(); // Atualiza a lista de vivos
    mortosVivos(); // Atualiza a lista de vizinhos mortos
    geracaoAtual = 1; // Resetar geração após alteração
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


int rconfirma(char pergunta[500])
{
    char resposta;
    printf("%s", pergunta);
    printf("\nDigite 'S' para confirmar e 'N' para cancelar: ");
    scanf(" %c", &resposta); 
    
    system("cls");
    
    if (resposta == 'S' || resposta == 's') {
        return 1; 
    } else if (resposta == 'N' || resposta == 'n') {
        return 0; 
    } else {
        printf("Opção inválida. Operação cancelada.\n");
        return 0;
    }
}

//funcao que permite ao usuario escolher a gravacao que deseja recuperar
void escolheGravacao()
{
	int opcao;
	do
	{
		recuperaCelulas();
		if(qtconf==0)
			return;
		
		printf("Digite 1 para escolher a geracao acima\n");
		printf("Digite 2 para mostrar outra geracao registrada\n");
		printf("Opcao:");
		scanf("%d",&opcao);
		system("cls");
		if(opcao!=1&&opcao!=2)
			printf("\t\tOpcao invalida\n");	
		
		
	}while(opcao!=1);
	apresentaMapa();
	
}

void regrasGerais()
{
	printf("\t\t\t\tREGRAS - JOGO DA VIDA\n");
	printf("=====================================================================");
    printf("\nReproducao: Um ser vivo nasce numa celula vazia se essa celula vazia tiver exatamente 3 seres vivos vizinhos.\n");
    printf("\nSobrevivencia: Um ser vivo que tenha 2 ou 3 vizinhos sobrevive para a geracao seguinte.\n");
    printf("\nMorte por falta de comida: Um ser vivo com 4 ou mais vizinhos morre porque fica sem comida.\n"); 
    printf("\nMorte por solidao: Um ser vivo com 0 ou 1 vizinhos morre de solidao.\n");
    printf("=====================================================================");
}

int apresentarMenuGeral(){ 
	int op;
	printf("\n                \n");
	printf("\t\t\t\tMENU - JOGO DA VIDA\n");
	printf("=====================================================================");
    printf("\n1 - Apresentar o Mapa\n");
    printf("2 - Limpar o Mapa\n");
    printf("3 - Incluir/excluir celulas vivas\n"); 
    printf("4 - Mostrar/Esconder os mortos-vizinhos\n");
    printf("5 - Iniciar o processo\n");
    printf("6 - Gravar uma geracao inicial\n");
    printf("7 - Recuperar uma geracao inicial cadastrada\n");
	printf("8 - Limpar o cadastro de geracoes iniciais cadastradas (n geracoes)\n");
	printf("9 - Regras de evolucao das celulas\n");
	printf("0 - Sair\n");
    printf("Opcao selecionada: ");
    scanf("%d", &op);
    system("cls");
    return op;
}

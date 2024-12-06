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
            	carregaConfig();
                gravaCelulas();
                break;
            case 7:
            	carregaConfig();
                escolheGravacao();
                break;
            case 8:
                limpaGeracoes();
                break;
            case 9:
                regrasGerais();
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

    // Resetar a geração atual
    geracaoAtual = 1;

    apresentarMensagem("Mapa limpo com sucesso. Adicione novas células para iniciar o processo.");
    apresentaMapa(); // Atualiza o mapa na visualização
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

void gravaCelulas() {
	int k,i,ni;
	k= qtconf;
	if(totvivo==0)
	  return;
	  
	TipoCel *aux;
	aux = pvivo;
	ni=0;
	do{
			Lvivo.L[ni].lin = aux->lin;
			Lvivo.L[ni].col = aux->col;
			ni++;
			aux = aux->next;
	  }while(aux!=NULL);
	Lvivo.dimensao = dim;
	Lvivo.cont = totvivo;
	LConfig[k].TL = Lvivo;
	
	FILE *fp;
	if((fp = fopen("CONFIG_INIC","w"))==NULL)
	{
		apresentarMensagem("ERRO: O arquivo CONFIG_INIC nao pode ser aberto para gravacao");
		return;
	}
	for(i = 0; i<=qtconf;i++)
	{
		if(fwrite(&LConfig[i],sizeof(TipoLista),1,fp)!=1)
		{
			apresentarMensagem("Erro na gravacao do arquivo CONFIG_INIC");
			fclose(fp);
			return;
		}
	}
	fclose(fp);
	qtconf++;
	system("cls");
	apresentarMensagem("Configuracao gravada OK");
}

void carregaConfig() {
	int k;
	FILE *fp;
	if((fp = fopen("CONFIG_INIC","r"))!=NULL)
	{
		qtconf = 0;
		k = 0;
		while(!feof(fp))
		{
			if(fread(&LConfig[k],sizeof(TipoLista),1,fp)!=1)
			{
				fclose(fp);
				return;
			}
			qtconf++;
			k++;
		}
		fclose(fp);
	}
}


// Em ultrecup temos a última recuperação realizada (ou -1 se nenhuma),
// e agora interessa-nos a próxima.
void recuperaCelulas() {
	int i,j,k,ni;
	TipoCel *aux;
	if(qtconf==0)
	{
		apresentarMensagem("Nao existe configuracao a recuperar");
		return;
	}
	k = ultrecup+1;
	if(k>=qtconf)
		k=0;
	Lvivo = LConfig[k].TL;
	ultrecup = k;
	
	clearListaMortos();
	clearListaVivos();
	dim = Lvivo.dimensao;
	criarMatriz();
	
	for(ni=0;ni<Lvivo.cont;ni++)
		carregaVivo(Lvivo.L[ni].lin,Lvivo.L[ni].col);
		
	if(totvivo>0)
	{
		aux = pvivo;
		do
		{
			matriz[aux->lin][aux->col]='O';
			aux = aux->next;
		}while(aux!=NULL);
		mortosVivos();
		apresentaMapa();
	}	
}


// Remove o arquivo de configurações iniciais
void deletaConfig() {
    if (remove("CONFIG_INIC") != 0) {
        apresentarMensagem("ERRO: O arquivo CONFIG_INIC nao pode ser removido");
        return;
    }

    qtconf = 0;
    apresentarMensagem("O arquivo CONFIG_INIC foi removido OK");
}


void clearListaVivos()
{
	TipoCel *aux,*aux2;
	if(totvivo>0)
	{
		aux = pvivo;
	while(aux->next!=NULL)
	{
		aux2 = aux->next;
		free(aux);
		aux = aux2;
	}
	free(aux);
	pvivo=NULL;
	totvivo=0;
	}
}

void clearListaMortos()
{
	TipoCel *aux,*aux2;
	if(totmorto>0)
	{
		aux = pmorto;
		while(aux->next!=NULL)
		{
		aux2 = aux->next;
		free(aux);
		aux = aux2;
		}
		free(aux);
		pmorto = NULL;
		totmorto=0;
	}
	
}

void vivosAtuais()
{
	for(int i = 1; i<=dim; i++)                   
		for(int j = 1; j<=dim; j++)
			if(matriz[i][j]=='O')
				carregaVivo(i,j);
}

//funcao que verifica quais celulas sao mortas vizinhas
void mortosVivos() {
    TipoCel *auxant, *aux;
    int i, j, m, c;

    // Percorre a matriz para identificar vizinhos mortos
    for (i = 0; i <= dim; i++) {
        for (j = 0; j <= dim; j++) {
            if (matriz[i][j] == 'O') { // Se é uma célula viva
                for (int l = (i - 1); l <= (i + 1); l++) {
                    for (int c = (j - 1); c <= (j + 1); c++) {
                        // Verifica os limites da matriz
                        if (l > 0 && l <= dim && c > 0 && c <= dim) {
                            // Processa células mortas vizinhas, mas não exibe '+'
                            if (matriz[l][c] != 'O' && matriz[l][c] != '+') {
                                MortosVivosAtuais(l, c); // Adiciona à lista de vizinhos mortos
                                if (mostrarMortosVizinhos) {
                                    matriz[l][c] = '+'; // Marca '+' apenas se o flag estiver ativo
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


//funcao que coloca na lista dinamica as celulas mortas vizinhas atuais
void MortosVivosAtuais(int ii, int jj)
{
	TipoCel* aux = (TipoCel*)malloc(sizeof(TipoCel));
	if(aux==NULL)
	{
		apresentarMensagem("Sem espaco na memoria para inclusao de celula morta\n");
		return;
	}
	aux->lin=ii;
	aux->col=jj;
	if(totmorto==0)
	{
		pmorto=aux;
		pmorto->next=NULL;
	}
	else
	{
		aux->next=pmorto;
		pmorto=aux;
	}
	totmorto++;
}

//funcao que coloca na lista dinamica as celulas vivas da proxima geracao
void ProximoVivo(int ii, int jj)
{
	TipoCel* aux = (TipoCel*)malloc(sizeof(TipoCel));
	if(aux==NULL)
	{
		apresentarMensagem("Sem espaco na memoria para inclusao de celula viva da proxima geracao\n");
		return;
	}
	aux->lin=ii;
	aux->col=jj;
	if(totvivoprox==0)
	{
		pvivoprox=aux;
		pvivoprox->next=NULL;
	}
	else
	{
		aux->next=pvivoprox;
		pvivoprox=aux;
	}
	totvivoprox++;
}

//funcao que que calcula as celulas da proxima geracao e as coloca na matriz
void proxGenMatriz()
{
	TipoCel *aux;
	for(int i = 0; i<=dim; i++)
		for(int j = 0; j<=dim; j++)
			matriz[i][j] = '.';
			
	aux = pvivoprox;
	while(totvivoprox>0)
	{
		matriz[aux->lin][aux->col]='O';
		pvivoprox=aux->next;
		free(aux);
		aux = pvivoprox;
		totvivoprox--;
	}	
}

void Evolucao()
{
	int i, j;
	int qtd = 0;
	TipoCel *aux;
	
	for(i = 0; i<=dim; i++)                   
			for(j = 0; j<=dim; j++)
				for(int l = (i-1); l <=(i+1); l++)
					for(int c = (j-1); c <=(j+1); c++)
						if ((l != 0) && (l != (dim + 1)))
							if ((c != 0) && (c != (dim + 1)))
								if((matriz[i][j] == 'O') && (matriz[l][c] != 'O'))
										matriz[l][c] = '+';

	{
		aux = pvivo;
		while(totvivo>0)	                               
		{
			i= aux->lin; j=aux->col;
			for(int l = (i-1); l <=(i+1); l++)
				for(int c = (j-1); c <=(j+1); c++)
					if ((l != 0) && (l != (dim + 1)))
						if ((c != 0) && (c != (dim + 1)))
							if(matriz[l][c] == 'O')
								qtd ++;	
		
			if(qtd == 4|| qtd==3)  
			        ProximoVivo(i,j);
			pvivo = aux->next;
			free(aux);
			aux = pvivo;
			totvivo--;
			qtd=0;
		}
	
	}
	
	aux=pmorto;
		{
			while(totmorto>0)	
			{
		 		i= aux->lin, j=aux->col;
					for(int l = (i-1); l <=(i+1); l++)
						for(int c = (j-1); c <=(j+1); c++)
							if ((l != 0) && (l != (dim + 1)))
								if ((c != 0) && (c != (dim + 1)))
									if(matriz[l][c] == 'O')
									qtd ++;				
			
			if(qtd ==3)
				ProximoVivo(i,j);
			pmorto=aux->next;
			free(aux);
			aux=pmorto;
			totmorto--;
			qtd=0;
			}
		}
		
		proxGenMatriz();
		clearListaVivos();
		clearListaMortos();
		vivosAtuais();
		mortosVivos();
			
}

void limpaGeracoes()
{
	if(qtconf>0)
	{
		if(rconfirma("Confirma exclusao das configuracoes iniciais? ")==0)
			return;
	}
	qtconf = 0;
	ultrecup = -1;
	deletaConfig();
	limparMapa();
	apresentarMensagem("O deposito de geracoes iniciais esta vazio");
	
}

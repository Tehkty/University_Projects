#ifndef JVIDA_Controller_h
#define JVIDA_Controller_h
;
void menu();
void limparMapa();
void celulavivamorta();
void vizinhosMortos();
void matrizAux();
void atualizarMatriz();
int calcVizinhos(int i, int j);
void evoluirJogo(int numGeracoes, int atraso);
bool verificarMatrizVazia();
void iniciarProcesso();
void carregaVivo(int ii, int jj);
void excluiLVivo(int ii, int jj);
void gravaCelulas();
void carregaConfig();
void recuperaCelulas();
void deletaConfig();
void clearListaVivos();
void clearListaMortos();
void vivosAtuais();
void mortosVivos();
void MortosVivosAtuais(int ii, int jj);
void ProximoVivo(int ii, int jj);
void proxGenMatriz();
void Evolucao();
void limpaGeracoes();

#endif

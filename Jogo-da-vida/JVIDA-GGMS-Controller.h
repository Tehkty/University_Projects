//JVIDA-GGMS - Projeto Jogo da Vida - Etapa 4
//Gabriel Azevedo Cruz
//Giulia Meninel Mattedi
//Matheus Gomes Costa Castanho Giacomini
//Sthefany Viveiros Cordeiro
#ifndef JVIDA_GGMS_Controller_h
#define JVIDA_GGMS_Controller_h
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

#endif
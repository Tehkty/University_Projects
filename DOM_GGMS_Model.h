//DOM-GGMS-Model.h - Projeto Domino - Etapa 6
//03/09/24 - Grupo: GGMS
//Gabriel Azevedo Cruz 
//Giulia Meninel Mattedi
//Matheus Gomes Costa Castanho Giacomini
//Sthefany Viveiros Cordeiro

//estrutura tipo peca
typedef struct {
    int lado1;
    int lado2;
    char status; //'J' = jogador 1, 'j' = jogador 2, 'M' = mesa, 'C' = compravel
} tipopeca;

typedef struct {
    int mesaE;
    int mesaD;
    int posicaoLivreMesa;
    tipopeca pecasNaMesa[28];  
} Mesa; 

void fCriar(tipopeca pecas[28]);
void distribuiPecas(tipopeca pecas[28]);


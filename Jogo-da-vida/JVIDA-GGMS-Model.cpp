//JVIDA-GGMS - Projeto Jogo da Vida - Etapa 4
//Gabriel Azevedo Cruz
//Giulia Meninel Mattedi
//Matheus Gomes Costa Castanho Giacomini
//Sthefany Viveiros Cordeiro

#include "JVIDA-GGMS-Model.h"

typedef struct cel
{
 int lin, col; //as 2 coordenadas da celula
 struct cel *next; //ponteiro (endereço) para a próxima célula
} TipoCel;

TipoCel *pvivo, *pmorto, *pvivoprox
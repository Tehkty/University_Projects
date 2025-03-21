#include "JVIDA-Model.h"

typedef struct c
{
 int lin, col;
} Cel;

typedef struct list
{
 int cont; //tamanho da lista de até no máximo 400 células vivas iniciais
 Cel L[400];
 int dimensao;
} TipoLista;

TipoLista Lvivo; //esta estrutura não contem mais os ponteiros de ligação entre as células, pois elas serão gravadas sequencialmente em disco.
//Define o array LConfig[50] para a gravação em disco de até 50 listas de células vivas iniciais

struct arquivo
{
 TipoLista TL; //1 lista total
} LConfig[50];


typedef struct cel
{
 int lin, col; //as 2 coordenadas da celula
 struct cel *next; //ponteiro (endereço) para a próxima célula
} TipoCel;

TipoCel *pvivo, *pmorto, *pvivoprox

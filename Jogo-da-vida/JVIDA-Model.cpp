#include "JVIDA-Model.h"

typedef struct cel
{
 int lin, col; //as 2 coordenadas da celula
 struct cel *next; //ponteiro (endereço) para a próxima célula
} TipoCel;

TipoCel *pvivo, *pmorto, *pvivoprox

typedef struct {//estrutura tipo peca
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

#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com água (0)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // Coordenadas iniciais do navio horizontal
    int linha_horizontal = 2;
    int coluna_horizontal = 4;

    // Coordenadas iniciais do navio vertical
    int linha_vertical = 5;
    int coluna_vertical = 6;

    // Validação para garantir que os navios estejam dentro dos limites
    if (coluna_horizontal + TAM_NAVIO <= TAM_TABULEIRO &&
        linha_vertical + TAM_NAVIO <= TAM_TABULEIRO) {

        // Posiciona o navio horizontal
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha_horizontal][coluna_horizontal + i] = VALOR_NAVIO;
        }

        // Posiciona o navio vertical (validação de sobreposição simplificada)
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha_vertical + i][coluna_vertical] == VALOR_NAVIO) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linha_vertical + i][coluna_vertical] = VALOR_NAVIO;
            }

            // Exibição do tabuleiro
            printf("Tabuleiro com os navios posicionados:\n\n");
            for (int i = 0; i < TAM_TABULEIRO; i++) {
                for (int j = 0; j < TAM_TABULEIRO; j++) {
                    printf("%d ", tabuleiro[i][j]);
                }
                printf("\n");
            }

            // Exibe coordenadas de cada parte dos navios
            printf("\nCoordenadas do navio horizontal:\n");
            for (int i = 0; i < TAM_NAVIO; i++) {
                printf("(%d, %d)\n", linha_horizontal, coluna_horizontal + i);
            }

            printf("\nCoordenadas do navio vertical:\n");
            for (int i = 0; i < TAM_NAVIO; i++) {
                printf("(%d, %d)\n", linha_vertical + i, coluna_vertical);
            }

        } else {
            printf("Erro: os navios se sobrepõem!\n");
        }
    } else {
        printf("Erro: coordenadas fora dos limites do tabuleiro.\n");
    }

    return 0;
}

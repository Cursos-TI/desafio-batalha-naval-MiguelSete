#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

// Declarações das funções auxiliares
int checarEspaco(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int l[], int c[]);
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int l[], int c[]);
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
void exibirCoordenadas(const char* titulo, int l[], int c[]);
void exibirHabilidade(const char* nome, int matriz[3][5]);

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com água (0)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // Coordenadas dos navios
    int lin_h = 1, col_h = 1;     // Horizontal
    int lin_v = 4, col_v = 3;     // Vertical
    int lin_d1 = 0, col_d1 = 0;   // Diagonal principal (\u2198)
    int lin_d2 = 2, col_d2 = 9;   // Diagonal secundária (\u2199)

    // Matrizes para os navios
    int h_linhas[TAM_NAVIO] = {lin_h, lin_h, lin_h};
    int h_colunas[TAM_NAVIO] = {col_h, col_h + 1, col_h + 2};

    int v_linhas[TAM_NAVIO] = {lin_v, lin_v + 1, lin_v + 2};
    int v_colunas[TAM_NAVIO] = {col_v, col_v, col_v};

    int d1_linhas[TAM_NAVIO] = {lin_d1, lin_d1 + 1, lin_d1 + 2};
    int d1_colunas[TAM_NAVIO] = {col_d1, col_d1 + 1, col_d1 + 2};

    int d2_linhas[TAM_NAVIO] = {lin_d2, lin_d2 + 1, lin_d2 + 2};
    int d2_colunas[TAM_NAVIO] = {col_d2, col_d2 - 1, col_d2 - 2};

    int sobreposicao = 0;

    // Posiciona os navios, verificando sobreposição
    if (!checarEspaco(tabuleiro, h_linhas, h_colunas)) {
        posicionarNavio(tabuleiro, h_linhas, h_colunas);
    } else sobreposicao = 1;

    if (!checarEspaco(tabuleiro, v_linhas, v_colunas)) {
        posicionarNavio(tabuleiro, v_linhas, v_colunas);
    } else sobreposicao = 1;

    if (!checarEspaco(tabuleiro, d1_linhas, d1_colunas)) {
        posicionarNavio(tabuleiro, d1_linhas, d1_colunas);
    } else sobreposicao = 1;

    if (!checarEspaco(tabuleiro, d2_linhas, d2_colunas)) {
        posicionarNavio(tabuleiro, d2_linhas, d2_colunas);
    } else sobreposicao = 1;

    // Erro em caso de conflito
    if (sobreposicao) {
        printf("Erro: Um ou mais navios estão sobrepostos ou fora dos limites.\n");
        return 1;
    }

    // Exibe o tabuleiro completo
    exibirTabuleiro(tabuleiro);

    // Exibe coordenadas
    exibirCoordenadas("Navio Horizontal", h_linhas, h_colunas);
    exibirCoordenadas("Navio Vertical", v_linhas, v_colunas);
    exibirCoordenadas("Navio Diagonal Principal (\u2198)", d1_linhas, d1_colunas);
    exibirCoordenadas("Navio Diagonal Secundária (\u2199)", d2_linhas, d2_colunas);

    // Matrizes de habilidades (Nível Mestre)
    int cone[3][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1}
    };

    int cruz[3][5] = {
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0}
    };

    int octaedro[3][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };

    // Exibir habilidades
    exibirHabilidade("Cone", cone);
    exibirHabilidade("Cruz", cruz);
    exibirHabilidade("Octaedro", octaedro);

    return 0;
}

// Verifica se há espaço disponível (sem sobreposição ou fora dos limites)
int checarEspaco(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int l[], int c[]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (l[i] < 0 || l[i] >= TAM_TABULEIRO || c[i] < 0 || c[i] >= TAM_TABULEIRO) {
            return 1; // Fora dos limites
        }
        if (tabuleiro[l[i]][c[i]] == VALOR_NAVIO) {
            return 1; // Já ocupado
        }
    }
    return 0;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int l[], int c[]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[l[i]][c[i]] = VALOR_NAVIO;
    }
}

// Exibe a matriz do tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro com os navios posicionados:\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Exibe as coordenadas de um navio
void exibirCoordenadas(const char* titulo, int l[], int c[]) {
    printf("\nCoordenadas do %s:\n", titulo);
    for (int i = 0; i < TAM_NAVIO; i++) {
        printf("(%d, %d)\n", l[i], c[i]);
    }
}

// Exibe a matriz de habilidade
void exibirHabilidade(const char* nome, int matriz[3][5]) {
    printf("\nExemplo de habilidade %s:\n", nome);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h> // Para a função abs()

// DESAFIO BATALHA NAVAL NÍVEL: MESTRE.
// Implementando habilidades especiais com áreas de efeito.

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // O tamanho das matrizes de habilidade
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("--- TABULEIRO DE BATALHA NAVAL ---\n");
    // Imprime os números das colunas para referência
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Imprime as linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Imprime o número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("--- Legenda: 0=Agua, 3=Navio, 5=Habilidade ---\n");
}

// Função para verificar se a posição é válida (dentro dos limites e não ocupada)
bool ehPosicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
        return false;
    }
    if (tabuleiro[linha][coluna] == VALOR_NAVIO) {
        return false;
    }
    return true;
}

// Funções para criar as matrizes de habilidade
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A lógica do cone se expande a partir do topo (vértice em i=0, j=centro)
            if (j >= centro - i && j <= centro + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A cruz afeta a linha e a coluna do centro
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A forma de losango (octaedro) é baseada na distância de Manhattan do centro
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para sobrepor a matriz de habilidade no tabuleiro principal
void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                        int linha_origem, int coluna_origem) {
    
    int metade_habilidade = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Converte as coordenadas da matriz de habilidade para as do tabuleiro principal
            int tabuleiro_linha = linha_origem - metade_habilidade + i;
            int tabuleiro_coluna = coluna_origem - metade_habilidade + j;
            
            // Verifica se a posição está dentro dos limites do tabuleiro e se a habilidade está ativa nela
            if (habilidade[i][j] == 1 && tabuleiro_linha >= 0 && tabuleiro_linha < TAMANHO_TABULEIRO &&
                tabuleiro_coluna >= 0 && tabuleiro_coluna < TAMANHO_TABULEIRO) {
                
                // Se a posição já for um navio, não a marca com a habilidade para manter a prioridade do navio
                if (tabuleiro[tabuleiro_linha][tabuleiro_coluna] != VALOR_NAVIO) {
                    tabuleiro[tabuleiro_linha][tabuleiro_coluna] = VALOR_HABILIDADE;
                }
            }
        }
    }
}

int main() {
    // 1. Criar e inicializar o tabuleiro 10x10 com 0s.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};
    
    // 2. Definir coordenadas e orientações dos navios.
    int n1_linha = 2, n1_coluna = 1; // Horizontal
    int n2_linha = 4, n2_coluna = 6; // Vertical
    int n3_linha = 7, n3_coluna = 7; // Diagonal Crescente
    int n4_linha = 1, n4_coluna = 8; // Diagonal Decrescente
    
    // Posicionando os navios (versão compacta para legibilidade)
    for (int i = 0; i < TAMANHO_NAVIO; i++) { if (!ehPosicaoValida(tabuleiro, n1_linha, n1_coluna + i)) { printf("Erro Navio 1\n"); return 1; } tabuleiro[n1_linha][n1_coluna + i] = VALOR_NAVIO; }
    for (int i = 0; i < TAMANHO_NAVIO; i++) { if (!ehPosicaoValida(tabuleiro, n2_linha + i, n2_coluna)) { printf("Erro Navio 2\n"); return 1; } tabuleiro[n2_linha + i][n2_coluna] = VALOR_NAVIO; }
    for (int i = 0; i < TAMANHO_NAVIO; i++) { if (!ehPosicaoValida(tabuleiro, n3_linha + i, n3_coluna + i)) { printf("Erro Navio 3\n"); return 1; } tabuleiro[n3_linha + i][n3_coluna + i] = VALOR_NAVIO; }
    for (int i = 0; i < TAMANHO_NAVIO; i++) { if (!ehPosicaoValida(tabuleiro, n4_linha + i, n4_coluna - i)) { printf("Erro Navio 4\n"); return 1; } tabuleiro[n4_linha + i][n4_coluna - i] = VALOR_NAVIO; }

    
    // 4. Criar e sobrepor as habilidades especiais no tabuleiro.

    // Matrizes para as habilidades
    int habilidade_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // Constrói as matrizes de habilidade
    criarHabilidadeCone(habilidade_cone);
    criarHabilidadeCruz(habilidade_cruz);
    criarHabilidadeOctaedro(habilidade_octaedro);

    // Define os pontos de origem para as habilidades no tabuleiro principal
    int origem_cone_linha = 4;
    int origem_cone_coluna = 2;
    int origem_cruz_linha = 8;
    int origem_cruz_coluna = 4;
    int origem_octaedro_linha = 5;
    int origem_octaedro_coluna = 8;
    
    // Sobrepõe as habilidades no tabuleiro
    sobreporHabilidade(tabuleiro, habilidade_cone, origem_cone_linha, origem_cone_coluna);
    sobreporHabilidade(tabuleiro, habilidade_cruz, origem_cruz_linha, origem_cruz_coluna);
    sobreporHabilidade(tabuleiro, habilidade_octaedro, origem_octaedro_linha, origem_octaedro_coluna);

    // 5. Exibir o tabuleiro completo.
    exibirTabuleiro(tabuleiro);

    return 0;
}
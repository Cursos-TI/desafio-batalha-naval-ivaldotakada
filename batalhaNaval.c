#include <stdio.h>
#include <stdbool.h>

// DESAFIO BATALHA NAVAL NÍVEL: AVENTUREIRO.
// Posicionando navios sem sobreposições.

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("--- TABULEIRO DE BATALHA NAVAL ---\n");
    // Imprime os números das colunas para referência
    printf("  "); // Espaço para alinhar com os números das linhas
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
    printf("--- Legenda: 0=Agua, 3=Navio ---\n");
}

// Função para verificar se a posição é válida (dentro dos limites e não ocupada)
bool ehPosicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se a linha e a coluna estão dentro dos limites do tabuleiro
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
        return false;
    }
    // Verifica se a posição já está ocupada por outro navio
    if (tabuleiro[linha][coluna] == 3) {
        return false;
    }
    return true;
}

int main() {
    // 1. Criar e inicializar o tabuleiro 10x10 com 0s.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // 2. Definir coordenadas e orientações dos navios.
    // Navio 1: horizontal
    int n1_linha = 2;
    int n1_coluna = 1;

    // Navio 2: vertical
    int n2_linha = 4;
    int n2_coluna = 6;
    
    // Navio 3: diagonal (crescente: linha e coluna aumentam)
    int n3_linha = 7;
    int n3_coluna = 7;

    // Navio 4: diagonal (decrescente: linha aumenta, coluna diminui)
    int n4_linha = 1;
    int n4_coluna = 8;
    
    // 3. Posicionar os navios, validando cada posição.

    // Posicionando Navio 1 (Horizontal)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (!ehPosicaoValida(tabuleiro, n1_linha, n1_coluna + i)) {
            printf("Erro: Posicionamento do Navio 1 (horizontal) invalido. Coordenadas ou sobreposicao.\n");
            return 1;
        }
        tabuleiro[n1_linha][n1_coluna + i] = 3;
    }

    // Posicionando Navio 2 (Vertical)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (!ehPosicaoValida(tabuleiro, n2_linha + i, n2_coluna)) {
            printf("Erro: Posicionamento do Navio 2 (vertical) invalido. Coordenadas ou sobreposicao.\n");
            return 1;
        }
        tabuleiro[n2_linha + i][n2_coluna] = 3;
    }
    
    // Posicionando Navio 3 (Diagonal Crescente)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (!ehPosicaoValida(tabuleiro, n3_linha + i, n3_coluna + i)) {
            printf("Erro: Posicionamento do Navio 3 (diagonal crescente) invalido. Coordenadas ou sobreposicao.\n");
            return 1;
        }
        tabuleiro[n3_linha + i][n3_coluna + i] = 3;
    }

    // Posicionando Navio 4 (Diagonal Decrescente)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (!ehPosicaoValida(tabuleiro, n4_linha + i, n4_coluna - i)) {
            printf("Erro: Posicionamento do Navio 4 (diagonal decrescente) invalido. Coordenadas ou sobreposicao.\n");
            return 1;
        }
        tabuleiro[n4_linha + i][n4_coluna - i] = 3;
    }

    // 4. Exibir o tabuleiro.
    exibirTabuleiro(tabuleiro);

    return 0; // Retorna 0 para indicar sucesso
}
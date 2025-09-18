#include <stdio.h>

// DESAFIO BATALHA NAVAL NÍVEL: NOVATO.
// Posicionando navios em um tabuleiro 10x10.

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("--- TABULEIRO DE BATALHA NAVAL ---\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("--- Legenda: 0=Agua, 3=Navio ---\n");
}

int main() {
    // 1. Representar o tabuleiro com uma matriz 10x10, inicializando com 0s (água).
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Loops aninhados para preencher o tabuleiro com 0s
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Posicionar os navios.
    
    // Navio 1 (horizontal): Posição inicial (linha 2, coluna 1)
    int linha_navio1 = 2;
    int coluna_navio1 = 1;

    // Navio 2 (vertical): Posição inicial (linha 4, coluna 6)
    int linha_navio2 = 4;
    int coluna_navio2 = 6;
    
    // Validação de posicionamento: verifica se os navios cabem no tabuleiro.
    // Navio horizontal: (coluna_inicial + tamanho do navio) deve ser <= TAMANHO_TABULEIRO.
    // Navio vertical: (linha_inicial + tamanho do navio) deve ser <= TAMANHO_TABULEIRO.
    if (coluna_navio1 + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
        linha_navio2 + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: A posicao dos navios esta fora dos limites do tabuleiro.\n");
        return 1; // Retorna 1 para indicar um erro
    }

    // Posicionando o Navio 1 (horizontal)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_navio1][coluna_navio1 + i] = 3;
    }

    // Posicionando o Navio 2 (vertical)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        // Validação de sobreposição simplificada para este nível
        // Verifica se a posição do navio 2 já está ocupada pelo navio 1.
        if (tabuleiro[linha_navio2 + i][coluna_navio2] == 3) {
            printf("Erro: Navios se sobrepoem! Ajuste as coordenadas.\n");
            // Limpa as posições já colocadas do navio 2 para evitar lixo
            for (int j = 0; j <= i; j++) {
                tabuleiro[linha_navio2 + j][coluna_navio2] = 0;
            }
            return 1;
        }
        tabuleiro[linha_navio2 + i][coluna_navio2] = 3;
    }

    // 3. Exibir o tabuleiro com os navios posicionados.
    exibirTabuleiro(tabuleiro);

    return 0; // Retorna 0 para indicar sucesso
}
#include <stdio.h>

// Função para inicializar o tabuleiro com espaços em branco
void inicializarTabuleiro(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(char tabuleiro[3][3]) {
    printf(" %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}

// Função para verificar se há um vencedor
char verificarVencedor(char tabuleiro[3][3]) {
    // Verificação de linhas e colunas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ')
            return tabuleiro[i][0];
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ')
            return tabuleiro[0][i];
    }
    // Verificação das diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ')
        return tabuleiro[0][0];
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ')
        return tabuleiro[0][2];

    // Sem vencedor
    return ' ';
}

// Função para verificar se o tabuleiro está cheio (empate)
int tabuleiroCheio(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

int main() {
    char tabuleiro[3][3];
    char jogador = 'X';
    char vencedor = ' ';
    int linha, coluna;

    inicializarTabuleiro(tabuleiro);

    // Jogo continua até haver um vencedor ou o tabuleiro ficar cheio
    while (vencedor == ' ' && !tabuleiroCheio(tabuleiro)) {
        exibirTabuleiro(tabuleiro);
        printf("Jogador %c, escolha sua linha (1-3) e coluna (1-3): ", jogador);
        scanf("%d %d", &linha, &coluna);

        // Ajusta os índices para 0-based
        linha--;
        coluna--;

        // Verifica se a posição é válida
        if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || tabuleiro[linha][coluna] != ' ') {
            printf("Jogada inválida! Tente novamente.\n");
        } else {
            tabuleiro[linha][coluna] = jogador;
            vencedor = verificarVencedor(tabuleiro);

            // Alterna jogador
            jogador = (jogador == 'X') ? 'O' : 'X';
        }
    }

    exibirTabuleiro(tabuleiro);

    if (vencedor != ' ') {
        printf("Jogador %c venceu!\n", vencedor);
    } else {
        printf("Empate!\n");
    }

    return 0;
}

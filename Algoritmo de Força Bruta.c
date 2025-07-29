#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAMANHO_MAX_INPUT 500

int busca_forca_bruta_avancado(const char* texto, const char* padrao, int indice_inicial) {
    int n = strlen(texto);
    int m = strlen(padrao);

    if (m > n) return -1;

    for (int L = indice_inicial; L <= n - m; L++) {
        int j = 0;
        while (j < m && texto[L + j] == padrao[j]) {
            j++;
        }
        if (j == m) {
            return L;
        }
    }
    return -1;
}

int main() {
    char texto_usuario[TAMANHO_MAX_INPUT];
    printf("Digite uma frase: ");
    fgets(texto_usuario, TAMANHO_MAX_INPUT, stdin);
    texto_usuario[strcspn(texto_usuario, "\n")] = 0;

    const char* palavras_para_censurar[] = {"chato", "bobo", "odeio", "terrível", "abacaxi"};
    int n_palavras = sizeof(palavras_para_censurar) / sizeof(palavras_para_censurar[0]);
    int palavra_encontrada_flag = 0;

    printf("\n--- Análise com Algoritmo de Força Bruta ---\n");
    
    for (int i = 0; i < n_palavras; i++) {
        const char* palavra_atual = palavras_para_censurar[i];
        int indice_busca = 0;
        
        while (indice_busca < strlen(texto_usuario)) {
            int indice_encontrado = busca_forca_bruta_avancado(texto_usuario, palavra_atual, indice_busca);

            if (indice_encontrado != -1) {
                printf("-> Palavra '%s' encontrada no indice %d.\n", palavra_atual, indice_encontrado);
                palavra_encontrada_flag = 1;
                indice_busca = indice_encontrado + 1;
            } else {
                break;
            }
        }
    }

    if (!palavra_encontrada_flag) {
        printf("Nenhuma palavra proibida foi encontrada.\n");
    }
    return 0;
}
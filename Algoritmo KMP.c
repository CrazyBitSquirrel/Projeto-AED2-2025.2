#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAMANHO_MAX_INPUT 500

void computarArrayLPS(const char* padrao, int m, int* lps) {
    int tamanho_prefixo = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m) {
        if (padrao[i] == padrao[tamanho_prefixo]) {
            tamanho_prefixo++;
            lps[i] = tamanho_prefixo;
            i++;
        } else {
            if (tamanho_prefixo != 0) {
                tamanho_prefixo = lps[tamanho_prefixo - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}


int buscarComKMP(const char* texto, const char* padrao) {
    int n = strlen(texto);
    int m = strlen(padrao);

    if (m == 0) return 0; 

    int* lps = (int*)malloc(sizeof(int) * m);
    if (lps == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 0;
    }
    
    computarArrayLPS(padrao, m, lps);

    int i = 0;
    int j = 0;
    int encontrou = 0; 

    while (i < n) {
        if (padrao[j] == texto[i]) {
            i++;
            j++;
        }
        if (j == m) {
            printf("-> Palavra '%s' encontrada no indice %d.\n", padrao, i - j);
            encontrou = 1;
            j = lps[j - 1];
        } else if (i < n && padrao[j] != texto[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);

    return encontrou;
}

int main() {
    char texto_usuario[TAMANHO_MAX_INPUT];
    printf("Digite uma frase: ");
    fgets(texto_usuario, TAMANHO_MAX_INPUT, stdin);
    texto_usuario[strcspn(texto_usuario, "\n")] = 0;

    const char* palavras_para_censurar[] = {"chato", "bobo", "odeio", "terrivel", "abacaxi"};
    int n_palavras = sizeof(palavras_para_censurar) / sizeof(palavras_para_censurar[0]);
    
 
    int encontrou_alguma_palavra = 0;

    printf("\n--- Analise com Algoritmo KMP ---\n");

    for (int k = 0; k < n_palavras; k++) {
       
        if (buscarComKMP(texto_usuario, palavras_para_censurar[k])) {
            
            encontrou_alguma_palavra = 1;
        }
    }
    

    if (!encontrou_alguma_palavra) {
  
        printf("Nenhuma palavra proibida foi encontrada.\n");
    }
    
    return 0;
}

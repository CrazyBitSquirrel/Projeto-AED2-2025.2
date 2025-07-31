#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 


#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


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
        printf("Erro de alocação de memória!\n");
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
            
            // printf("-> Palavra '%s' encontrada no indice %d.\n", padrao, i - j);
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
    
#ifdef _WIN32
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceFrequency(&frequency); 
#else
    struct timespec start, end;
#endif
    double time_used;
   
    FILE *arquivo = fopen("input_grande.txt", "r");
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel abrir o arquivo 'input_grande.txt'.\n");
        printf("Certifique-se de que ele esta na mesma pasta que o executavel.\n");
        return 1;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    char *texto_usuario = (char *)malloc(tamanho_arquivo + 1);
    if (texto_usuario == NULL) {
        printf("Erro de alocacao de memoria para ler o arquivo.\n");
        fclose(arquivo);
        return 1;
    }
    
    fread(texto_usuario, 1, tamanho_arquivo, arquivo);
    texto_usuario[tamanho_arquivo] = '\0';
    fclose(arquivo);
   
    const char* palavras_para_censurar[] = {"abacaxi", "banana", "laranja", "morango", "abacate", "ameixa", "amora",
    "computador", "algoritmo", "programacao", "desenvolvimento", "software",
    "hardware", "internet", "protocolo", "roteador", "servidor", "cliente",
    "universidade", "estudante", "professor", "disciplina", "biblioteca",
    "conhecimento", "aprendizagem", "inteligencia", "artificial", "paradigma",
    "estrutura", "abstrato", "abstracao", "complexidade", "eficiencia",
    "otimizacao", "escalabilidade", "manutencao", "depuracao", "compilador",
    "interpretador", "linguagem", "variavel", "constante", "ponteiro",
    "memoria", "processador", "paralelepipedo", "otorrinolaringologista",
    "inconstitucionalissimamente", "pneumoultramicroscopicossilicovulcanoconiotico"};
    int n_palavras = sizeof(palavras_para_censurar) / sizeof(palavras_para_censurar[0]);
    
    int encontrou_alguma_palavra = 0;

    printf("Arquivo 'input_grande.txt' lido com sucesso (%ld bytes).\n", tamanho_arquivo);
    printf("\n--- Analise com Algoritmo KMP ---\n");

   
#ifdef _WIN32
    QueryPerformanceCounter(&start);
#else
    clock_gettime(CLOCK_MONOTONIC, &start);
#endif

   
    for (int k = 0; k < n_palavras; k++) {
        if (buscarComKMP(texto_usuario, palavras_para_censurar[k])) {
            encontrou_alguma_palavra = 1;
        }
    }
    
   
#ifdef _WIN32
    QueryPerformanceCounter(&end);
#else
    clock_gettime(CLOCK_MONOTONIC, &end);
#endif

    if (!encontrou_alguma_palavra) {
        printf("Nenhuma palavra proibida foi encontrada.\n");
    }

  
#ifdef _WIN32
    time_used = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
#else
    time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
#endif
    printf("\n--------------------------------------------\n");
    printf("Tempo pratico de execucao da busca: %.9f segundos\n", time_used);
    printf("--------------------------------------------\n");

   
    free(texto_usuario);
    
    return 0;
}
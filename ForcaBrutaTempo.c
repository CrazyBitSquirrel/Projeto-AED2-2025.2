#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


int busca_forca_bruta_avancado(const char* texto, const char* padrao, int indice_inicial) {
    int n = strlen(texto);
    int m = strlen(padrao);

    if (m > n || indice_inicial > n - m) return -1;

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
    int palavra_encontrada_flag = 0;

    printf("Arquivo 'input_grande.txt' lido com sucesso (%ld bytes).\n", tamanho_arquivo);
    printf("\n--- Analise com Algoritmo de Forca Bruta ---\n");
    
   
#ifdef _WIN32
    QueryPerformanceCounter(&start);
#else
    clock_gettime(CLOCK_MONOTONIC, &start);
#endif

    
    for (int i = 0; i < n_palavras; i++) {
        const char* palavra_atual = palavras_para_censurar[i];
        int indice_busca = 0;
        
        
        while (1) {
            int indice_encontrado = busca_forca_bruta_avancado(texto_usuario, palavra_atual, indice_busca);

            if (indice_encontrado != -1) {
                // printf("-> Palavra '%s' encontrada no indice %d.\n", palavra_atual, indice_encontrado); // Opcional: remover para um teste "silencioso"
                palavra_encontrada_flag = 1;
                indice_busca = indice_encontrado + 1;
            } else {
                break;
            }
        }
    }

   
#ifdef _WIN32
    QueryPerformanceCounter(&end);
#else
    clock_gettime(CLOCK_MONOTONIC, &end);
#endif

    if (!palavra_encontrada_flag) {
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
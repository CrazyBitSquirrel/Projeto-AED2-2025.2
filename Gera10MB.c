#include <stdio.h>
#include <string.h> 
#include <stdlib.h>


#define TAMANHO_ARQUIVO_MB 10

int main() {
    
    FILE *arquivo_saida = fopen("input_grande.txt", "w");
    if (arquivo_saida == NULL) {
        printf("Erro ao criar o arquivo de saida.\n");
        return 1;
    }

    
    const char* palavras_para_inserir[] = {
        "chato", "bobo", "odeio", "terrível", "abacaxi", "algoritmo", 
        "complexidade", "software", "computador", "inconstitucionalissimamente"
    };
    int num_palavras = sizeof(palavras_para_inserir) / sizeof(palavras_para_inserir[0]);
    
   
    const char* frase_base = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue. ";

    
    long tamanho_final_bytes = TAMANHO_ARQUIVO_MB * 1024 * 1024;
    long tamanho_atual_bytes = 0;
    long i = 0;

   
    int contador_de_palavras = 0; 

    printf("Gerando arquivo 'input_grande.txt' de %d MB... Aguarde.\n", TAMANHO_ARQUIVO_MB);

    while (tamanho_atual_bytes < tamanho_final_bytes) {
        
        fputs(frase_base, arquivo_saida);
        tamanho_atual_bytes += strlen(frase_base);

       
        if (i % 10 == 0) {
           
            fprintf(arquivo_saida, " %s ", palavras_para_inserir[contador_de_palavras % num_palavras]);
            tamanho_atual_bytes += strlen(palavras_para_inserir[contador_de_palavras % num_palavras]) + 2;
            contador_de_palavras++; 
        }
        i++;
    }

    fclose(arquivo_saida);
    printf("Arquivo 'input_grande.txt' criado com sucesso!\n");

    return 0;
}
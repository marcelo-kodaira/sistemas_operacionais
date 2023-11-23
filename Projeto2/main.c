#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t;
    int d;
} Pessoa;

typedef struct {
    int direcao;
    int tempo;
} Posterior;

// Função de comparação para qsort
int compararPessoas(const void *a, const void *b) {
    return ((Pessoa*)a)->t - ((Pessoa*)b)->t;
}

void escreverEmArquivo(const char *nomeArquivo) {
    // Abre o arquivo "entrada.txt" para escrita
    FILE* file = fopen("entradas.txt", "w");
    if (file == NULL) {
        // Exibe uma mensagem de erro se a abertura do arquivo falhar
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int num_pessoas, checar_num_pessoas, entradaInvalida = 0;
    // Realiza a inserção dos valores no arquivo
    printf("\n\n\t\t\t***Escada rolante dupla***\n");
    while(entradaInvalida ==0){
      printf("\nQuantas pessoas vão usar a escada rolante: ");
      scanf("%d", &checar_num_pessoas);
      if (checar_num_pessoas<=0){
        printf("\nQuantidade de pessoas inválida! Tente novamente.\n");
      }else{
        num_pessoas = checar_num_pessoas;
        entradaInvalida = 1;;
      }
    }

    // Escreve o número de pessoas no arquivo
    fprintf(file, "%d", num_pessoas);

    // Cria um array de structs Pessoa
    Pessoa pessoas[num_pessoas];

    for (int i = 0; i < num_pessoas; i++) {
        // Solicita o momento de entrada da pessoa e a direção desejada da escada
        printf("\n[0] Subindo\n[1] Descendo\n");
        printf("\nInsira momento de entrada da pessoa e o valor representante a direção desejada da escada:\n");
        scanf("%d%d", &pessoas[i].t, &pessoas[i].d);

        // Verifica se a direção é válida
        if (pessoas[i].d != 0 && pessoas[i].d != 1) {
            printf("Direção inválida! Tente novamente.\n");
            i--;
        }
    }

    // Ordena o array de pessoas com base nos valores de t
    qsort(pessoas, num_pessoas, sizeof(Pessoa), compararPessoas);

    // Escreve no arquivo os momentos e as direções ordenados
    for (int i = 0; i < num_pessoas; i++) {
        fprintf(file, "\n%d %d", pessoas[i].t, pessoas[i].d);
    }

    // Fecha o arquivo
    fclose(file);
}

Posterior recursaoChecagemDirecao(const char *nomeArquivo, int t, int d) {
    Posterior posterior;
    int n, t_checar, d_checar;

    // Abre o arquivo "entrada.txt" para leitura
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        // Exibe uma mensagem de erro se a abertura do arquivo falhar
        printf("Erro ao abrir o arquivo.\n");
    }

    // Lê o número de pessoas do arquivo
    if (fscanf(file, "%d", &n) == EOF) {
        printf("Erro ao ler o valor de n.\n");
        fclose(file);
    }

    // Lê os valores de t e d do arquivo
    // Loop para processar as informações de cada pessoa
    for (int i = 0; i < n; i++) {
        // Lê o momento de entrada e a direção da pessoa do arquivo
        if (fscanf(file, "%d %d", &t_checar, &d_checar) == EOF) {
            printf("Erro ao ler os valores de t e d.\n");
            fclose(file);
        }
        // Verifica qual o proximo elemento maior que o t e tem direção direferente 
        if (t_checar > t && d != d_checar) {
          posterior.direcao = d_checar;
          posterior.tempo = t_checar;
        }
    }

    fclose(file);
    return posterior;
}


int main() {
    // Chama a função para escrever no arquivo
    escreverEmArquivo("entradas.txt");

    // Abre o arquivo "entrada.txt" para leitura
    FILE* file = fopen("entradas.txt", "r");
    if (file == NULL) {

        // Exibe uma mensagem de erro se a abertura do arquivo falhar
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int n, t, d,tempo_saida, direcao_anterior, ver = 0;

    // Lê o número de pessoas do arquivo
    if (fscanf(file, "%d", &n) == EOF) {
        printf("Erro ao ler o valor de n.\n");
        fclose(file);
        return 1;
    }

    // Lê os valores de t e d do arquivo
    // Loop para processar as informações de cada pessoa
      for (int i = 0; i < n; i++) {
          // Lê o momento de entrada e a direção da pessoa do arquivo
          if (fscanf(file, "%d %d", &t, &d) == EOF) {
              printf("Erro ao ler os valores de t e d.\n");
              fclose(file);
              return 1;
          }

          // Lógica para calcular o tempo total
          if (i == 0) {
            // Cenário 0

            /* Primeira pessoa usando a escada rolante */

            tempo_saida = t + 10;
            direcao_anterior = d;
          } 
          else if (tempo_saida > t && direcao_anterior == d){
            // Cenário 1

            /* Se o proximo tempo de entrada tiver diferença menor que 10 segundos,
            ou seja, o tempo final da pesso anterior sair da escada, e tiver na mesma direção
            que a escada já estiver indo, a pessoa entra direto na escada rolante sem esperar
            */

            tempo_saida = t + 10; // Atualiza o valor de saida da pessoa que entrou agora
          } 
          else if (direcao_anterior != d && tempo_saida > t) {
            // Cenário 2

            /* Se tiver e não tiver na mesma direção que a escada já estiver indo,
            a pessoa tem que espera para entrar escada rolante*/

            Posterior posterior = recursaoChecagemDirecao("entradas.txt", t, d);
            //checar se o proximo tem a mesma direção da escada atual
            if (posterior.direcao == direcao_anterior && posterior.tempo - t < 10 && posterior.direcao != EOF){
              //ver
              if (posterior.tempo != EOF){
                if (posterior.tempo - t < 10 ){
                  int t_atualizado = posterior.tempo;
                  int d_atualizado = posterior.direcao;
                  if (ver == 0){
                    tempo_saida = posterior.tempo + 10; // Atualiza o valor de saida da pessoa que entrou agora
                    direcao_anterior = d;
                    ver ++;
                  }
                  direcao_anterior = d;
                }  
                //ver
              }
              // termino do erro
            } else if (posterior.tempo - t >= 10 || posterior.direcao != direcao_anterior){

              /* Checar se os proximos está na outra direcao da situação da escada rolante atual ou se ele 
              tiver a mesma que a de quem estou lendo atualmente - passar valor do proximo para o atual 
              e atualizar o tempo de saida*/

              tempo_saida = tempo_saida + 10; // Atualiza o valor de saida da pessoa que entrou agora
              direcao_anterior = d; // Atualiza a atual direção da escada rolante

            }
          } 
          else if(i !=0 && tempo_saida < t){
            // Cenário 3

            /* Se eu não for o primeiro e a escada rolante estiver parada, ou seja, 
            a pessoaanterior já saiu da escada rolante e essa pesso entra direto sem 
            esperar na escada rolante*/

            direcao_anterior = d; // Atualiza a atual direção da escada rolante 
            tempo_saida = t + 10; //Atualiza o valor de saida da pessoa que entrou agora
          } else return 1; // Ocorreu algum erro
      }

    // Exibe o tempo total
    printf("\nA última pessoa a utilizar a escada rolante saiu após %d segundos.", tempo_saida);

    // Fecha o arquivo
    fclose(file);
    return 0;
}


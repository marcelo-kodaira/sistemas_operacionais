#include <stdio.h>
#include <stdlib.h>

void processarArquivo(const char *nome_arquivo) {
    char input_filename[20];
    char output_filename[20];
    sprintf(input_filename, "input/%s", nome_arquivo);
    sprintf(output_filename, "output/%s", nome_arquivo);

    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada %s\n", input_filename);
        return;
    }

    int n;
    int last = 0, dir = -1, op = 0;

    fscanf(input_file, "%d", &n);
    for (int i = 0; i < n; i++) {
        int t, d;
        fscanf(input_file, "%d%d", &t, &d);

        if (t > last) {
            if (op)
                dir ^= 1, op = 0, last += 10;
        }
        if (t > last) {
            dir = d, last = t + 10;
        } else if (dir == d)
            last = t + 10;
        else
            op = 1;
    }

    if (op)
        last += 10;

    fclose(input_file);

    FILE *output_file = fopen(output_filename, "r");
    if (output_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de saida %s\n", output_filename);
        return;
    }

    int expected_result;
    fscanf(output_file, "%d", &expected_result);

    fclose(output_file);

    if (last == expected_result) {
        printf("Os resultados para %s sao iguais. (%d)\n", nome_arquivo, last);
    } else {
        printf("Os resultados para %s sao diferentes. (%d)\n", nome_arquivo, last);
    }
}

int main() {
    int num_files = 58;

    for (int i = 1; i <= num_files; ++i) {
        char nome_arquivo[20];
        sprintf(nome_arquivo, "E_%d", i);

        processarArquivo(nome_arquivo);
    }

    return 0;
}


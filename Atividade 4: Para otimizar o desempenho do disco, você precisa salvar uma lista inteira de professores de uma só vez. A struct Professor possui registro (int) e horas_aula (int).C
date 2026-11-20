#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int registro;
    int horas_aula;
} Professor;

Professor* carregarProfessores(const char *nomeArquivo, int n) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        return NULL;
    }

    Professor *listaLida = (Professor *)malloc(n * sizeof(Professor));
    if (listaLida == NULL) {
        fclose(arquivo);
        return NULL;
    }

    fread(listaLida, sizeof(Professor), n, arquivo);
    fclose(arquivo);

    return listaLida;
}

int main() {
    int n;

    printf("Quantos professores deseja cadastrar? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    Professor *professores = (Professor *)malloc(n * sizeof(Professor));
    if (professores == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\n--- Professor %d ---\n", i + 1);
        printf("Registro: ");
        scanf("%d", &professores[i].registro);
        printf("Horas-aula: ");
        scanf("%d", &professores[i].horas_aula);
    }

    void *buffer = malloc(n * sizeof(Professor));
    if (buffer == NULL) {
        printf("Erro ao alocar buffer.\n");
        free(professores);
        return 1;
    }

    memcpy(buffer, professores, n * sizeof(Professor));

    FILE *arquivo = fopen("folha.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo folha.dat.\n");
        free(professores);
        free(buffer);
        return 1;
    }

    fwrite(buffer, n * sizeof(Professor), 1, arquivo);
    fclose(arquivo);

    free(professores);
    free(buffer);

    Professor *carregados = carregarProfessores("folha.dat", n);
    if (carregados == NULL) {
        printf("Erro ao carregar os dados do arquivo.\n");
        return 1;
    }

    printf("\n--- DADOS CARREGADOS DO ARQUIVO ---\n");
    for (int i = 0; i < n; i++) {
        printf("Registro: %d | Horas-aula: %d\n", carregados[i].registro, carregados[i].horas_aula);
    }

    free(carregados);

    return 0;
}

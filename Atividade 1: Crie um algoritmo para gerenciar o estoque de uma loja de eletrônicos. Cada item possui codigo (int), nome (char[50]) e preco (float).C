#include <stdio.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
};

int main() {
    struct Produto produtos[3];
    FILE *arquivo;

    for (int i = 0; i < 3; i++) {
        printf("\n--- Produto %d ---\n", i + 1);
        printf("Codigo: ");
        scanf("%d", &produtos[i].codigo);
        printf("Nome: ");
        scanf(" %[^\n]", produtos[i].nome);
        printf("Preco: ");
        scanf("%f", &produtos[i].preco);
    }

    arquivo = fopen("estoque.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        fprintf(arquivo, "%d;%s;%.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }
    fclose(arquivo);

    arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("\n==================================================\n");
    printf("%-10s | %-25s | %s\n", "CODIGO", "NOME DO PRODUTO", "PRECO (R$)");
    printf("==================================================\n");

    struct Produto p;
    while (fscanf(arquivo, "%d;%49[^;];%f\n", &p.codigo, p.nome, &p.preco) == 3) {
        printf("%-10d | %-25s | R$ %.2f\n", p.codigo, p.nome, p.preco);
    }
    printf("==================================================\n");

    fclose(arquivo);

    return 0;
}

#include <stdio.h>

struct Cliente {
    int conta_corrente;
    char nome;
    float saldo;
};

int main() {
    int contaBusca;
    float valor;
    struct Cliente c;
    int encontrou = 0;

    printf("Numero da conta corrente: ");
    scanf("%d", &contaBusca);
    printf("Valor (positivo para deposito, negativo para saque): ");
    scanf("%f", &valor);

    FILE *arquivo = fopen("clientes.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo clientes.bin.\n");
        return 1;
    }

    while (fread(&c, sizeof(struct Cliente), 1, arquivo) == 1) {
        if (c.conta_corrente == contaBusca) {
            c.saldo += valor;
            fseek(arquivo, -sizeof(struct Cliente), SEEK_CUR);
            fwrite(&c, sizeof(struct Cliente), 1, arquivo);
            encontrou = 1;
            printf("\nSaldo atualizado com sucesso!\n");
            printf("Cliente: %s | Novo saldo: R$ %.2f\n", c.nome, c.saldo);
            break;
        }
    }

    if (!encontrou) {
        printf("\nConta corrente %d nao encontrada.\n", contaBusca);
    }

    fclose(arquivo);

    return 0;
}

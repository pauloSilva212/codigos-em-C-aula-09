#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Funcionario {
    int id;
    char cargo;
    float salario;
};

int main() {
    struct Funcionario *func = (struct Funcionario *)malloc(sizeof(struct Funcionario));
    if (func == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("ID do funcionario: ");
    scanf("%d", &func->id);
    printf("Cargo: ");
    scanf(" %[^\n]", func->cargo);
    printf("Salario: ");
    scanf("%f", &func->salario);

    struct Funcionario *backup = (struct Funcionario *)malloc(sizeof(struct Funcionario));
    if (backup == NULL) {
        printf("Erro ao alocar memoria para o backup.\n");
        free(func);
        return 1;
    }

    memcpy(backup, func, sizeof(struct Funcionario));

    FILE *arquivo = fopen("backup_rh.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo binario.\n");
        free(func);
        free(backup);
        return 1;
    }

    fwrite(backup, sizeof(struct Funcionario), 1, arquivo);
    fclose(arquivo);

    printf("\nBackup realizado com sucesso!\n");
    printf("Dados espelhados -> ID: %d | Cargo: %s | Salario: R$ %.2f\n", backup->id, backup->cargo, backup->salario);

    free(func);
    free(backup);

    return 0;
}

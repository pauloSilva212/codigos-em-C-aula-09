#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char titulo;
    int zona;
} Eleitor;

typedef struct {
    Eleitor eleitor;
    int numero_voto;
} Cedula;

Cedula* adicionarVoto(Cedula *lista, int *qtd) {
    Cedula *temp = (Cedula *)realloc(lista, (*qtd + 1) * sizeof(Cedula));
    if (temp == NULL) {
        printf("Erro ao realocar memoria.\n");
        return lista;
    }
    lista = temp;

    printf("\n--- Novo Voto ---\n");
    printf("Titulo de eleitor (ate 11 digitos): ");
    scanf(" %11s", lista[*qtd].eleitor.titulo);
    printf("Zona eleitoral: ");
    scanf("%d", &lista[*qtd].eleitor.zona);
    printf("Numero do candidato: ");
    scanf("%d", &lista[*qtd].numero_voto);

    (*qtd)++;
    return lista;
}

Cedula* recuperarVotos(const char *nomeArquivo, int *qtdRecuperada) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        *qtdRecuperada = 0;
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoBytes = ftell(arquivo);
    rewind(arquivo);

    *qtdRecuperada = tamanhoBytes / sizeof(Cedula);
    if (*qtdRecuperada == 0) {
        fclose(arquivo);
        return NULL;
    }

    Cedula *bloco = (Cedula *)malloc(tamanhoBytes);
    if (bloco == NULL) {
        fclose(arquivo);
        *qtdRecuperada = 0;
        return NULL;
    }

    fread(bloco, sizeof(Cedula), *qtdRecuperada, arquivo);
    fclose(arquivo);

    return bloco;
}

int main() {
    Cedula *cedulas = NULL;
    int qtdVotos = 0;
    int opcao;

    do {
        cedulas = adicionarVoto(cedulas, &qtdVotos);
        printf("Deseja registrar outro voto? (1 - Sim / 0 - Nao): ");
        scanf("%d", &opcao);
    } while (opcao == 1);

    FILE *arquivo = fopen("urnas.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo urnas.bin.\n");
        free(cedulas);
        return 1;
    }

    fwrite(cedulas, sizeof(Cedula), qtdVotos, arquivo);
    fclose(arquivo);
    free(cedulas);

    int totalLido = 0;
    Cedula *votosRecuperados = recuperarVotos("urnas.bin", &totalLido);

    if (votosRecuperados == NULL) {
        printf("\nErro ao recuperar votos ou arquivo vazio.\n");
        return 1;
    }

    printf("\n=== VOTOS RECUPERADOS DA URNA (%d) ===\n", totalLido);
    for (int i = 0; i < totalLido; i++) {
        printf("Titulo: %s | Zona: %d | Voto: %d\n",
               votosRecuperados[i].eleitor.titulo,
               votosRecuperados[i].eleitor.zona,
               votosRecuperados[i].numero_voto);
    }

    free(votosRecuperados);

    return 0;
}

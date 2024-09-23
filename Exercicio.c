// Para printf, scanf e fgets
#include <stdio.h>
// Para system (para limpar a tela)
#include <stdlib.h>
// Para strtok
#include <string.h>
// Para SetConsoleOutputCP
#include <windows.h>

// Tamanho maximo das cadeias de entrada
#define TAMANHO_CADEIA 100

// Definição de um funcionario
struct funcionario {
    char nome[TAMANHO_CADEIA];
    char setor[TAMANHO_CADEIA];
    float salario;
    float vale_transporte;
    float vale_alimentacao;
};

// Numero maximo de funcionarios
#define MAX_FUNCIONARIOS 100

// Vetor do tipo funcionario com capacidade MAX_FUNCIONARIOS
struct funcionario funcionarios[MAX_FUNCIONARIOS];
// Quantidade de funcionarios registrados, começando em 0 sempre
int quantidade_funcionarios = 0;

// Função de conveniencia para ler um e retornar inteiro
int ler_inteiro() {
    int n;
    scanf("%d", &n);
    fseek(stdin, 0, SEEK_END);
    return n;
}

// Função de conveniencia para ler e retornar um float
float ler_float() {
    float n;
    scanf("%f", &n);
    fseek(stdin, 0, SEEK_END);
    return n;
}

// Função de conveniencia para ler uma string e botar ela na string passada por argumento
void ler_texto(char* str) {
    fgets(str, TAMANHO_CADEIA, stdin);
    // Remove a quebra de linha que o fgets le
    strtok(str, "\n");
}

// Pega um funcionario por argumento e retorna o valor do inss
float inss_funcionario(struct funcionario fun) {
    if (fun.salario < 1302.0) {
        return 0.0;
    }
    if (fun.salario > 1302.0 && fun.salario < 2571.29) {
        return fun.salario * 0.075;
    }
    else if (fun.salario > 2571.29 && fun.salario < 3856.94) {
        return fun.salario * 0.9;
    }
    else if (fun.salario > 3856.94 && fun.salario < 7507.49) {
        return fun.salario * 0.12;
    }
    else {
        return fun.salario * 0.14;
    }
}

// Pega um funcionario por argumento e retorna o valor do irrf
float irrf_funcionario(struct funcionario fun) {
    if (fun.salario < 1903.98) {
        return 0.0;
    }
    else if (fun.salario > 1903.98 && fun.salario < 2826.65) {
        return fun.salario * 0.075 - 142.8;
    }
    else if (fun.salario > 2826.65 && fun.salario < 3751.05) {
        return fun.salario * 0.15 - 354.8;
    }
    else if (fun.salario > 3751.05 && fun.salario < 4664.68) {
        return fun.salario * 0.225 - 636.13;
    }
    else {
        return fun.salario * 0.275 - 869.36;
    }
}

// Pega um funcionario por argumento e retorna o total que vai ser reduzido do salario
float total_reducao(struct funcionario fun) {
    float total = 0.0;

    total += inss_funcionario(fun);
    total += irrf_funcionario(fun);
    total += fun.vale_alimentacao * 0.2;
    total += fun.vale_transporte * 0.06;

    return total;
}

// Pega um funcionario por argumento e retorna o valor do salario depois de todas as reduçoes
float salario_reduzido(struct funcionario fun) {
    return fun.salario - total_reducao(fun);
}

// Função para criar um novo funcionario
void novo_funcionario() {
    // Criar uma variavel do tipo funcionario chamada novo_funcionario
    struct funcionario novo_funcionario;

    printf("Digite o nome do funcionario: ");
    ler_texto(novo_funcionario.nome);

    printf("Digite o setor do funcionario: ");
    ler_texto(novo_funcionario.setor);

    printf("Digite o salario bruto do funcionario: ");
    novo_funcionario.salario = ler_float();

    printf("Digite o valor do vale transporte do funcionario: ");
    novo_funcionario.vale_transporte = ler_float();

    printf("Digite o valor do vale alimentacao do funcionario: ");
    novo_funcionario.vale_alimentacao = ler_float();

    // Coloca o funcionario no vetor
    funcionarios[quantidade_funcionarios] = novo_funcionario;
    // Aumenta a quantidade de funcionarios
    quantidade_funcionarios += 1;
}

void listar_funcionarios() {
    // Para i = 0 ate i = quantidade_funcionarios
    for (int i = 0; i < quantidade_funcionarios; i += 1) {
        // Pegue o funcionario na posição i
        struct funcionario fun = funcionarios[i];
        // Escreva o numero (i + 1), nome, setor, salario
        printf("%d - %s - %s - %f\n", i + 1, fun.nome, fun.setor, fun.salario);
    }
}

void menu_funcionario() {
    int opcao;
    do {
        printf("\n1 - Novo funcionario\n2 - Listar funcionarios\n0 - Voltar para menu principal\n");
        opcao = ler_inteiro();
        system("cls");
        switch (opcao) {
            case 1:
                novo_funcionario();
            break;
            case 2:
                listar_funcionarios();
            break;

            case 0:
                // Nada, so pra nao dar "opçao invalida" ao digitar 0 para sair
            break;
            default:
                printf("Opção invalida\n");
            break;
        }
    } while (opcao != 0);
}

void gastos_total() {
    float salario_bruto_total = 0.0;
    float inss_total = 0.0;
    float irrf_total = 0.0;

    for (int i = 0; i < quantidade_funcionarios; i++) {
        struct funcionario fun = funcionarios[i];
        salario_bruto_total += fun.salario;
        inss_total += inss_funcionario(fun);
        irrf_total += irrf_funcionario(fun);
    }

    printf("Salario bruto total: %.2f\n", salario_bruto_total);
    printf("INSS total: %.2f\n", inss_total);
    printf("IRFF total: %.2f\n", irrf_total);
}

void gasto_funcionario() {
    // Mostra todos os funcionarios para o usuario saber qual o numero dele
    listar_funcionarios();
    printf("Digite o numero do funcionario: ");
    int numero_funcionario = ler_inteiro();

    // Pega o funcionario na posição (transformando 1 -> 0, 2 -> 1)
    struct funcionario fun = funcionarios[numero_funcionario - 1];

    // Faz uma tabela bonitinha
    printf("Holerite de %s - %s\n", fun.nome, fun.setor);
    printf("------------------Proventos-----------------\n");
    printf("|%-20s|%10.2f|%10.2f|\n", "Salario Base", fun.salario, 0.0);
    printf("------------------Descontos-----------------\n");
    printf("|%-20s|%10s|%10s|\n", "", "Entrada", "Saida");
    printf("|%-20s|%10.2f|%10.2f|\n", "INSS", 0.0, inss_funcionario(fun));
    printf("|%-20s|%10.2f|%10.2f|\n", "IRRF", 0.0, irrf_funcionario(fun));
    printf("|%-20s|%10.2f|%10.2f|\n", "Vale transporte", 0.0, fun.vale_transporte * 0.06);
    printf("|%-20s|%10.2f|%10.2f|\n", "Vale alimentacao", 0.0, fun.vale_alimentacao * 0.20);
    printf("-------------------Resumo-------------------\n");
    printf("|%-20s|%10.2f|%10.2f|\n", "Total Reduzido", 0.0, total_reducao(fun));
    printf("|%-20s|%10.2f|%10.2f|\n", "Salario Reduzido", salario_reduzido(fun), 0.0);
}

void titulo() {
    printf("\
██╗  ██╗ ██████╗ ██╗     ███████╗██████╗ ██╗████████╗███████╗    ███████╗██╗  ██╗██████╗ ██████╗ ███████╗███████╗███████╗\n\
██║  ██║██╔═══██╗██║     ██╔════╝██╔══██╗██║╚══██╔══╝██╔════╝    ██╔════╝╚██╗██╔╝██╔══██╗██╔══██╗██╔════╝██╔════╝██╔════╝\n\
███████║██║   ██║██║     █████╗  ██████╔╝██║   ██║   █████╗      █████╗   ╚███╔╝ ██████╔╝██████╔╝█████╗  ███████╗███████╗\n\
██╔══██║██║   ██║██║     ██╔══╝  ██╔══██╗██║   ██║   ██╔══╝      ██╔══╝   ██╔██╗ ██╔═══╝ ██╔══██╗██╔══╝  ╚════██║╚════██║\n\
██║  ██║╚██████╔╝███████╗███████╗██║  ██║██║   ██║   ███████╗    ███████╗██╔╝ ██╗██║     ██║  ██║███████╗███████║███████║\n\
╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝╚═╝   ╚═╝   ╚══════╝    ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}

void sobre() {
    titulo();
    printf("Programa para holerite de funcionario\n");
    printf("Autores:\n");
    printf("\tp\n");
    printf("\tRafael\n");
    printf("\tDayane\n");
    printf("\tChat GPT\n");
}

void menu_gastos() {
    int opcao;
    do {
        printf("\n1 - Gastos total\n2 - Gastos de um funcionario\n0 - Voltar para menu principal\n");
        opcao = ler_inteiro();
        system("cls");
        switch (opcao) {
            case 1:
                gastos_total();
            break;
            case 2:
                gasto_funcionario();
            break;

            case 0:
                // Nada, so pra nao dar "opçao invalida" ao digitar 0 para sair
            break;
            default:
                printf("Opção invalida\n");
            break;
        }
    } while (opcao != 0);
}

void menu_principal() {
    int opcao;
    do {
        printf("\n1 - Funcionarios\n2 - Gastos\n3 - Sobre\n0 - Sair\n");
        opcao = ler_inteiro();
        system("cls");
        switch (opcao) {
            case 1:
                menu_funcionario();
            break;
            case 2:
                menu_gastos();
            break;
            case 3:
                sobre();
            break;

            case 0:
                exit(0);

            default:
                printf("Opção invalida\n");
            break;
        }
    } while (opcao != 0);
}

int main() {
    // Windows não suporta caracteres especias por padrao, essa funcao muda o modo do console para suportar
    SetConsoleOutputCP(65001);

    titulo();
    menu_principal();

    return 0;
}

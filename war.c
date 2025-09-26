#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 30
#define MAX 5

typedef struct {
    char nome[TAM];
    char corExercito[TAM];
    int tropas;
} Territorio;

typedef struct {
    char descricao[100];  // descrição da missão
    int concluida;        // 0 = não, 1 = sim
} Missao;

void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n=====================================\n");
    printf("         ESTADO ATUAL DO MAPA \n");
    printf("=====================================\n\n");

    for (int i = 0; i < qtd; i++) {
        printf("TERRITÓRIO %d\n", i + 1);
        printf("- Nome: %s\n", mapa[i].nome);
        printf("- Dominado por: Exército %s\n", mapa[i].corExercito);
        printf("- Tropas: %d\n", mapa[i].tropas);
        printf("-------------------------------------\n");
    }
}

void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf(" O território atacante precisa ter mais de 1 tropa para atacar!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n Dados sorteados!\n");
    printf("Atacante (%s - %s): %d\n", atacante->nome, atacante->corExercito, dadoAtacante);
    printf("Defensor  (%s - %s): %d\n", defensor->nome, defensor->corExercito, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        defensor->tropas--;
        printf(" atacante venceu! O defensor perdeu 1 tropa.\n");

        if (defensor->tropas <= 0) {
            printf(" O território %s foi conquistado pelo exército %s!\n",
                   defensor->nome, atacante->corExercito);
            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->tropas = 1;
            atacante->tropas--; // envia 1 tropa para ocupar
        }
    } else {
        atacante->tropas--;
        printf("🛡️ O defensor resistiu! O atacante perdeu 1 tropa.\n");
    }
}

void gerarMissoes(Missao *missoes, int qtd) {
    char lista[3][100] = {
        "Conquistar 2 territórios inimigos",
        "Ter pelo menos 10 tropas em um único território",
        "Dominar todos os territórios de uma mesma cor de exército"
    };

    for (int i = 0; i < qtd; i++) {
        strcpy(missoes[i].descricao, lista[i]);
        missoes[i].concluida = 0;
    }
}

void verificarMissoes(Missao *missoes, int qtd, Territorio *mapa, int tam) {
    for (int i = 0; i < qtd; i++) {
        if (missoes[i].concluida) continue;

        if (i == 0) {
            // Missão 1: conquistar 2 territórios (simulação simples: verifica se há 2 da mesma cor)
            char cor[TAM];
            int count = 0;
            strcpy(cor, mapa[0].corExercito);
            for (int j = 0; j < tam; j++) {
                if (strcmp(mapa[j].corExercito, cor) == 0) {
                    count++;
                }
            }
            if (count >= 2) missoes[i].concluida = 1;
        }
        else if (i == 1) {
            // Missão 2: ter 10 tropas em um território
            for (int j = 0; j < tam; j++) {
                if (mapa[j].tropas >= 10) {
                    missoes[i].concluida = 1;
                    break;
                }
            }
        }
        else if (i == 2) {
            // Missão 3: dominar todos os territórios de uma mesma cor
            int completo = 1;
            char cor[TAM];
            strcpy(cor, mapa[0].corExercito);
            for (int j = 0; j < tam; j++) {
                if (strcmp(mapa[j].corExercito, cor) != 0) {
                    completo = 0;
                    break;
                }
            }
            if (completo) missoes[i].concluida = 1;
        }
    }
}

void mostrarMissoes(Missao *missoes, int qtd) {
    printf("\n===== MISSÕES =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d) %s [%s]\n", i + 1, missoes[i].descricao,
               missoes[i].concluida ? "✔ Concluída" : "❌ Em andamento");
    }
    printf("===================\n");
}

int main() {
    srand(time(NULL));
    Territorio *mapa = (Territorio *) calloc(MAX, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    Missao missoes[3];
    gerarMissoes(missoes, 3);

    int opcao, cadastrado = 0;

    do {
        printf("\n==== MENU PRINCIPAL ====\n");
        printf("1. Cadastrar territórios\n");
        printf("2. Mostrar mapa\n");
        printf("3. Atacar território\n");
        printf("4. Ver missões\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                for (int i = 0; i < MAX; i++) {
                    printf("\n>>> Cadastro do Território %d <<<\n", i + 1);

                    printf("Nome: ");
                    fgets(mapa[i].nome, TAM, stdin);
                    mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

                    printf("Cor do Exército: ");
                    fgets(mapa[i].corExercito, TAM, stdin);
                    mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = 0;

                    printf("Número de Tropas: ");
                    scanf("%d", &mapa[i].tropas);
                    getchar();
                }
                cadastrado = 1;
                break;

            case 2:
                if (!cadastrado) printf(" Cadastre os territórios primeiro!\n");
                else exibirMapa(mapa, MAX);
                break;

            case 3:
                if (!cadastrado) {
                    printf(" Cadastre os territórios primeiro!\n");
                    break;
                }
                int a, d;
                exibirMapa(mapa, MAX);
                printf("Digite o número do território atacante: ");
                scanf("%d", &a);
                printf("Digite o número do território defensor: ");
                scanf("%d", &d);

                if (a < 1 || a > MAX || d < 1 || d > MAX || a == d) {
                    printf("Escolha inválida!\n");
                    break;
                }

                atacar(&mapa[a - 1], &mapa[d - 1]);
                verificarMissoes(missoes, 3, mapa, MAX);
                break;

            case 4:
                mostrarMissoes(missoes, 3);
                break;

            case 0:
                printf("Jogo encerrado. Até a próxima!\n");
                break;

            default:
                printf(" Opção inválida!\n");
        }

    } while (opcao != 0);

    free(mapa);
    return 0;
}







// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.




// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

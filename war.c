#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX 5   // número fixo de territórios
#define TAM 30  // tamanho máximo para as strings (nome e cor do exército)

// Definição da estrutura "Territorio"
typedef struct {
    char nome[TAM];        // Nome do território
    char corExercito[TAM]; // Cor do exército que domina
    int tropas;            // Número de tropas no território
} Territorio;


//funçao para exibir estado atual do mapa


void exibirMapa(Territorio *mapa, int qtd) {
    printf("=====================================\n");
    printf("      ESTADO ATUAL DO MAPA \n");
    printf("=====================================\n\n");

    for (int i = 0; i < qtd; i++) {
        printf("TERRITORIO %d\n", i + 1);
        printf(" - Nome: %s\n", mapa[i].nome);
        printf(" - Dominado por: Exercito %s\n", mapa[i].corExercito);
        printf(" Tropas: %d \n", mapa[i].tropas);
        printf("---------------------------------------------\n");
    }
}
 // funçao para simular um ataque entre dois territorios

 void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand () % 6 - 1; //valor entre 1 e 6
    int dadoDefensor = rand () % 6 - 1;

    printf("\n Dados sorteados!\n");
    printf("Atacante (%s - %s): %d\n", atacante->nome, atacante->corExercito, dadoAtacante);
    printf("Defensor (%s - %s): %d\n", defensor->nome, defensor->corExercito, dadoDefensor);

    if (dadoAtacante >= dadoDefensor)



 }




int main() {
    Territorio mapa[MAX]; // Vetor estático de 5 territórios

    // Mensagem inicial do jogo
    printf("=====================================\n");
    printf("      Bem-vindos ao Jogo de Guerra \n");
    printf("=====================================\n\n");

    printf("Vamos cadastrar os territórios!\n");

    // Loop para cadastrar os 5 territórios
    for (int i = 0; i < MAX; i++) {
        printf("\n>>> Cadastro do Território %d <<<\n", i + 1);

        // Lê o nome do território
        printf("Nome: ");
        fgets(mapa[i].nome, TAM, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; // remove o "\n" do final

        // Lê a cor do exército
        printf("Cor do Exército: ");
        fgets(mapa[i].corExercito, TAM, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = 0;

        // Lê o número de tropas
        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // consome o "\n" que sobra do scanf
    }

    // Exibição final formatada do estado atual do mapa
    printf("\n=====================================\n");
    printf("         ESTADO ATUAL DO MAPA \n");
    printf("=====================================\n\n");

    // Loop para mostrar cada território cadastrado
    for (int i = 0; i < MAX; i++) {
        printf("TERRITÓRIO %d\n", i + 1);
        printf("- Nome: %s\n", mapa[i].nome);
        printf("- Dominado por: Exército %s\n", mapa[i].corExercito);
        printf("- Tropas: %d\n", mapa[i].tropas);
        printf("-------------------------------------\n");
    }

    return 0; // fim do programa



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
int main() {
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

    return 0;
}

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

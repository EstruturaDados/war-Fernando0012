// ================================================
// Desafio WAR com linguagem C
// Nivel do desafio mestre
//
// Objetivo:
// Implementa as missões
//=====================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

//-- Contantes Globais --
#define MAX_TERRITORIOS 5
#define TAM_STRINGS 100
#define MAX_MISSOES 6

// -- Definição da struct dos territorios
typedef struct{
    char nome[TAM_STRINGS];
    char cor[TAM_STRINGS];
    int numeroDeTropas;
}Territorio;

typedef struct{
    char descricao[TAM_STRINGS];
    int tipo; //1: Conquistar X Territorios, 2: Destruir exercito de uma cor
    char alvo[TAM_STRINGS]; // Armazena o alvo para missoes de destruicao
}Missao;


// Prototipos das Funções
// Funções de setup e gerenciamento de memória:
Territorio* alocarMapa();
void inicializarTerritorios(Territorio *mapa);
void liberarMemoria(Territorio *mapa);

// Funções de interface com usuário:
void exibirMenuPrincipal();
void exibirMapa(const Territorio *mapa, int totalTerritorios);
void exibirMissao(const Missao *missoes, int missaoID);

//Funções de lógica principal do jogo:
void faseDeAtaque(Territorio *mapa);
int simularAtaque(Territorio *atacante, Territorio *defensor);
int sortearMissao();
int verificarVitoria(const Territorio *mapa, int missaoID, const char *corJogador);

//Função utilitária
void limparBufferEntrada();
int rolagemDeDados();

// Funções Principal (main)
int main(){
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    Territorio *mapa = alocarMapa();
    if (mapa == NULL){
        return 1;
    }

    inicializarTerritorios(mapa);

    Missao missoes[MAX_MISSOES];
    strcpy(missoes[0].descricao, "Conquiste 3 territorios.");
    missoes[0].tipo = 1;

    // Usando sprintf para formatar a string de missao corretamente
    sprintf(missoes[1].descricao, "Destrua o exercito da cor AZUL.");
    missoes[1].tipo = 2;
    strcpy(missoes[1].alvo, "Azul");

    sprintf(missoes[2].descricao, "Destrua o exercito da cor MARROM.");
    missoes[2].tipo = 2;
    strcpy(missoes[2].alvo, "Marrom");

    sprintf(missoes[3].descricao, "Destrua o exercito da cor VERDE.");
    missoes[3].tipo = 2;
    strcpy(missoes[3].alvo, "Verde");

    sprintf(missoes[4].descricao, "Destrua o exercito da cor VERMELHO.");
    missoes[4].tipo = 2;
    strcpy(missoes[4].alvo, "Vermelho");
    
    // Removido a missao[5] para evitar acesso invalido à memoria

    const char *corJogador = "Branco";
    int missaoAtualID = sortearMissao();
    int opcao;
    int vitoria = 0;

    do{
        system("clear"); // Use "cls" para Windows
        exibirMapa(mapa, MAX_TERRITORIOS);
        exibirMissao(missoes, missaoAtualID);
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao){
            case 1:
                faseDeAtaque(mapa);
                break;

            case 2:
                vitoria = verificarVitoria(mapa, missaoAtualID, corJogador);
                if(vitoria){
                    printf("\nParabens! Você completou sua missao e venceu o jogo!\n");
                    opcao = 0;
                } else{
                    printf("\nMissao ainda nao cumprida. Continue lutando!\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            
            case 0:
                printf("\nSaindo do Jogo...\n");
                break;
                
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
        }
    } while(opcao != 0);

    liberarMemoria(mapa);
    return 0;
}

// -- Implementação das Funções --
Territorio* alocarMapa(){
    Territorio *mapa = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL){
        printf("Erro: Falha ao alocar memoria.\n");
    }
    return mapa;
}

void inicializarTerritorios(Territorio *mapa){
    // Definindo os territorios do jogo
    strcpy(mapa[0].nome,"Franca");
    strcpy(mapa[0].cor,"Branco");
    mapa[0].numeroDeTropas = 3;

    strcpy(mapa[1].nome,"Estados Unidos");
    strcpy(mapa[1].cor,"Azul");
    mapa[1].numeroDeTropas = 4;

    strcpy(mapa[2].nome,"Africa");
    strcpy(mapa[2].cor,"Marrom");
    mapa[2].numeroDeTropas = 3;

    strcpy(mapa[3].nome,"Brasil");
    strcpy(mapa[3].cor,"Verde");
    mapa[3].numeroDeTropas = 5;

    strcpy(mapa[4].nome,"Japao");
    strcpy(mapa[4].cor,"Vermelho");
    mapa[4].numeroDeTropas = 4;
}

void liberarMemoria(Territorio *mapa){
    free(mapa);
    printf("Memoria liberada com sucesso.\n");
}

void exibirMenuPrincipal(){
    printf("\n==================================\n");
    printf("           MENU DE ACOES\n");
    printf("==================================\n");
    printf("1. Atacar\n");
    printf("2. Verificar Missao\n");
    printf("0. Sair\n");
    printf("----------------------------------\n");
    printf("Escolha uma opcao: ");
}

void exibirMapa(const Territorio *mapa, int totalTerritorios){
    printf("========== MAPA DO MUNDO ==========\n");
    for(int i = 0; i < totalTerritorios; i++){
        printf("%d. %s | Dono: %s | Tropas: %d\n",
            i + 1, mapa[i].nome, mapa[i].cor, mapa[i].numeroDeTropas);
    }
    printf("===================================\n");
}

void exibirMissao(const Missao *missoes, int missaoID){
    printf("\n>>> Sua Missao secreta: %s <<<\n", missoes[missaoID].descricao);
}

void faseDeAtaque(Territorio *mapa){
    int atacanteID, defensorID;

    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Selecione o territorio Atacante (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &atacanteID);
    limparBufferEntrada();

    printf("Selecione o territorio Defensor (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &defensorID);
    limparBufferEntrada();

    int atacanteIndex = atacanteID - 1;
    int defensorIndex = defensorID - 1;

    // Validação
    if(atacanteIndex < 0 || atacanteIndex >= MAX_TERRITORIOS ||
       defensorIndex < 0 || defensorIndex >= MAX_TERRITORIOS){
        printf("\nOpcao de territorio invalida.\n");
        return;
    }
    if(atacanteIndex == defensorIndex){
        printf("\nNao e possivel atacar seu proprio territorio!\n");
        return;
    }
    if(strcmp(mapa[atacanteIndex].cor, mapa[defensorIndex].cor) == 0){
        printf("\nNao e possivel atacar um territorio da mesma cor!\n");
        return;
    }
    if(mapa[atacanteIndex].numeroDeTropas <= 1){
        printf("\nTerritorio atacante deve ter pelo menos 2 tropas.\n");
        return;
    }

    simularAtaque(&mapa[atacanteIndex], &mapa[defensorIndex]);
}

int simularAtaque(Territorio *atacante, Territorio *defensor){
    int dadoAtacante = rolagemDeDados();
    int dadoDefensor = rolagemDeDados();

    printf("\n>>> Batalha entre %s (tropas: %d) e %s (Tropas: %d) <<<\n", 
            atacante->nome, atacante->numeroDeTropas,
            defensor->nome, defensor->numeroDeTropas);
        
    printf("Resultados dos dados: Atacante tirou %d, Defensor tirou %d.\n", dadoAtacante, dadoDefensor);

    if(dadoAtacante > dadoDefensor){
        printf("\n>>> Ataque Bem-Sucedido! Defensor perdeu uma Tropa. <<<\n");
        defensor->numeroDeTropas--;
        if(defensor->numeroDeTropas == 0){
            printf("\n>>> Territorio Conquistado! <<<\n");
            strcpy(defensor->cor, atacante->cor);
            defensor->numeroDeTropas = 1; // Atacante move uma tropa para o novo territorio
            atacante->numeroDeTropas--;
            return 1; // Retorna 1 para indicar que houve conquista
        }
    } else {
        printf("\n>>> Ataque Falhou! Atacante perdeu uma tropa. <<<\n");
        atacante->numeroDeTropas--;
        defensor->numeroDeTropas++;
    }
    return 0;
}

int sortearMissao(){
    return rand() % MAX_MISSOES;
}

int verificarVitoria(const Territorio *mapa, int missaoID, const char *corJogador){
    if(missaoID == 0){
        // Missao 1: Conquistar 3 territorios
        int territoriosConquistados = 0;
        for(int i = 0; i < MAX_TERRITORIOS; i++){
            if(strcmp(mapa[i].cor, corJogador) == 0){
                territoriosConquistados++;
            }
        }    
        return territoriosConquistados >= 3;
    } else {
        // Missoes de 2 a 5: Destruir exercito de uma cor
        const char *alvoCor = (missaoID == 1) ? "Azul" :
                              (missaoID == 2) ? "Marrom" :
                              (missaoID == 3) ? "Verde" : "Vermelho";
        
        int exercitoEliminado = 1;
        for(int i = 0; i < MAX_TERRITORIOS; i++){
            if(strcmp(mapa[i].cor, alvoCor) == 0){
                exercitoEliminado = 0;
                break;
            }
        }
        return exercitoEliminado;
    }
    return 0;
}

void limparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int rolagemDeDados(){
    return rand() % 6 + 1; // Retorna um número entre 1 e 6
}
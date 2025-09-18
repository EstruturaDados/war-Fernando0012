// =====================================
//  Desafio WAR com linguagem C
//  Nível do desafio Aventureiro
//
//  Objetivo:
//  Implementar o cadastro e a listagem de territórios
//  para o jogo WAR, com menu interativo.
//
// ===========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessario para a semente de numeros aleatorios

// -- Constantes Globais --
#define MAX_TERRITORIOS 5
#define TAM_STRINGS 100

// -- Definição da struct dos territorios
typedef struct {
    char nome[TAM_STRINGS];
    char cor[TAM_STRINGS];
    int numeroDeTropas;
} territorio;


// -- Função para limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

int rolagemDeDados(){
    return rand() % 10;
}

//-- Função de ataque 
void ataque(territorio *mapa,int totalTerritorio){

    int indiceAtacante, indiceDefesor;

    printf("----- Fase de Ataque ----\n");
    printf("Escolha o territorio atacante (1 a %d): ", totalTerritorio);
    scanf("%d", &indiceAtacante);
    limparBufferEntrada();

    //Verifique se o indice é válido (1 a 5, não 0 a N-1)
    if (indiceAtacante < 1 || indiceAtacante > totalTerritorio){
        printf("Escolha de territorio atacante invalida.\n");
        return;
    }

    printf("Escolha o territorio defensor (1 a %d): ",totalTerritorio);
    scanf("%d", &indiceDefesor);
    limparBufferEntrada();

    //Verifique se o indice é valido
    if (indiceDefesor < 1 || indiceDefesor > totalTerritorio){
        printf("Escolha de territorio defensor invalida.\n");
        return;
    }

    //Assegure que os territorios não são o mesmo
    if (indiceAtacante == indiceDefesor){
        printf("O atacante e o defensor nao podem ser o mesmo territorio!\n");
        return;
    }

    //Obtenha os ponteiros para os territorios escolhidos
    territorio* atacante = &mapa[indiceAtacante - 1];
    territorio* defensor = &mapa[indiceDefesor - 1];

    //Agora, com os ponteiros corretos, você pode implementar a lógica do ataque 
    printf("Territorio atacante: %s (%d tropas)\n", atacante->nome, atacante->numeroDeTropas);
    printf("Territorio defensor: %s (%d tropas)\n", defensor->nome, defensor->numeroDeTropas);

    // sorteio numerico do atacante
    int dadoAtacante = rolagemDeDados();

    // sorteio numerico do defensor
    int dadoDefensor = rolagemDeDados();

    if(dadoAtacante > dadoDefensor){
        printf("\nAtaque bem sucedido, %s venceu, %s perdeu uma tropa", atacante->nome, defensor->nome);
        printf("\nNumero do atacante: %d", dadoAtacante);
        printf("\nNumero do defensor: %d", dadoDefensor);
        defensor->numeroDeTropas--;
        atacante->numeroDeTropas++;
        return;
    } else{
        printf("\nO ataque FALHOU, %s venceu, %s perdeu uma tropa", defensor->nome, atacante->nome);
        printf("\nNumero do atacante: %d", dadoAtacante);
        printf("\nNumero do defensor: %d", dadoDefensor);
        atacante->numeroDeTropas--;
        defensor->numeroDeTropas++;

        return;
    }

    return;
}

int main(){
    territorio* t = (territorio*)malloc(MAX_TERRITORIOS * sizeof(territorio));
    if(t == NULL){
        printf("Erro ao alocar memoria. Saindo. \n");
        return 1;
    }
    int totalTerritorio = 0;
    int opcao;

    // --- Laço do menu --
    do
    {
        //Exibe o menu de opções
        printf("==========================================\n");
        printf("             TERRITORIO      \n");
        printf("===========================================\n");
        printf("1 - Cadastrar Territorios \n");
        printf("2 - Listar territorio \n");
        printf("0 - Sair\n");
        printf("-------------------------------------------\n");
        printf("Escolha uma opcao: ");

        // Lê a opcao do usuario
        scanf("%d", &opcao);
        limparBufferEntrada();

        // ---- Processamento da Opcao
        switch (opcao)
        {
            case 1:
                printf("---- Cadastro de Territorio ----\n\n");

                if (totalTerritorio < MAX_TERRITORIOS){
                    printf("Digite o nome do Territorio: ");
                    fgets(t[totalTerritorio].nome, TAM_STRINGS, stdin);
                    t[totalTerritorio].nome[strcspn(t[totalTerritorio].nome, "\n")] = '\0';

                    printf("Digite a Cor: ");
                    fgets(t[totalTerritorio].cor, TAM_STRINGS, stdin);
                    t[totalTerritorio].nome[strcspn(t[totalTerritorio].cor, "\n")] = '\0';

                    printf("Numero de Tropas: ");
                    scanf("%d", &t[totalTerritorio].numeroDeTropas);
                    limparBufferEntrada();

                    totalTerritorio++;
                    printf("\nTerritorio cadastrado com sucesso!");
                }else {
                    printf("Limite de territorios chegou no limite");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 2: //Listagem de Territorio
                printf("--- Lista de Territorios -- \n\n");

                if(totalTerritorio == 0){
                    printf("Nenhum territorio cadastro ainda. \n");
                } else{
                    for (int i = 0; i < totalTerritorio; i++){
                        printf("=========================================\n");
                        printf("Territorio %d\n", i + 1);
                        printf("Nome: %s\n", t[i].nome);
                        printf("Cor: %s\n", t[i].cor);
                        printf("Numero de Tropas: %d\n", t[i].numeroDeTropas);
                    }
                    printf("=================================================\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 4: 
                ataque(t, totalTerritorio);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            
            case 0: //Sair
                printf("\nSaindo do sistema... \n");
                break;
            
            default: //opção invalida
                printf("\nOpcao invalida! Tente novamente. \n");
                printf("\nPressione Enter para continuar... \n");
                break;
        };

    } while (opcao != 0);

        //Libera a memoria alocada dinamicamente
        free(t);
        return 0;
    
}

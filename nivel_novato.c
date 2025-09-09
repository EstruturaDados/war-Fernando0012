// =====================================
//  Desafio WAR com linguagem C
//  Nível do desafio Novato
//
//  Objetivo:
//  Implementar o cadastro e a listagem de territórios
//  para o jogo WAR, com menu interativo.
//
// ===========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -- Constantes Globais --
#define MAX_TERRITORIOS 5
#define TAM_STRINGS 100

// -- Definição da struct dos territorios
struct territorio {
    char nome[TAM_STRINGS];
    char cor[TAM_STRINGS];
    int numeroDeTropas;
};

// -- Função para limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

int main(){
    struct territorio t [MAX_TERRITORIOS];
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
            
            case 0: //Sair
                printf("\nSaindo do sistema... \n");
                break;
            
            default: //opção invalida
                printf("\nOpcao invalida! Tente novamente. \n");
                printf("\nPressione Enter para continuar... \n");
                break;
        };

    } while (opcao != 0);
        return 0;
    
}

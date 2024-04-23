#include "store.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern User* users;
extern Item* items;

int main() {
    printf("Bem-vindo a Ze Neto Moda!\n");
    printf("Encontre as melhores roupas importadas aqui.\n\n");

    // Adicionando itens de exemplo à lista encadeada de itens
    Item* newItem1 = (Item*)malloc(sizeof(Item));
    newItem1->id = 1;
    strcpy(newItem1->name, "Camisa Polo");
    newItem1->price = 120.0;
    newItem1->quantity = 20;
    newItem1->next = NULL;
    addItemToList(&items, newItem1);

    Item* newItem2 = (Item*)malloc(sizeof(Item));
    newItem2->id = 2;
    strcpy(newItem2->name, "Calca Jeans");
    newItem2->price = 150.0;
    newItem2->quantity = 15;
    newItem2->next = NULL;
    addItemToList(&items, newItem2);

    Item* newItem3 = (Item*)malloc(sizeof(Item));
    newItem3->id = 3;
    strcpy(newItem3->name, "Vestido Longo");
    newItem3->price = 200.0;
    newItem3->quantity = 10;
    newItem3->next = NULL;
    addItemToList(&items, newItem3);

    Item* newItem4 = (Item*)malloc(sizeof(Item));
    newItem4->id = 4;
    strcpy(newItem4->name, "Bone Adidas Preto e Branco");
    newItem4->price = 50.0;
    newItem4->quantity = 10;
    newItem4->next = NULL;
    addItemToList(&items, newItem4);

    Item* newItem5 = (Item*)malloc(sizeof(Item));
    newItem5->id = 5;
    strcpy(newItem5->name, "Bone Nike Preto");
    newItem5->price = 50.0;
    newItem5->quantity = 15;
    newItem5->next = NULL;
    addItemToList(&items, newItem5);

    Item* newItem6 = (Item*)malloc(sizeof(Item));
    newItem6->id = 6;
    strcpy(newItem6->name, "Camisa Oversized");
    newItem6->price = 120.0;
    newItem6->quantity = 10;
    newItem6->next = NULL;
    addItemToList(&items, newItem6);

    Item* newItem7 = (Item*)malloc(sizeof(Item));
    newItem7->id = 7;
    strcpy(newItem7->name, "Short Dry Fit");
    newItem7->price = 75.0;
    newItem7->quantity = 10;
    newItem7->next = NULL;
    addItemToList(&items, newItem7);

    int choice;
    while (1) {
        printf("\n===== Menu Principal =====\n");
        printf("1. Login\n");
        printf("2. Registrar\n");
        printf("3. Esqueceu a Senha ou Email\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("Por favor, entre em contato com o suporte para recuperar sua senha ou email.\n");
                break;
            case 4:
                printf("Saindo do programa. Obrigado!\n");
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
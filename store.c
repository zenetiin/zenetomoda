#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"

User* users = NULL;
Item* items = NULL;

void addUserToList(User** userList, User* newUser) {
    if (*userList == NULL) {
        *userList = newUser;
    } else {
        User* current = *userList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newUser;
    }
}

void addItemToList(Item** itemList, Item* newItem) {
    if (*itemList == NULL) {
        *itemList = newItem;
    } else {
        Item* current = *itemList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newItem;
    }
}

int compareItemsByPrice(const void* a, const void* b) {
    const Item* itemA = *(const Item**)a;
    const Item* itemB = *(const Item**)b;
    return (itemA->price - itemB->price);
}

void sortItemsByPrice(Item** itemList) {
    int numItems = 0;
    Item* current = *itemList;
    // Contar o número de itens
    while (current != NULL) {
        numItems++;
        current = current->next;
    }
    // Criar um array de ponteiros para itens
    Item* itemsArray[numItems];
    current = *itemList;
    for (int i = 0; i < numItems; i++) {
        itemsArray[i] = current;
        current = current->next;
    }
    // Ordenar o array de itens
    qsort(itemsArray, numItems, sizeof(Item*), compareItemsByPrice);
    // Reconstruir a lista encadeada com os itens ordenados
    *itemList = itemsArray[0];
    current = *itemList;
    for (int i = 1; i < numItems; i++) {
        current->next = itemsArray[i];
        current = current->next;
    }
    current->next = NULL;
}

bool isEmailDuplicate(char *email) {
    User* current = users;
    while (current != NULL) {
        if (strcmp(current->username, email) == 0)
            return true;
        current = current->next;
    }
    return false;
}

bool isOver18(char *birthdate) {
    // Implementação simples para verificar se o usuário tem mais de 18 anos
    // Vamos supor que o formato de data de nascimento seja DD/MM/AAAA
    int birthYear;
    sscanf(birthdate + 6, "%d", &birthYear);
    return 2024 - birthYear >= 18;
}

void registerUser() {
    char name[MAX_ITEM_NAME_LENGTH];
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char birthdate[DATE_LENGTH];

    printf("Digite seu nome: ");
    scanf("%s", name);

    printf("Digite seu email: ");
    scanf("%s", username);
    while (isEmailDuplicate(username)) {
        printf("Email ja cadastrado. Tente novamente: ");
        scanf("%s", username);
    }

    printf("Digite sua senha: ");
    scanf("%s", password);

    printf("Digite sua data de nascimento (DD/MM/AAAA): ");
    scanf("%s", birthdate);
    while (!isOver18(birthdate)) {
        printf("Voce precisa ser maior de 18 anos para se registrar. Por favor, insira uma data de nascimento valida (DD/MM/AAAA): ");
        scanf("%s", birthdate);
    }

    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->name, name);
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    strcpy(newUser->birthdate, birthdate);
    newUser->valid = true;
    newUser->next = NULL;

    addUserToList(&users, newUser);

    printf("Usuario cadastrado com sucesso!\n");
}

void login() {
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    bool valid_user = false;
    printf("Digite seu email: ");
    scanf("%s", username);
    printf("Digite sua senha: ");
    scanf("%s", password);
    User* current = users;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            valid_user = true;
            break;
        }
        current = current->next;
    }
    if (valid_user) {
        printf("Login realizado com sucesso!\n");
        listItems(); // Mostrar a lista de itens após o login
    } else
        printf("Usuario ou senha invalidos.\n");
}
void listItems() {
    printf("Itens em Promocao:\n");
    Item* current = items;
    while (current != NULL) {
        if (current->price < 100) {  // Considerando que os itens com preco abaixo de R$ 100 estão em promocao
            printf("ID: %d | Nome: %s | Preco: R$ %.2f | Quantidade: %d\n", current->id, current->name, current->price, current->quantity);
        }
        current = current->next;
    }
    printf("\nOutros Itens Disponiveis:\n");
    current = items;
    while (current != NULL) {
        if (current->price >= 100) {  // Itens com preco acima ou igual a R$ 100
            printf("ID: %d | Nome: %s | Preco: R$ %.2f | Quantidade: %d\n", current->id, current->name, current->price, current->quantity);
        }
        current = current->next;
    }
    
    // Adicionando opções adicionais após o login
    printf("\n===== Opcoes Adicionais =====\n");
    printf("1. Listar Preco de um Item\n");
    printf("2. Listar Quantidade de um Item\n");
    printf("3. Editar um Item\n");
    printf("4. Excluir um Item\n");
    printf("5. Adicionar Item no Carrinho\n");
    printf("6. Finalizar Compra\n");
    printf("7. Sair\n");
    
    int choice;
    printf("Escolha uma opcao: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            listPrice();
            break;
        case 2:
            listQuantity();
            break;
        case 3:
            editItem();
            break;
        case 4:
            deleteItem();
            break;
        case 5:
            addToCart();
            break;
        case 6:
            checkout();
            break;
        case 7:
            printf("Saindo do programa. Obrigado!\n");
            exit(0);
        default:
            printf("Opcao invalida. Tente novamente.\n");
    }
}

void listPrice() {
    int itemId;
    printf("Digite o ID do item que deseja verificar o preco: ");
    scanf("%d", &itemId);
    Item* current = items;
    while (current != NULL) {
        if (current->id == itemId) {
            printf("O preco do item %s eh R$ %.2f\n", current->name, current->price);
            return;
        }
        current = current->next;
    }
    printf("Item nao encontrado.\n");
}
void listQuantity() {
    int itemId;
    printf("Digite o ID do item que deseja verificar a quantidade: ");
    scanf("%d", &itemId);
    Item* current = items;
    while (current != NULL) {
        if (current->id == itemId) {
            printf("A quantidade disponivel do item %s eh %d\n", current->name, current->quantity);
            return;
        }
        current = current->next;
    }
    printf("Item nao encontrado.\n");
}

void editItem() {
    int itemId;
    printf("Digite o ID do item que deseja editar: ");
    scanf("%d", &itemId);
    Item* current = items;
    while (current != NULL) {
        if (current->id == itemId) {
            printf("Digite o novo nome do item: ");
            scanf("%s", current->name);
            printf("Digite o novo preco do item: ");
            scanf("%f", &current->price);
            printf("Digite a nova quantidade do item: ");
            scanf("%d", &current->quantity);
            printf("Item editado com sucesso.\n");
            return;
        }
        current = current->next;
    }
    printf("Item nao encontrado.\n");
}

void deleteItem() {
    int itemId;
    printf("Digite o ID do item que deseja excluir: ");
    scanf("%d", &itemId);
    Item* prev = NULL;
    Item* current = items;
    while (current != NULL) {
        if (current->id == itemId) {
            if (prev == NULL) {
                items = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Item excluido com sucesso.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Item nao encontrado.\n");
}

void addToCart() {
    int itemId, quantity;
    printf("Digite o ID do item que deseja adicionar ao carrinho: ");
    scanf("%d", &itemId);
    printf("Digite a quantidade desejada: ");
    scanf("%d", &quantity);

    Item* current = items;
    while (current != NULL) {
        if (current->id == itemId) {
            if (current->quantity >= quantity) {
                // Adicionar item ao carrinho (implementação específica depende da estrutura do carrinho)
                printf("Item adicionado ao carrinho com sucesso.\n");
            } else {
                printf("Quantidade insuficiente em estoque.\n");
            }
            return;
        }
        current = current->next;
    }
    printf("Item nao encontrado.\n");
}

void checkout() {
    // Implementação específica da finalização da compra (depende da estrutura do carrinho)
    printf("Compra finalizada. Obrigado por comprar na Ze Neto Moda!\n");
}

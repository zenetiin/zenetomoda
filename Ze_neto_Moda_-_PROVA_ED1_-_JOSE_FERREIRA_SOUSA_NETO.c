#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 80
#define MAX_PASSWORD_LENGTH 20
#define MAX_ITEM_NAME_LENGTH 50
#define DATE_LENGTH 11 // formato: DD/MM/AAAA

// Estrutura para armazenar informações do usuário
typedef struct User {
    char name[MAX_ITEM_NAME_LENGTH];
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char birthdate[DATE_LENGTH];
    bool valid;
    struct User* next; // Ponteiro para o próximo usuário na lista
} User;

// Estrutura para armazenar informações do item (roupa)
typedef struct Item {
    int id;
    char name[MAX_ITEM_NAME_LENGTH];
    float price;
    int quantity;
    struct Item* next; // Ponteiro para o próximo item na lista
} Item;

User* users = NULL; // Lista encadeada de usuários
Item* items = NULL; // Lista encadeada de itens

// Função para adicionar um usuário à lista encadeada de usuários
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

// Função para adicionar um item à lista encadeada de itens
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

// Função para comparar dois itens por preço (para ser usada na ordenação)
int compareItemsByPrice(const void* a, const void* b) {
    const Item* itemA = *(const Item**)a;
    const Item* itemB = *(const Item**)b;
    return (itemA->price - itemB->price);
}

// Função para ordenar os itens por preço
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

// Função para verificar se o email já está cadastrado
bool isEmailDuplicate(char *email) {
    User* current = users;
    while (current != NULL) {
        if (strcmp(current->username, email) == 0)
            return true;
        current = current->next;
    }
    return false;
}

// Função para verificar se o usuário tem mais de 18 anos
bool isOver18(char *birthdate) {
    // Implementação simples para verificar se o usuário tem mais de 18 anos
    // Vamos supor que o formato de data de nascimento seja DD/MM/AAAA
    int birthYear;
    sscanf(birthdate + 6, "%d", &birthYear);
    return 2024 - birthYear >= 18;
}

// Função para realizar o registro de um novo usuário
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

// Função para realizar o login
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

// Função para listar os itens disponíveis
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

// Função para listar o preço de um item
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

// Função para listar a quantidade de um item
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

// Função para editar um item
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

// Função para excluir um item
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

// Função para adicionar um item ao carrinho de compras
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

// Função para finalizar a compra
void checkout() {
    // Implementação específica da finalização da compra (depende da estrutura do carrinho)
    printf("Compra finalizada. Obrigado por comprar na Ze Neto Moda!\n");
}

// Função principal
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

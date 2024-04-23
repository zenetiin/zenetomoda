#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_EMAIL_LENGTH 80
#define MAX_PASSWORD_LENGTH 20
#define MAX_ITEMS 100
#define MAX_ITEM_NAME_LENGTH 50
#define DATE_LENGTH 11 // formato: DD/MM/AAAA

// Estrutura para armazenar informações do usuário
typedef struct {
    char name[MAX_ITEM_NAME_LENGTH];
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char birthdate[DATE_LENGTH];
    bool valid;
} User;

// Estrutura para armazenar informações do item (roupa)
typedef struct {
    int id;
    char name[MAX_ITEM_NAME_LENGTH];
    float price;
    int quantity;
} Item;

User users[MAX_USERS];
Item items[MAX_ITEMS];
Item cart[MAX_ITEMS]; // Carrinho de compras
int num_users = 0;
int num_items = 0;
int num_cart_items = 0;
bool isLoggedIn = false; // Variável para controlar o estado de login

// Função para verificar se o email já está cadastrado
bool isEmailDuplicate(char *email) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, email) == 0)
            return true;
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

    strcpy(users[num_users].name, name);
    strcpy(users[num_users].username, username);
    strcpy(users[num_users].password, password);
    strcpy(users[num_users].birthdate, birthdate);
    users[num_users].valid = true;
    num_users++;
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
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            valid_user = true;
            break;
        }
    }
    if (valid_user) {
        printf("Login realizado com sucesso!\n");
        isLoggedIn = true;
        listItems(); // Mostrar a lista de itens após o login
    } else
        printf("Usuario ou senha invalidos.\n");
}

// Função para listar os itens disponíveis
void listItems() {
    printf("Itens em Promocao:\n");
    for (int i = 0; i < num_items; i++) {
        if (items[i].price < 100) {  // Considerando que os itens com preco abaixo de R$ 100 estão em promocao
            printf("ID: %d | Nome: %s | Preco: R$ %.2f | Quantidade: %d\n", items[i].id, items[i].name, items[i].price, items[i].quantity);
        }
    }
    printf("\nOutros Itens Disponiveis:\n");
    for (int i = 0; i < num_items; i++) {
        if (items[i].price >= 100) {  // Itens com preco acima ou igual a R$ 100
            printf("ID: %d | Nome: %s | Preco: R$ %.2f | Quantidade: %d\n", items[i].id, items[i].name, items[i].price, items[i].quantity);
        }
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
    for (int i = 0; i < num_items; i++) {
        if (items[i].id == itemId) {
            printf("O preco do item %s eh R$ %.2f\n", items[i].name, items[i].price);
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

// Função para listar a quantidade de um item
void listQuantity() {
    int itemId;
    printf("Digite o ID do item que deseja verificar a quantidade: ");
    scanf("%d", &itemId);
    for (int i = 0; i < num_items; i++) {
        if (items[i].id == itemId) {
            printf("A quantidade disponivel do item %s eh %d\n", items[i].name, items[i].quantity);
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

// Função para editar um item
void editItem() {
    int itemId;
    printf("Digite o ID do item que deseja editar: ");
    scanf("%d", &itemId);
    for (int i = 0; i < num_items; i++) {
        if (items[i].id == itemId) {
            printf("Digite o novo nome do item: ");
            scanf("%s", items[i].name);
            printf("Digite o novo preco do item: ");
            scanf("%f", &items[i].price);
            printf("Digite a nova quantidade do item: ");
            scanf("%d", &items[i].quantity);
            printf("Item editado com sucesso.\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

// Função para excluir um item
void deleteItem() {
    int itemId;
    printf("Digite o ID do item que deseja excluir: ");
    scanf("%d", &itemId);
    for (int i = 0; i < num_items; i++) {
        if (items[i].id == itemId) {
            for (int j = i; j < num_items - 1; j++) {
                items[j] = items[j + 1];
            }
            num_items--;
            printf("Item excluido com sucesso.\n");
            return;
        }
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

    for (int i = 0; i < num_items; i++) {
        if (items[i].id == itemId) {
            if (items[i].quantity >= quantity) {
                for (int j = 0; j < num_cart_items; j++) {
                    if (cart[j].id == itemId) {
                        cart[j].quantity += quantity;
                        printf("Item adicionado ao carrinho com sucesso.\n");
                        break;
                    }
                }
                cart[num_cart_items] = items[i];
                cart[num_cart_items].quantity = quantity;
                num_cart_items++;
                printf("Item adicionado ao carrinho com sucesso.\n");
            } else {
                printf("Quantidade insuficiente em estoque.\n");
            }
            printf("Deseja adicionar outro item? (1 - Sim / 2 - Finalizar Compra): ");
            int choice;
            scanf("%d", &choice);
            if (choice == 2)
                checkout();
            else if (choice != 1)
                printf("Opcao invalida. Finalizando compra.\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

// Função para finalizar a compra
void checkout() {
    float total = 0;
    printf("Itens no carrinho:\n");
    for (int i = 0; i < num_cart_items; i++) {
        printf("ID: %d | Nome: %s | Preco: R$ %.2f | Quantidade: %d\n", cart[i].id, cart[i].name, cart[i].price, cart[i].quantity);
        total += cart[i].price * cart[i].quantity;
    }
    printf("Total da compra: R$ %.2f\n", total);
    printf("Compra finalizada. Obrigado por comprar na Ze Neto Moda!\n");
    // Resetar o carrinho
    num_cart_items = 0;
}

// Função principal
int main() {
    printf("Bem-vindo a Ze Neto Moda!\n");
    printf("Encontre as melhores roupas importadas aqui.\n\n");

    // Adicionando itens de exemplo
    strcpy(items[num_items].name, "Camisa Polo");
    items[num_items].price = 120.0;
    items[num_items].quantity = 20;
    items[num_items].id = 1;
    num_items++;

    strcpy(items[num_items].name, "Calca Jeans");
    items[num_items].price = 150.0;
    items[num_items].quantity = 15;
    items[num_items].id = 2;
    num_items++;

    strcpy(items[num_items].name, "Vestido Longo");
    items[num_items].price = 200.0;
    items[num_items].quantity = 10;
    items[num_items].id = 3;
    num_items++;

    strcpy(items[num_items].name, "Bone Adidas Preto e Branco");
    items[num_items].price = 50.0;
    items[num_items].quantity = 10;
    items[num_items].id = 4;
    num_items++;

    strcpy(items[num_items].name, "Bone Nike Preto");
    items[num_items].price = 50.0;
    items[num_items].quantity = 15;
    items[num_items].id = 5;
    num_items++;

    strcpy(items[num_items].name, "Camisa Oversized");
    items[num_items].price = 120.0;
    items[num_items].quantity = 10;
    items[num_items].id = 6;
    num_items++;

    strcpy(items[num_items].name, "Short Dry Fit");
    items[num_items].price = 75.0;
    items[num_items].quantity = 10;
    items[num_items].id = 7;
    num_items++;

    int choice;
    while (1) {
        if (!isLoggedIn) {
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
        } else {
            listItems();
        }
    }
    return 0;
}

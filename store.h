#ifndef STORE_H
#define STORE_H

#include <stdbool.h>

#define MAX_EMAIL_LENGTH 80
#define MAX_PASSWORD_LENGTH 20
#define MAX_ITEM_NAME_LENGTH 50
#define DATE_LENGTH 11

typedef struct User {
    char name[MAX_ITEM_NAME_LENGTH];
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char birthdate[DATE_LENGTH];
    bool valid;
    struct User* next;
} User;

typedef struct Item {
    int id;
    char name[MAX_ITEM_NAME_LENGTH];
    float price;
    int quantity;
    struct Item* next;
} Item;

void addUserToList(User** userList, User* newUser);
void addItemToList(Item** itemList, Item* newItem);
void sortItemsByPrice(Item** itemList);
bool isEmailDuplicate(char *email);
bool isOver18(char *birthdate);
void registerUser();
void login();
void listItems();
void listPrice();
void listQuantity();
void editItem();
void deleteItem();
void addToCart();
void checkout();

#endif /* STORE_H */

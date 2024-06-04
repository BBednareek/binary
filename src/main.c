#include <mysql/mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "user.h"
#include <mysql/mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "user.h"
#include "database.h"
#include "ui.h"

int main() {
    MYSQL *conn = connectDatabase();

    char username[50];
    char password[50];

    User loggedUser;
    User* userPtr = &loggedUser;

    int loginAttempts = 0; 
    const int MAX_ATTEMPTS = 3;

    do {
        printf("Nazwa uzytkownika: ");
        scanf("%49s", username);
        printf("Haslo: ");
        scanf("%49s", password);

        userPtr = login(conn, username, password);

        if (userPtr->id == -1) {
            system("clear");
            printf("Bledny login lub haslo. ");
            loginAttempts++;

            if (loginAttempts >= MAX_ATTEMPTS) {
                printf("Maksymalna liczba prob logowania przekroczona.\n");
				break;
            } else {
                printf("Sprobuj ponownie!\n\n");
            }
        }
    } while (userPtr->id == -1);

    if (userPtr->id != -1) {
        if (strcmp(userPtr->role, "admin") == 0) {
            adminMenu(conn);
        } else {
            userMenu(conn, userPtr);
        }
    }

    closeDatabase(conn);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>

#include "user.h"
#include "binary_converter.h"
#include "database.h"

void adminMenu(MYSQL *conn){
	int optionChoice, userId, note_id;

	do{
		printf("\nMenu admina\n");
		printf("1. Dodaj uzytkownika\n");
		printf("2. Pokaz wszystkich uzytkownikow\n");
		printf("3. Pokaz notatki konkretnego uzytkownika\n");
		printf("4. Pokaz wszystkie notatki\n");
		printf("5. Edytuj notatke\n");
		printf("6. Usun notatke\n");
		printf("7. Usun uzytkownika\n");
		printf("8. Wyjscie\n");
		printf("Wybor: ");
		scanf("%d", &optionChoice);

		switch (optionChoice){
			char username[50];
			char password[50];
			char role[10];
			int id;
			char data[MAX_STRING_LENGTH];

			case 1:
			printf("Podaj nazwe uzytkownika: ");
			scanf("%49s", username);
			printf("Podaj haslo ");
			scanf("%49s", password);
			printf("Podaj uprawnienia uzytkownika (admin/user): ");
			scanf("%9s", role);
			insertUser(conn, username, password, role);
			break;
			case 2:
			listUsers(conn);
			break;
			case 3:
			listUsers(conn);
			printf("\nKtorego uzytkownika notatki chcesz wyswietlic: ");
			scanf("%d", &userId);
			listData(conn, userId, "user");
			break;
			case 4:
			listData(conn, -1, "admin");
			break;
			case 5:
				system("clear");
				listData(conn, -1, "admin");
				printf("Podaj indeks uzytkownika, ktorego notatke chcesz edytowac: ");
				scanf("%d", &userId);
				printf("\nPodaj numer notatki, ktora chcesz edytowac: ");
				scanf("%d", &note_id);
				updateData(conn, note_id, userId);
			break;
			case 7:
			listData(conn, -1, "admin");
			printf("Podaj id uzytkownika, ktorego wpis chcesz usunac: ");
			scanf("%d", &userId);
			deleteData(conn, userId);
			break;
			case 6:
			listUsers(conn);
			deleteUser(conn);
			break;
			case 8:
			printf("Do zobaczenia!\n");
			exit(1);
			break;
			default:
			printf("Podaj prawidlowa opcje!");
			break;
		}
	} while(optionChoice != 8);
}

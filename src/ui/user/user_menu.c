#include <stdlib.h>
#include <stdio.h>

#include "user.h"
#include "database.h"

void userMenu(MYSQL *conn, User* loggedUser)
{
	char *data = NULL;
	size_t len = 0;
	ssize_t read;
	int choice;

	do
	{
		printf("\nMenu uzytkownika\n");
		printf("1. Dodaj notatke\n");
		printf("2. Pokaz moje notatki\n");
		printf("3. Usun notatke\n");
		printf("4. Wyjscie\n");
		printf("Wybor: ");
		scanf("%d", &choice);

		while (getchar() != '\n'){}
		switch (choice)
		{
			case 1:
				system("clear");
				printf("Wprowadz dane: ");
				read = getline(&data, &len, stdin);
				if (read != -1) {
					if (data[read-1] == '\n'){
						data[read-1] = '\0';
					}
				}
				insertData(conn, loggedUser->id, data);
				break;
			case 2:
				system("clear");
				listData(conn, loggedUser->id, loggedUser->role);
				break;
			case 3:
				system("clear");
				listData(conn, loggedUser->id, loggedUser->role);
				deleteData(conn);
				break;
			case 4:
				printf("Do zobaczenia!\n");
				exit(1);
				break;
			default:
				printf("Podaj prawidlowa opcje!\n");
				break;
		}
	} while (choice != 4);
}

#include <mysql/mysql.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "binary_converter.h"
#include "data.h"
#include "database.h"

void listData(MYSQL *conn, int user_id, const char *role){
	system("clear");

	MYSQL_RES *res;
	MYSQL_ROW row;
	Data *data = NULL;
	char query[256];

	if (strcmp(role, "admin") == 0)	{
		snprintf(query, sizeof(query), "SELECT * FROM data");
	} else {
	snprintf(query, sizeof(query), "SELECT id, user_id, data FROM data WHERE user_id = %d", user_id);
}
	if (mysql_query(conn, query)){
		errorHandler(conn);
		return;
	}

	res = mysql_store_result(conn);
	if(res == NULL){
		errorHandler(conn);
		return;
	}

	printf("ID\tUser ID\tBinary Data\n");
	

	while ((row = mysql_fetch_row(res))){
		data = (Data *)malloc(sizeof(Data));
		
		if(data == NULL){
			errorHandler(conn);
			return;
		}

		data->id = atoi(row[0]);
		data->user_id = atoi(row[1]);
		binaryToString(row[2], data->binary_data);
		printf("%d\t%d\t%s\n", data->id, data->user_id, data->binary_data);
		free(data);
	}
	mysql_free_result(res);
}

void insertData(MYSQL *conn, int user_id, const char *data){
	char binaryData[MAX_BINARY_LENGTH];
	char query[MAX_BINARY_LENGTH + 256];

	stringToBinary(data, binaryData);
	snprintf(query, sizeof(query), "INSERT INTO data (user_id, data) VALUES (%d, '%s')", user_id, binaryData);

	if (mysql_query(conn, query)) {
		errorHandler(conn);
	}

	system("clear");
	printf("Pomyslnie dodano nowy wpis\n");
}

void deleteData(MYSQL *conn, const int user_id) {
    int note_id;
    
    printf("Podaj id wpisu, ktory chcesz usunac: ");
    scanf("%d", &note_id);

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM data WHERE id = %d AND user_id = %d", note_id, user_id);

    if (mysql_query(conn, query)) {
        errorHandler(conn);
    } else {
        int affectedRows = mysql_affected_rows(conn);
        if (affectedRows > 0) {
            system("clear");
            printf("Pomyslnie usunieto wpis o id %d\n", note_id);
        } else {
            system("clear");
            printf("Wpis o id %d nie istnieje lub nie nalezy do uzytkownika o id %d\n", note_id, user_id);
        }
    }
}

void updateData(MYSQL *conn, const int id, const int user_id){
	system("clear");

	char query[MAX_BINARY_LENGTH + 256];
	
	snprintf(query, sizeof(query), "SELECT data FROM data WHERE id = %d AND user_id = %d", id, user_id);

	if (mysql_query(conn, query)){
		errorHandler(conn);
	}

	MYSQL_RES *result = mysql_store_result(conn);

	if (result == NULL) {
		errorHandler(conn);
	}

	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;

	char text[MAX_STRING_LENGTH] = "";

	if ((row = mysql_fetch_row(result))) {
		binaryToString(row[0], text);
	}

	mysql_free_result(result);

	system("clear");
	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	printw("Notatka, ktora chcesz edytowac: %s\n", text);
	refresh();

	edit_text(text);

	char binaryData[MAX_BINARY_LENGTH];

	stringToBinary(text, binaryData);
	snprintf(query, sizeof(query), "UPDATE data SET data = '%s' WHERE id = %d AND user_id = %d", binaryData, id, user_id);

	if(mysql_query(conn, query)) {
		errorHandler(conn);
	} else {
		clear();
		printw("Zaktualizowana notatka: %s\n", text);
		refresh();
	}
	getch();
	endwin();
}

void edit_text(char *text) {
	int ch;
	int pos = 0;
	int len = strlen(text);

	mvprintw(1, 0, "Edit the text and press ENTER when done:\n");
	mvprintw(2, 0, "%s", text);
	move(2, pos);

	while((ch = getch()) != '\n') {
		if(ch == KEY_LEFT) {
			if(pos>0){
				pos--;
			}
		} else if (ch == KEY_RIGHT) {
			if(pos < len) {
				pos++;
			}	
		} else if (ch == KEY_BACKSPACE || ch == 127) {
			if (pos > 0){
				memmove(&text[pos-1], &text[pos], len - pos + 1);
				pos--;
				len--;
				text[len] = '\0';
				mvprintw(2, 0, "%s ", text);
				move(2, pos);
			}
		} else if (ch == KEY_DC) {
			if (pos < len) {
				memmove(&text[pos], &text[pos+1], len - pos);
				len--;
				text[len] = '\0';
				mvprintw(2, 0, "%s ", text);
				move(2, pos);
			}
		} else if (ch >= 32 && ch <= 126) {
			if (len < MAX_STRING_LENGTH - 1){
				memmove(&text[pos+1], &text[pos], len - pos + 1);
				text[pos] = ch;
				pos++;
				len++;
				text[len] = '\0';
				mvprintw(2, 0, "%s", text);
				move(2, pos);
			}
		}
		move(2, pos);
		refresh();
	}}

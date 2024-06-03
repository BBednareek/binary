#include <mysql/mysql.h>
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

void updateData(MYSQL *conn, int id, const char *newData)
{
	char binaryData[MAX_BINARY_LENGTH];
	char query[MAX_BINARY_LENGTH + 256];
	
	stringToBinary(newData, binaryData);
	snprintf(query, sizeof(query), "UPDATE data SET data = '%s' WHERE id = %d", binaryData, id);

	if (mysql_query(conn, query)){
		errorHandler(conn);
	}

	system("clear");
	printf("Pomyslnie zaktualizowano wiersz o id %d\n", id);
}

void deleteData(MYSQL *conn){
	int noteId;

	printf("Podaj id wpisu, ktory chcesz usunac: ");
	scanf("%d", &noteId);

	char query[256];
	snprintf(query, sizeof(query), "DELETE FROM data WHERE id = %d", noteId);

	if (mysql_query(conn, query)){
		errorHandler(conn);
	}

	system("clear");
	printf("Pomyslnie usunieto wpis o id %d\n", noteId);
}

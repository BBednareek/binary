#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

#include "data.h"
#include "user.h"

MYSQL* connectDatabase();
void closeDatabase(MYSQL *conn);
void errorHandler(MYSQL *conn);

User* login(MYSQL *conn, const char *username, const char *password);
void insertUser(MYSQL *conn, const char *username, const char *password, const char *role);
void listUsers(MYSQL *conn);
void deleteUser(MYSQL *conn);

void insertData(MYSQL *conn, int user_id, const char *data);
void updateData(MYSQL *conn, const int id,  const int user_id);
void deleteData(MYSQL *conn, const int user_id);
void listData(MYSQL *conn, int user_id, const char *role);

void edit_text(char *text);

#endif // DATABASE_H

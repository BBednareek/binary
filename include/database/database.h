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

void insertData(MYSQL *conn, int user_id, const char *data);
void updateData(MYSQL *conn, int id, const char *newData);
void deleteData(MYSQL *conn);
void listData(MYSQL *conn, int user_id, const char *role);

#endif // DATABASE_H

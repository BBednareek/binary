#ifndef UI_H
#define UI_H

#include <mysql/mysql.h>
#include "user.h"

void userMenu(MYSQL *conn, User* loggedUser);
void adminMenu(MYSQL *conn);

#endif // UI_H

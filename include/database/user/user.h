#ifndef USER_H
#define USER_H

typedef struct
{
    int id;
    char username[50];
    char password[50];
    char role[10];
} User;

#endif // USER_H
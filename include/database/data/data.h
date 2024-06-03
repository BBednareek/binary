#ifndef DATA_H
#define DATA_H

#define MAX_BINARY_LENGTH 4096

typedef struct
{
    int id;
    int user_id;
    char binary_data[MAX_BINARY_LENGTH];
} Data;

#endif // DATA_H

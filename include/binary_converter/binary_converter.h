#ifndef BINARY_CONVERTER_H
#define BINARY_CONVERTER_H

#define MAX_STRING_LENGTH 512

// Funkcje związane z szyfrowaniem
void charToBinary(unsigned char c, char *output);
void stringToBinary(const char *input, char *output);
void binaryToString(const char *input, char *output);

#endif // BINARY_CONVERTER_H

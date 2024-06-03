#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "binary_converter.h"

void charToBinary(unsigned char c, char *output)
{
	for (int i = 7; i >= 0; i--)
	{
		output[7 - i] = (c & (1 << i)) ? '1' : '0';
	}
	output[8] = '\0';
}

void stringToBinary(const char *input, char *output)
{
	char binary[9];
	output[0] = '\0'; // Zainicjuj output jako pusty string

	for (size_t i = 0; i < strlen(input); i++)
	{
		charToBinary(input[i], binary);
		strcat(output, binary);
		if(i<strlen(input)-1){
			strcat(output, " "); // Dodaj spację między bajtami dla czytelności

		}
	}
}

void binaryToString(const char *input, char *output)
{
	size_t len = strlen(input);
	char buffer[9];
	buffer[8] = '\0';
	output[0] = '\0';

	for (size_t i = 0; i < len; i += 9)
	{ // Co 9 znaków (8 bitów + spacja)
		strncpy(buffer, input + i, 8);
		buffer[8] = '\0';
		unsigned char c = strtol(buffer, NULL, 2);
		strncat(output, (char *)&c, 1);
	}
}

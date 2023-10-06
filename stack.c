/* stack.c */

/* This program has a buffer overflow vulnerability. */
/* Our task is to exploit this vulnerability */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bof(char *str)
{
    char buffer[24];

    /* The following statement has a buffer overflow problem */ 
    strcpy(buffer, str); //first is destination, second is source

    return 1;
}

int main(int argc, char **argv)
{
    char str[517];
    FILE *badfile;

    badfile = fopen("badfile", "r"); //opens a file for reading. the r stands for reading.
	
	//first parameter is a pointer, second is size in bytes of each element to be read, third is number of elements,
	// last is the stream. reading data from the stream into the array.
	//I'm putting badfile into str?
    fread(str, sizeof(char), 517, badfile); 
    
	//putting str into buffer
	bof(str);

    printf("Returned Properly\n");
    return 1;
}

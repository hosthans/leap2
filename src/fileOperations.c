/*
 * fileOperations.c
 *
 *  Created on: Oct 14, 2023
 *      Author: bot
 */


#include <stdio.h>
#include "../headers/fileOperations.h"

int isFileEmpty(FILE *file){
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (size == 0){
		return 1;
	} else {
		return 0;
	}
}

void writeLog(FILE *file, const char *message){
	if (file != NULL){
		puts("Write...");
		fprintf(file, "%s", message);
	} else {
		printf("Fehler beim Dateizugriff!\n");
	}
}

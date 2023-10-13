/*
 * fileOperations.h
 *
 *  Created on: Oct 14, 2023
 *      Author: bot
 */

#ifndef HEADERS_FILEOPERATIONS_H_
#define HEADERS_FILEOPERATIONS_H_
#include <stdio.h>

void writeLog(FILE *file, const char *message);
int isFileEmpty(FILE *file);

#endif /* HEADERS_FILEOPERATIONS_H_ */

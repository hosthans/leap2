/*
 * time_stamping.c
 *
 *  Created on: Oct 14, 2023
 *      Author: bot
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "timeStamping.h"

void getCurrentTimeStamp(char *timeStamp) {
	struct timeval tv;
	gettimeofday(&tv, NULL);

	struct tm *currentTime;
	currentTime = localtime(&tv.tv_sec);

	snprintf(timeStamp, 50, "%04d-%02d-%02d %02d:%02d:%02d.%03ld",
			 currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday,
			 currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec,
			 tv.tv_usec / 1000); // Mikrosekunden in Millisekunden umwandeln
}

/*
 * main.c
 *
 *  Created on: Oct 13, 2023
 *      Author: bot
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "headers/connection.h"
#include "headers/fileOperations.h"

FILE *file = NULL;
const char HEADER[] = "frame_id\thand_count\tl_hand_p(x,y,z)\tr_hand_p(x,y,z)\n";

void handleInterrupt(int signum) {
	if (file != NULL) {
		fclose(file);
		puts("file closed!");
	}
	exit(signum);
}

int main() {

	// register handler
	signal(SIGINT, handleInterrupt);

	int64_t lastFrameID = 0; //The last frame received

	// Initialize File Object
	file = fopen("logfile.txt", "a");

	// check if file is empty
	if (isFileEmpty(file) == 1) {
		printf("file empty - write header ... \n");
		printf("following header will be inserted: %s\n", HEADER);
		writeLog(file, HEADER);

	} else {
		printf("file not empty - no header insertion \n");
	}

	OpenConnection();
	while (!IsConnected)
		millisleep(100); //wait a bit to let the connection complete

	printf("Connected.");
	LEAP_DEVICE_INFO *deviceProps = GetDeviceProperties();
	if (deviceProps)
		printf("Using device %s.\n", deviceProps->serial);

	for (;;) {
		LEAP_TRACKING_EVENT *frame = GetFrame();
		if (frame && (frame->tracking_frame_id > lastFrameID)) {
			lastFrameID = frame->tracking_frame_id;
			if (file != NULL) {
				char logMessage[1000];
				if (frame->nHands >= 2) {
					LEAP_HAND *first_hand = &frame->pHands[0];
					LEAP_HAND *second_hand = &frame->pHands[1];

					sprintf(logMessage, "%lli\t%i\t(%f,%f,%f)\t(%f,%f,%f)\n",
							(long long int) frame->tracking_frame_id,
							frame->nHands, first_hand->palm.position.x,
							first_hand->palm.position.y,
							first_hand->palm.position.z,
							second_hand->palm.position.x,
							second_hand->palm.position.y,
							second_hand->palm.position.z);
					writeLog(file, logMessage);
				} else if (frame->nHands == 1) {
					LEAP_HAND *first_hand = &frame->pHands[0];
					sprintf(logMessage, "%lli\t%i\t(%f,%f,%f)\t(%s,%s,%s)\n",
							(long long int) frame->tracking_frame_id,
							frame->nHands, first_hand->palm.position.x,
							first_hand->palm.position.y,
							first_hand->palm.position.z, "x", "x", "x");
					writeLog(file, logMessage);
				} else {
					puts("no hand detected");
				}

			}
		}
	} //ctrl-c to exit
	return 0;
}


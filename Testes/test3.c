/*
 * test3.c
 *
 *  Created on: 01/11/2015
 *      Author: Amanda
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "uvm.h"

int main(void) {
	uvm_create();
	char* page;
	page = uvm_extend();

	int pid;
	pid = fork();
	if (pid == -1)
		perror("fork:");
		exit(EXIT_FAILURE);
	if (pid == 0) { //filho
		strcat(page, "Try me!");
	} else { //pai
		wait(NULL);
	}

	uvm_syslog(page, strlen(page) + 1);
	exit(EXIT_SUCCESS);
}

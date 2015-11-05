/*
 * test5.c
 *
 *  Verifica a substituicao de paginas.
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
	int i;
	char* page[4];
	char charUm = '1';
	for (i = 0; i < 4; i++) {
		page[i] = uvm_extend();
		page[i][0] = charUm + i;
		page[i][1] = '\0';
	}
	char *pageout = uvm_extend();
	pageout[0] = '\0';
	strcat(pageout, "hello");

	char *pageout2 = uvm_extend();
	pageout2[0] = '\0';
	strcat(pageout2, "hello2");

	for (i = 0; i < 4; i++)
		uvm_syslog(page[i], strlen(page[i]) + 1);

	char* page2[3];
	for (i = 0; i < 3; i++) {
		page2[i] = uvm_extend();
		page2[i][0] = '0' + i + 1;
		page2[i][1] = '\0';
	}

	for (i = 0; i < 3; i++)
		uvm_syslog(page2[i], strlen(page2[i]) + 1);

	exit(EXIT_SUCCESS);
}

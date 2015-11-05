/*
 * test4.c
 *
 * Verificacao de escrita e leitura: Escreve na memoria virtual x blocos,
 * le os x blocos e compara para ver se os blocos estao certos.
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
	for (i = 0; i < 3; i++) {
		page[i] = uvm_extend();
		page[i][0] = charUm + i;
		page[i][1] = '\0';
	}

	for (i = 0; i < 3; i++) {
		uvm_syslog(page[i], strlen(page[i]) + 1);
	}
	int hits = 0;
	for (i = 0; i < 3; i++) {
		if(page[i][0] == charUm + 1)
			++hits;
	}
	exit((hits == 3)? EXIT_SUCCESS : EXIT_FAILURE);
}

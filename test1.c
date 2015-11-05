/*
 * test1.c
 *
 *  Verifica o tratamento de falha de paginas.
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
		page[i] = uvm_extend(); //aloca todos os quadros de memoria fisica
		page[i][0] = charUm + i;
		page[i][1] = '\0';
	}
	char* pageout = uvm_extend(); //aloca mais um quandro de memoria. Deve ser feita a substitucao de alguma pagina
	pageout[0] = '\0';
	strcat(pageout, "hello");

	for (i = 0; i < 4; i++) {
		uvm_syslog(page[i], strlen(page[i]) + 1);
	}
	exit(EXIT_SUCCESS);
}

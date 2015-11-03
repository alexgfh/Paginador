/*
 * test2.c
 *
 * Verifica proteção de memória: Escreve em página não alocada.
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
	char* page = "hello";
	uvm_syslog(page, strlen(page) + 1);
	exit(EXIT_SUCCESS);
}

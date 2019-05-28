/*
 ============================================================================
 Name        : 2.c
 Author      : Kamil Lopuszynski
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int args, char **argv) {

	if(args < 2){
		printf("Brak podanych argumentów\n");
		return 0;
	}


	return 1;
}

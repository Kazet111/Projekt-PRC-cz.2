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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <net/if.h>
#include <unistd.h>
#include <dlfcn.h>
#include <byteswap.h>

int main(int args, char **argv) {

	if(args < 2){
		printf("Brak podanych argumentów\n");
		return 0;
	}

	long adresDocelowy = inet_addr(argv[1]);
	int portDocelowy = atoi(argv[2]);
	int rozmiarWiadomosci = 999999;
	int liczbaWyslanych = 0;
	int ograniczenieWyslanychWiadomosci = argv[3];
	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	int inneDane = 0;
	const int on = 1;

	if(socket < 0){
		perror("Socket nie został utworzony, upewnij się czy masz uprawnienia administratora");
	}

	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, (const char*) &on, sizeof(on)) == -1) {
		perror("Nagłówek IP nie został wygenerowany");
		return (0);
	}

	char *pakiet = (char *) malloc(sizeof(struct iphdr) + sizeof(struct tcphdr) + inneDane);

	if(!pakiet){
		perror("Błąd alokacji pamięci");
		close(sockfd);
		return 0;
	}



	return 1;
}

/*
 ============================================================================
 Name        : 2.c
 Author      : Kamil Lopuszynski
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "Dec.h"

typedef unsigned short int u16;

int main(int args, char **argv) {
	Library = dlopen("/home/kazet/Programowanie/Projekt-PRC-cz.2/src/Library.so", RTLD_NOW);
		  	if (!Library) {
		  		printf("Błąd otwarcia: %s\n", dlerror());
		  		return (1);
		  	}


	if(args < 3){
		typedef void(*Function)();
		Function show = (Function)dlsym(Library,"show");
		show();
		return 0;
	}
	//Sprawdzenie interfejsu
	struct ifaddrs *ifaddr, *ifa;
		    int s;
		    char host[NI_MAXHOST];
		    int zn=0;
		    if (getifaddrs(&ifaddr) == -1)
		    {
		        perror("getifaddrs");
		        exit(EXIT_FAILURE);
		    }


		    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next){
		        if (ifa->ifa_addr == NULL)
		            continue;

		        s=getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		        if((strcmp(ifa->ifa_name,argv[1])==0)&&(ifa->ifa_addr->sa_family==AF_INET)){
		            if (s != 0){
		                printf("getnameinfo() failed: %s\n", gai_strerror(s));
		                exit(EXIT_FAILURE);
		            }
		            zn=1;
		        }

		    } if (zn == 0){
		printf("Podany interfejs nie istnieje\nLista dostępnych interfejsów -> ifconfig\n");
		    return(0);
		    }

		    freeifaddrs(ifaddr);

	long destinationAddress = inet_addr(argv[2]);
	uint16_t destinationPort = atoi(argv[3]);
	int messageSize = 999;
	int messageSent = 0;
	int messageAllSent;
	if(argv[4] != NULL){
		messageAllSent = atoi(argv[4]);
	} else {
		messageAllSent = 4;
	}
	printf("\nZostanie wysłanych %d pakietów\n", messageAllSent);

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	int otherData = 0;
	const int on = 1;

	if(socket < 0){
		perror("Socket nie został utworzony, upewnij się czy masz uprawnienia administratora\n");
	}

	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, (const char*) &on, sizeof(on)) == -1) {
		perror("Nagłówek IP nie został wygenerowany : ");
		return (0);
	}

	int packageSize = sizeof(struct iphdr) + sizeof(struct tcphdr) + otherData;
	char *package = (char *) malloc(packageSize);

	if(!package){
		perror("Błąd alokacji pamięci\n");
		close(sockfd);
		return 0;
	}
	//Naglowek IP
	struct iphdr *ip = (struct iphdr *) package;
	struct tcphdr *tcp = (struct tcphdr *) (package + sizeof(struct iphdr));

	memset(package, 0, packageSize);

	tcp->th_dport=bswap_16(destinationPort);
	ip->daddr=destinationAddress;

	setIp(ip,packageSize);
	setTcp(tcp);

	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = tcp->th_dport;
	memset(&servaddr.sin_zero, 0, sizeof(servaddr.sin_zero));

	printf("\n### Wysyłanie ###\n");

	create(ip,tcp);

	while (messageSent < messageAllSent) {
		memset(package + sizeof(struct iphdr) + sizeof(struct tcphdr),
				rand() % 255, otherData);

		if ((messageSize = sendto(sockfd, package, messageSize, 0,
				(struct sockaddr*) &servaddr, sizeof(servaddr))) < 1) {
			perror("Wystąpił błąd podczas próby wysłania\n");
			break;
		}
		++messageSent;
		printf(".");
		fflush(stdout);

		usleep(100000);
	}

	printf("\n\nPomyślnie wysłano następującą liczbę pakietów : %d\n", messageAllSent);

	free(package);
	close(sockfd);

	return (0);
}

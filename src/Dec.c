/*
 * Dec.c
 *
 *  Created on: 11 cze 2019
 *      Author: root
 */

#include "Dec.h"

struct package *anchorAddress = NULL;
struct package *currentAddress = NULL;
struct package *lastAddress = NULL;
struct package *temp;

unsigned short checkSum(unsigned short *ptr, int nbytes) {
	register long sum;
	u_short oddbyte;
	register u_short answer;
	sum = 0;

	while (nbytes > 1) {
		sum += *ptr++;
		nbytes -= 2;
	}

	if (nbytes == 1) {
		oddbyte = 0;
		*((u_char *) &oddbyte) = *(u_char *) ptr;
		sum += oddbyte;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return (answer);
}

void create(struct iphdr *ip, struct tcphdr *tcp) {
	if(anchorAddress == NULL){
		anchorAddress = (struct package*) malloc(sizeof(struct package));
		currentAddress = anchorAddress;
		currentAddress->first = anchorAddress;
		currentAddress->previous = NULL;
		currentAddress->next = NULL;
		memcpy(&(currentAddress->ip),ip,sizeof(struct iphdr));
		memcpy(&(currentAddress->tcp),tcp,sizeof(struct tcphdr));
		currentAddress = NULL;
	} else {
		lastAddress = anchorAddress;
		for(int n = 0 ; n < 10 ; ++n){
			if(lastAddress->next != NULL){
				lastAddress = lastAddress->next;
			} else {
				break;
			}
		}

		currentAddress = (struct package*) malloc(sizeof(struct package));
		lastAddress->next = currentAddress;
		currentAddress->first = anchorAddress;
		currentAddress->previous = lastAddress;
		currentAddress->next = NULL;

		memcpy(&(currentAddress->ip),ip,sizeof(struct iphdr));
		memcpy(&(currentAddress->tcp),tcp,sizeof(struct tcphdr));
	}
}


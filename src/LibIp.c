/*
 * LibIp.c
 *
 *  Created on: 11 cze 2019
 *      Author: root
 */
#include "Dec.h"

int setIp(struct iphdr *ip, int packet_size) {
	ip->tos = 0;
	ip->tot_len = htons(packet_size);
	ip->id = rand();
	ip->frag_off = IPTOS_CLASS_DEFAULT;
	ip->ttl = IPDEFTTL;
	ip->protocol = IPPROTO_TCP;
	ip->version = 4;
	ip->ihl = 5; //default iphdr len
	ip->check = checkSum((u16 *) ip, sizeof(struct iphdr));

	return (1);
}

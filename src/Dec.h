/*
 * Dec.h
 *
 *  Created on: 11 cze 2019
 *      Author: root
 */

#ifndef DEC_H_
#define DEC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/if.h>
#include <dlfcn.h>
#include <byteswap.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#include "LibIp.h"
#include "LibTcp.h"

typedef unsigned char u8;
typedef unsigned short int u16;

unsigned short checkSum(unsigned short *ptr, int nbytes);
void create(struct iphdr *ip, struct tcphdr *tcp);

struct package{
	struct package *first;
	struct package *next;
	struct package *previous;
	struct tcphdr tcp;
	struct iphdr ip;
};
#endif /* DEC_H_ */

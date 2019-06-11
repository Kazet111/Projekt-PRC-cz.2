/*
 * LibTcp.c
 *
 *  Created on: 11 cze 2019
 *      Author: root
 */
#include "Dec.h"

int setTcp(struct tcphdr *tcp) {
	tcp->th_x2 = 0;
	tcp->th_off = 5;
	tcp->th_flags = TH_SYN;
	tcp->th_win = 65535;
	tcp->th_urp = 0;
	tcp->th_seq = rand();
	tcp->th_sum = checkSum((u16 *) tcp, sizeof(struct tcphdr));

	return (1);
}

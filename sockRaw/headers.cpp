

#include"headers.h"
#include<iostream>

#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0



void fill_icmp_head(char*data, int dataSize){     //填充ICMP协议头
	ICMP_HEAD *head = (ICMP_HEAD*)data;
	head->i_type = ICMP_ECHO;
	head->i_code = 0;
	head->i_id = (USHORT)GetCurrentThreadId();
	//printf("current id is %d",head->i_id);
	head->i_seq = 0;
	head->timestamp = GetTickCount();
	head->i_checksum = 0;                    //校验和出错会导致丢包
	char *part = data + sizeof(ICMP_HEAD);
	memset(part,'U',dataSize-sizeof(ICMP_HEAD));

	head->i_checksum = checksum((USHORT*)data,dataSize);
}

void decode_icmp(char*buf,int bytes, sockaddr_in *from){

	IP_HEAD *iphdr;
	ICMP_HEAD *icmphdr;
	USHORT iphdrlen;
	iphdr = (IP_HEAD*)buf;
	iphdrlen = iphdr->len * 4;
	icmphdr = (ICMP_HEAD*)(buf + iphdrlen);
//	printf("current id is %d", GetCurrentThreadId());
	if (icmphdr->i_type!=ICMP_ECHOREPLY)
	{
		printf("non-echo type %d recvd  ", icmphdr->i_type);
/*		printf("id is %d",icmphdr->i_id);
		sockaddr_in ad;
		ad.sin_addr.s_addr = iphdr->desIp;
		printf("IP   %s is using",inet_ntoa(ad.sin_addr));
		*/
	}
	else{


		if ((icmphdr->i_id) != 0)
			printf("IP   %s   is using\n", inet_ntoa(from->sin_addr));
	}

}


/*
u_short chechkSum(char*data, int len){
	u_long sum = 0;

	USHORT*temp = (USHORT*)data;
	for (; len> 0;len-=2){
		sum += *temp++;

		if (sum>0xffff){
		
			sum = sum << 16;
			sum = sum >> 16;
			sum += 1;
		
		
		}
		
	
	}
	return sum;

}
*/



USHORT checksum(USHORT *buffer, int size)
{
	unsigned long cksum = 0;
	while (size > 1)
	{
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}
	if (size)
	{
		cksum += *(UCHAR*)buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}
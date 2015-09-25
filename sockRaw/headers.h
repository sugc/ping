#ifndef  _HEAD
#define  _HEAD

#include<Windows.h>

#include<minwindef.h>


typedef struct ICMP{
	BYTE i_type;    //ICMP 类型吗，回送请求类型码为8
	BYTE i_code;    //子类型码，保存与特定ICMP报文类型相关的细节信息
	USHORT  i_checksum;  //校验和
	USHORT i_id;       //ICMP报文的ID号
	USHORT i_seq;      //ICMP数据报的序列号
	ULONG  timestamp;   //可选数据部分，可忽略

}ICMP_HEAD;





typedef struct IP{


#if LITTLE_ENDIAN

	UCHAR verison :4; //4位版本号和4位首部长度
	UCHAR len :4;
#else
	UCHAR len : 4;
	UCHAR verison : 4; //4位版本号和4位首部长度
	
#endif
	UCHAR tos;
	USHORT totalLen;
	USHORT id;
	USHORT def_off; //3标志位和13位偏移量
	UCHAR ttl;
	UCHAR proto;
	USHORT checkSum;
	ULONG  sourceIp;
	ULONG  desIp;
	
}IP_HEAD;


void fill_icmp_head(char* data,int dataSize);
void decode_icmp(char*buf, int bytes, struct sockaddr_in *from);
USHORT checksum(USHORT*data,int len);

#endif
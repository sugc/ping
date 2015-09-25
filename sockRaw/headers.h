#ifndef  _HEAD
#define  _HEAD

#include<Windows.h>

#include<minwindef.h>


typedef struct ICMP{
	BYTE i_type;    //ICMP �����𣬻�������������Ϊ8
	BYTE i_code;    //�������룬�������ض�ICMP����������ص�ϸ����Ϣ
	USHORT  i_checksum;  //У���
	USHORT i_id;       //ICMP���ĵ�ID��
	USHORT i_seq;      //ICMP���ݱ������к�
	ULONG  timestamp;   //��ѡ���ݲ��֣��ɺ���

}ICMP_HEAD;





typedef struct IP{


#if LITTLE_ENDIAN

	UCHAR verison :4; //4λ�汾�ź�4λ�ײ�����
	UCHAR len :4;
#else
	UCHAR len : 4;
	UCHAR verison : 4; //4λ�汾�ź�4λ�ײ�����
	
#endif
	UCHAR tos;
	USHORT totalLen;
	USHORT id;
	USHORT def_off; //3��־λ��13λƫ����
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
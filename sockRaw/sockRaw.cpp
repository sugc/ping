#include<iostream>
#include<WinSock2.h>
#include<ws2tcpip.h> 
#include"headers.h"
#include<stdio.h>


using namespace std;
#pragma comment(lib,"ws2_32.lib")
void main(){
	DWORD version = MAKEWORD(2,2);
	
	WSADATA data;
	DWORD err=WSAStartup(version,&data);
	if (err != 0)
		return;
	SOCKET sock = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
	if (sock==INVALID_SOCKET){

		printf("socket  \n ");
		exit(1);
	
	
	
	}
	char datas[100];
	sockaddr_in src,des;
	des.sin_family = AF_INET;
	des.sin_addr.s_addr =inet_addr("111.13.100.91");
	
	
	int timeout = 1000;
//	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,(char*)&timeout,sizeof(timeout));

	u_long iMode = 1;  //non-blocking mode is enabled.

	//ioctlsocket(sock, FIONBIO, &iMode); //设置为非阻塞模式

	

	fill_icmp_head(datas,sizeof(datas));        //填充icmp报文
	int sendcode=sendto(sock,datas,sizeof(datas),0,(sockaddr*)&des,sizeof(des));

	if (sendcode==SOCKET_ERROR){
		cout << "send erro" << endl;
		system("pause");
		exit(1);
	
	
	}


	if (sendcode < sizeof(datas)){           //发送
		cout << "send erro" << endl;
		exit(1);
	
	
	}


	sockaddr_in from;
	int fromlen = sizeof(from);
	char buf[200];

	memset(buf,0,sizeof(buf));
	
	while (1){                    //接收
		int bread = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&from, &fromlen);


		
		//	cout << bread;

		decode_icmp(buf, bread, &from);
		memset(buf, 0, sizeof(buf));

	}

	system("pause");
}



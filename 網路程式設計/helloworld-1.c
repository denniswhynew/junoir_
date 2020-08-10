#include <stdio.h>
#include <string.h>
#include <winsock.h>

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024]/*="Hello World!"*/;
   WSADATA 		wsadata;

   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�

   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   //���s�u�@�ǳơA�]�t��g sockaddr_in ���c (serv) �C
   //���e���Gserver �� IP ��}�Aport number �����C
   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(IPPORT_ECHO);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server

   int i=1;
   sprintf(str,"%d",i);
   send(sd, str, strlen(str)+1, 0);
   i++; //�ǰehello world��echo server
   send(sd, str, strlen(str)+1, 0);

   recv(sd, str, 1024, 0); //��echo server���� hello world
   //recv(sd, str, 1024, 0);
   printf(str);

   closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�

   return 0;
}



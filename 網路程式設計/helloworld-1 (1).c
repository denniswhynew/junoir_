#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <stdlib.h>

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024]/*="Hello World!"*/;
   int i,j;

   WSADATA 		wsadata;

   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�

   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   //���s�u�@�ǳơA�]�t��g sockaddr_in ���c (serv) �C
   //���e���Gserver �� IP ��}�Aport number �����C
   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(IPPORT_ECHO);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server
   for(i=1;i<=9;i++)
   {
       for(j=1;j<=9;j++)
       {
           sprintf(str,"%dx%d%=%d  ",j,i,(i*j));
           send(sd, str, strlen(str)+1, 0); //�ǰehello world��echo server

           recv(sd, str, 1024, 0); //��echo server���� hello world
           printf("%s",str);
       }
       char ss[2]="\n";
        send(sd, ss, strlen(ss)+1, 0); //�ǰehello world��echo server

        recv(sd, ss, 2, 0); //��echo server���� hello world
        printf("%s",ss);
   }

   closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�

   return 0;
}



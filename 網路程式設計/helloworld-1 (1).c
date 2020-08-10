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

   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用

   sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.

   //為連線作準備，包含填寫 sockaddr_in 結構 (serv) 。
   //內容有：server 的 IP 位址，port number 等等。
   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(IPPORT_ECHO);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server
   for(i=1;i<=9;i++)
   {
       for(j=1;j<=9;j++)
       {
           sprintf(str,"%dx%d%=%d  ",j,i,(i*j));
           send(sd, str, strlen(str)+1, 0); //傳送hello world至echo server

           recv(sd, str, 1024, 0); //由echo server接收 hello world
           printf("%s",str);
       }
       char ss[2]="\n";
        send(sd, ss, strlen(ss)+1, 0); //傳送hello world至echo server

        recv(sd, ss, 2, 0); //由echo server接收 hello world
        printf("%s",ss);
   }

   closesocket(sd); //關閉TCP socket

   WSACleanup();  // 結束 WinSock DLL 的使用

   return 0;
}



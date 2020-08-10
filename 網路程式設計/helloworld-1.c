#include <stdio.h>
#include <string.h>
#include <winsock.h>

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024]/*="Hello World!"*/;
   WSADATA 		wsadata;

   WSAStartup(0x101,(LPWSADATA) &wsadata); // 呼叫 WSAStartup() 註冊 WinSock DLL 的使用

   sd=socket(AF_INET, SOCK_STREAM, 0); //開啟一個 TCP socket.

   //為連線作準備，包含填寫 sockaddr_in 結構 (serv) 。
   //內容有：server 的 IP 位址，port number 等等。
   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(IPPORT_ECHO);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // 連接至 echo server

   int i=1;
   sprintf(str,"%d",i);
   send(sd, str, strlen(str)+1, 0);
   i++; //傳送hello world至echo server
   send(sd, str, strlen(str)+1, 0);

   recv(sd, str, 1024, 0); //由echo server接收 hello world
   //recv(sd, str, 1024, 0);
   printf(str);

   closesocket(sd); //關閉TCP socket

   WSACleanup();  // 結束 WinSock DLL 的使用

   return 0;
}



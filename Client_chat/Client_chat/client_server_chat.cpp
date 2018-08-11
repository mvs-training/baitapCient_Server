//#include "stdafx.h"
#include<conio.h>
#include "Client.h"
#include<iostream>
#include<Winsock2.h>
#include<stdio.h>
#pragma comment(lib,"Ws2_32")
using namespace std;
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.100"
#define BUFF_SIZE 2048

void Client::Connect(){
	WSADATA wsaData;  // struct
	WORD wVersion = MAKEWORD(2, 2);   // phiên bản hiện tại 
	int tv = 10000;
	// kieetr tra và khởi động winsock
	if (WSAStartup(wVersion, &wsaData))

		cout << "KHONG THE KHOI DONG DUOC WINSOCK\n";

	//	SOCKET client; // khai báo  tên 

		// khơi tạo socket
		client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&tv), sizeof(int));

		//sockaddr_in serverAddr; //Winsock người ta sử dụng cấu trúc sockaddr_in để biểu diễn địa chỉ IP

		// khai bao doi tượng
		serverAddr.sin_family = AF_INET;

		serverAddr.sin_port = htons(SERVER_PORT); //cong logic de lang nghe ket noi

		serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

		if (connect(client, (sockaddr *)&serverAddr, sizeof(serverAddr))) {
			cout << "ERROR! Cannot connect server " << WSAGetLastError() << endl;
			_getch();

		}

		cout << "Connected server!\n";
	}


void Client::aa(){
		// gui du lieu di send

		//khai bao bien can gửi
		char buff[BUFF_SIZE];

		

		cout << " Send to server: ";
		// nhap du lieu và size
		gets_s(buff, BUFF_SIZE);

		//gui du lieu voi ten file do dai kich thước, cờ hiệu
		ret = send(client, buff, strlen(buff), 0);

		if (ret == SOCKET_ERROR)

			cout << "ERROR! cannot send message";

		ret = recv(client, buff, BUFF_SIZE, 0);

		if (ret == SOCKET_ERROR) {

			if (WSAGetLastError() == WSAETIMEDOUT)

				cout << "TIME-out";

			else

				cout << "ERROR! Cannot receive message.";


		}

		else if (strlen(buff) > 0) {

			buff[ret] = 0;

			printf("Receive form server[%s:%d] %s\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port), buff);
		}
	}
void Client::close(){


		closesocket(client);
	



}
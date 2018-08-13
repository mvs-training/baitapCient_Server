//#include"stdafx.h"
#include<iostream>
#include<Winsock2.h>
#include<stdio.h>

#include<conio.h>
#pragma comment(lib,"Ws2_32")
using namespace std;
#define BUFF_SIZE 2048

#include "server_chat.h"

int main()
{
	while (true)
	{
		char a[BUFF_SIZE];
	//a = new char;
	Server sv;
	sv.OpenSocket();
	int ret, clientAddrLen = sizeof(sv.clientAddr);

	sv.connSock = accept(sv.listenSock, (sockaddr*)& sv.clientAddr, &clientAddrLen);

	ret = recv(sv.connSock, a, sizeof(a), 0);

	if (ret == SOCKET_ERROR) {

		cout << "ERROR:" << WSAGetLastError();

	}

	else if (strlen(a) > 0) {
		a[ret] = 0;
		cout << a << endl;
	}
	closesocket(sv.connSock);
	sv.CloseSocket();
	int leghtchar = strlen(a);
	cout << leghtchar;

		
		switch (leghtchar)
		{
		case 1:
			cout << "ct 1";
			sv.OpenSocket();
			sv.signup();
			sv.CloseSocket();

			break;
		case 2:
			cout << "ct 2";
			sv.OpenSocket();
			sv.signin();
			
			sv.CloseSocket();
			//return true;
			break;
		case 3:
			cout << "ct 3";
			sv.OpenSocket();
			sv.ShowMessdrec(sv.id);
			sv.CloseSocket();
			break;
		case 4:
			cout << "ct 4";
			sv.ShowMesssen(sv.id);
			break;
		case 5:
			cout << "ct 5";

			sv.SendMess(sv.id);
			break;
		case 6:
			cout << "ct 6";
			sv.AddFriend(sv.id);
			break;
		case 7:
			cout << "ct 7";
			sv.ShowFriend(sv.id);
			break;
		default:
			break;
		}



	}
	system("pause");

}

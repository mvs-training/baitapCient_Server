//#include"stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Winsock2.h>
#include<stdio.h>
#include "server_chat.h"
#include<conio.h>
#pragma comment(lib,"Ws2_32")
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.100"
#define BUFF_SIZE 2048
#define _CRT_SECURE_NO_WARNINGS
using namespace std;



void Server::OpenSocket(){
	WSADATA wsaData;

	WORD WVersion = MAKEWORD(2, 2);

	if (WSAStartup(WVersion, &wsaData))

		cout << "Version is not supported" << endl;

	// khai báo tên socket
	//SOCKET listenSock;

	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	///sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;

	serverAddr.sin_port = htons(SERVER_PORT);

	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	if (bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr))) {

		cout << "Error! Cannot bind this address." << endl;


	}

	if (listen(listenSock, 10)) {

		cout << "Error, Cannot listen.";



	}

	cout << "Server da hoat dong" << endl;

	//	sockaddr_in clientAddr;
}

void Server::CloseSocket(){
	closesocket(listenSock);  // ham dong 
}


void Server::b(){
	char buff[BUFF_SIZE];

	int ret, clientAddrLen = sizeof(clientAddr);

	while (1) {

		//	SOCKET connSock;
		// lang nghe

		connSock = accept(listenSock, (sockaddr*)& clientAddr, &clientAddrLen);

		ret = recv(connSock, buff, BUFF_SIZE, 0);

		if (ret == SOCKET_ERROR) {

			cout << "ERROR:" << WSAGetLastError();

			break;
		}

		else if (strlen(buff) > 0) {

			buff[ret] = 0;

			cout << " Rececive from client " << inet_ntoa(clientAddr.sin_addr) << "  " << ntohs(clientAddr.sin_port) << "  " << buff << endl;

			char abc[100];
			//abc = new char;

			gets_s(abc, 100);

			ret = send(connSock, abc, strlen(abc), 0);

			if (ret == SOCKET_ERROR);

			cout << "ERROR:" << WSAGetLastError();




		}

		// ham dong 
		

	}
	closesocket(connSock);  // ham dong 
}
void Server::signup(){

	int ret, clientAddrLen = sizeof(clientAddr);

	connSock = accept(listenSock, (sockaddr*)& clientAddr, &clientAddrLen);

	ret = recv(connSock, username, BUFF_SIZE, 0);
	ret = recv(connSock, password, BUFF_SIZE, 0);
	ret = recv(connSock, birthday, BUFF_SIZE, 0);
	ret = recv(connSock, city, BUFF_SIZE, 0);

	if (ret == SOCKET_ERROR) {

		cout << "ERROR:" << WSAGetLastError();

	}

	else if (strlen(username) > 0) {

		username[ret] = 0;
		password[ret] = 0;
		birthday[ret] = 0;
		city[ret] = 0;

		cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << username << endl;
		cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << password << endl;
		cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << birthday << endl;
		cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << city << endl;
		ConnectSQlite conn;
		conn.Open();
		conn.RunInsertParamSQL(username, password, birthday, city);

	}

	closesocket(connSock);

}
void Server::signin(){
	int ret, clientAddrLen = sizeof(clientAddr);

	connSock = accept(listenSock, (sockaddr*)& clientAddr, &clientAddrLen);

	ret = recv(connSock, username, BUFF_SIZE, 0);
	ret = recv(connSock, password, BUFF_SIZE, 0);
	// gui id ve
	if (ret == SOCKET_ERROR) {

		cout << "ERROR:" << WSAGetLastError();

	}

	else if (strlen(username) > 0) {

		username[ret] = 0;
		password[ret] = 0;
		cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << username << endl;
		cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << password << endl;

		ConnectSQlite conn;
		conn.Open();
		if (conn.RunSelectParamSQL(username, password) > 0) {
			cout << "thanh cong ";
			id = conn.RunSelectParamSQL(username, password);
			ret = send(connSock, username, strlen(username), 0);
		if (ret == SOCKET_ERROR);
			cout << "ERROR:" << WSAGetLastError();
		}
		else cout << "that bai";

	}
//	cout << "-======="<<id;
	closesocket(connSock);  // ham dong 
}
void Server::ShowMessdrec(int id){
	Server sv;
		int id2;
		cout << "Chon nguoi dung: \n";
		//cin >> frien;
		ConnectSQlite conn;
		conn.Open();
		conn.ShowFriend(conn.db, id);
	//	conn.ShowListFriend(conn.db, id);
		//	cout << conn.ten << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	// hien thi ten frien tu client len sever
		sv.OpenSocket();
		int ret, clientAddrLen = sizeof(clientAddr);
		connSock = accept(listenSock, (sockaddr*)& clientAddr, &clientAddrLen);
		ret = recv(connSock, frien, BUFF_SIZE, 0);
		// gui  ve
		if (ret == SOCKET_ERROR) {
			cout << "ERROR:" << WSAGetLastError();
		}
		else if (strlen(frien) > 0) {

			frien[ret] = 0;
			cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << frien << endl;
		}
		closesocket(connSock);  // ham dong 
		sv.CloseSocket();
		cout << frien << "aaaaaaaa";
	//	memcpy(frien, conn.ten.c_str(), sizeof(conn.ten)); // chuyển chuỗi kiểu tra sang kiểu string từ string ten --> in ra  char * frien
		id2 = conn.TransNameToId(frien);
		if (id2 > 0){

			cout << "Gui tu *** " << frien << " ***den :\n";
			conn.ShowMessdrec(id2, id);
			conn.UpdateMessage(id2, id);
			// khi an ctrl + r
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
		
}
void Server::ShowMesssen(int id){
	Server sv;
	int id2;
	cout << "Chon nguoi dung: \n";
	//cin >> frien;
	ConnectSQlite conn;
	conn.Open();
	conn.ShowFriend(conn.db, id);
	//	conn.ShowListFriend(conn.db, id);
	//	cout << conn.ten << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	// hien thi ten frien tu client len sever
	sv.OpenSocket();
	int ret, clientAddrLen = sizeof(clientAddr);
	connSock = accept(listenSock, (sockaddr*)& clientAddr, &clientAddrLen);
	ret = recv(connSock, frien, BUFF_SIZE, 0);
	// gui  ve
	if (ret == SOCKET_ERROR) {
		cout << "ERROR:" << WSAGetLastError();
	}
	else if (strlen(frien) > 0) {

		frien[ret] = 0;
		cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << frien << endl;
	}
	closesocket(connSock);  // ham dong 
	sv.CloseSocket();
	cout << frien << "aaaaaaaa";
	//	memcpy(frien, conn.ten.c_str(), sizeof(conn.ten)); // chuyển chuỗi kiểu tra sang kiểu string từ string ten --> in ra  char * frien
	id2 = conn.TransNameToId(frien);
	if (id2 > 0){

		cout << "Gui tu *** " << frien << " ***den :\n";
		conn.ShowMessDetail(conn.db, id, id2);
	}
	else cout << "----Tai khoan khong ton tai-----------\n";

}
void Server::SendMess(int id){
	int id2;
	cout << "Chon nguoi dung: \n";
			ConnectSQlite conn;
			conn.Open();
			cout << "danh sach ban be\n";
			conn.ShowFriend(conn.db, id);
			conn.ShowListFriend(conn.db, id);
			//ShowListFriend(id);
			//	cout << conn.ten << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

// hient hi ten firen
			Server sv;
			sv.OpenSocket();
			int ret, clientAddrLen = sizeof(clientAddr);
			connSock = accept(listenSock, (sockaddr*)& clientAddr, &clientAddrLen);
			ret = recv(connSock, frien, BUFF_SIZE, 0);
			// gui  ve
			if (ret == SOCKET_ERROR) {
				cout << "ERROR:" << WSAGetLastError();
			}
			else if (strlen(frien) > 0) {
				frien[ret] = 0;
				cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << frien << endl;
			}
		cout << "To :" << frien << "      \n";
		id2 = conn.TransNameToId(frien);
		if (id2 > 0){
			// gui thong bao tai khoan ton tai ve
			ret = send(connSock, frien, strlen(frien), 0);
			if (ret == SOCKET_ERROR);   cout << "ERROR:" << WSAGetLastError();
			if (!conn.CheckBlock(conn.db, id, id2)){

				cout << "---------You is blocked by her--------\n";
			}
			else{
				cout << "Nhap Tin nhan: \n";
				//cin >> mess;
				ret = recv(connSock, mess, BUFF_SIZE, 0);
				// gui  ve
				if (ret == SOCKET_ERROR) {
					cout << "ERROR:" << WSAGetLastError();
				}
				else if (strlen(mess) > 0) {
					mess[ret] = 0;
					cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << mess << endl;
				}
				time_t hientai = time(0);
				char *dt;
				dt = ctime(&hientai);
				int sent = 0;
				conn.WriteToMess(conn.db, id, id2, mess, dt, sent);
				//conn.ShowMessDetail(conn.db,id,id2);

			}

			
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
		closesocket(connSock);  // ham dong 
		sv.CloseSocket();

}
void Server::AddFriend(int id){

		cout << "Nhap ten nguoi ban muon them: ";
		char  *dt;
		//cin >> newfr;
		Server sv;
		sv.OpenSocket();
		int ret, clientAddrLen = sizeof(clientAddr);
		connSock = accept(listenSock, (sockaddr*)& clientAddr, &clientAddrLen);
		ret = recv(connSock, newfr, BUFF_SIZE, 0);
		// gui  ve
		if (ret == SOCKET_ERROR) {
			cout << "ERROR:" << WSAGetLastError();
		}
		else if (strlen(newfr) > 0) {

			newfr[ret] = 0;
			cout << " Rececive from client " << ntohs(clientAddr.sin_port) << "  " << newfr << endl;
		}
		ConnectSQlite conn;
		conn.Open();
		int id2 = conn.TransNameToId(newfr);
		if (id2 > 0){
			if (conn.CheckBlock(conn.db, id, id2)){
				conn.CityID(newfr);
				//	cout << conn.thanhpho << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

				memcpy(city, conn.thanhpho.c_str(), sizeof(conn.thanhpho)); // them city vao bang Friend
				//cout << city;
				time_t hientai = time(0);
				dt = ctime(&hientai);
				conn.WriteToFriend(conn.db, id, id2, city, dt);
				//ShowFriend(id);
				cout << "them thanh cong\n";
				// phan hoi 
				ret = send(connSock, newfr, strlen(newfr), 0);
				if (ret == SOCKET_ERROR);   cout << "ERROR:" << WSAGetLastError();
			}
			else {
				cout << "------You were blocked by her  or You was friend ----------\n\n\n";
				//conn.CheckFriend(conn.db,id,id2);
			}
		}
		else { cout << "----Tai khoan khong ton tai-----------\n"; }
		closesocket(connSock);  // ham dong 
		sv.CloseSocket();
}



void Server::ShowFriend(int id){
		
	ConnectSQlite conn;
		conn.Open();
		conn.ShowFriend(conn.db, id);
	//	int sapsep;
//		cout << "Ctrl + C de hien danh sach theo thanh pho\n an bat ky de tro lai\n";
//		sapsep = _getch();
//		if (sapsep == 3){
//			conn.CityID(username);
//			conn.Showcity(city, id);
//		}if (sapsep != 3){
//			cout << "*.--------------.*\n";
//		}
}

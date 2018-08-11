#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "server_chat.h"
//#include "sha1.hpp"
//#include<bits/stdc++.h>
#include "sqlite3.h"
using namespace std;
#include <cstring>
#include <string>
#include <list>
#include <sstream>
#include <ctime>
#include <chrono>
#include<conio.h>
#include<stdio.h>
#include<time.h>
using namespace std;

int ConnectSQlite::callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
void ConnectSQlite::Open(){
	rc = sqlite3_open("baitap.db", &db);
	if (rc){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else{
		//  fprintf(stderr, "Opened database successfully\n");

	}
}
void ConnectSQlite::RunInsertParamSQL(char *fn, char *ln, char *bir, char *city){
	if (!db)return;
	// Insert data item into myTable
	szSQL = "insert into user1 (username, password,birthday,city) values (?,?,?,?)";

	int rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, fn, strlen(fn), 0);
		sqlite3_bind_text(stmt, 2, ln, strlen(ln), 0);
		sqlite3_bind_text(stmt, 3, bir, strlen(bir), 0);
		sqlite3_bind_text(stmt, 4, city, strlen(city), 0);
		// sqlite3_bind_int(stmt, 3, age);

		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		cout << " -----Successfuly---------\n";
	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
}
int ConnectSQlite::RunSelectParamSQL(char *us, char *pa){
	int id = 0;
	if (!db)return 0;

	szSQL = "SELECT * FROM  user1 WHERE username = ? and password = ? ";

	rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, us, strlen(us), 0);
		sqlite3_bind_text(stmt, 2, pa, strlen(pa), 0);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id;
		}
		sqlite3_finalize(stmt);


	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
	return id;

}


int ConnectSQlite::TransNameToId(char *frien){
	int id2 = -1;
	szSQL = "SELECT id FROM user1 WHERE username = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

	if (rc == SQLITE_OK){
		sqlite3_bind_text(stmt, 1, frien, strlen(frien), 0);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id2;

		}
		sqlite3_finalize(stmt);
	}
	else{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	return id2;

}



void ConnectSQlite::SelectMessenger(sqlite3 *db, int id){
	if (!db)return;
	szSQL = "SELECT DISTINCT user1.username FROM"
		"(SELECT * FROM messenger where idsen = ? ) as A LEFT JOIN user1 ON A.idrec = user1.id";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			answer.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
		}
		sqlite3_finalize(stmt);
		cout << "-----Danh sach tin nhan-------\n";
		for (list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
			cout << *it << endl;

	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
}


void ConnectSQlite::ShowMessDetail(sqlite3 *db, int id1, int id2){
	string kiemtra;
	string drec1;
	string drec2;
	char *drec_char1, *drec_char3, *drec_char2;
	drec_char1 = new (char);
	drec_char2 = new (char);
	drec_char3 = new (char);
	if (!db)return;
	cout << "--------Detail--------\n";
	szSQL = "SELECT * FROM (SELECT * FROM messenger WHERE (idsen = ? AND idrec = ?)  ) AS B LEFT JOIN  user1 ON (user1.id = B.idsen )";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		int sent;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		Server sv;
		sv.OpenSocket();
		int ret, clientAddrLen = sizeof(sv.clientAddr);
		sv.connSock = accept(sv.listenSock, (sockaddr*)& sv.clientAddr, &clientAddrLen);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			// hien thi tin nhan
			kiemtra = string((const char *)sqlite3_column_text(stmt, 6));
			//			cout << "   " << kiemtra << " : " << endl;
			// gui ve client
			memcpy(drec_char1, kiemtra.c_str(), sizeof(kiemtra));
			sv.ret = send(sv.connSock, drec_char1, sizeof(drec_char1), 0);
			cout << drec_char1 << sizeof(drec_char1) << "*\n";
			if (sv.ret == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAETIMEDOUT)
					cout << "TIME-out";
				else
					cout << "ERROR! Cannot receive message.";
			}

			// hien thi tin nhan
			drec1 = string((const char *)sqlite3_column_text(stmt, 2));
			// gui ve client
			memcpy(drec_char2, drec1.c_str(), sizeof(drec1));
			sv.ret = send(sv.connSock, drec_char2, sizeof(drec_char2), 0);
			cout << drec_char2 << sizeof(drec_char2) << "*\n";
			if (sv.ret == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAETIMEDOUT)
					cout << "TIME-out";
				else
					cout << "ERROR! Cannot receive message.";
			}
			// hien thi tin nhan
			drec2 = string((const char *)sqlite3_column_text(stmt, 3));
			// gui ve client
			memcpy(drec_char3, drec2.c_str(), sizeof(drec2));
			sv.ret = send(sv.connSock, drec_char3, sizeof(drec_char3), 0);
			cout << drec_char3 << sizeof(drec_char3) << "*\n";
			if (sv.ret == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAETIMEDOUT)
					cout << "TIME-out";
				else
					cout << "ERROR! Cannot receive message.";
			}
			sent = sqlite3_column_int(stmt, 4);
			if (sent == 1){ cout << "                             (Da xem.) \n"; }
			if (sent == 0) {
				cout << "                             (da gui tin nhan. )\n";}
		}
		if (kiemtra == ""){
			cout << "khong co tin nhan den\n";
		}
		// dóng sever
		closesocket(sv.connSock);  // ham dong 
		sv.CloseSocket();
		sqlite3_finalize(stmt);
	}
	else{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);

	}
			
	
}

bool ConnectSQlite::CheckBlock(sqlite3 *db, int id1, int id2){
	int isblock = 0;
	if (!db)return 0;
	szSQL = "SELECT isblock FROM friend WHERE (id1 = ? AND id2 = ?) OR (id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id2);
		sqlite3_bind_int(stmt, 4, id1);

		// commit                                                                              
		//sqlite3_step(stmt);
		if (sqlite3_step(stmt) == SQLITE_ROW){
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isblock;
			sqlite3_finalize(stmt);
		}
	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
	return !isblock;
}
void ConnectSQlite::WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time, int sent){
	szSQL = "INSERT INTO messenger VALUES (?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_text(stmt, 3, mes, strlen(mes), 0);
		sqlite3_bind_text(stmt, 4, time, strlen(time), 0);
		sqlite3_bind_int(stmt, 5, sent);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);

	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}

}
bool ConnectSQlite::CheckFriend(sqlite3 *db, int id1, int id2){
	int isFriend = 0;
	szSQL = "SELECT * FROM friend WHERE ( id1 = ? AND id2 = ?) OR ( id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id2);
		sqlite3_bind_int(stmt, 4, id1);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW){
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isFriend;

			if (isFriend != 0) isFriend = 1;
			else isFriend = 0;

			sqlite3_finalize(stmt);
		}
	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
	return isFriend;
}
void ConnectSQlite::WriteToFriend(sqlite3 *db, int id1, int id2, char *city, char *dt){
	if (!db)return;
	szSQL = "INSERT INTO friend VALUES (?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		int isblock = 0;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, isblock);
		sqlite3_bind_text(stmt, 4, city, strlen(city), 0);
		sqlite3_bind_text(stmt, 5, dt, strlen(dt), 0);

		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);

	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
}
void ConnectSQlite::CityID(char *username){
	if (!db)return;
	szSQL = "SELECT * FROM user1 WHERE username = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	//cout << username << "\n";
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, username, strlen(username), 0);
		if (sqlite3_step(stmt) == SQLITE_ROW){
			// stringstream str;
			// str << sqlite3_column_text(stmt, 4);
			// str >> thanhpho;
			thanhpho = string((const char *)sqlite3_column_text(stmt, 4));
			cout << thanhpho << "\n";
			sqlite3_finalize(stmt);
		}
	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
void ConnectSQlite::ShowFriend(sqlite3 *db, int id1){
	cout << "-------List Friends-----------\n";
	if (!db)return;
	//  szSQL = "SELECT DISTINCT user1.username FROM"
	//            "(SELECT * FROM friend where (id1 = ? OR id2 = ?) AND isblock = 0) as A LEFT JOIN user1 ON (A.id2 = user1.id OR A.id1 = user1.id)";
	szSQL = "SELECT DISTINCT user1.username FROM"
		"(SELECT * FROM friend where (id1 = ? ) AND isblock = 0) as A LEFT JOIN user1 ON (A.id2 = user1.id) ORDER BY timeadd ASC ";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		int i = 1;
		
		char *Friend_char;
		Friend_char = new (char);
		string Friend_str;
		Server sv;
		sv.OpenSocket();
		int ret, clientAddrLen = sizeof(sv.clientAddr);
		sv.connSock = accept(sv.listenSock, (sockaddr*)& sv.clientAddr, &clientAddrLen);
		while (sqlite3_step(stmt) == SQLITE_ROW) {

	//		ret = recv(sv.connSock, Friend_char, BUFF_SIZE, 0);
//			char * Friend_char = new char[i];
			Friend_str = string((const char *)sqlite3_column_text(stmt, 0)) ;
			
		//	if (Friend_str == "d"){
			memcpy(Friend_char, Friend_str.c_str(), sizeof(Friend_str));
			sv.ret = send(sv.connSock, Friend_char, sizeof(Friend_char), 0);
			cout << Friend_char << sizeof(Friend_char) << "*\n";

		//	delete Friend_char;
		//	cout << Friend_char << "*\n";
			if (sv.ret == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAETIMEDOUT)
					cout << "TIME-out";
				else
					cout << "ERROR! Cannot receive message.";
		}
			
			//
	//	}
	}
		closesocket(sv.connSock);
		sv.CloseSocket();
		sqlite3_finalize(stmt);

		cout << "-------------------------------------\n";
	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
}

void ConnectSQlite::BlockFriend(sqlite3 *db, int id1, int id2){
	if (!db)return;
	szSQL = "UPDATE friend SET isblock = 1 WHERE id1 = ? AND id2 = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);

	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
}
void ConnectSQlite::ShowListFriend(sqlite3 *db, int id1){
	if (!db)return;
	szSQL = "SELECT DISTINCT user1.username FROM"
		"(SELECT * FROM friend where (id1 = ? ) AND isblock = 0) as A LEFT JOIN user1 ON (A.id2 = user1.id) ORDER BY timeadd ASC ";

	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		//    sqlite3_bind_int(stmt,1,id1);
		// commit
		int nhap;
		int i = 0;
		//string ten;
		cin >> nhap;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			//	for (int = 1; i <= 10; i++){
			i++;
			if (nhap == i)	{

				//  cout << string((const char *) sqlite3_column_text(stmt, 0)) << endl;
				ten = string((const char *)sqlite3_column_text(stmt, 0));
			}
		}

		sqlite3_finalize(stmt);

	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}

}
void ConnectSQlite::Showcity(char *city, int id1){
	if (!db)return;
	SQL = "SELECT * FROM friend WHERE (id1 = ?)  ORDER BY city ASC";
	rcp = sqlite3_prepare_v2(db, SQL, strlen(SQL), &stmtp, &pzTest);
	if (rcp == SQLITE_OK) {
		sqlite3_bind_int(stmtp, 1, id1);
		while (sqlite3_step(stmtp) == SQLITE_ROW) {
			thanhpho = string((const char *)sqlite3_column_text(stmtp, 3));
			if (thanhpho == sosanh) {
				cout << "";
			}
			else{

				sosanh = thanhpho;
				cout << "Thanh Pho : ";
				cout << thanhpho << "\n";
				//ConnectSQlite conn;
				memcpy(city, thanhpho.c_str(), sizeof(thanhpho));
				UserNameCity(db, city, id1);
				cout << "\n *****************\n";
				//}// for																							
			}
		}
		sqlite3_finalize(stmtp);

		cout << "------------------------------------\n";
	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	//	} //for
}
void ConnectSQlite::UserNameCity(sqlite3 *db, char *city, int id1){
	int i = 1;
	if (!db)return;
	szSQL = "SELECT DISTINCT user1.username FROM"
		"(SELECT * FROM friend where (id1 = ?) AND isblock = 0  AND (city = ?)) as A LEFT JOIN user1 ON (A.id2 = user1.id )";
	//	szSQL =   "SELECT * FROM user1 WHERE (city = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, id1);
		//sqlite3_bind_int(stmt,1,id1); 
		sqlite3_bind_text(stmt, 2, city, strlen(city), 0);
		while (sqlite3_step(stmt) == SQLITE_ROW) {

			tentp = string((const char *)sqlite3_column_text(stmt, 0));

			cout << " tai khoan " << i++ << " : " << tentp << "\n";

		}
		sqlite3_finalize(stmt);

	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
void ConnectSQlite::UpdateMessage(int id1, int id2){

	szSQL = "UPDATE messenger SET sent = '1' WHERE (idsen = ? AND idrec =?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	cout << id1 << id2 << "\n";
	if (rc == SQLITE_OK) {
		cout << "thanh công ";
		//sqlite3_bind_int(stmt,,sen);
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);


		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else{

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

}
void ConnectSQlite::ShowMessdrec(int id1, int id2){
	string kiemtra;
	string drec1;
	string drec2;
	char *drec_char1, *drec_char3, *drec_char2;
	drec_char1 = new (char);
	drec_char2 = new (char);
	drec_char3 = new (char);
	if (!db)return;
	cout << "--------Detail--------\n";
	szSQL = "SELECT * FROM (SELECT * FROM messenger WHERE (idsen = ? AND idrec = ?)  ) AS B LEFT JOIN  user1 ON (user1.id = B.idsen )";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		int sent;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		Server sv;
		sv.OpenSocket();
		int ret, clientAddrLen = sizeof(sv.clientAddr);
		sv.connSock = accept(sv.listenSock, (sockaddr*)& sv.clientAddr, &clientAddrLen);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			// hien thi tin nhan
			kiemtra = string((const char *)sqlite3_column_text(stmt, 6));
//			cout << "   " << kiemtra << " : " << endl;
			// gui ve client
			memcpy(drec_char1, kiemtra.c_str(), sizeof(kiemtra));
			sv.ret = send(sv.connSock, drec_char1, sizeof(drec_char1), 0);
			cout << drec_char1 << sizeof(drec_char1) << "*\n";
			if (sv.ret == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAETIMEDOUT)
					cout << "TIME-out";
				else
					cout << "ERROR! Cannot receive message.";
			}

			// hien thi tin nhan
			drec1 = string((const char *)sqlite3_column_text(stmt, 2));
			// gui ve client
			memcpy(drec_char2, drec1.c_str(), sizeof(drec1));
			sv.ret = send(sv.connSock, drec_char2, sizeof(drec_char2), 0);
			cout << drec_char2 << sizeof(drec_char2) << "*\n";
			if (sv.ret == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAETIMEDOUT)
					cout << "TIME-out";
				else
					cout << "ERROR! Cannot receive message.";
			}
			// hien thi tin nhan
			drec2 = string((const char *)sqlite3_column_text(stmt, 3));
			// gui ve client
			memcpy(drec_char3, drec2.c_str(), sizeof(drec2));
			sv.ret = send(sv.connSock, drec_char3, sizeof(drec_char3), 0);
			cout << drec_char3 << sizeof(drec_char3) << "*\n";
			if (sv.ret == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAETIMEDOUT)
					cout << "TIME-out";
				else
					cout << "ERROR! Cannot receive message.";
			}
			sent = sqlite3_column_int(stmt, 4);
			if (sent == 1){ cout << "                             (Da xem.) \n"; }
			if (sent == 0) { cout << ""; }
		}
		if (kiemtra == ""){
			cout << "khong co tin nhan den\n";
		}
		// dóng sever
		closesocket(sv.connSock);  // ham dong 
		sv.CloseSocket();
		sqlite3_finalize(stmt);
	}
	else{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);

	}
}
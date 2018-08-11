#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Client.h"
//#include "sha1.hpp"
//#include<bits/stdc++.h>
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
#include<Winsock2.h>
using namespace std;
#define BUFF_SIZE 2048



void Client::RunInsertParamSQL(char *fn, char *ln, char *bir, char *city){

	// nhap du lieu và size
	//gui du lieu voi ten file do dai kich thước, cờ hiệu
	ret = send(client, fn, strlen(fn), 0);
	ret = send(client, ln, strlen(ln), 0);
	ret = send(client, bir, strlen(bir), 0);
	ret = send(client, city, strlen(city), 0);

	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			cout << "TIME-out";
		else
			cout << "ERROR! Cannot receive message.";
	}
	
	
	
}

int Client::RunSelectParamSQL(char *us, char *pa){
	int id = 0;
	

	ret = send(client, us, strlen(us), 0);
	ret = send(client, pa, strlen(pa), 0);
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			cout << "TIME-out";
		else
			cout << "ERROR! Cannot receive message.";
	}
	// nhan id tra ve 
	
	ID = new char;
	ret = recv(client, ID, sizeof(ID), 0);
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			cout << "That bai";
		else
			cout << "moi dang nhap lai";
	}
	else if (strlen(ID) > 0) {

		ID[ret] = 0;
		printf("Dang nhap thanh cong\n");
		
	}
	
	return id;

}


int Client::TransNameToId(char *frien){
	int id2 = -1;
	ID = new char;
	// gửi ten nhap vao len sever
	ret = send(client, frien, strlen(frien), 0);
	
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			cout << "TIME-out";
		else
			cout << "ERROR! Cannot receive message.";
	}
	// láy kết quả tra về
	
	ret = recv(client, ID, sizeof(ID), 0);
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			cout << "sai ten dang nhap";
		else
			cout << "that bai";
	}
	else if (strlen(ID) > 0) {

		ID[ret] = 0;
		cout << ID ;
		// nhân danh sach về
		bool kt = true;
		int i = 1;
		while (kt)
		{
			ret = recv(client, drec, sizeof(drec), 0);
			cout << sizeof(drec);
			if (ret == SOCKET_ERROR) {
				kt = false;
			}
			if (strlen(drec) == NULL){
				cout << "";
			}
			else if (strlen(drec) > 0) {
				drec[ret] = 0;
				cout << i << "   --   " << drec << "\n" << endl;
				i++;
				fflush(stdout);

				drec = new char;

			}
		}

	}
	return 0;
}
void Client::SendMess(char *frien){

	ret = send(client, frien, strlen(frien), 0);

	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			cout << "TIME-out";
		else
			cout << "ERROR! Cannot receive message.";
	}
	// láy kết quả tra về
	ID = new char;
	ret = recv(client, ID, sizeof(ID), 0);
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			cout << "sai ten dang nhap";
		else
			cout << "that bai";
	}
	else if (strlen(ID) > 0) {

		ID[ret] = 0;
		cout <<"To  :" <<ID<< "\n";
		// nhân danh sach về
		gets_s(mess, BUFF_SIZE);
		ret = send(client, mess, strlen(mess), 0);
		if (ret == SOCKET_ERROR) {
				cout << "ERROR! Cannot receive message.";
		}
		

	}
}
void Client::AddFriend(char *frien){
	
	ret = send(client, frien, strlen(frien), 0);

	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			cout << "TIME-out";
		else
			cout << "ERROR! Cannot receive message.";
	}
	// láy kết quả tra về
	ID = new char;
	ret = recv(client, ID, sizeof(ID), 0);
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			cout << "sai ten dang nhap";
		else
			cout << "that bai";
	}
	else if (strlen(ID) > 0) {

		ID[ret] = 0;
		cout << "To  :" << ID << "\n";
		cout << "Add Friend thanh cong";
	}
}
void Client::ShowFriend(int id1){
	cout << "-------List Friends-----------\n";
	//	Client cl;
	//cl.Connect();
	bool kt = true;

	char * a;
	a = new char;
	int i = 1;
	ret = send(client, a, strlen(a), 0);


	ID = new char;
	//ID = new char;
	delete ID;
	//	Client cl;
	char *frien;
	frien = new char;
	while (kt)
	{
		ret = recv(client, frien, sizeof(frien), 0);
		cout << sizeof(frien);
		if (ret == SOCKET_ERROR) {
			kt = false;
		}
		if (strlen(frien) == NULL){
			cout << "";
		}
		else if (strlen(frien) > 0) {
			frien[ret] = 0;
			cout << i << "   --   " << frien << "\n" << endl;
			i++;
			fflush(stdout);

			frien = new char;

		}
	}
	//	cl.close();

}
/*
void Client::SelectMessenger(sqlite3 *db, int id){
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


void Client::ShowMessDetail( int id1, int id2){
	string kiemtra;
	cout << "--------Detail--------\n";
	// gui len server

	if (rc == SQLITE_OK) {
		int sent;
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		// sqlite3_bind_int(stmt,3,id1);
		// sqlite3_bind_int(stmt,4,id2);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			kiemtra = string((const char *)sqlite3_column_text(stmt, 6));
			cout << "   " << kiemtra << " : " << endl;
			cout << "       " << string((const char *)sqlite3_column_text(stmt, 2)) << "-";
			cout << string((const char *)sqlite3_column_text(stmt, 3)) << endl;
			sent = sqlite3_column_int(stmt, 4);
			if (sent == 1){ cout << "                             (Da xem.) \n"; }
			if (sent == 0) { cout << "                             (da gui tin nhan. )\n"; }
		}
		if (kiemtra == ""){
			cout << "chua nhan tin \n";
		}
		sqlite3_finalize(stmt);
	}
	else{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		// break the loop if error occur
	}
}*/
/*
bool Client::CheckBlock(sqlite3 *db, int id1, int id2){
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
void Client::WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time, int sent){
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
bool Client::CheckFriend(sqlite3 *db, int id1, int id2){
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
void Client::WriteToFriend(sqlite3 *db, int id1, int id2, char *city, char *dt){
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
void Client::CityID(char *username){
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
}*/


/*
void Client::BlockFriend(sqlite3 *db, int id1, int id2){
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
void Client::ShowListFriend(sqlite3 *db, int id1){
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
void Client::Showcity(char *city, int id1){
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
				//Client conn;
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
void Client::UserNameCity(sqlite3 *db, char *city, int id1){
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
void Client::UpdateMessage(int id1, int id2){

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
void Client::ShowMessdrec(int id1, int id2){
	string kiemtra;
	if (!db)return;
	cout << "--------Detail--------\n";
	szSQL = "SELECT * FROM (SELECT * FROM messenger WHERE (idsen = ? AND idrec = ?)  ) AS B LEFT JOIN  user1 ON (user1.id = B.idsen )";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		int sent;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);

		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			kiemtra = string((const char *)sqlite3_column_text(stmt, 6));
			cout << "   " << kiemtra << " : " << endl;
			cout << "       " << string((const char *)sqlite3_column_text(stmt, 2)) << "-";
			cout << string((const char *)sqlite3_column_text(stmt, 3)) << endl;
			sent = sqlite3_column_int(stmt, 4);
			if (sent == 1){ cout << "                             (Da xem.) \n"; }
			if (sent == 0) { cout << ""; }
		}
		if (kiemtra == ""){
			cout << "khong co tin nhan den\n";
		}
		sqlite3_finalize(stmt);
	}
	else{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);

	}
}
*/
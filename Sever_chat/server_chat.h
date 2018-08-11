
#include <iostream>
#include "sqlite3.h"
//#include<bits/stdc++.h>
#include <cstring>
#include <string>
#include <list>
#include <sstream>
#include <ctime>
#include<conio.h>
#include<stdio.h>
#define BUFF_SIZE 2048

#include <windows.h>
using namespace std;


class User{
public:
	
	int  id;
	char *username;
	char *password;
	char *birthday;
	char *city;
	int sent;
	int flag; //danh dau dang nhap

public:
	User(){};
	void SignUp();
	void SignIn();

	bool isSignIn(); // kiem tra da dang nhap chua
	void nameuser();
	void SignOut();
	bool Check(User u);
	void ShowMessdrec(int);
	void ShowMesssen(int);
	void SendMess(int);
	void AddFriend(int);
	void ShowFriend(int);
	void BlockFriend(int);
	void ShowListFriend(int);
	void Showcity(int);
};

class ConnectSQlite{
public:
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	int rcp;
	const char *szSQL;
	const char *SQL;
	const char *pzTest;
	sqlite3_stmt *stmt;
	sqlite3_stmt *stmtp;
	list<string> answer;
	string ten;
	string thanhpho;
	string sosanh;
	string tentp;
	// int countRow; //dem so hang o cau lenh select
public:
	static int callback(void *, int, char **, char **);
	void Open();
	void RunInsertParamSQL(char *, char *, char *, char *);
	int RunSelectParamSQL(char *fn, char *ln);
	int TransNameToId(char *frien);
	void SelectMessenger(sqlite3 *db, int id);
	void ShowMessDetail(sqlite3 *db, int id1, int id2);
	bool CheckBlock(sqlite3 *db, int id1, int id2);
	void WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time, int sent);
	bool CheckFriend(sqlite3 *db, int id1, int id2);
	void WriteToFriend(sqlite3 *db, int id1, int id2, char *, char *);
	void CityID(char *);
	void ShowFriend(sqlite3 *db, int id1);
	void BlockFriend(sqlite3 *db, int id1, int id2);
	void ShowListFriend(sqlite3 *db, int id1);
	void Showcity(char*, int id1);
	void UserNameCity(sqlite3 *db, char *, int id1);
	void UpdateMessage(int id1, int id2);
	void ShowMessdrec(int id1, int id2);

};
class Server
{
public:
	SOCKET listenSock;
	sockaddr_in serverAddr;
	sockaddr_in clientAddr;
	SOCKET connSock;
	int Bind;
	int  id = 34;
	char username[BUFF_SIZE];
	char password[BUFF_SIZE];
	char birthday[BUFF_SIZE];
	char city[BUFF_SIZE];
	int sent;
	int flag;
	int ret;
	char frien[BUFF_SIZE];
	char mess[BUFF_SIZE];
	char newfr[BUFF_SIZE];
public:
	Server(){};
	void OpenSocket();
	void b();
	void CloseSocket();
	void signup();
	void signin();
	void ShowFriend(int);
	void ShowMessdrec(int);
	void ShowMesssen(int);
	void SendMess(int);
	void AddFriend(int);
};

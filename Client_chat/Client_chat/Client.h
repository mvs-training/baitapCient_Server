
#include <iostream>
//#include<bits/stdc++.h>
#include <cstring>
#include <string>
#include <list>
#include <sstream>
#include <ctime>
#include<conio.h>
#include<stdio.h>
#include<Winsock2.h>
using namespace std;
#define BUFF_SIZE 2048
class User{
public:

	int  id;
	char *username;
	char *password;
	char *birthday;
	char *city;
	int sent;
//	int flag = 1; //danh dau dang nhap

public:
	User(){};
	void SignUp();
	void SignIn();

	bool isSignIn(); // kiem tra da dang nhap chua
	void nameuser();
	void SignOut();
	bool Check(User u);
	void ShowMessdrec();
	void ShowMesssen(int);
	void SendMess(int);
	void AddFriend(int);
	void ShowFriend(int);
///	void BlockFriend(int);
//	void ShowListFriend(int);
//	void Showcity(int);
};

class Client
{
public:
	SOCKET client;
	sockaddr_in serverAddr;
	int ret;
	char *ID;
	char mess[BUFF_SIZE];
	char *drec;
public:
	void Connect();
	void aa();
	void close();
	void RunInsertParamSQL(char *, char *, char *, char *);
	int RunSelectParamSQL(char *fn, char *ln);
	int TransNameToId(char *frien);
	void SendMess(char *frien);
	void AddFriend(char *frien);
//	int RunSelectParamSQL(char *fn, char *ln);
//	int TransNameToId(char *frien);
//	void SelectMessenger(, int id);
	void ShowMessDetail( int id1, int id2);
//	bool CheckBlock(int id1, int id2);
//	void WriteToMess( int id1, int id2, char *mes, char *time, int sent);
//	bool CheckFriend( int id1, int id2);
//	void WriteToFriend( int id1, int id2, char *, char *);
//	void CityID(char *);
	void ShowFriend( int id1);
//	void BlockFriend( int id1, int id2);
//	void ShowListFriend( int id1);
//	void Showcity(char*, int id1);
//	void UserNameCity( char *, int id1);
//	void UpdateMessage(int id1, int id2);
//	void ShowMessdrec(int id1, int id2);

};
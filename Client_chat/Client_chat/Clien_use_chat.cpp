
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Client.h"
//#include "sha1.hpp"
//#include<bits/stdc++.h>
//#include "sqlite3.h"
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
#include <Thread>
#include <mutex>
#include <windows.h>
#define BUFF_SIZE 2048

std::mutex m;
using namespace std;
int flag ;


void User::SignUp(){
	cout << "-------Dien cac thong tin de dang ky!-------" << endl;
	username = new (char);
	birthday = new (char);
	password = new char;

	cout << "Nhap vao username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	//password = sha1(password);
	//cout << password;
	cout << "Enter birthday: ";
	cin >> birthday;
	cout << "nhap city: (tru chu bac giang ra la khong an dc a) :";
	//cin >> city;
	city = new (char);
	//cin.ignore(1);
	cin.ignore(1000, '\n');
	cin.get(city, 50);
	//cout << city;
	
	Client cl;
	cl.Connect();
	cl.RunInsertParamSQL(username, password, birthday, city);
	cl.close();
}

void  User::SignIn(){
	username = new (char);
	password = new (char);
	city = new (char);
	cout << "Nhap vao username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	city = username;
	//password = sha1(password);
	Client cl;

	// gui clentsever
	cl.Connect();
	cl.RunSelectParamSQL(username, password);
	if (strlen(cl.ID) > 0) {
		cout << "Sign in successfuly!\n";
		cout << "Hello " << username << "\n";
		
		flag = 1;
	}
	else {
		cout << "Sign in fail!\n";
		flag = 0;
	}
	//conn.SelectUser1();
	cl.close();
}

void User::SignOut(){
	flag = 0;
	cout << "-----Ban da dang xuat.-------\n";
}

bool User::isSignIn(){

	if (flag == 1) return true;
	return false;
}

void User::ShowMessdrec(){
	
	cout << flag; 
	Client cl;
	
	if (isSignIn()){
		char *id2;
		id2 = new char;
		cout << "Chon nguoi dung: \n";
		char *frien;
		frien = new char;
		cin >> frien;
		//m.lock();

		// 	hiên bạn bè
		cl.Connect();
		cl.ShowFriend(id);
		cl.close();
		// kiem tra va hien tin nhan
		cl.Connect();
		cl.TransNameToId(frien);
		cl.close();


		int guilai;
		cout << "gui lai an ctrl + R \n";
		guilai = _getch();
		cout << guilai;
		if (guilai == 18){
			cout << guilai << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
			cl.Connect();
			SendMess(id);
			cl.close();
		}
		if (guilai != 18) {
			cout << "---------Da Thoat----------\n";
		}
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}

}
void User::ShowMesssen(int id){
	Client cl;
	if (isSignIn()){
		char *id2;
		id2 = new char;
		cout << "Chon nguoi dung: \n";
		char *frien;
		frien = new char;
		cin >> frien;
		//m.lock();
		
		// 	hiên bạn bè
		cl.Connect();
		cl.ShowFriend(id);
		cl.close();
		// kiem tra va hien tin nhan
		cl.Connect();
		cl.TransNameToId(frien);
		cl.close();
		
		
		int guilai;
		cout << "gui lai an ctrl + R \n";
		guilai = _getch();
		cout << guilai;
		if (guilai == 18){
			cout << guilai << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
			cl.Connect();
			SendMess(id);
			cl.close();
		}
		if (guilai != 18) {
			cout << "---------Da Thoat----------\n";
		}
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
	
}
void User::SendMess(int id){
	if (isSignIn()){
		Client cl;
		int id2;
		cout << "Chon nguoi dung:( Ctrl + L de hien danh sach ban be) \n";
		char *frien;
		frien = new char;
		char name;
		name = _getch();
		if (name == 12){
	
			cout << "danh sach ban be\n";
			cl.Connect();
			cl.ShowFriend(id);
			cl.close();
		//	conn.ShowListFriend(conn.db, id);
			//ShowListFriend(id);
		//	cout << conn.ten << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

		//	memcpy(frien, conn.ten.c_str(), sizeof(conn.ten));
			cout << "nhap ten tai khoan muon gui\n";
			cin >> frien;

		}
		else{
			cout << "nhap ten tai khoan muon gui\n";
			
			cin >> frien;

		}
	//	cout << "To :" << frien << "      \n";
		
		cl.Connect();
		cl.SendMess(frien);
		cl.close();
		//cout << id2;
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}

void User::AddFriend(int id){
	Client cl;
	
	if (isSignIn()){
		cout << "Nhap ten nguoi ban muon them: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		cl.Connect();
		cl.AddFriend(newfr);
		cl.close();
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
	
}

void User::ShowFriend(int id){

	if (isSignIn()){
		char *id2;
		//m.lock();
		Client cl;
		// 	hiên bạn bè
		cl.Connect();
		cl.ShowFriend(id);
		cl.close();
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
/*
void User::BlockFriend(int id1){
	m.lock();
	if (isSignIn()){
		cout << "---------Chon nguoi block :(-------- \n";
		char *name;
		name = new char;
		cin >> name;
		ConnectSQlite conn;
		conn.Open();
		int id2 = conn.TransNameToId(name);
		if (id2 > 0){
			conn.BlockFriend(conn.db, id1, id2);
			cout << "---------Block Successfuly---------\n";
			conn.ShowFriend(conn.db, id1);
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
	m.unlock();
}
void User::Showcity(int id){
	if (isSignIn()){
		ConnectSQlite conn;
		conn.Open();
		int id2;
		cout << "nhap id2\n";
		int sen;

		cin >> id2;

		cout << "thay doi";
		cin >> sen;
		cout << "hien thi";		//conn.Showcity(city);
		conn.UpdateMessage(id, id2);
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}

}
*/
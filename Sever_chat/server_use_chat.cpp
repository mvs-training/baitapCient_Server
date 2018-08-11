/*
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "server_chat.h"
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
#include <Thread>
#include <mutex>
#include <windows.h>
std::mutex m;
using namespace std;



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
	ConnectSQlite conn;
	conn.Open();

	conn.RunInsertParamSQL(username, password, birthday, city);
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
	ConnectSQlite conn;
	conn.Open();

	if (conn.RunSelectParamSQL(username, password) > 0) {
		cout << "Sign in successfuly!\n";
		cout << "Hello " << username << "\n";
		id = conn.RunSelectParamSQL(username, password);
		flag = 1;

	}
	else {
		cout << "Sign in fail!\n";
		flag = 0;
	}
	//conn.SelectUser1();
}
void User::nameuser(){
	if (isSignIn()){
		cout << "                         *********************************\n";
		cout << "                         **   Hello :   " << username << "  **\n";
	}
	else{ cout << "\n"; }
}
void User::SignOut(){
	flag = 0;
	cout << "-----Ban da dang xuat.-------\n";
}
bool User::isSignIn(){
	ConnectSQlite conn;
	if (flag == 1) return true;
	return false;
}

void User::ShowMessdrec(int id){

	if (isSignIn()){
		int id2;
		cout << "Chon nguoi dung: \n";
		char *frien;
		frien = new char;
		//cin >> frien;
		m.lock();
		ConnectSQlite conn;
		conn.Open();

		conn.ShowFriend(conn.db, id);
		conn.ShowListFriend(conn.db, id);
	//	cout << conn.ten << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

		memcpy(frien, conn.ten.c_str(), sizeof(conn.ten)); // chuyển chuỗi kiểu tra sang kiểu string từ string ten --> in ra  char * frien
		id2 = conn.TransNameToId(frien);
		if (id2 > 0){

			cout << "Gui tu *** " << frien << " ***den :\n";
			conn.ShowMessdrec(id2, id);
			conn.UpdateMessage(id2, id);
			// khi an ctrl + r
			int guilai;
			char *mess, *dt;
			mess = new char;
			dt = new char;
			cout << "gui lai an ctrl + R \n";
			guilai = _getch();
			cout << guilai;
			if (guilai == 18){
				//cout << guilai;
				cout << "To : " << frien << "\n";
				cout << "Nhap Tin nhan: \n";
				cin.ignore(1);
				cin.get(mess, 200);
				//cout << mess;
				//cin >> mess;

				time_t hientai = time(0);
				dt = ctime(&hientai);
				int sent = 0;
				conn.WriteToMess(conn.db, id, id2, mess, dt, sent);
			}
			if (guilai != 18) {

				cout << "---------Da Thoat----------\n";
			}
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
		m.unlock();

	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void User::ShowMesssen(int id){

	if (isSignIn()){
		int id2;
		cout << "Chon nguoi dung: \n";
		char *frien;
		frien = new char;
		//cin >> frien;
		m.lock();

		ConnectSQlite conn;
		conn.Open();

		conn.ShowFriend(conn.db, id);
		conn.ShowListFriend(conn.db, id);
	//	cout << conn.ten << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		memcpy(frien, conn.ten.c_str(), sizeof(conn.ten)); // chuyển chuỗi kiểu tra sang kiểu string từ string ten --> in ra  char * frien
		id2 = conn.TransNameToId(frien);
		if (id2 > 0){

			cout << "Gui tu *** " << frien << " ***den :\n";
			conn.ShowMessDetail(conn.db, id, id2);
			int guilai;
			char *mess, *dt;
			mess = new char;
			dt = new char;
			cout << "gui lai an ctrl + R \n";
			guilai = _getch();
			cout << guilai;
			if (guilai == 18){
				//cout << guilai;
				cout << "To : " << frien << "\n";
				cout << "Nhap Tin nhan: \n";
				cin.ignore(1);
				cin.get(mess, 200);
				//cout << mess;
				//cin >> mess;

				time_t hientai = time(0);
				dt = ctime(&hientai);
				int sent = 0;
				conn.WriteToMess(conn.db, id, id2, mess, dt, sent);
			}
			if (guilai != 18) {

				cout << "---------Da Thoat----------\n";
			}
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
		m.unlock();

	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}


}

void User::SendMess(int id){

	if (isSignIn()){
		int id2;
		cout << "Chon nguoi dung:( Ctrl + L de hien danh sach ban be) \n";
		char *frien;
		frien = new char;
		char name;
		name = _getch();
		if (name == 12){
			m.lock();

			ConnectSQlite conn;
			conn.Open();
			cout << "danh sach ban be\n";
			conn.ShowFriend(conn.db, id);
			conn.ShowListFriend(conn.db, id);
			//ShowListFriend(id);
		//	cout << conn.ten << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

			memcpy(frien,conn.ten.c_str(), sizeof(conn.ten));

		}
		else{

			cin >> frien;

		}
		cout << "To :" << frien << "      \n";
		ConnectSQlite conn;
		conn.Open();
		id2 = conn.TransNameToId(frien);
		//cout << id2;
		if (id2 > 0){
			char *mess, *dt;
			mess = new char;
			dt = new char;
			if (!conn.CheckBlock(conn.db, id, id2)){

				cout << "---------You is blocked by her--------\n";
			}
			else{
				cout << "Nhap Tin nhan: \n";
				//cin >> mess;
				cin.ignore(1);
				cin.get(mess, 200);
				time_t hientai = time(0);
				dt = ctime(&hientai);
				int sent = 0;
				conn.WriteToMess(conn.db, id, id2, mess, dt, sent);
				//conn.ShowMessDetail(conn.db,id,id2);

			}

			m.unlock();
		}
		else cout << "----Tai khoan khong ton tai-----------\n";

	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}


}

void User::AddFriend(int id){

	if (isSignIn()){
		cout << "Nhap ten nguoi ban muon them: ";
		char *newfr, *dt;
		newfr = new char;
		cin >> newfr;
		m.lock();
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
			}
			else {
				cout << "------You were blocked by her  or You was friend ----------\n\n\n";
				//conn.CheckFriend(conn.db,id,id2);
			}
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
		m.unlock();

	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}

}

void User::ShowFriend(int id){
	m.lock();

	if (isSignIn()){
		ConnectSQlite conn;
		conn.Open();
		conn.ShowFriend(conn.db, id);
		int sapsep;
		cout << "Ctrl + C de hien danh sach theo thanh pho\n an bat ky de tro lai\n";
		sapsep = _getch();
		if (sapsep == 3){
			conn.CityID(username);
			conn.Showcity(city, id);
		}if (sapsep != 3){
			cout << "*.--------------.*\n";
		}
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
	m.unlock();

}

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


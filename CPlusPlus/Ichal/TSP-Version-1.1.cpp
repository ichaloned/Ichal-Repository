//	GraphProject.cpp : Defines the entry point for the console application.
//	function by Faizal Ramadhan
//	©2013 Faizal Ramadhan | 125150300111028 | SISKOM-B | Angkatan 2012
//	-------------------------------------------------------------------------------------------------------------
//	Version 1.1 || Monday, 11.20 PM **  05/27/2013
//	* Added "nest_print", now can used more than 5 cities / point / nodes
//	* "z" variable (global) deleted, useless variable
//	* change "global_loop" variable to declaration separator for "dot[]" and "max_input"
//	* a Little fix :3
//	-------------------------------------------------------------------------------------------------------------
//  =============================================================================================================
//	Change Logs :
//  Version 0.1 [Beta]
//	* Initial Release
//	Version 0.2 [Beta]
//	* Fix Manually Input, "Point" and "Distance" Input separated
//	* Delete Magic Input, Because Possibily All Point will be not connected
//	Version 0.3 [Beta] - Version 0.5 [Beta]
//	* Silent Build
//	Version 0.6 [Beta] || Saturday, 3:26 AM ** 05/25/2013
//	* Start to build Process Function, using Recrusive Algorithm
//	* Added "export_data", "get_start", "start_again", "factorial", and "print_min" Function
//	* Added Linked List for saving & printing "way of point" after get the total of distance
//	* Added "Brute Force" Algorithm [Experimental, not Fixed yet]
//	* Using Static array at the moment until "Process" function working perfectly
//	Version 0.7 [Beta] - Version 0.8 [Beta]
//	* Silent Build, Trying Fixing the "BruteForce" Algorithm!
//	Version 0.9 [Beta] || Monday, 1:10 AM ** 05/27/2013
//	* Process 90% Functional
//	* Using Nested Loop for "BruteForce" Algorithm #NEW
//	* Remove Linked List
//	* Deleted all unnessersary variable, because older "BruteForce" Algorithm
//	* Increase the dimension of array (default + 1), becausing can be messing up!
//	* Source Code Now More Clean :3
//	Version 0.9 [Beta] Build 2 (Version 0.9.2) || Monday, 11:38 AM ** 05/27/2013
//	* TSP Algorithm Fixed, #distance still messed up#
//	* Process now 95% Functional
//	Version 1.0 || Monday, 8.25 PM **  05/27/2013
//	* Process 100% Functional :D
//	* Using "check_up" function to cleaning the nested loop at "process" function
//	* All Function Fixed
//	* Can be Used only for 5 point / nodes / cities
//	* Change Variable Declaration place, because "hi-size" variable can be messed up the variable below them
//	=============================================================================================================
//	Known Bug :
//	* Code still dirty, need clean up :3
//	* variable "cur_value" messed up in start, but it is not a big problem
//	* Unknown bugs, need a tester for find a bugs
//  =============================================================================================================

using namespace std;

//	==== Libraries ====
#include "stdafx.h"										// Needed for Visual Studio
#include <iostream>;
#include <stdio.h>;
#include <conio.h>;
#include <Windows.h>;


//	===== Function =====
void insert();											// Function Untuk menambah point dan distance
void search();											// Function Untuk menampilkan detail point
void process();											// Function Untuk mencari jalan tercepat ke semua point
void print();											// Function Menampilkan semua point dan distance dengan bentuk tabel
void export_data();										// Function untuk memindahkan nilai "ex_" ke nilai asli
void print_min();										// Function untuk menampilkan hasil TSP tercepat / terpendek
void nest_print();										// Function untuk printing "Walking Point"
void in_dot();											// Function untuk memindahkan "nest_arry" ke "dot[]"
void in_value();										// Function untuk memproses nilai terkecil
bool check_up();										// Function pengganti nested loop di "process()" function

//	===== Global Variable ====
bool point[5][5];										// Variable Point
bool pInput[5][5];										// Variable untuk melihat bahwa Variable "point" sudah terisi atau belum
int cur_value = 0;										// Variable penyimpan jumlah jarak terpendek
int dist[6][6];											// Variable Distance dari "point" ke "point" (note : dimension must -> max cities + 1)
int nest_arry[5];										// Variable penyebut apakah point 'x' dan point 'y' sudah terlewati
bool separator_var[5];									// Useless variable, untuk memisahkan deklarasi "nest_arry[]" dan "ex_value" agar tidak hancur
int ex_value = 0;										// Variable penyimpan jumlah jarak sementara
int dot[5];												// Variable penyimpan nodes / cities / point terpendek
int separator_var2 = 1;									// Useless variable, untuk memisahkan deklarasi "dot[]" dan "max_input" agar tidak hancur
int max_input = 5;										// Variable untuk menyimpan banyaknya point yang ingin dimasukkan
//  =============================================================================================================

void main(){											// Detele "void" if using Dev C++
	char pilih;
	do{
		system("cls");
		cout << "============ Main Menu ============\n";
		cout << "===================================\n";
		cout << "1. Insert\n";
		cout << "2. Process\n";
		cout << "3. Search and Show Detail\n";
		cout << "4. Print All\n";
		cout << "Press 'q' to exit\n";
		cout << "===================================\n";
		cout << "Masukkan input : "; cin >> pilih;
		switch(pilih){
		case '1' : insert(); break;
		case '2' : process(); break;
		case '3' : search(); break;
		case '4' : print(); break;
		case 'q' : exit; break;
		}
	}while(pilih != 'q');
}

void init_arry(int x, int y, int in){
	dist[x][y] = in;
	dist[y][x] = in;
}

void insert(){
	int x = 1;
	int y = 1;
	int z = 0;
	int jarak = 0;
	// Connecting point to point
	while(1){
		if(pInput[x][y] == 1){
			x = x + 1;
			if(x > max_input){ x = 1; y = y + 1; }
			if(y > max_input){ break; }
			continue;
		}
		system("cls");
		cout << "Hubungkan point '" << x << "' dengan point '" << y << "' ?\n";
		cout << "1. Iya\n";
		cout << "0. Tidak\n";
		cout << "Masukkan pilihan : "; cin >> z; cout << "\n";
		if(z == 1){
			point[x][y] = 1;
			point[y][x] = 1;
			pInput[x][y] = 1;
			pInput[y][x] = 1;
		} else{
			point[x][y] = 0;
			point[y][x] = 0;
			pInput[x][y] = 1;
			pInput[y][x] = 1;
		}
		if(y == max_input){ break; }
		x = x + 1;
		if(x > max_input){ x = 1; y = y + 1; }
	}

	// Input a distance between connection point
	x = 1;
	y = 1;
	while(1){
		if(point[x][y] == 1 && dist[x][y] == NULL){
			system("cls");
			cout << "Masukkan jarak point '" << x << "' dan point '" << y << "' : "; cin >> jarak; cout << "\n";
			init_arry(x, y, jarak);
			if(y == max_input){ break; }
			x = x + 1;
			if(x > max_input){ x = 1; y = y + 1; }
		} else{
			if(y == max_input){ break; }
			x = x + 1;
			if(x > max_input){ x = 1; y = y + 1; }
		}
	}
	cout << "Data berhasil di masukkan !\n"; system("pause");
}

void search(){
	int x = 1;
	int y = 1;
	int input = 0;
	cout << "Masukkan point yang ingin dicari : "; cin >> input; cout << "\n";
	if(input <= max_input && input > 0){
		x = input;
		while(1){
			if(point[x][y] == 1){
				cout << "Point '" << x << "' Berhubungan dengan Point '" << y << "' berjarak : " << dist[x][y] << "\n";
				if(y == max_input){ break; }
				y = y + 1;
			} else{
				if(y == max_input){ break; }
				y = y + 1;
			}
		}
	} else{
		cout << "Point yang anda cari tidak ditemukan !\n";
	}
	system("pause");
}

void print(){
	int x = 1;
	int y = 1;
	int tab_x = 1;
	int tab_y = 1;
	cout << "==================== Point ====================\n";
	cout << "\t";
	while(1){
		cout << tab_x << "\t";
		tab_x = tab_x + 1;
		if(tab_x > max_input){ break; }
	}
	cout << "\n\n";
	while(1){
		cout << tab_y << "\t";
		while(1){
			cout << point[x][y] << "\t";
			if(x == max_input){ x = 1; y = y + 1; tab_y = tab_y + 1; break; }
			x = x + 1;
		}
		cout << "\n";
		if(y > max_input){ cout << "\n"; break; }
	}
	cout << "===============================================\n";
	cout << "=================== Distance ==================\n";
	x = 1;
	y = 1;
	tab_x = 1;
	tab_y = 1;
	cout << "\t";
	while(1){
		cout << tab_x << "\t";
		tab_x = tab_x + 1;
		if(tab_x > max_input){ break; }
	}
	cout << "\n\n";
	while(1){
		cout << tab_y << "\t";
		while(1){
			cout << dist[x][y] << "\t";
			if(x == max_input){ x = 1; y = y + 1; tab_y = tab_y + 1; break; }
			x = x + 1;
		}
		cout << "\n";
		if(y > max_input){ cout << "\n"; break; }
	}
	cout << "===============================================\n";
	system("pause");
}

void print_min(){
	int a = 1;
	cout << "Point tercepat yang dilalui : ";
	while(a <= max_input){
		cout << dot[a] << " ";
		a = a + 1;
	}
	cout << "\nDengan jarak : " << cur_value << "\n";
}

void nest_print(){
	int a = 1;
	while(1){
		cout << nest_arry[a] << "\t";
		a = a + 1;
		if(a > max_input){ break; }
	}
	cout << "\n";
}

bool check_up(){
	int a = 1;
	int b = 1;
	while(1){
		if(a > max_input){ break; }
		if(a == b){
			b = b + 1;
			if(b > max_input){
				a = a + 1;
				b = 1;
				continue;
			}
			continue;
		}
		if(nest_arry[a] == nest_arry[b]){ return 1; }
		b = b + 1;
		if(b > max_input){
			a = a + 1;
			b = 1;
		}
	}
	a = 1;
	while(1){
		if(a == max_input){ return 0; break; }
		if(point[nest_arry[a]][nest_arry[a+1]] == 0){ return 1; }
		a = a + 1;
	}
}

void process(){
	int a = max_input;
	int b = 1;
	while(1){
		if(nest_arry[1] > max_input){ break; }
		nest_arry[max_input] = nest_arry[max_input] + 1;
		cout << "Walking Point : \n";
		if(check_up() == 0){ export_data(); }
		nest_print();
		print_min();
		system("cls");
		while(1){
			if(a < 2){ break; }
			if(nest_arry[a] > max_input - 1){
				if(nest_arry[1] > max_input){ break; }
				nest_arry[a-1] = nest_arry[a-1] + 1;
				nest_arry[a] = 1;
			}
			a = a - 1;
		}
		a = max_input;
	}
	cout << "Walking Point : \n";
	nest_print();
	print_min();
	system("pause");
}


void export_data(){
	if(cur_value == 0){
		in_dot();
	}
	in_value();
	if(ex_value < cur_value){
		cur_value = ex_value;
		in_dot();
	}
	ex_value = 0;
}

void in_dot(){
	int a = 1;
	while(1){
		dot[a] = nest_arry[a];
		a = a + 1;
		if(a > max_input){ break; }
	}
}	

void in_value(){
	int value = 0;
	int a = 1;
	if(cur_value == 0){
		while(1){
			cur_value = cur_value + dist[nest_arry[a]][nest_arry[a+1]];
			a = a + 1;
			if(a == max_input){ break; }
		}
	} else{
		while(1){
			ex_value = ex_value + dist[nest_arry[a]][nest_arry[a+1]];
			a = a + 1;
			if(a == max_input){ break; }
		}
	}
}


//	Graph Project
//	function by Faizal Ramadhan
//	©2013 Faizal Ramadhan | 125150300111028 | SISKOM-B | Angkatan 2012

//  Latihan Tree AVL.cpp : Defines the entry point for the console application.
//	function by Faizal Ramadhan
//	©2013 Faizal Ramadhan | 125150300111028 | SISKOM-B | Angkatan 2012
//  =============================================================================================================
//  Version 0.4 [Beta]
//	* All Basic Print Tree Successfully added, Using "Rekrusif" Algorithm
//	* Search Min Max Value Added
//	* Search Data Added
//	* Re-Format Script
//	* Fixed :
//		- Print Tree View Still using Next and Prev (bad, should using Right and Left -> increase search time)
//  =============================================================================================================
//	Change Logs :
//	Version 0.1 [Beta]
//	* Initial Build
//	------------------------------------------------------
//	Version 0.2 [Beta]
//	* Adding previous for Linked List (I forgot :P)
//  * Trying Add Print With Basic 3 Reading on Tree (PreOrder, PostOrder, and InOrder)
//  Build 2 :
//  * PreOder Successfully Added [Ver. 0.2 Build 2]
//	------------------------------------------------------
//	Version 0.3 [Beta]
//	* Temporary Remove Basic 3 Reading on Tree, because infinite condition (searching for algorithm at the moment)
//	* Trying to add Delete Function
//	------------------------------------------------------
//  Known Bugs :
//  - All AVL Function Unavailable at the moment, maybe next release
//  - Print will be buggy if there is a node with same value
//  =============================================================================================================


// ================== Library ==================
using namespace std;
#include "stdafx.h"									// Require for Visual Studio, disable this if using DevC++
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

//================== Struct ==================
struct node{
	int data;										// Variable Data / Number / Nodes
	int level;										// Variable Penentu Level dari Node
	char direction;									// Variable Penentu Direction dari Node (Right, Left, or Center?)
	int parentVar;									// Variable untuk mengambil "Data" data dari parent (Untuk Print)
	node *next;										// next Node (pointer Linked List)
	node *prev;										// previous Node (pointer Linked List)
	node *right;									// right direction of node (pointer Tree)
	node *left;										// left direction of node (pointer Tree)
	node *parent;									// Variable Parent (Tree)
	node *child;									// Variable Child (Tree)
};typedef struct node node;

//================== Global Variable ==================
// Pointer Variable
node *root;											// Variable ROOT (Tree)
node *head;											// Variable Head (Linked List)
node *tail;											// Variable Tail (Linked List)
// Standart Variable
int AVL_Stat = 0;									// Variable ON/OFF AVL Input
int banyak_data = 0;								// Variable Banyaknya Node / Data
int max_level = 0;									// Variable check berapa level tertinggi
int data_avail = 0;									// Required for searchInOrder function
char centerDir = 'c';								// Variable center = 'c'
char rightDir  = 'r';								// Variable right  = 'r'
char leftDir   = 'l';								// Variable left   = 'l'

//================== Function ==================
void Insert();										// Insert Node BST + Linked List
//void InsertAVL();									// Insert Node AVL + Linked List
void Print();										// Print All Node with Tree Interface
void PrintLS();										// Print All Node with Linked List Interface
//void Delete();									// Delete BST + Linked List
//void DeleteAVL();									// Delete AVL + Linked List
void Setting();										// Setting about turn ON/OFF AVL Insertion
//void ConvertAVL();								// Convert BST --> AVL with Rebuilding Tree
void getMaxLVL();									// Function to Search maximum level
void preOrder(node *tWalker);						// Function preOrder Tree Print
void inOrder(node *tWalker);						// Function inOrder Tree Print
void postOrder(node *tWalker);						// Function postOrder Tree Print
void search();										// Function Search data and show parent and level
void Min_Max();										// Function Show the Value Max and Min
void searchInOrder(node *tWalker, int input);		// Function Search Data Using In-Order 


void main(){
	char pilihan;
	do{
		system("cls");
		cout << "=============================================\n";
		cout << "================= Main Menu =================\n";
		cout << "Banyak data : " << banyak_data << "\n";
		if(AVL_Stat == 1){
			cout << "AVL Status  : ON\n";
		}
		if(AVL_Stat == 0){
			cout << "AVL Status  : OFF\n";
		}
		cout << "1. Insert\n";
		cout << "2. Delete\n";
		cout << "3. Print Tree Version\n";
		cout << "4. Print Linked List Version\n";
		cout << "5. Search Data\n";
		cout << "6. Show Min & Max \n";
		cout << "7. Setting\n";
		cout << "Press 'q' to Exit\n";
		cout << "=============================================\n";
		cout << "Input Here : "; cin >> pilihan;

		switch(pilihan){
		case '1': /*if(AVL_Stat == 1){ InsertAVL(); }*/	if(AVL_Stat == 0){ Insert(); } break;
		case '2': /*if(AVL_Stat == 1){ DeleteAVL(); }*/	//if(AVL_Stat == 0){ Delete(); } break;
		case '3': Print(); break;
		case '4': PrintLS(); break;
		case '5': search(); break;
		case '6': Min_Max(); break;
		case '7': Setting(); break;
		case 'q': break;
		default	: cout << "Input Yang anda masukkan salah!, Silahkan Masukkan sekali lagi!\n"; system("pause"); break;
		}
	}while(pilihan != 'q');
}


void Insert(){
	node *tWalker;
	tWalker = root;
	node *pTemp = NULL;
	node *temp;
	temp = (node *)malloc(sizeof(node));
	int input;
	int level = 1;
	cout << "Silahkan Input data baru : "; cin >> input;
	temp -> data = input;

	if(head == NULL || root == NULL){
		// Input Linked List
		head = temp;
		tail = temp;
		head -> next = NULL;
		head -> prev = NULL;

		// Input BST Tree
		temp -> level = level;
		temp -> direction = centerDir;				// Because ROOT doesnt have any direction (center anyway :D)
		temp -> right = NULL;
		temp -> left  = NULL;
		root = temp;
	} else{
		// Input Linked List
		tail -> next = temp;
		temp -> prev = tail;
		tail = temp;
		tail -> next = NULL;

		// Input BST Tree
		level = 1;
		// Searching NULL Node and ready to input new node
		while(tWalker != NULL){
			if(temp -> data > tWalker -> data){
				pTemp = tWalker;
				tWalker = tWalker -> right;
				level = level + 1;
			} else{
				if(temp -> data < tWalker -> data){
					pTemp = tWalker;
					tWalker = tWalker -> left;
					level = level + 1;
				} else{
					if(temp -> data == tWalker -> data){
						pTemp = tWalker;
						break;
					}
				}
			}
		}

		// Magic Start Here! :3

		if(temp -> data > pTemp -> data){
			temp -> level = level;
			temp -> direction = rightDir;
			temp -> parent = pTemp;
			temp -> parentVar = pTemp -> data;
			pTemp -> child = temp;
			pTemp -> right = temp;
			temp -> right = NULL;
			temp -> left  = NULL;
		} else{
			if(temp -> data < pTemp -> data){
				temp -> level = level;
				temp -> direction = leftDir;
				temp -> parent = pTemp;
				temp -> parentVar = pTemp -> data;
				pTemp -> child = temp;
				pTemp -> left  = temp;
				temp -> right = NULL;
				temp -> left  = NULL;
			} else{
				if(temp -> data == pTemp -> data){
					temp -> level = pTemp -> level;
					temp -> direction = pTemp -> direction;
					temp -> parent = pTemp -> parent;
					temp -> parentVar = pTemp -> parentVar;
					pTemp -> child = temp -> child;
					pTemp -> left = temp -> left;
					pTemp -> right = temp -> right;
				}
			}
		}
	}
	banyak_data = banyak_data + 1;
}

void Print(){
	node *pWalker;
	node *tWalker;
	node *ParTemp = NULL;
	pWalker = head;
	tWalker = root;
	getMaxLVL();
	int levl = 1;
	if(head != NULL){

		// ========================== Print Based on Level ==========================
		while(1){
			if(levl == 1){
				cout << "Level 1 : [" << tWalker -> data << "] Merupakan Root dari Tree\n";
				levl = levl + 1;
			} else{
				if(levl > max_level){ break; }
				cout << "Level " << levl << " : \n";
				cout << "Right : [n(p)] ";
				while(1){
					if(pWalker -> level == levl && pWalker -> direction == rightDir){
						cout << "[" << pWalker -> data << "(" << pWalker -> parentVar << ")] "; 
					}
					pWalker = pWalker -> next;
					if(pWalker == NULL){ cout << "\n"; pWalker = head; break; }
				}
				cout << "Left  : [n(p)] ";
				while(1){
					if(pWalker -> level == levl && pWalker -> direction == leftDir){
						cout << "[" << pWalker -> data << "(" << pWalker -> parentVar << ")] "; 
					}
					pWalker = pWalker -> next;
					if(pWalker == NULL){ cout << "\n"; pWalker = head; break; }
				}
				levl = levl + 1;
			}
		}
		// ========================== Print Based on Level ==========================

		// ============== Print Based on Pre-Order, Post-Order, and In-Order ==============
		cout << "\nPre-Order : "; preOrder(root); cout << "\n";
		cout << "In-Order  : "; inOrder(root); cout << "\n";
		cout << "Post-Order: "; postOrder(root); cout << "\n";
		// ============== Print Based on Pre-Order, Post-Order, and In-Order ==============

	} else{
		cout << "Data Masih Kosong\n";
	}
	cout << "\n\nNote : \nn = Node / Data\np = Parent\n";
	system("pause");
}

void PrintLS(){
	node *pWalker;
	pWalker = head;
	int a = 0;
	if(head != NULL){
		while(1){
			if(pWalker == root){
				cout << "Data ke-" << a << ", bernilai : " << pWalker -> data << " merupakan Root dari Tree (" << pWalker -> direction << ")\n";
			}
			else {
				cout << "Data ke-" << a << ", bernilai : " << pWalker -> data << " mempunyai parent : " << pWalker -> parentVar << " (" << pWalker -> direction << ")\n";
			}
			pWalker = pWalker -> next;
			a = a + 1;
			if(pWalker == NULL){
				break;
			}
		}
		cout << "\n";
	} else{
		cout << "Data Masih Kosong\n";
	}
	system("pause");
}

//void Delete(){
//	node *tWalker;
//	int input;
//	cout << "Silahkan masukkan data yang ingin dihapus!"; cin >> input;
//}



void Setting(){
	char pilihan;
	char confirm;
	do{
		system("cls");
		cout << "=============================================\n";
		cout << "================== Setting ==================\n";
		if(AVL_Stat == 1){
			cout << "AVL Status  : ON\n";
		}
		if(AVL_Stat == 0){
			cout << "AVL Status  : OFF\n";
		}
		cout << "1. Turn ON/OFF AVL Insertion\n";
		cout << "Press 'q' for back to Main Menu\n";
		cout << "=============================================\n";
		cout << "Input Here : "; cin >> pilihan;

		switch(pilihan){
		case '1' :
			if(AVL_Stat == 0){ 
				if(banyak_data >= 1){
					cout << "Mengaktifkan AVL Insertion akan membangun kembali Tree!, Lanjutkan?\n";
					cout << "1. Lanjutkan, dan membangun Tree ulang\n";
					cout << "2. Jangan lanjutkan, biarkan berbentuk BST\n";
					cout << "Pilihan : "; cin >> confirm;
					if(confirm == 1){
						AVL_Stat = 1; 
						//ConvertAVL();
						break;
					}
				} else{ AVL_Stat = 1; break;}
			} 
			if(AVL_Stat == 1){ AVL_Stat = 0; } break;
		case 'q' : break;
		default	 : cout << "Input Yang anda masukkan salah!, Silahkan Masukkan sekali lagi!\n"; system("pause"); break;
		}
	}while(pilihan != 'q');
}

void getMaxLVL(){
	node *pWalker;
	pWalker = head;
	max_level = pWalker -> level;
	while(1){
		if(pWalker -> level >= max_level){
			max_level = pWalker -> level;
		}
		pWalker = pWalker -> next;
		if(pWalker == NULL){ break; }
	}

}

void preOrder(node *tWalker){
	if(tWalker != NULL){
		cout << tWalker -> data << " ";
		if(tWalker -> left) { preOrder(tWalker -> left); }
		if(tWalker -> right) { preOrder(tWalker -> right); }
	} else return;
}

void inOrder(node *tWalker){
	if(tWalker != NULL){
		if(tWalker -> left) { inOrder(tWalker -> left); }
		cout << tWalker -> data << " ";
		if(tWalker -> right) { inOrder(tWalker -> right); }
	} else return;
}

void postOrder(node *tWalker){
	if(tWalker != NULL){
		if(tWalker -> left) { postOrder(tWalker -> left); }
		if(tWalker -> right) { postOrder(tWalker -> right); }
		cout << tWalker -> data << " ";
	} else return;
}

void search(){
	int input;
	node *tWalker = root;
	cout << "Masukkan data yang ingin dicari : "; cin >> input; cout << "\n";
	searchInOrder(root, input);
	if(data_avail == 0){ cout << "Data yang anda cari tidak ada!\n"; }
	system("pause");
}

void searchInOrder(node *tWalker, int input){
	if(tWalker != NULL){
		if(tWalker -> data == input){ cout << "Nilai : " << tWalker -> data << ", Parent : " << tWalker -> parentVar << ", Level : " << tWalker -> level << "\n"; data_avail = 1;}
		if(tWalker -> left) { searchInOrder(tWalker -> left, input); }
		if(tWalker -> right) { searchInOrder(tWalker -> right, input); }
	} else return;
}


void Min_Max(){
	node *tWalker;
	tWalker = root;
	while(tWalker -> left != NULL){
		tWalker = tWalker -> left;
	}
	cout << "Nilai Minimal  : " << tWalker -> data << "\n";
	tWalker = root;
	while(tWalker -> right != NULL){
		tWalker = tWalker -> right;
	}
	cout << "Nilai Maksimal : " << tWalker -> data << "\n";
	system("pause");
}

//	function by Faizal Ramadhan
//	©2013 Faizal Ramadhan | 125150300111028 | SISKOM-B | Angkatan 2012
//	Version 0.4 [Beta]
//	Do not copy this source code without permission!

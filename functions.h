#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include<fstream>
//#include <stdio.h>
//#include "clui.h"
//#include <conio.h>
#include <cstring>
#include <ctime>
#include <thread>
#include <iomanip> 
#include <cstdio>
#include <stdlib.h>
//#include <windows.h>
// #include <iomanip> 
// #include <chrono>
// #include <termios.h>
// #include <Cocoa/Cocoa.h>


using namespace std ; 
void menu();
int sign_in_page();
void simple_loading();
void loading();
void thread_loading();
void sign_up();
void sign_in() ;
string encrypt(string);
string decrypt(string) ;
//void new_game() ;
void select_difficulty();
void easy();
void easy_soduko();
void moderate();
void moderate_sudoku();
void hard();
void hard_soduko();
void clock(int , int , int);
inline void printer();
void hidecursor();
void curser(int,int);
void changer(int , int , int);

#endif
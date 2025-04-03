//starting date : 29 Jan : 1:50 pm
#include <iostream>
#include<fstream>
//#include <stdio.h>
#include "functions.h"
#include "clui.h"
//#include <conio.h>
#include <cstring>
#include <thread>
#include <ctime>
#include <iomanip> 
#include <cstdio>
#include <stdlib.h>
//#include <windows.h>
// #include <iomanip> 
// #include <chrono>
// #include <termios.h>
// #include <Cocoa/Cocoa.h>


using namespace std ; 


int main()
{
    srand (time(NULL));
    rand() ; rand() ; rand() ;
    clear_screen();
    simple_loading();
    clear_screen();
    sign_in_page();
    //cout <<sign_in_page();
    getch();
    return 0 ; 

}
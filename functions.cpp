//to do : log file / heart / timer / leaderboard / save game / load game /;
#include <iostream>
//#include <stdio.h>
#include "functions.h"
#include "clui.h"
#include<fstream>
//#include <conio.h>
#include <cstring>
#include <ctime>
#include <iomanip> 
//include <cstdio>
#define MAX_USERNAME 100
#include <stdlib.h>
#include <thread>
#include <iomanip> 
#include <cstdio>
// #include <chrono>
// #include <termios.h>
// #include <Cocoa/Cocoa.h>
// #ifdef _WIN32
// #include <windows.h>
// #endif

// void hidecursor() {
//     NSCursor.hide()
// }
//#include <windows.h>
// #include <conio.h>
struct cordinate {
    int x , y ; 
};
cordinate datas[81];
using namespace std ;
int x_curser = get_window_rows()/2 - 8 , y_curser = get_window_cols()/2 - 25 ;

void hidecursor() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    printf("\033[?25l"); 
}

// void hidecursor() {
//     HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//     CONSOLE_CURSOR_INFO info;
//     info.dwSize = 100; 
//     info.bVisible = FALSE; 
//     SetConsoleCursorInfo(consoleHandle, &info);
// }

void menu()
{
    int choice ; 
    clear_screen();
    string first = "1.Start a New Game" ;
    string second = "2.Play a Saved Game";
    string leader = "3.Leader Board";
    string quit = "4.Exit";
    string game_name = "SUDOKU";
    string underline = "_______________________" ;
   cursor_to_pos(get_window_rows()/2 , get_window_cols()/2 - game_name.length()/2) ;
   change_color(14);
   cout << game_name ; 
   cursor_to_pos(get_window_rows()/2 +1  , get_window_cols()/2 - underline.length()/2) ;
   change_color(3);
   cout << underline ;
   cursor_to_pos(get_window_rows()/2 +3, get_window_cols()/2 - first.length()/2) ;
   change_color(3);
   cout << first ;
   cursor_to_pos(get_window_rows()/2 +4, get_window_cols()/2 - second.length()/2) ;
   change_color(3);
   cout << second ;
   cursor_to_pos(get_window_rows()/2 +5, get_window_cols()/2 - leader.length()/2) ;
   change_color(3);
   cout << leader ;
   cursor_to_pos(get_window_rows()/2 +6, get_window_cols()/2 - quit.length()/2) ;
   change_color(3);
   cout << quit ;
   cursor_to_pos(get_window_rows()/2 +7, get_window_cols()/2 -1) ;
   cout << ">" ;
   reset_color ;
   cursor_to_pos(get_window_rows()/2 +7, get_window_cols()/2 ) ;
    cin >> choice ; 
    switch(choice) 
    {
        case 1 : 
        {
            select_difficulty();
        }break;
        case 2 : 
        {
sign_in_page();
            delay(500);
        }break;
        case 3 :
        {
sign_in_page();
            delay(500);
        }break;
        case 4 : 
        {
            sign_in_page();
            delay(500);
        }break ;
        default : {
            clear_screen() ; 
            cursor_to_pos(get_window_rows()/2 , get_window_cols()/2 - 22 ) ; 
            change_color(13);
            cout << "Please Enter a number between 1 / 2 / 3 / 4 ";
            delay(1000) ;
            menu();
            };
    }







}

int sign_in_page()
{
    clear_screen();
    int choice = 0 ; 
    cursor_to_pos(get_window_rows()/5 , 4);
    //change_color_rgb(5, 83, 166) ;
    change_color(3);
    //std::cout << "\033[31m" << "This is red text." << "\033[0m" << std::endl;  // Red text
    //change_background_color(3);
    cout << "Log in to your account : ";
    reset_color();
    //change_color_rgb()
    cout  <<endl;
    cursor_to_pos(get_window_rows()/5 +3 , 4);
    change_color(2);
    cout << "1.Log In" << endl ;
    cursor_to_pos(get_window_rows()/5+5, 4);
    change_color(2);
    cout << "2.Sign Up" << endl; 
    cursor_to_pos(get_window_rows()/5+6, 5);
    change_color(2);
    cout << ">";
    cursor_to_pos(get_window_rows()/5+6, 6);
    reset_color();
    cin >> choice ;
    //return choice ; 
    //int choice = sign_in_page();
    switch(choice)
    {
        case 1: {
            sign_in();
    }break;
        case 2: {
            sign_up();
    }break;
        default : {
            clear_screen();
                        cursor_to_pos(get_window_rows()/2 , get_window_cols()/2 - 18) ; 
            change_color(12);
            cout << "Please Enter a number between 1 / 2 ";
            delay(1000) ;
            sign_in_page();



        }
        break ; 
    }
    getch();
    

}
void thread_loading()
{
  int u = get_cursor_x() ; 
    int e = get_cursor_y();
    clear_screen();
    //int seconds = 600 ; 
    thread l1([](){
        loading();
    });
    
    thread l2([](){
        simple_loading();//sudoku template
    });
    
    l1.join();
    l2.join();
  //  easy_soduko();

}
void loading()
{
    cursor_to_pos(2,2);
cout << "Loading..." << endl;
        delay(800);cout<<"\u2713";
        
        cout << "Accessing User Data..." << endl;
            cursor_to_pos(3,2);
        delay(800);cout<<"\u2713";
        cout << "Checking Game Files Health..." << endl;
            cursor_to_pos(4,2);
        delay(800);cout<<"\u2713";
        cout << "Checking System Time..." << endl;
            cursor_to_pos(5,2);
        delay(800);cout<<"\u2713";
        cout << "Loading Background Activities..." << endl;
            cursor_to_pos(6,2);
        delay(800);cout<<"\u2713";
        cout << "Preparing Templates...." << endl;
}
void simple_loading()
{
     //cursor_to_pos(get_window_rows()-2, 0);
    for (int i = 0 ; i < 50 ; i++);
    {
         delay(300);cout<<"\u2713";
        
        cout << "Accessing User Data..." << endl;

        delay(300);cout<<"\u2713";
        cout << "Checking Game Files Health..." << endl;



        delay(300);cout<<"\u2713";
        cout << "Loading Background Activities..." << endl;

        delay(300);cout<<"\u2713";
        cout << "Preparing Templates...." << endl;
        cout << "loading...." << endl;




        delay(1000);
        change_background_color(2);
        cursor_to_pos(get_window_rows()-2, 0);
        for(int j = 0 ; j < 50 ; j++) {cout << "." ; delay(100);};
        // clear_screen();
    } reset_color();
}
void sign_up()
{
    clear_screen();
    bool sameuser = false ;
    string input ;
    //string inputs[MAX_USERNAME];
    string* inputs = new string[MAX_USERNAME] ;
    int i = 0 ;

    ifstream file4("all_usernames");
    if(file4.is_open())
    {
        while(file4 >> input)
        {
            inputs[i] = input ;
            i++;
        }
    }else {
       cout << "\u26A0" << " " <<"ERR : The File that countains all username could not open!";
    }

    clear_screen();
    string user_name, password ;
    cursor_to_pos(get_window_rows()/5 , 4);
    change_color(3);
    cout << "Username : " ;
    reset_color();
    cin >> user_name ;
    for(int i = 0 ; i < MAX_USERNAME ; i++ )
    {
        if(inputs[i] == user_name)
        {
            sameuser = true ; 
            
            delay(500);
            
        }
       
    }
    if(sameuser == true)
    {
        change_color(4);
        clear_screen();
        cursor_to_pos(get_window_rows()/2 , get_window_cols()/2 - 25);

        cout << "\u26A0" << " " << "ERR : A user with the same username Already Exist!" ;
        cursor_to_pos(get_window_rows()/2 +1 , get_window_cols()/2 - 25);
         cout << endl << "These are some recomendations for you: " << endl ; 
            delay(1000) ;
            for (int j = 0 ; j<3 ; j++)//3 recoms only
            {
                cursor_to_pos(get_window_rows()/2 + i + 3, get_window_cols()/2 - 25);
                cout << ". "<<user_name << rand();
                delay(1000) ;
            } delay(2000) ; sign_in_page();
    }
    if(sameuser == false)
    {
        cursor_to_pos(get_window_rows()/5 + 2, 4);
    change_color(3);
    cout << "Password : " ;
    reset_color();
    cin >> password ;
    ofstream file("all_usernames" , ios::app);
     if(file.is_open())
     {
        file << user_name <<endl; 
     }else{
        cout << "\u26A0" << " " <<"ERR : The File that countains all username could not open!";
    }
    ofstream file1(user_name , ios::app);
    if(file1.is_open())
     {
        //string enc_pass = encrypt(password);
        file1 << user_name << endl<< password;
     }else{
        cout << "\u26A0" << " " <<"ERR : The File that countains all username could not open!";
    }
    }
    clear_screen();
    cursor_to_pos(get_window_rows()/2 , get_window_cols()/2) ;
    change_color(5);
    clear_screen();
    cursor_to_pos(get_window_rows()/2 , get_window_cols()/2) ;
    change_color(8);
    cout << "For Your Own safty You will need to log in to the account you just created..";
    sign_in_page();
    delete[] inputs ;
}
void sign_in()
{
    clear_screen();
    string user ; 
    string password_check ; 
    string user_name , password ;
    bool is_found = false;
    cursor_to_pos(get_window_rows()/5 , 4);
    change_color(6);
    cout << "Username : " ;
    reset_color();
    cin >> user_name ;
    //if(user_name == "admin") {easy_soduko();}
    string input ;
    //string inputs[MAX_USERNAME] ; 
    string* inputs = new string[MAX_USERNAME];
    int k = 0 ;
    //clear_screen();
    //string user_name , password ; 
    ifstream file5("all_usernames");
    if(file5.is_open())
    {
        while(file5 >> input)
        {
            inputs[k] = input ;
            k++;
        }
        for(int u = 0  ; u < MAX_USERNAME ; u++)
        {
            if(inputs[u] == user_name)
            {
                is_found = true ; 
            }
        }
    }else {
         cout << "\u26A0" << " " <<"ERR : The File that countains all username could not open!";
    }

    if(is_found == true)
    {
        change_color(6) ;
        cursor_to_pos(get_window_rows()/5 + 2, 4);
         cout << "Password : " ;
             reset_color();
             cin >> password ; 
            ifstream file6(user_name);
                    if (file6.is_open())
                    {
                        getline(file6 , user) ; 
                        getline(file6 , password_check) ;
                    }else {
                        cout << "\u26A0" << " " <<"ERR : There was an issue accessing the user data please try again later or log in with another account !";
                        delay(500); sign_in_page();
                    }
        
    }else {
        clear_screen();
        cursor_to_pos(get_window_rows()/2 , get_window_cols()/2);
        cout << "\u26A0" << " " <<"ERR : No Such a username found Please Sign Up!";
        delay(500) ;
        sign_in_page();
    }
    if(password != password_check || password.length() != password_check.length())
    {
        cout << "\u26A0" << " " <<"ERR : Incorrect Password! Try Again!";
        delay(500) ; sign_in_page();
    }else {
        change_color(3) ;
         cursor_to_pos(get_window_rows()/5 + 4, 5);
        cout << "You Have successfully Logged In to your Account With user name : " << user_name ; 
        change_color(3); 
        cursor_to_pos(get_window_rows()/5 + 5, 5);
        cout  << "Have fun Playing!";
        delay(2000);
        menu();
    }
    delete[] inputs ;
}
string encrypt(string pass)
{
    string result ;
    int i = 0 ;
    while (pass[i+1] != '\0')
    {
        result[i] = pass[i] + 1; 
        i++;
    }
    cout << "result :" <<result ; 
    return result ; 
}
string decrypt(string pass)
{
    string result ; 
    int i = 0 ;
    while (pass[i+1] != '\0')
    {
        result[i] = pass[i] - 1  ; 
        i++;
    }
    return result ; 
}

void select_difficulty()
{
    int choice ; 
    clear_screen();
    string first = "1.Easy" ;
    string second = "2.Moderate";
    string leader = "3.Hard";
    string quit = "4.Sign In with different Account";
    string _menu = "5.Back to Menu" ;
    string game_name = "Select Difficulty";
    string underline = "_______________________" ;
   cursor_to_pos(get_window_rows()/2 , get_window_cols()/2 - game_name.length()/2) ;
   change_color(6);
   cout << game_name ; 
   cursor_to_pos(get_window_rows()/2 +1  , get_window_cols()/2 - underline.length()/2) ;
   change_color(6);
   cout << underline ;
   cursor_to_pos(get_window_rows()/2 +3, get_window_cols()/2 - first.length()/2) ;
   change_color(6);
   cout << first ;
   cursor_to_pos(get_window_rows()/2 +4, get_window_cols()/2 - second.length()/2) ;
   change_color(6);
   cout << second ;
   cursor_to_pos(get_window_rows()/2 +5, get_window_cols()/2 - leader.length()/2) ;
   change_color(6);
   cout << leader ;
   cursor_to_pos(get_window_rows()/2 +6, get_window_cols()/2 - quit.length()/2) ;
   change_color(6);
   cout << quit ;
   cursor_to_pos(get_window_rows()/2 +7, get_window_cols()/2 - _menu.length()/2) ;
   change_color(6);
   cout << _menu ;

   cursor_to_pos(get_window_rows()/2 +8, get_window_cols()/2 -1) ;
   cout << ">" ;
   reset_color ;
   cursor_to_pos(get_window_rows()/2 +8, get_window_cols()/2 ) ;
    cin >> choice ; 
    switch(choice) 
    {
        case 1 : 
        {
           easy();
        }break;
        case 2 : 
        {
            moderate();
        }break;
        case 3 :
        {
            hard();
        }break;
        case 4 : 
        {
            delay(200);
            sign_in_page();
            delay(200);
        }break ;
        case 5 :
        {
            delay(200);
            menu();
            delay(200);

        }break ;
        default : {
            clear_screen() ; 
            cursor_to_pos(get_window_rows()/2 , get_window_cols()/2 - 22 ) ; 
            change_color(13);
            cout << "Please Enter a number between 1 / 2 / 3 / 4 / 5";
            delay(1000) ;
            menu();
            };
    }






}

void easy()
{
    int u = get_cursor_x() ; 
    int e = get_cursor_y();
    clear_screen();
    int seconds = 300 ; 
    thread timer([seconds , u , e](){
        clock(seconds , u , e );
    });
    
    thread easy_soduko_([](){
        easy_soduko();//sudoku template
    });
    timer.join();
    easy_soduko_.join();
    easy_soduko();

    clear_screen();
    //clock(600);
    //cursor_to_pos(2 , cursor_col()/2 - 2);
    // string* _easy = new string[81];
    // ifstream file7("easy");
    // if(file7.is_open())






    //delete[] _easy ;
}



// else {
//      cout << "\u26A0" << " " <<"ERR : There was an issue accessing the soduko template please try again later or log in with another account !";
//      delay(500);
//      sign_in_page();
     
// }
void easy_soduko()
{

    int answer_input ; 
    int* answer = new int[81];

    ifstream file15("easy_answer");
    // int start_i_answer = i_start_answer , start_j_asnwer = j_start_answer;
    //     cursor_to_pos(get_window_rows()/2 +start_i_answer ,get_window_cols() / 2 + start_j_asnwer);
        int o = 0 ; 
        while(file15 >> answer_input)
        {
            answer[o] = answer_input ;
            //cout << i_s[index] << endl;
            o++ ;
        }


// for(int u = 0 ; u < 81 ; u++)
// {
// cout << answer[u] ;
// }







    int trtr ;
    int char1 ;
    cursor_to_pos(get_window_rows()/2 , get_window_cols()/2);
    int i_start = -8 , j_start = -25 ;
    int color = 0 ; 
    int inputed;
    //clear_screen();
    change_color(color);
   
    int* i_s = new int[81];
    ifstream file11("easy");
    int index = 0 ; 
    int j = 0 ;
    
    if(file11.is_open())
    {
        int start_i = i_start , start_j = j_start;
        cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
        while(file11 >> inputed)
        {
            i_s[index] = inputed ;
            //cout << i_s[index] << endl;
            index++;
        }






        for(int i = 0 ; i <= 9 ; i++)
        {
            
            //cout << i_s[i] << endl;
            for( ; j < i * 9  ; j++)
            {
                if(j%3 == 0)
                {
                    //cout << "     " ;
                     start_j += 5 ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
                    
                }
                if(i_s[j] != 0)
                {
                    cout << i_s[j] ;//<< " " << " ";
                    datas[j].x = get_cursor_x();
                    datas[j].y = get_cursor_y();
                    start_j += 2 ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
                    if(color>14) color = 0 ;
                    color++ ; 
                    change_color(color);
                }else{
                    cout << " " ;//<< " " << " " ; 
                     start_j += 2 ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
                    if(color>14) color = 0 ;
                    color++ ; 
                    change_color(color);
                }
                
                
            }
            if(i%3 == 0){//cout << endl<<endl << endl << endl ;
             start_i += 4 ;
             start_j = j_start ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
             if(color>14) color = 0 ;
                    color++ ; 
                    change_color(color);}
            else{//cout << endl << endl ;
             start_i += 2 ;
             start_j = j_start;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j); if(color>14) color = 0 ;
                    color++ ; 
                     change_color(color);}
        }
    reset_color();







    }
   // file11.close();
    // }else{
        
    //  cout << "\u26A0" << " " <<"ERR : There was an issue accessing the soduko template please try again later or log in with another account !";
    //  delay(500);
    //  sign_in_page();
     

    // }
     int x = get_cursor_x()/2 ;
    int y = get_cursor_y()/2 ;
        //cout << "\x1B[?25l"; // ANSI escape sequence to hide cursor
            curser(x, y);
         
    //cursor_to_pos(x, y);
    //cursor_to_pos(get_cursor_x()/2-7 , get_cursor_y()/2-25);
    while(true)
    {
       
        //change_character_background(x ,  y , 20 , 90 , 181);
        char1 = getchar();
        switch(char1)
        {
            case 119 : { //UP
                x_curser--;
                x-- ; 
                 curser(x , y);
                cursor_to_pos(x_curser , y_curser);//...
                //hidecursor();

                // x_curser = get_cursor_x();
                // y_curser = get_cursor_y();

                //cursor_up(1);
                
                break;
            }
            case 115 : { //DOWN

               x_curser++;
               x++ ; 
                curser(x , y);
                cursor_to_pos(x_curser , y_curser);//...
                 //hidecursor();
                // x_curser = get_cursor_x();
                // y_curser = get_cursor_y();
                //cursor_down(1); 
                
                break;
            }
            case 100 : { //RIGHT

                y_curser++;
                y++ ;
                 curser(x , y);
                   cursor_to_pos(x_curser , y_curser);//...
                    //hidecursor();

                // x_curser = get_cursor_x();
                // y_curser = get_cursor_y();
                //cursor_forward(1);
                
                break;
            }
            case 97 :{ //LEFT
                y_curser--;
                y--;
                 curser(x , y);
                cursor_to_pos(x_curser , y_curser);//...
                 //hidecursor();
                // x_curser = get_cursor_x();
                // y_curser = get_cursor_y();
                //cursor_backward(1);
                 
                break;
            }
            case '0'...'9' : 
            {
                trtr = char1 - '0' ;
               // changer(x_curser,y_curser,trtr);
               for(int y = 0 ; y < 81 ; y++)
               {
                if(datas[y].x == x_curser && datas[y].y == y_curser)
                {
                    if(answer[y] == i_s[y])
                    {
                        changer(x_curser , y_curser , trtr);
                    }
                }break;
               }

            }
        
        }
        
    }






        
    delete[] i_s ;
    delete [] answer ;
}





        
void moderate()
{


int u = get_cursor_x() ; 
    int e = get_cursor_y();
    clear_screen();
    int seconds = 180 ; 
    thread timer([seconds , u , e](){
        clock(seconds , u , e );
    });
    
    thread moderate_soduko_([](){
        easy_soduko();//sudoku template
    });
    timer.join();
    moderate_soduko_.join();
    moderate_sudoku();

    clear_screen();

}


void moderate_sudoku()
{
int i_start = -8 , j_start = -25 ;
    int color = 0 ; 
    int inputed;
    clear_screen();
    change_color(color);
   
    int* i_s = new int[81];
    ifstream file12("moderate");
    int index = 0 ; 
    int j = 0 ;
    
    if(file12.is_open())
    {
        int start_i = i_start , start_j = j_start;
        cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
        while(file12 >> inputed)
        {
            i_s[index] = inputed ;
            //cout << i_s[index] << endl;
            index++;
        }
        for(int i = 0 ; i <= 9 ; i++)
        {
            
            //cout << i_s[i] << endl;
            for( ; j < i * 9  ; j++)
            {
                if(j%3 == 0)
                {
                    //cout << "     " ;
                     start_j += 5 ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
                    
                }
                if(i_s[j] != 0)
                {
                    cout << i_s[j] ;//<< " " << " ";
                    start_j += 2 ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
                    if(color>14) color = 0 ;
                    color++ ; 
                    change_color(color);
                }else{
                    cout << " " ;//<< " " << " " ; 
                     start_j += 2 ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
                    if(color>14) color = 0 ;
                    color++ ; 
                    change_color(color);
                }
                
                
            }
            if(i%3 == 0){//cout << endl<<endl << endl << endl ;
             start_i += 4 ;
             start_j = j_start ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
             if(color>14) color = 0 ;
                    color++ ; 
                    change_color(color);}
            else{//cout << endl << endl ;
             start_i += 2 ;
             start_j = j_start;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j); if(color>14) color = 0 ;
                    color++ ; 
                     change_color(color);}
        }
    }else{
        
     cout << "\u26A0" << " " <<"ERR : There was an issue accessing the soduko template please try again later or log in with another account !";
     delay(500);
     sign_in_page();
     

    }
    delete[] i_s ;

}
void hard()
{
 int u = get_cursor_x() ; 
    int e = get_cursor_y();
    clear_screen();
    int seconds = 120 ; 
    thread timer([seconds , u , e](){
        clock(seconds , u , e );
    });
    
    thread hard_soduko_([](){
        easy_soduko();//sudoku template
    });
    timer.join();
    hard_soduko_.join();
    easy_soduko();

    clear_screen();
     
}





void hard_soduko()
{
    int i_start = -8 , j_start = -25 ;
    int color = 0 ; 
    int inputed;
    clear_screen();
    change_color(color);
   
    int* i_s = new int[81];
    ifstream file13("hard");
    int index = 0 ; 
    int j = 0 ;
    
    if(file13.is_open())
    {
        int start_i = i_start , start_j = j_start;
        cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
        while(file13 >> inputed)
        {
            i_s[index] = inputed ;
            //cout << i_s[index] << endl;
            index++;
        }
        for(int i = 0 ; i <= 9 ; i++)
        {
            
            //cout << i_s[i] << endl;
            for( ; j < i * 9  ; j++)
            {
                if(j%3 == 0)
                {
                    //cout << "     " ;
                     start_j += 5 ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
                    
                }
                if(i_s[j] != 0)
                {
                    cout << i_s[j] ;//<< " " << " ";
                    start_j += 2 ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
                    if(color>14) color = 0 ;
                    color++ ; 
                    change_color(color);
                }else{
                    cout << " " ;//<< " " << " " ; 
                     start_j += 2 ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
                    if(color>14) color = 0 ;
                    color++ ; 
                    change_color(color);
                }
                
                
            }
            if(i%3 == 0){//cout << endl<<endl << endl << endl ;
             start_i += 4 ;
             start_j = j_start ;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j);
             if(color>14) color = 0 ;
                    color++ ; 
                    change_color(color);}
            else{//cout << endl << endl ;
             start_i += 2 ;
             start_j = j_start;
                    cursor_to_pos(get_window_rows()/2 +start_i ,get_window_cols() / 2 + start_j); if(color>14) color = 0 ;
                    color++ ; 
                     change_color(color);}
        }
    }else{
        
     cout << "\u26A0" << " " <<"ERR : There was an issue accessing the soduko template please try again later or log in with another account !";
     delay(500);
     sign_in_page();
     

    }getch();//remove this later: 
    delete[] i_s ;
}
void clock(int milliseconds , int x , int y)
{
    cursor_to_pos(2 , get_window_cols()/2 - 2);
    //clear_screen();
    
    for(int i = milliseconds ; i > 0 ; i-- )
    {
       
        cursor_to_pos(2 , get_window_cols()/2 - 10);
        
        int min = i / 60 ;
        printf("0%d:%d%d" , min , (i-60*min)/10  , (i-60*min)%10);
        delay(1000);
        //clear_screen();
        cursor_to_pos(3 , get_window_cols()/2 - 17);
        change_color(11);
        cout << "____________________";
        
    }
    
    cursor_to_pos(x , y);
}

void curser( int x ,  int y)
{

    //hidecursor();
    //  x = get_cursor_x() ;
    //  y = get_cursor_y() ; 
    change_character_background(x ,  y , 255 , 0 , 0);
}
//20, 90, 181


void changer(int x, int y, int to)
{
    cursor_to_pos(x , y) ;
    cout << to ;
}
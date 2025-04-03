#ifndef _CLUI
#define _CLUI
#include<fstream>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64) || defined(WI32)
#define OS_UNIX 0
#include <Windows.h>
#include <conio.h>
#define _NO_OLDNAMES // for MinGW compatibility
#define getch _getch
#define kbhit _kbhit
#else
#define OS_UNIX 1
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#endif

#define COLOR_DEFAULT 0
#define COLOR_RED 1
#define COLOR_BOLD_RED 2
#define COLOR_GREEN 3
#define COLOR_BOLD_GREEN 4
#define COLOR_YELLOW 5
#define COLOR_BOLD_YELLOW 6
#define COLOR_BLUE 7
#define COLOR_BOLD_BLUE 8
#define COLOR_MAGENTA 9
#define COLOR_BOLD_MAGENTA 10
#define COLOR_CYAN 11
#define COLOR_BOLD_CYAN 12

#define COLOR_ORANGE_1 13
#define COLOR_ORANGE_2 14
#define COLOR_ORANGE_3 15

#define BG_DEFAULT 0
#define BG_BLUE 1
#define BG_CYAN 2
#define BG_GREEN 3
#define BG_PURPLE 4
#define BG_RED 5
#define BG_WHITE 6
#define BG_YELLOW 7

void flush();
void __enable_raw_mode();
void __disable_raw_mode();
bool is_keyboard_hit();
void clear_screen();
void change_color_rgb(int r, int g, int b);
void change_color(int color);
void change_background_color(int color);
void reset_color();
void quit();
void init_clui();
void delay(size_t milli_seconds);
int get_window_rows();
int get_window_cols();
int get_cursor_x();
int get_cursor_y();
void cursor_up(int n);
void cursor_down(int n);
void cursor_forward(int n);
void cursor_backward(int n);
void cursor_to_pos(int row, int col);
void save_cursor();
void restore_cursor();
void play_beep();
int getch();
int nb_getch(void);
void change_character_background(int , int , int , int , int );


#endif
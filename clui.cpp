#include "clui.h"

void flush()
{
    fflush(stdout);
    fflush(stderr);
}

void __enable_raw_mode()
{
#if OS_UNIX
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
#else


#endif
}

void __disable_raw_mode()
{
#if OS_UNIX
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
#else

#endif
}

bool is_keyboard_hit()
{
#if OS_UNIX
    static struct termios oldt, newt;
    int cnt = 0;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_iflag = 0;     // input mode
    newt.c_oflag = 0;     // output mode
    newt.c_cc[VMIN] = 1;  // minimum time to wait
    newt.c_cc[VTIME] = 1; // minimum characters to wait for
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ioctl(0, FIONREAD, &cnt); // Read count
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100;
    select(STDIN_FILENO + 1, NULL, NULL, NULL, &tv); // A small time delay
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return cnt > 0;
#else
    return kbhit();
#endif
}

#if OS_UNIX
int getch()
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON /* | ECHO */);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#endif

int nb_getch(void)
{
    if (is_keyboard_hit())
        return getch();
    else
        return 0;
}

void clear_screen()
{
#if OS_UNIX
    system("reset");
    system("clear");
#else
    system("CLS");
#endif
}

void change_color_rgb(int r, int g, int b)
{
    if (0 <= r && r <= 255
        && 0 <= g && g <= 255
        && 0 <= b && b <= 255) {
        printf("\033[38;2;%d;%d;%dm", r, g, b);
        
        flush();
    }
}

void change_color(int color)
{
    const char* colors[] = { "[0m", "[0;31m", "[1;31m", "[0;32m",
        "[1;32m", "[0;33m", "[1;33m", "[0;34m",
        "[1;34m", "[0;35m", "[1;35m", "[0;36m",
        "[1;36m", "[38;5;202m", "[38;5;208m", "[38;5;214m" };

    if (color >= 0 && color <= 15) {
        printf("\033");
        printf("%s", colors[color]);
    }
    flush();
}

void change_background_color(int color)
{
    const char* colors[] = { "[40m", "[44m", "[46m", "[42m",
        "[45m", "[41m", "[47m", "[43m" };

    if (color >= 0 && color <= 7) {
        printf("\033");
        printf("%s", colors[color]);
    }
    flush();
}

void reset_color()
{
    change_color(COLOR_DEFAULT);
}

void quit()
{
    reset_color();
    __disable_raw_mode();
    clear_screen();
    exit(0);
}

static void sigint_handler(int dummy)
{
    (void)dummy;
    quit();
}

void init_clui()
{
    clear_screen();
    signal(SIGINT, sigint_handler);
    __enable_raw_mode();
    flush();
}

void delay(size_t milli_seconds)
{
    flush();
#if OS_UNIX
    usleep(1000 * milli_seconds);
#else
    Sleep(milli_seconds);
#endif
}

int get_window_rows()
{
#if OS_UNIX
    struct winsize max;
    ioctl(0, TIOCGWINSZ, &max);
    return (int)max.ws_row;
#else
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
#endif
}

int get_window_cols()
{
#if OS_UNIX
    struct winsize max;
    ioctl(0, TIOCGWINSZ, &max);
    return (int)max.ws_col;
#else
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
#endif
}

int get_cursor_x()
{
    flush();
    int x = 0;
#if OS_UNIX
    const char* const cmd = "IFS=\";\" read -sdR -p $'\"'\\E[6n'\"' ROW COL;\
                             echo \"${ROW#*[}\" > /tmp/cursor_row";

    char cmd_bash[200];
    sprintf(cmd_bash, "bash -c '%s' ", cmd);
    int status = system(cmd_bash);
    if (status != 0) {
        return 0;
    }
    FILE* fp = fopen("/tmp/cursor_row", "r");
    if (fp == NULL) {
        return 0;
    }
    fscanf(fp, "%d", &x);
    fclose(fp);
#else
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    x = csbi.dwCursorPosition.Y + 1;
#endif
    return x;
}

int get_cursor_y()
{
    flush();
    int y = 0;
#if OS_UNIX
    const char* const cmd = "IFS=\";\" read -sdR -p $'\"'\\E[6n'\"' ROW COL;\
                             echo \"${COL#*[}\" > /tmp/cursor_col";

    char cmd_bash[200];
    sprintf(cmd_bash, "bash -c '%s' ", cmd);
    int status = system(cmd_bash);
    if (status != 0) {
        return 0;
    }
    FILE* fp = fopen("/tmp/cursor_col", "r");
    if (fp == NULL) {
        return 0;
    }
    fscanf(fp, "%d", &y);
    fclose(fp);
#else
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    y = csbi.dwCursorPosition.X + 1;
#endif
    return y;
}

void cursor_up(int n)
{
    printf("\033[%dA", n);
    flush();
}

void cursor_down(int n)
{
    printf("\033[%dB", n);
    flush();
}

void cursor_forward(int n)
{
    printf("\033[%dC", n);
    flush();
}

void cursor_backward(int n)
{
    printf("\033[%dD", n);
    flush();
}

void cursor_to_pos(int row, int col)
{
    printf("\033[%d;%dH", row, col);
    flush();
}

void save_cursor()
{
    printf("\0337");
    flush();
}

void restore_cursor()
{
    printf("\0338");
    flush();
}

void play_beep()
{
    printf("\07");
    flush();
}


void change_character_background(int row, int col, int r, int g, int b) {
    if (0 <= r && r <= 255 && 0 <= g && g <= 255 && 0 <= b && b <= 255) {
        printf("\0337");
        flush();
        printf("\033[%d;%dH", row, col);
        flush();
        printf("\033[48;2;%d;%d;%dm", r, g, b);
        flush();
    }
}

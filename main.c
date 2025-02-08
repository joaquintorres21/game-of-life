#define program_loop for(;;)
#define routine_loop for(;;)

//To include an exit.
#include <stdlib.h>

#include <curses.h>
//Included for tick refreshing
#include <time.h>
//Included for multithreading
#include <windows.h>
//The program declarations.
#include "automaton.h"

int update();

char ui_print(char cursor, char state, int* dimension);

char controller(char* cursor_memory_address, char* simulation_state_address);


Cell **gen_pointer;
char cursor, sim_state;
int screen_dimension[2], last_dim[2];

int main(){

    cursor = sim_state = 0;
    last_dim[0] = last_dim[1] = 0;

    //Initialization settings.
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    program_loop{

        getmaxyx(stdscr, screen_dimension[1], screen_dimension[0]);
        if(screen_dimension[1] != last_dim[1] || screen_dimension[0] != last_dim[0]) clear(); 
        ui_print(cursor, sim_state, screen_dimension);
        mvprintw(screen_dimension[1] - 5, screen_dimension[0] - 5, "%d", cursor);
        controller(&cursor, &sim_state);
        update();
        last_dim[0] = screen_dimension[0];
        last_dim[1] = screen_dimension[1];
    
    }
}

char ui_print(char cursor, char state, int* screen){

    if(cursor<1) attron(A_REVERSE);
    mvprintw(1, 1, "[ START ]");
    attroff(A_REVERSE);

    if(cursor==1) attron(A_REVERSE);
    mvprintw(3, 1, "[ PAUSE ]");
    attroff(A_REVERSE);

    if(cursor==2) attron(A_REVERSE);
    mvprintw(5, 1, "[ RESTART ]");
    attroff(A_REVERSE);

    if(cursor==3) attron(A_REVERSE);
    mvprintw(7, 1, "[ EXIT ]");
    attroff(A_REVERSE);

    if(state) mvprintw(1, screen[0] - 10, "PAUSED");
    else mvprintw(1, screen[0] - 10, "      ");
    
    return 0;

}

char controller(char* cursor_ptr, char* sim_ptr){
    
    int c = getch();
    if(c == '\n'){
        switch(*(cursor_ptr)){
            case 0: 
                *(sim_ptr) = 0;
                break;
            case 1: 
                *(sim_ptr) = 1;
                break;
            case 2:
                break;
            case 3:
                exit(0);
        }
    }
    if(c == KEY_UP) *cursor_ptr -= 1;
    if(c == KEY_DOWN) *cursor_ptr += 1;
    
    *(cursor_ptr) = *(cursor_ptr) < 0 ? *(cursor_ptr) + 4 : *(cursor_ptr) % 4;
    return 0;
}

int update(){
    clock_t time_0;
    time_0 = clock();
    
    routine_loop{

        if((clock() - time_0) > 100) break;
    
    }
    return refresh();
}


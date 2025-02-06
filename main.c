#define program_loop for(;;)
#define routine_loop for(;;)

#include <curses.h>
//Included for tick refreshing
#include <time.h>
//Included for multithreading
#include <windows.h>

//The program declarations.
#include "automaton.h"

int update(); //Used for refreshing


int main(){
    program_loop{
        initscr();
        addch('*');
        update();
    }
}

int update(){
    clock_t time_0, time_1;
    int delta_time;
    time_0 = clock();
    routine_loop{
        time_1 = clock();
        delta_time = time_1 - time_0;
        if(delta_time > 1000) break;
    }
    return refresh();
}
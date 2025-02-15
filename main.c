#define program_loop for(;;)
#define routine_loop for(;;)

#define NCURSES_MOUSE_VERSION

//Visualize the result.
#include <curses.h>

//To include an exit.
#include <stdlib.h>

//Included for refreshing
#include <time.h>

//The program declarations.
#include "automaton.h"

Cell *first = NULL;

int update(int state);
void ui_print(char state, int* dimension);
void controller(char* simulation_state_address);
void print_cells(Cell *first_cell, char print_or_del);

MEVENT event;
char sim_state;
int screen_dimension[2], last_dim[2], mouse_pos[2];

int main(){

    sim_state = 1;
    last_dim[0] = last_dim[1] = 0;

    //Initialization settings.
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, screen_dimension[1], screen_dimension[0]);

    program_loop{
        
        //Previously the program had a menu with a cursor, now are just buttons
        ui_print(sim_state, screen_dimension);
        controller(&sim_state);
        
        if(!sim_state){
            sim(&first, screen_dimension);
            clear();
        }

        print_cells(first, PRINT);
        update(sim_state);
        
    }

}

void ui_print(char state, int* screen){

    mvprintw(0, 0, "Z - Resume/Pause | X - Restart | C - Exit");
    mvprintw(10,0,"%d : %d", screen[0], screen[1]);
    if(state) mvprintw(1, screen[0] - 10, "PAUSED");
    else mvprintw(1, screen[0] - 10, "      ");
    
}

void print_cells(Cell *first, char print_or_del){
    
    Cell *current = first;
    int print = print_or_del ? ' ' : ICON;
    while(current){
        mvprintw(current->position[1], current->position[0], "%c", print);
        current = current->next;
    }
    return;

}

void controller(char* sim_ptr){
    
    int c = getch();
    if(c == KEY_MOUSE){
        if(!nc_getmouse(&event)){

            if(event.bstate & BUTTON1_CLICKED){

                Cell *temp = first;
                
                mouse_pos[0] = event.x;
                mouse_pos[1] = event.y;

                if(is_alive(mouse_pos[0], mouse_pos[1])) return;
                if(temp) {
                    while(temp->next) temp = temp->next;
                    temp->next = new_cell(mouse_pos);
                }
                else first = new_cell(mouse_pos);

            }

            return;
        }
    }

    if(c == 'Z' || c == 'z'){
        *(sim_ptr) = !(*(sim_ptr));
        return;
    }

    if(c == 'X' || c == 'x'){
        if(first) {
            kill_all(first); 
            clear();
            first = NULL;
        } 
        return;
    }

    if(c == 'C' || c == 'c'){
        exit(0);
    }

    return;
}

int update(int sim){
    clock_t time_0;
    time_0 = clock();
    int x = sim ? 10 : 750;
    routine_loop{
        if((clock() - time_0) > x) break;
    }
    return refresh();
}

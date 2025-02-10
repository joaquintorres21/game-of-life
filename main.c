#define program_loop for(;;)
#define routine_loop for(;;)

//Visualize the result.
#include <curses.h>

//To include an exit.
#include <stdlib.h>

//Included for refreshing
#include <time.h>

//Included for multithreading on array roaming.
#include <windows.h>

//The program declarations.
#include "automaton.h"

Cell *first = NULL;

int update();
void ui_print(char state, int* dimension);
void controller(char* simulation_state_address);
void print_cells(Cell *first_cell);

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

        ui_print(sim_state, screen_dimension);
        controller(&sim_state);
        update();
    
    }

}

void ui_print(char state, int* screen){

    mvprintw(0, 0, "Z - Resume/Pause | X - Restart | C - Exit");
    if(state) mvprintw(1, screen[0] - 10, "PAUSED");
    else mvprintw(1, screen[0] - 10, "      ");
    
}

void print_cells(Cell *first){
    
    Cell *current = first;
    while(current){
        mvprintw(current->position[1], current->position[0], "%c", 254);
        current = current->next;
    }
    return;

}

void controller(char* sim_ptr){
    
    int c = getch();
    if(c == KEY_MOUSE){
        if(nc_getmouse(&event) == OK){

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
        kill_all(first);
        return;
    }

    if(c == 'C' || c == 'c'){
        exit(0);
    }

    return;
}

int update(){
    clock_t time_0;
    time_0 = clock();
    routine_loop{
        if((clock() - time_0) > 100) break;
    }
    return refresh();
}
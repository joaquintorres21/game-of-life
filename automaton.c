#include "automaton.h"

#include <stdlib.h>

#define PDC_LOG
#include <curses.h>

Cell *new_cell(int *position){
    
    Cell *my_cell = (Cell*)malloc(sizeof(Cell));
    my_cell->position = (int*)malloc(2*sizeof(int));
    my_cell->position[0] = position[0];
    my_cell->position[1] = position[1];
    my_cell->next = NULL;
    return my_cell;

}

void sim(Cell **first_add){

    Cell *current = *first_add;
    if(!*first_add) return;
    Cell *temp; 
    char neighbor_count;
    char i = -1, j;
    int dyn_pos[2];
    if((neighbor_count = near_alive(current->position)) < 2 || neighbor_count < 3){
        *first_add = current->next;
        kill_cell(current);
        current = *first_add;
    }
    while(current){
        temp = current->next;
        neighbor_count = near_alive(temp->position);
        if(neighbor_count < 2 || neighbor_count > 3){
            current->next = temp->next;
            kill_cell(temp);
        }
        while(i < 2){
            j = -1;
            while(j < 2){
                if(j == 0 && i == 0) continue;
                dyn_pos[0] = current->position[0] + i;
                dyn_pos[1] = current->position[1] + j;
                //since is_alive() checks character instead of object, the function returns
                //a truthy even if the current cell has been already deleted.
                if(near_alive(dyn_pos) > 2 && !is_alive(dyn_pos[0], dyn_pos[1])) new_cell(dyn_pos);
                j++;
            }
            i++;
        }
        current = temp;
    }
    
    return;
}

void kill_cell(Cell *cell){
    
    free(cell->position);
    free(cell);
    return;
    
}

void kill_all(Cell *first){
    
    Cell *current = first;
    Cell *temp;
    while(current){
        temp = current->next;
        kill_cell(current);
        current = temp;
    }
    return;

}

int *get_pos(Cell *cell){
    return cell->position;
}

char near_alive(int *pos){
    char i = -1, j;
    char result = 0;
    
    while(i < 2){
        j = -1;
        while(j < 2){
            if((j == 0 && i == 0)) continue;
            result += is_alive(pos[0] + i, pos[1] + j++);
        }
        i++;
    }
    return result;
}

char is_alive(int pos_x, int pos_y){
    //Bitwise operation to delete all style stuff and equaling to the icon.
    chtype formatted = mvinch(pos_y, pos_x);
    if((formatted & A_CHARTEXT) == ICON) return 1;
    return 0;
}
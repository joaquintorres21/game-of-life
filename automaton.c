#include "automaton.h"

#include <stdlib.h>

#include <curses.h>

Cell *new_cell(int *position){
    
    Cell *my_cell = (Cell*)malloc(sizeof(Cell));
    my_cell->position = (int*)malloc(2*sizeof(int));
    my_cell->position[0] = position[0];
    my_cell->position[1] = position[1];
    my_cell->next = NULL;
    my_cell->prev = NULL;
    return my_cell;

}

void kill_cell(Cell *cell){
    
    Cell *temp; 
    free(cell->position);
    free(cell);
    return;
    
}

void kill_all(Cell *first){
    
    Cell *current = first;
    Cell *temp;
    while(current){
        temp = current->next;
        free(current->position);
        free(current);
        current = temp;
    }
    return;

}

int *get_pos(Cell *cell){
    return cell->position;
}

char near_alive(int *pos){
    char i = -1, j = -1;
    char result = 0;
    
    while(i < 2){
        while(j < 2){
            if((j == 0 && i ==0)) continue;
            result += is_alive(pos[0] + i, pos[1] + j);
            j++;
        }
        i++;
    }
    return result;
}

char is_alive(int x, int y){
    //Bitwise operation to delete all style stuff and equaling to the icon.
    return ((mvinch(y, x) & A_CHARTEXT) == ICON);
}

void sim(Cell *first){

    Cell *current = first;
    Cell *temp; 
    char neighbor_count;
    char i = -1, j = -1;
    int dyn_pos[2];
    
    current = first;
    while(current){
        neighbor_count = near_alive(current->position);
        if(neighbor_count < 2 || neighbor_count > 3){
            temp = current->next;
            kill_cell(current);
            current = temp;
            temp = NULL;
        }
        while(i < 2){
            while(j < 2){
                dyn_pos[0] = current->position[0] + i;
                dyn_pos[1] = current->position[1] + j;
                //since is alive checks character instead of object, the function returns
                //a truthy even if the current cell has been deleted.
                if(near_alive(dyn_pos) > 2 && !is_alive(dyn_pos[0], dyn_pos[1])) new_cell(dyn_pos);
                j++;
            }
            i++;
        }
        
    }
    
    return;
}
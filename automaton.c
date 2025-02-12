#include "automaton.h"

#include <stdlib.h>

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
    Cell *save = NULL;
    while(current) {
        if(!sim_kill(current)){
           if(save) save->next = current;
           save = current;
        }
    }
}

Cell *sim_kill(Cell *cell){
    char near;
    if((near = near_alive(cell->position)) < 2 || near > 3){
        Cell *next = cell->next;
        kill_cell(cell);
        return next;
    } return NULL;
}

void kill_cell(Cell *cell){

    mvprintw(cell->position[1], cell->position[0], " ");
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
    signed char i = -1;
    signed char j;
    char result = 0;
    
    while(i < 2){
        j = -1;
        while(j < 2){
            result += is_alive(pos[0] + i, pos[1] + j++);
        }
        i++;
    }
    return result-1;
}

char is_alive(int pos_x, int pos_y){
    //Bitwise operation to delete all style stuff and equaling to the icon.
    chtype formatted = mvinch(pos_y, pos_x);
    if((formatted & A_CHARTEXT) == ICON) return 1;
    return 0;
}

int count_cells(Cell *first){
    if(!first) return 0;
    int i = 1;
    while((first= first->next)) i++;
    return i;
}
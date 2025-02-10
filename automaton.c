#include "automaton.h"

#include <stdlib.h>

#include <curses.h>

Cell *new_cell(int *position){
    
    Cell *my_cell = (Cell*)malloc(sizeof *my_cell);
    my_cell->position = (int*)malloc(2*sizeof(int));
    my_cell->position[0] = position[0];
    my_cell->position[1] = position[1];
    return my_cell;

}

void kill_cell(Cell *cell){
    
    free(cell->position);
    cell->prev->next = cell->next;
    free(cell);
    return NULL;
    
}

void kill_all(Cell *first){
    
    Cell *current = first;
    Cell *next;
    while((next = current->next)){
        free(current->position);
        free(current);
        current = next;
    }
    return NULL;

}

double *get_pos(Cell *cell){
    return cell->position;
}

char near_alive(int *pos){
    char i = -1, j = -1;
    char result = 0;
    
    while(i < 2){
        while(j < 2){
            if((j==i==0)) continue;
            result += is_alive(pos[0]+i, pos[1]+j);
            j++;
        }
        i++;
    }
    return result;
}

char is_alive(int x, int y){
    return (mvinch(y, x) & A_CHARTEXT == '*');
}
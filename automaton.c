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

void sim(Cell **first_add, int *dim){

    Cell *current = *first_add;
    if(!current) return;
    Cell *save = NULL;
    Cell *util_p = NULL;
    Cell *util_n = NULL;
    char near;

    while(current){
        near = near_alive(current->position);
        util_p = current;
        util_n = current->next;
        if(near < 2 || near > 3)
            kill_cell(current);
        else{
            if(save) save->next = current;
            else *first_add = current;
            save = current;
            save->next = NULL;
        }
        current = util_n;
    }

    if(!save) *first_add = NULL;

    int std_dim[2] = {0,0};
    Cell *append = NULL;
    Cell *append_f = NULL;

    while(1){
        
        if(std_dim[1] >= dim[1]) break;
        if(std_dim[0] >= dim[0]) {
            std_dim[1]++;
            std_dim[0] = 0;
            continue;
        }
        if(near_alive(std_dim) != 3 || is_alive(std_dim[0], std_dim[1])) {
            std_dim[0]++;
            continue;
        }
        Cell *new = new_cell(std_dim);    
        if(append) append->next = new;
        else append_f = new;
        append = new;
        std_dim[0]++;
    }

    if(save) save->next = append_f;
    else *first_add = append_f;
    return;
}

void kill_cell(Cell *cell){

    //mvprintw(cell->position[1], cell->position[0], " ");
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
            result += is_alive(pos[0] + i, pos[1] + j);
            j++;
        }
        i++;
    }
    char diff = is_alive(pos[0], pos[1]) ? 1 : 0;
    return result-diff;
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
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
    
    if(!*first_add) return;
    Cell *current = *first_add;
    Cell *temp, *save, *sub_list, *new, *first_sub;
    save = sub_list = new = first_sub = NULL;
    char neighbor_count;
    char i = -1, j = -1;
    int static_pos[2], dyn_pos[2];

    while(1){
        
        static_pos[0] = current->position[0];
        static_pos[1] = current->position[1];
        temp = current->next;
        
        neighbor_count = near_alive(current->position);
        if(neighbor_count < 2 || neighbor_count > 3){
            if(current == *first_add)
                *first_add = temp;
            kill_cell(current);
        } 
        else {
            if(save) save->next = current;
            save = current;
        }
        
        while(i < 2){
          while(j < 2){
            dyn_pos[0] = static_pos[0] + i;
            dyn_pos[1] = static_pos[1] + j;
            //since is_alive() checks character instead of object, the function returns
            //a truthy even if the current cell has been already deleted.
            if(near_alive(dyn_pos) > 2 && !is_alive(dyn_pos[0], dyn_pos[1])){
                new = new_cell(dyn_pos);
                if(sub_list) sub_list->next = new;
                else first_sub = new;
                sub_list = new;
            }
            j++;
        }
        j = -1;
        i++;
        }

        if(!(current = temp)){
            if(first_sub) save->next = first_sub;
            //else save->next = NULL;
            return;
        }
    }
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
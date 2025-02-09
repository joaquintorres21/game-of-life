#include "automaton.h"

Cell *new_cell(int *position){
    
    Cell *returned = (Cell*)malloc(sizeof *returned);
    returned->position = (int*)malloc(2*sizeof(int));
    returned->position[0] = position[0];
    returned->position[1] = position[1];

}


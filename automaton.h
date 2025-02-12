#define ALIVE 1
#define DEAD 0

#define ICON 254 //Rectangle for symbolizing the cells.

#define PRINT 0
#define DEL 1

#define PDC_LOG
#include <curses.h>

typedef struct PCell{

    int *position;
    struct PCell *next;

} Cell;

Cell* new_cell(int *pos);

void sim(Cell **first_cell);

void kill_cell(Cell *cell_to_kill);

void kill_all(Cell *first);

int *get_pos(Cell *cell);

char near_alive(int *cell_to_check);

char is_alive(int x, int y);

int count_cells(Cell *first_cell);
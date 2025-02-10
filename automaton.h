#define ALIVE 1
#define DEAD 0

#define ICON 254 //Rectangle for symbolizing the cells.


typedef struct PCell{

    int *position;
    struct PCell *next;
    struct PCell *prev;

} Cell;

void sim(Cell *first_cell);

void kill_cell(Cell *cell_to_kill);

void kill_all(Cell *first);

Cell* new_cell(int *pos);

int *get_pos(Cell *cell);

char near_alive(int *cell_to_check);

char is_alive(int x, int y);
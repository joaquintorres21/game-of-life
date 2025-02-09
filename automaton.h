#define ALIVE 1
#define DEAD 0

typedef struct PCell{

    int *position;
    struct PCell *next;
    struct PCell *prev;

} Cell;

Cell* new_cell(int *pos);

void kill_cell(Cell *cell_to_kill);

char near_alive(Cell *cell_to_check);

double *get_coords(Cell *cell);

void sim(Cell *cell_not_being_pointed);
#define ALIVE 1
#define DEAD 0

typedef struct PCell{

    int *position;
    struct PCell *next;
    struct PCell *prev;

} Cell;

Cell* new_cell(int *pos);

void kill_cell(Cell *cell_to_kill);

void kill_all(Cell *first);

char near_alive(int *cell_to_check);

char is_alive(int x, int y);

double *get_coords(Cell *cell);

void sim(Cell *first_cell);
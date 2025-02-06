#define ALIVE 1
#define DEAD 0


typedef struct {
    
    double *position;
    char state;

} Cell;


Cell *new_cell(double *pos);

void* kill_cell(Cell *cell_to_kill);

//Returns a number between 0 (zero) and 8 (Eight).
char near_alive(Cell *cell_to_check);

char universe();
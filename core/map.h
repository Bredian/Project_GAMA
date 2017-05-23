/*level, enemies, hero*/

int enemies [80][2];
int herox,heroy;
/*clear map*/

/*Main game map*/
char mapa[10][42];

void generate_level(int level);

void copy_map();

void print_map();

int level_current();

void level_up();


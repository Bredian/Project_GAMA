#define ONE 0b00000001
#define TWO 0b00000010
#define THREE 0b00000011
#define FOUR 0b00000100
#define FIVE 0b00000101
#define SIX 0b00000110
#define SEVEN 0b00000111
#define EIGHT 0b00001000
#define NINE 0b00001001
#define DOT 0b00010000
#define LEFT 0b00001000
#define RIGHT 0b00000100
#define UP 0b00100000
#define DOWN 0b00010000
#define BOMB 0b00000010
#define SKIP 0b00000001
#define JOY_ADDR 0b00000010

void show_level(int number);

void show_bombs(int number);
  
u08* button();
  
void controls();

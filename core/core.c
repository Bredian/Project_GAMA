#include "global.h"
#include <avr/io.h>
#include <stdlib.h>
#include "lcd.h"
#include "i2c.h"
#include "bomb.h"
#include "map.h"
#include "logic.h"
#include "joystick.h"





/*extern int bx, by, bc, btimer, bp;		//bomb parameters
extern int level;
extern char mapac1[10][42];*/

void setup(){
	lcdInit();
	lcdClear();
	i2cInit();
	copy_map();
	generate_level(level_current());
	print_map();
	return;
	
}

void loop(){
	show_level(level_current());
	check_gameover();
	controls();
	/*Sucsessful Turn Sound Here*/
	proceed_turn(level_current());
	if(bomb_counter()!=0 ) bomb_explosion();
	check_nish();
	print_map();
	return;
}

void main(){
	setup();
	while(1){
		loop();
	}
	return;
}

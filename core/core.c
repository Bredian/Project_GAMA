#include "global.h"
#include <avr/io.h>
#include <stdlib.h>
#include <math.h>
#include "lcd.h"
#include "i2c.h"
#include "bomb.h"
#include "map.h"
#include "logic.h"
#include "joystick.h"

//~ extern int bx, by, bc, btimer, bp;		//bomb parameters
//~ extern int level;
//~ extern char mapac1[10][42];

void setup(){
	lcdInit();
	i2cInit();
	copy_map();
	generate_level(level);
	print_map();
	return;
	
}

void loop(){
	show_level(level);
	check_gameover();
	controls();
	/*Sucsessful Turn Sound Here*/
	proceed_turn(level);
	if(bp==1 && bx!=-1 && by!=-1 && bc!=0 ) bomb_explosion();
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

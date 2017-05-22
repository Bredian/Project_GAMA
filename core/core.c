#include <avr/io.h>
#include <stdlib.h>
#include <math.h>
#include "bomb.h"
#include "map.h"
#include "logic.h"
#include "lcd.h"
#include "sid.h"
#include "joystick.h"

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

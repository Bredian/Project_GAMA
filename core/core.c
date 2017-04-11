#include <avr/io.h>
#include <stdlib.h>
#include <math.h>
#include "bomb.h"
#include "map.h"
#include "logic.h"
#include "screen.h"
#include "sid.h"
#include "joystick.h"

int setup(){
	
}

int loop(){
	/*7 Segment Level Show Here*/
	check_gameover();
	/*Controls Function Here*/
	/*Sucsessful Turn Sound Here*/
	proceed_turn(level);
	if(bp==1 && bx!=-1 && by!=-1 && bc!=0 ) bomb_explosion();
	check_nish();
	/*Printing Map Function Here*/
}

int main(){
	setup();
	while(1){
		loop();
	}
}

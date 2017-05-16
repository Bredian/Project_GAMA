#include <avr/io.h>
#include <avr/interrupt.h>

#include "global.h"
#include "i2cconf.h"
#include "rprintf.h"
#include "joystick.h"
#include "bomb.h"
#include "map.h"

void show_level(int number){
	switch(number){
		case 1:
			u08 n=ONE; 
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 2:
			u08 n=TWO;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 3:
			u08 n=THREE;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 4:
			u08 n=FOUR;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 5:
			u08 n=FIVE;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 6:
			u08 n=SIX;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 7:
			u08 n=SEVEN;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 8:
			u08 n=EIGHT;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 9:
			u08 n=NINE;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
	}
}

void show_bombs(int number){
	switch(number){

	switch(number){
		case 1:
			u08 n=ONE || DOT; 
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 2:
			u08 n=TWO || DOT;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 3:
			u08 n=THREE || DOT;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 4:
			u08 n=FOUR || DOT;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 5:
			u08 n=FIVE || DOT;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 6:
			u08 n=SIX || DOT;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 7:
			u08 n=SEVEN || DOT;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 8:
			u08 n=EIGHT || DOT;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
		case 9:
			u08 n=NINE || DOT;
			i2cMasterSend(JOY_ADDR,1,*n);
			break;
	}
}

u08* button(){
	u08* button_pressed;
	i2cMasterRecieve(JOY_ADDR,1,button_pressed);
	return button_pressed;
}
	
void controls(){
	int a=herox;
	a--;
	int b=herox;
	b++;
	int c=heroy;
	c--;
	int d=heroy;
	d++;
	while(1){
		if(*(button())==SKIP)
			break;
		if(*(button())==BOMB){
			if(bc==0) continue;
		}
			else {
				bomb_placement();
				break;
			}
		if( *(button())==LEFT && mapa[heroy][a]!='#' && mapa[heroy][a]!='@' && mapa[heroy][a]!='*' && mapa[heroy][a]!='='){
                	mapa[heroy][herox]='.';
                	herox--;
                	mapa[heroy][herox]='1';
                	break;
            }
		if(*(button())==RIGHT && mapa[heroy][b]!='#' && mapa[heroy][b]!='@' && mapa[heroy][b]!='*' && mapa[heroy][b]!='='){
                	mapa[heroy][herox]='.';
                	herox++;
                	mapa[heroy][herox]='1';
                	break;
            }
		if( *(button())==UP && mapa[c][herox]!='#' && mapa[c][herox]!='@' && mapa[c][herox]!='*' && mapa[c][herox]!='='){
                	mapa[heroy][herox]='.';
                	heroy--;
                	mapa[heroy][herox]='1';
                	break;
            }
		if( *(button())==DOWN && mapa[d][herox]!='#' && mapa[d][herox]!='@' && mapa[d][herox]!='*' && mapa[d][herox]!='='){
                	mapa[heroy][herox]='.';
                	heroy++;
                	mapa[heroy][herox]='1';
                	break;
            }
		if(*(button())==LEFT && (mapa[heroy][a]=='#' || mapa[heroy][a]=='@' || mapa[heroy][a]=='*' || mapa[heroy][a]=='=')) || *(button())==RIGHT && (mapa[heroy][b]=='#' || mapa[heroy][b]=='@' || mapa[heroy][b]=='*' || mapa[heroy][b]=='=')) || (*(button())==UP && (mapa[c][herox]=='#' || mapa[c][herox]=='@' || mapa[c][herox]=='*' || mapa[c][herox]=='=')) || (*(button())==DOWN && (mapa[d][herox]=='#' || mapa[d][herox]=='@' || mapa[d][herox]=='*' || mapa[d][herox]=='='))) /*music here*/; 
	}
}

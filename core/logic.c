#include "global.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "i2c.h"
//~ #include "i2cconf.h"
//~ #include "rprintf.h"
#include "joystick.h"
#include "bomb.h"
#include "map.h"

void show_level(int number){
	u08 n;
	switch(number){
		case 1:
			n=ONE; 
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 2:
			n=TWO;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 3:
			n=THREE;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 4:
			n=FOUR;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 5:
			n=FIVE;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 6:
			n=SIX;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 7:
			n=SEVEN;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 8:
			n=EIGHT;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 9:
			n=NINE;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
	}
	return;
}

void show_bombs(int number){
	u08 n;
	switch(number){
		case 1:
			n=ONE || DOT; 
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 2:
			n=TWO || DOT;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 3:
			n=THREE || DOT;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 4:
			n=FOUR || DOT;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 5:
			n=FIVE || DOT;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 6:
			n=SIX || DOT;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 7:
			n=SEVEN || DOT;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 8:
			n=EIGHT || DOT;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
		case 9:
			n=NINE || DOT;
			i2cMasterSend(JOY_ADDR,1,&n);
			break;
	}
	return;
}

u08* button(){
	u08* button_pressed;
	i2cMasterReceive(JOY_ADDR,1,button_pressed);
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
			if(bomb_counter()==0) continue;
		}
			else {
				bomb_placement();
				break;
			}
		if( (*(button())==LEFT) && (mapa[heroy][a]!='#') && (mapa[heroy][a]!='@') && (mapa[heroy][a]!='*') && (mapa[heroy][a]!='=')){
                	mapa[heroy][herox]='.';
                	herox--;
                	mapa[heroy][herox]='1';
                	break;
            }
		if( (*(button())==RIGHT) && (mapa[heroy][b]!='#') && (mapa[heroy][b]!='@') && (mapa[heroy][b]!='*') && (mapa[heroy][b]!='=')){
                	mapa[heroy][herox]='.';
                	herox++;
                	mapa[heroy][herox]='1';
                	break;
            }
		if( (*(button())==UP) && (mapa[c][herox]!='#') && (mapa[c][herox]!='@') && (mapa[c][herox]!='*') && (mapa[c][herox]!='=')){
                	mapa[heroy][herox]='.';
                	heroy--;
                	mapa[heroy][herox]='1';
                	break;
            }
		if( (*(button())==DOWN) && (mapa[d][herox]!='#') && (mapa[d][herox]!='@') && (mapa[d][herox]!='*') && (mapa[d][herox]!='=')){
                	mapa[heroy][herox]='.';
                	heroy++;
                	mapa[heroy][herox]='1';
                	break;
            }
		//~ if(*(button())==LEFT && (mapa[heroy][a]=='#' || mapa[heroy][a]=='@' || mapa[heroy][a]=='*' || mapa[heroy][a]=='=')) || *(button())==RIGHT && (mapa[heroy][b]=='#' || mapa[heroy][b]=='@' || mapa[heroy][b]=='*' || mapa[heroy][b]=='=')) || (*(button())==UP && (mapa[c][herox]=='#' || mapa[c][herox]=='@' || mapa[c][herox]=='*' || mapa[c][herox]=='=')) || (*(button())==DOWN && (mapa[d][herox]=='#' || mapa[d][herox]=='@' || mapa[d][herox]=='*' || mapa[d][herox]=='='))) /*music here*/; 
	}
	return;
}

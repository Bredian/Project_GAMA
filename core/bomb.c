#include "global.h"
#include "bomb.h"
#include "map.h"
#include "joystick.h"

void bomb_placement(){
	int a=herox;
	a--;
  	int b=herox;
  	b++;
  	int c=heroy;
  	c--;
  	int d=heroy;
  	d++;
	show_bombs(bc);
	while(1){	
	if(mapa[heroy][a]!='#' && mapa[heroy][a]!='@' && mapa[heroy][a]!='=' && *(button())==LEFT){
	            bx=a;
                by=heroy;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
			show_level(level);
                break;
	}
	if(mapa[heroy][b]!='#' && mapa[heroy][b]!='@' && mapa[heroy][b]!='=' && *(button())==RIGHT){
		bx=b;
                by=heroy;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                show_level(level);
                break;
	}
	if(mapa[c][herox]!='#' && mapa[c][herox]!='@' && mapa[c][herox]!='=' && *(button())==DOWN){
		bx=herox;
                by=c;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                show_level(level);
                break;
	}
	if(mapa[d][herox]!='#' && mapa[d][herox]!='@' && mapa[d][herox]!='=' && *(button())==UP){
		bx=herox;
                by=c;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                show_level(level);
                break;
	}
	}
	return;
}

void bomb_explosion(){
	int v, j, i;
	btimer--;
	if(btimer==0){
    	for(v=0;v<level;v++){
    		for(j=by-1;j<by+2;j++){
      			for(i=bx-1;i<bx+2;i++){
      				if(enemies[v][0]==j && enemies[v][1]==i){
        				enemies[v][0]=-1;
        				enemies[v][1]=-1;
        }
      }
    }
  }
  for(j=by-1;j<by+2;j++){
    for(i=bx-1;i<bx+2;i++){
      if(mapa[j][i]!='=') mapa[j][i]='.';
    }
  }
  /*chord(7,500,150,160,170);*/
  /*sound playback here*/
  bp=0;
  bc--;
  }
  else /*tone(7,220,120)*/;
  /*sound playback here*/
  return;
}

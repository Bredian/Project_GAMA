#include "bomb.h"
#include "map.h"
#include "joystick.h"

int bomb_placement(){
	int a=herox;
	a--;
  	int b=herox;
  	b++;
  	int c=heroy;
  	c--;
  	int d=heroy;
  	d++;
	/*7_Segment_Show(bc);*/
	/*7 Segment interaction here*/	
	if(mapa[heroy][a]!='#' && mapa[heroy][a]!='@' && mapa[heroy][a]!='=' && *(button())=LEFT){
	            bx=a;
                by=heroy;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                /*7_Segment_Clean();*/
		/*7 Segment interaction here*/
                break;
	}
	if(mapa[heroy][b]!='#' && mapa[heroy][b]!='@' && mapa[heroy][b]!='=' && *(button())=RIGHT){
		bx=b;
                by=heroy;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                /*7_Segment_Clean();*/
		/*7 Segment interaction here*/
                break;
	}
	if(mapa[c][herox]!='#' && mapa[c][herox]!='@' && mapa[c][herox]!='=' && *(button())=DOWN){
		bx=herox;
                by=c;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                /*7_Segment_Clean();*/
		/*7 Segment interaction here*/
                break;
	}
	if(mapa[d][herox]!='#' && mapa[d][herox]!='@' && mapa[d][herox]!='=' && *(button())==UP){
		bx=herox;
                by=c;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                /*7_Segment_Clean();*/
		/*7 Segment interaction here*/
                break;
	}
}

int bomb_expolion(){
	btimer--;
	if(btimer==0){
    	for(int v=0;v<level;v++){
    		for(int j=by-1;j<by+2;j++){
      			for(int i=bx-1;i<bx+2;i++){
      				if(enemies[v][0]==j && enemies[v][1]==i){
        				enemies[v][0]=-1;
        				enemies[v][1]=-1;
        }
      }
    }
  }
  for(int j=by-1;j<by+2;j++){
    for(int i=bx-1;i<bx+2;i++){
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
}

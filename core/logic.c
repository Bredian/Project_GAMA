#include "map.h"
#include "logic.h"

int proceed_turn(int level){
  		int q;
        for(q=0;q<level;q++){
            int rx,ry,a,b;
            ry=heroy-enemies[q][0];
            rx=herox-enemies[q][1];
            ry=ry;
            if(abs(rx)<abs(ry)){
                a=enemies[q][0]-1;
                b=enemies[q][0]+1;
                if(ry>0 && mapa[b][enemies[q][1]]!='#' && mapa[b][enemies[q][1]]!='~' && mapa[b][enemies[q][1]]!='*' && mapa[b][enemies[q][1]]!='='){
                    mapa[enemies[q][0]][enemies[q][1]]='.';
                    enemies[q][0]++;
                    mapa[enemies[q][0]][enemies[q][1]]='@';
                }
                if(ry<0 && mapa[a][enemies[q][1]]!='#' && mapa[a][enemies[q][1]]!='~' && mapa[a][enemies[q][1]]!='*' && mapa[a][enemies[q][1]]!='='){
                    mapa[enemies[q][0]][enemies[q][1]]='.';
                    enemies[q][0]--;
                    mapa[enemies[q][0]][enemies[q][1]]='@';
                }
            }
            if(abs(rx)>abs(ry)){
                a=enemies[q][1]-1;
                b=enemies[q][1]+1;
                if(rx>0 && mapa[enemies[q][0]][b]!='#' && mapa[enemies[q][0]][b]!='~' && mapa[enemies[q][0]][b]!='*' && mapa[enemies[q][0]][b]!='='){
                    mapa[enemies[q][0]][enemies[q][1]]='.';
                    enemies[q][1]++;
                    mapa[enemies[q][0]][enemies[q][1]]='@';
                }
                if(rx<0 && mapa[enemies[q][0]][a]!='#' && mapa[enemies[q][0]][a]!='~' && mapa[enemies[q][0]][a]!='*' && mapa[enemies[q][0]][a]!='='){
                    mapa[enemies[q][0]][enemies[q][1]]='.';
                    enemies[q][1]--;
                    mapa[enemies[q][0]][enemies[q][1]]='@';
                }
            }
        }
}

int check_gameover(){
	          int i, j, k=0;
          for(j=0;j<10;j++)
            for(i=0;i<42;i++)
                if(mapa[j][i]=='1') k++;
        if(k==0) {
            delay(1000);
            /*lcd.clear();
            lcd.print("Game over");
            lcd.setCursor(0,1);
            lcd.print("Button to Play Again");*/
			/*Game Over Screen here*/
            while(1){
              /*play_Music_Gamover(chords,noteDurations,198);*/
			/*Game Over Music here*/
            }
        }
        
        if(k!=0) k=0;
}

int levelup(){
  copy_Map();
  generate_Level(level);
  /*print_Map();*/
	/*printing map function here*/
  /*7 Segment clean here*/
  }	
}

int check_nish(){
            int i,j,k=0;
          for(j=0;j<10;j++)
            for(i=0;i<42;i++)
                if(mapa[j][i]=='~') k++;
        if(k==0) {
            level++;
            levelup();
            /*lcd.clear();*/
            /*Main Screen Cleaning Function Here*/
        }
        
        if(k!=0) {
          k=0;
        }
}

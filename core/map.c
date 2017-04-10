#include "map.h"

int generate_level(int level){
	/*random seed here*/
	int n=0;
    while(n<level){
        int x,y;
        x=random(41);
        y=random(9);
        if(mapa[y][x]=='.'){
            enemies[n][0]=y;
            enemies[n][1]=x;
            mapa[y][x]='@';
            n++;
        }
    }
    int m=0;
    while(m<1){
        int x,y;
        x=random(41);
        y=random(9);
        if(mapa[y][x]=='.'){
            heroy=y;
            herox=x;
            mapa[y][x]='1';
            m++;
        }
    }
    int p=0;
    while(p<2){
        int x,y;
        x=random(41);
        y=random(9);
        if(mapa[y][x]=='.'){
            mapa[y][x]='~';
            p++;
        }
    }
}

int copy_map(){
	int i=0,j=0;
  for(j=0;j<10;j++){
            for(i=0;i<42;i++){
              mapa[j][i]=mapac1[j][i];
            }
        }	
}

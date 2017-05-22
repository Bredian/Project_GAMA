#include "map.h"

void generate_level(int level){
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
    return;
}

void copy_map(){
	int i=0,j=0;
  for(j=0;j<10;j++){
            for(i=0;i<42;i++){
              mapa[j][i]=mapac1[j][i];
            }
        }
        return;	
}

void print_map(){
	int i=0, j=0;
	int a=heroy-2;
	int b=heroy+1;
	int c=herox-9;
	int d= herox+10;
	for(j=a;j<b+1;j++){
		for(i=c;i<d+1;i++){
			lcdGotoXY(i-c,j-a);
			lcdPrintData(&mapa[j][i],1);
		}
	}
	return;
}

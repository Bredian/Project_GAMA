/*Display Inclusion*/
#include <LiquidCrystal.h>
/*For I2C(not relealised in code)*/
#include <Wire.h>
#include <avr/pgmspace.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

/*bomb variables*/
int bx=-1,by=-1,btimer=0,bp=0,bc=3;
/*tiles*/ 
/*Detail for sceleton Sans*/
byte TL[8] = {
  0b00000,
  0b00011,
  0b00100,
  0b00100,
  0b01000,
  0b01000,
  0b01000,
  0b01000
};
/*Bomb tile*/
byte bomba[8]={
  0b00001,
  0b00011,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110
};
/*Detail for sceleton Sans*/
byte TM[8] = {
  0b00000,
  0b11111,
  0b00000,
  0b11011,
  0b11011,
  0b00000,
  0b00100,
  0b01110
};
/*Wall tile*/
byte wall[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01100,
  0b01110,
  0b11110,
  0b11111
};
/*Player tile*/
byte player[8] = {
  0b01110,
  0b01010,
  0b01110,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b11011
};
/*Detail for sceleton Sans*/
byte TR[8] = {
  0b00000,
  0b11000,
  0b00100,
  0b00100,
  0b00010,
  0b00010,
  0b00010,
  0b00010
};
/*Detail for sceleton Sans*/
byte BL[8] = {
  0b00110,
  0b01100,
  0b01000,
  0b01000,
  0b00110,
  0b00001,
  0b00000,
  0b00000
};
/*Detail for sceleton Sans*/
byte BM[8] = {
  0b00000,
  0b11111,
  0b01010,
  0b11111,
  0b00000,
  0b11111,
  0b00000,
  0b00000
};
/*Detail for sceleton Sans*/
byte BR[8] = {
  0b01100,
  0b00110,
  0b00010,
  0b00010,
  0b01100,
  0b10000,
  0b00000,
  0b00000
};

byte gold[8]={
  0b01110,
  0b11111,
  0b11011,
  0b10011,
  0b11011,
  0b10001,
  0b11111,
  0b01110
};

byte omich[8]={
  0b01010,
  0b11111,
  0b11111,
  0b10101,
  0b11011,
  0b00011,
  0b11111,
  0b11111
};
 
/*level, enemies, hero*/
int level=1;
int enemies [80][2];
int herox,heroy;
/*clear map*/
char mapac1[10][42]=
    {   
        {'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','='},
        {'=','.','#','.','.','.','.','.','.','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','='},
        {'=','.','.','.','#','#','.','.','.','#','#','.','#','#','#','#','#','.','#','#','.','.','.','.','#','#','.','.','.','.','.','.','.','#','.','.','.','.','.','.','.','='},
        {'=','#','.','.','#','.','.','.','.','.','#','.','.','.','.','#','.','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','='},
        {'=','#','#','.','#','#','#','#','.','.','#','#','.','.','.','.','.','.','.','.','#','.','.','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','='},
        {'=','#','.','.','.','.','#','.','.','#','.','.','#','#','#','#','#','#','#','#','#','.','.','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','='},
        {'=','.','#','#','#','#','#','.','#','.','.','.','.','.','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','.','='},
        {'=','.','.','.','.','.','.','.','#','.','#','#','#','.','#','.','.','#','#','.','#','.','.','.','#','#','.','.','.','.','.','.','.','.','#','#','#','.','.','.','.','='},
        {'=','.','.','.','.','.','.','.','.','.','#','.','.','.','.','.','#','.','.','.','#','.','.','.','#','#','.','.','.','.','.','.','.','.','.','.','#','.','.','.','.','='},
        {'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','='},
    };
/*Main game map*/
char mapa[10][42];
/*some music*/
int mainTheme[]{
  117,0,466, 175,0,466, 233,0,466, 233,175,349, 233,175,349, 233,175,466, 104,0,415, 104,0,370, 104,0,415, 156,0,415, 156,208,415, 93,0,466, 139,0,466, 185,0,466, 185,139,349, 185,139,349, 185,139,466, 87,0,440, 87,0,392, 87,0,440, 131,0,440, 131,175,440
};

int mainDurations[]{
  1200,1200,1200,520,520,520,300,300,300,1200,1200,1200,1200,1200,520,520,520,300,300,300,1200,1200
};

int chords[] = {
  147,0,0,   175,220,0,   175,220,0,   165,0,0,  165,196,247,  175,0,0, 220,262,0, 220,262,0, 165,0,0, 165,196,247, 147,0,294, 147,0,349, 175,220,587, 165,0,294, 165,0,349, 196,247,587, 175,0,659, 220,262,0, 220,262,699, 220,262,659, 220,262,699, 165,0,659, 165,0,523, 196,247,440, 117,0,440, 196,233,294, 196,233,349, 196,233,392, 175,0,440, 175,220,440, 117,0,440, 196,233,294, 196,233,349, 196,233,392, 110,0,330, 165,220,330, 147,0,294, 147,0,349, 175,220,587, 165,0,294, 165,0,349, 196,247,587, 175,0,659, 220,262,0, 220,262,699, 220,262,659, 220,262,699, 165,0,659, 165,0,523, 196,247,440, 117,0,440, 196,233,294, 196,233,349, 196,233,392, 110,0,440, 175,220,440, 147,0,0,   175,220,0,   175,220,0,   165,0,0,  165,196,247,  175,0,0, 220,262,0, 220,262,0, 165,0,0, 165,196,247 
};

int noteDurations[] = {
  480,480,480,480,1200,480,480,480,480,1200,120,120,1200,120,120,1200,480,120,80,80,80,80,80,1200,480,480,120,120,480,1200,480,480,120,120,480,1200,120,120,1200,120,120,1200,480,120,80,80,80,80,80,1200,480,480,120,120,1200,480,480,480,480,480,1200,480,480,480,480,1200
};

/*how to play chords*/

void chord(int pin,int duration, int pitch_1, int pitch_2, int pitch_3){
  int i=0;
  if(pitch_2==0 && pitch_3==0){
    while(i<duration){
    tone(pin,pitch_1,30);
    delay(30);
    noTone(pin);
    tone(pin,pitch_1*1.01,30);
    delay(30);
    noTone(pin);
    i=i+120;
    }
        }
  if(pitch_2!=0 && pitch_3==0){
  while(i<duration){
  tone(pin,pitch_1,30);
  delay(30);
  noTone(pin);
  tone(pin,pitch_2,30);
  delay(30);
  noTone(pin);
  i=i+120;
  }
  delay(120);
  }
  else {
  while(i<duration){
  tone(pin,pitch_1,20);
  delay(20);
  noTone(pin);
  tone(pin,pitch_2,20);
  delay(20);
  noTone(pin);
  tone(pin,pitch_3,20);
  delay(20);
  noTone(pin);
  i=i+120;    
  }
  delay(120);
  }
}

void main_chord(int pin,int duration, int pitch_1, int pitch_2, int pitch_3){
  
  int i=0;
  if(pitch_2==0 && pitch_3==0){
    while(i<duration){
    tone(pin,pitch_1,30);
    delay(30);
    noTone(pin);
    tone(pin,pitch_1*1.01,30);
    delay(30);
    noTone(pin);
    i=i+120;
    return;
    }
        }
  if(pitch_2!=0 && pitch_3==0){
  while(i<duration){
  tone(pin,pitch_1,30);
  delay(30);
  noTone(pin);
  tone(pin,pitch_2,30);
  delay(30);
  noTone(pin);
  i=i+120;
  }
  delay(20);
  return;
  }
  else {
  while(i<duration){
  tone(pin,pitch_1,20);
  delay(20);
  noTone(pin);
  tone(pin,pitch_2,20);
  delay(20);
  noTone(pin);
  tone(pin,pitch_3,20);
  delay(20);
  noTone(pin);
  i=i+120;    
  }
  delay(20);
  return;
  }
}
/*bomb funtctions*/
/*placements*/
void bomb_placement(){
  Serial.println("Bomb placement");
  int a=herox;
  a--;
  int b=herox;
  b++;
  int c=heroy;
  c--;
  int d=heroy;
  d++;
  Show(bc);
        while(1){
              if( digitalRead(50)==1 && mapa[heroy][a]!='#' && mapa[heroy][a]!='@' && mapa[heroy][a]!='='){
                bx=a;
                by=heroy;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                Clean();
                break;
            }
            if( digitalRead(51)==1 && mapa[heroy][b]!='#' && mapa[heroy][b]!='@' && mapa[heroy][b]!='='){
                bx=b;
                by=heroy;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                Clean();
                break;
            }
            if( digitalRead(52)==1 && mapa[c][herox]!='#' && mapa[c][herox]!='@' && mapa[c][herox]!='='){
                bx=herox;
                by=c;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                Clean();
                break;
            }
            if( digitalRead(53)==1 && mapa[d][herox]!='#' && mapa[d][herox]!='@' && mapa[d][herox]!='='){
                bx=herox;
                by=d;
                btimer=3;
                mapa[by][bx]='*';
                bp=1;
                Clean();
                break;
            }
            if((digitalRead(50)==1 && (mapa[heroy][a]=='#' || mapa[heroy][a]=='@' || mapa[heroy][a]=='=')) || (digitalRead(51)==1 && (mapa[heroy][b]=='#' || mapa[heroy][b]=='@' || mapa[heroy][b]=='=')) || (digitalRead(52)==1 && (mapa[c][herox]=='#' || mapa[c][herox]=='@' || mapa[c][herox]=='=')) || (digitalRead(53)==1 && (mapa[d][herox]=='#' || mapa[d][herox]=='@' || mapa[d][herox]=='='))) chord(7,123,129,145,200);
            else delay(65);
            }
            return;
}

/*and proceeding their explosion*/
void bomb_ex(){
  Serial.println("Bomb explosion");
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
      if(mapa[j][i]!='=')mapa[j][i]='.';
    }
  }
  chord(7,500,150,160,170);
  bp=0;
  bc--;
  }
  else tone(7,220,120);
  return;
}
/*Demonstration*/
void Demo(){
  Serial.println("Demo");
  lcd.createChar(2, TL);
  lcd.createChar(3, TM);
  lcd.createChar(4, TR);
  lcd.createChar(5, BL);
  lcd.createChar(6, BM);
  lcd.createChar(7, BR);
  lcd.setCursor(8,0);
  lcd.print("Omsk");
  lcd.setCursor(5,2);
  lcd.print("by Bredian");
  lcd.setCursor(4,3);
  lcd.print("2017, Dolgop");
  play_Main(mainTheme,mainDurations,33);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Explore maze");
  lcd.setCursor(0,1);
  lcd.print("Avoid enemies");
  lcd.setCursor(0,2);
  lcd.print("Destroy walls");
  lcd.setCursor(0,3);
  lcd.print("Take all gold");
  lcd.setCursor(16,0);
  lcd.write((byte) 2);
  lcd.setCursor(17,0);
  lcd.write((byte) 3);
  lcd.setCursor(18,0);
  lcd.write((byte) 4);
  lcd.setCursor(16,1);
  lcd.write((byte) 5);
  lcd.setCursor(17,1);
  lcd.write((byte) 6);
  lcd.setCursor(18,1);
  lcd.write((byte) 7);
    play_Main(mainTheme+33,mainDurations+11,33);
  return;
  }
/*how to play music*/
void play_Music_Gamover(int * chords, int * noteDurations,int noteNumber){
  for (int thisNote = 0; thisNote < noteNumber; thisNote=thisNote+3) {
 
 chord(7,noteDurations[thisNote/3],chords[thisNote],chords[thisNote+1],chords[thisNote+2]);
  }
  return;
}

void play_Main(int * chords, int * noteDurations,int noteNumber){
  for (int thisNote = 0; thisNote < noteNumber; thisNote=thisNote+3) {
 
 main_chord(7,noteDurations[thisNote/3],chords[thisNote],chords[thisNote+1],chords[thisNote+2]);
  }
  return;
}

/*level generator*/
void generate_Level(int level){
  Serial.println("Generate level");
  randomSeed(analogRead(A0));
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
/*Show level and items on indicator*/

void Show(int digit) {
  Serial.println("Show");
  switch(digit) {
    case 0: {
      digitalWrite(22,HIGH); digitalWrite(23,HIGH);
      digitalWrite(29,HIGH); digitalWrite(24,HIGH);
      digitalWrite(25,HIGH); digitalWrite(26,HIGH);
    }
    break;
    case 1: {
      digitalWrite(23,HIGH); digitalWrite(24,HIGH);
    }
    break;
    case 2: {
      digitalWrite(22,HIGH); digitalWrite(23,HIGH);
      digitalWrite(28,HIGH); digitalWrite(25,HIGH);
      digitalWrite(29,HIGH);
    }
    break;
    case 3: {
      digitalWrite(22,HIGH); digitalWrite(23,HIGH);
      digitalWrite(28,HIGH); digitalWrite(24,HIGH);
      digitalWrite(29,HIGH);
    }
    break;
    case 4: {
      digitalWrite(26,HIGH); digitalWrite(28,HIGH);
      digitalWrite(24,HIGH); digitalWrite(23,HIGH);
    }
    break;
    case 5: {
      digitalWrite(22,HIGH); digitalWrite(28,HIGH);
      digitalWrite(26,HIGH); digitalWrite(24,HIGH);
      digitalWrite(29,HIGH);
    }
    break;
    case 6: {
      digitalWrite(22,HIGH); digitalWrite(26,HIGH);
      digitalWrite(25,HIGH); digitalWrite(28,HIGH);
      digitalWrite(29,HIGH); digitalWrite(24,HIGH);
    }
    break;
    case 7: {
      digitalWrite(22,HIGH); digitalWrite(23,HIGH);
      digitalWrite(24,HIGH);
    }
    break;
    case 8: {
      digitalWrite(22,HIGH); digitalWrite(28,HIGH);
      digitalWrite(23,HIGH); digitalWrite(26,HIGH);
      digitalWrite(24,HIGH); digitalWrite(25,HIGH);
      digitalWrite(29,HIGH);
    }
    break;
    case 9: {
      digitalWrite(26,HIGH); digitalWrite(29,HIGH);
      digitalWrite(28,HIGH); digitalWrite(24,HIGH);
      digitalWrite(22,HIGH); digitalWrite(23,HIGH);
    }
    break;
  }
  return;
}

void Clean() {
  Serial.println("clean");
    digitalWrite(22,LOW); digitalWrite(29,LOW);
    digitalWrite(23,LOW); digitalWrite(28,LOW);
    digitalWrite(24,LOW); digitalWrite(26,LOW);
    digitalWrite(25,LOW);
    return;
}

/*process controls*/
void control(){
  Serial.println("Control");
  int a=herox;
  a--;
  int b=herox;
  b++;
  int c=heroy;
  c--;
  int d=heroy;
  d++;
            while(1){
              delay(65);
            if(digitalRead(48)==1){
              break;
            }
            if( digitalRead(49)==1){
                tone(7,1000,200);
                Serial.println(bc);
                Clean();
                if(bc==0) {
                  tone(7,110,200);
                  continue;
                }
                bomb_placement();
                
                break;
            }
            if( digitalRead(50)==1 && mapa[heroy][a]!='#' && mapa[heroy][a]!='@' && mapa[heroy][a]!='*' && mapa[heroy][a]!='='){
                mapa[heroy][herox]='.';
                herox--;
                mapa[heroy][herox]='1';
                break;
            }
            if( digitalRead(51)==1 && mapa[heroy][b]!='#' && mapa[heroy][b]!='@' && mapa[heroy][b]!='*' && mapa[heroy][b]!='='){
                mapa[heroy][herox]='.';
                herox++;
                mapa[heroy][herox]='1';
                break;
            }
            if( digitalRead(52)==1 && mapa[c][herox]!='#' && mapa[c][herox]!='@' && mapa[c][herox]!='*' && mapa[c][herox]!='='){
                mapa[heroy][herox]='.';
                heroy--;
                mapa[heroy][herox]='1';
                break;
            }
            if( digitalRead(53)==1 && mapa[d][herox]!='#' && mapa[d][herox]!='@' && mapa[d][herox]!='*' && mapa[d][herox]!='='){
                mapa[heroy][herox]='.';
                heroy++;
                mapa[heroy][herox]='1';
                break;
            }
            if((digitalRead(50)==1 && (mapa[heroy][a]=='#' || mapa[heroy][a]=='@' || mapa[heroy][a]=='*' || mapa[heroy][a]=='=')) || (digitalRead(51)==1 && (mapa[heroy][b]=='#' || mapa[heroy][b]=='@' || mapa[heroy][b]=='*' || mapa[heroy][b]=='=')) || (digitalRead(52)==1 && (mapa[c][herox]=='#' || mapa[c][herox]=='@' || mapa[c][herox]=='*' || mapa[c][herox]=='=')) || (digitalRead(53)==1 && (mapa[d][herox]=='#' || mapa[d][herox]=='@' || mapa[d][herox]=='*' || mapa[d][herox]=='='))) chord(7,123,129,145,200); 
            else delay(65);
            }
            return;
}
/*clear main map and put there clear one*/
void copy_Map(){
  Serial.println("Copy Map");
    int i=0,j=0;
  for(j=0;j<10;j++){
            for(i=0;i<42;i++){
              mapa[j][i]=mapac1[j][i];
            }
        }
}
/*proceed turn for omich*/
void proceed_Turn(int level){
  Serial.println("Proceed Turn");
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
        return;
}
/*check if any gold is on the map*/
void check_Nish(){
  Serial.println("Check Nish");
          int i,j,k=0;
          for(j=0;j<10;j++)
            for(i=0;i<42;i++)
                if(mapa[j][i]=='~') k++;
        if(k==0) {
            level++;
            levelup();
            lcd.clear();
        }
        
        if(k!=0) {

          k=0;
        }
        return;
}
/*check if player alive*/
void check_Gameover(){
          Serial.println("check Gameover");
          int i, j, k=0;
          for(j=0;j<10;j++)
            for(i=0;i<42;i++)
                if(mapa[j][i]=='1') k++;
        if(k==0) {
            delay(1000);
            lcd.clear();
            lcd.print("Game over");
            lcd.setCursor(0,1);
            lcd.print("Button to Play Again");
            while(1){
              play_Music_Gamover(chords,noteDurations,198);
            }
        }
        
        if(k!=0) k=0;
}
/*print main game map*/
void print_Map(){
  Serial.println("Print map");
  int i=0,j=0;
  int a=heroy-2;
  int b=heroy+1;
  int c=herox-9;
  int d=herox+10;
  for(j=a;j<b+1;j++){
            for(i=c;i<d+1;i++){
            
            lcd.setCursor(i-c,j-a);
            if(mapa[j][i]=='*') lcd.write((byte) 2);
            if(mapa[j][i]=='@') lcd.write((byte) 4);
            if(mapa[j][i]=='~') lcd.write((byte) 3);
            if(mapa[j][i]=='#') lcd.write((byte) 5);
            if(mapa[j][i]=='1') lcd.write((byte) 6);
            if(mapa[j][i]=='.') lcd.write(' ');
            if(mapa[j][i]=='=') lcd.write('=');
            else lcd.write(' ');
            }
        }
        return;
}
/*new level if all gold founded*/
void levelup(){
  Serial.println("level up");
  copy_Map();
  generate_Level(level);
  print_Map();
  //imperial march here
    for(int j=0;j<10;j++){
    for(int i=0;i<42;i++){
      Serial.write(mapa[j][i]);
    }
    Serial.write('\n');
    Clean();
  }
  return;
}



void setup() {
  Wire.begin();
  lcd.begin(20,4);
  lcd.clear();
  Serial.begin(9600);
  
  pinMode(22, OUTPUT); pinMode(27, OUTPUT);
  pinMode(23, OUTPUT); pinMode(28, OUTPUT);
  pinMode(24, OUTPUT); pinMode(29, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT); 

  Demo();
  
  copy_Map();
  generate_Level(level);
  print_Map();
  for(int j=0;j<10;j++){
    for(int i=0;i<42;i++){
      Serial.write(mapa[j][i]);
    }
    Serial.write('\n');

  }
  lcd.createChar(2, bomba);
  lcd.createChar(3,gold);
  lcd.createChar(4,omich);
  lcd.createChar(5,wall);
  lcd.createChar(6,player);
}

void loop() {
  Show(level);
  check_Gameover();
  control();
  tone(7,880,100);
  delay(100);
  noTone(7);
  proceed_Turn(level);
  if(bp==1 && bx!=-1 && by!=-1 && bc!=0 ) bomb_ex();
  check_Nish();
  print_Map();
}

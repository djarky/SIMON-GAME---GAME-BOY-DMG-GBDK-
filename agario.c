#include<stdio.h>
#include<gb/gb.h>
#include<gb/drawing.h>
#include<time.h>
#include<stdlib.h>
#include<rand.h>

unsigned char i=0;
unsigned char k=0;
unsigned char x=0;
unsigned char y=0;
UBYTE BallsX[]={
0x32,0x01,0x05,0x08,0x0A,0x10,0x15,0x20,0x25,0x30
};
UBYTE BallsY[]={
0x32,0x01,0x05,0x08,0x0A,0x10,0x15,0x20,0x25,0x30
};
UBYTE BallsR[]={
0x05,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01
};

void inputt(UBYTE p,UBYTE in){
 switch(in){
  case J_UP:   BallsY[p]--;break;
  case J_DOWN: BallsY[p]++;break;
  case J_RIGHT:BallsX[p]++;break;
  case J_LEFT: BallsX[p]--;break;
  default: if(joypad()!=in){inputt(i,rand());}
}
}

int distancia(UBYTE a,UBYTE b){
return (BallsX[a]-BallsX[b])*(BallsX[a]-BallsX[b])+(BallsY[a]-BallsY[b])*(BallsY[a]-BallsY[b]);
}


void comer(UBYTE p){
for(k=0;k<10;k++){
 if(distancia(k,p)==((BallsR[k]+BallsR[p])*2)*((BallsR[k]+BallsR[p])*2)){
  if(BallsR[k]>BallsR[p]){BallsR[p]=0x01;BallsX[p]=rand();BallsY[p]=rand();BallsR[k]++;}
  else{BallsR[k]=0x01;BallsX[k]=rand();BallsY[k]=rand();BallsR[p]++;}break;
}
}
}


void drawballs(){
for(i=0;i<10;i++){
x=BallsX[i];y=BallsY[i];

if(i==0){inputt(i,joypad());}
else{inputt(i,rand());}
comer(i);

if(x==BallsX[i]&& y==BallsY[i]){
color(BLACK,WHITE,SOLID);if(i==0){color(2,2,SOLID);}
circle(x,y,BallsR[i],1);
}
else{
color(WHITE,WHITE,SOLID);
circle(x,y,BallsR[i],1);
color(BLACK,WHITE,SOLID);if(i==0){color(2,2,SOLID);}
circle(BallsX[i],BallsY[i],BallsR[i],1);
}

}
}

void randpos(){
for(i=0;i<10;i++){
BallsX[i]=rand();BallsY[i]=rand();
}
}

void main(){
randpos();
while(1){
drawballs();
delay(35);
}
}
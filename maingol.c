#include<stdio.h>
#include<gb/gb.h>
#include<gb/drawing.h>
#include<time.h>
#include<stdlib.h>
#include<rand.h>

unsigned char x=0;
unsigned char y=0;
unsigned char z=0;
unsigned char i=0;
unsigned char k=0;

unsigned char n=0;

unsigned char Xpos[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char Ypos[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

int min(unsigned char a,unsigned char b){
if(a<b){return a;}else{return b;}
}
int max(unsigned char a,unsigned char b){
if(a>b){return a;}else{return b;}
}

void registrar(unsigned char xxx,unsigned char yyy){
if(xxx<0||xxx>160||yyy<8||yyy>144){
Xpos[1]=min(xxx,Xpos[1]);Ypos[1]=min(yyy,Ypos[1]);
Xpos[2]=max(xxx,Xpos[2])+1;Ypos[2]=max(yyy,Ypos[2])+1;}
else{Xpos[1]=0;Xpos[2]=160;Ypos[1]=8;Ypos[2]=144;}
}

void raiz(){
while(1){
color(WHITE,BLACK,SOLID);
gotogxy(0,0);gprintf("    ");
gotogxy(9,0);gprintf("           ");
gotogxy(4,0);gprintf("Ha %u",n);
if(n<10){gotogxy(3,0);gprintf(" ");gotogxy(8,0);gprintf(" ");}
if (getpix(x,y)!=BLACK){plot(x,y,4);}
if (joypad()==J_DOWN){y++;waitpadup();}
if (joypad()==J_UP){y--;waitpadup();}
if (joypad()==J_LEFT){x--;waitpadup();}
if (joypad()==J_RIGHT){x++;waitpadup();}
if (joypad()==J_UP+J_LEFT){y--;x--;}
if (joypad()==J_UP+J_RIGHT){y--;x++;}
if (joypad()==J_DOWN+J_LEFT){y++;x--;}
if (joypad()==J_DOWN+J_RIGHT){y++;x++;}
if (joypad()==J_START){break;}
if (getpix(x,y)==BLACK){z=35;}else{z=2;}
if(joypad()==J_A){z=35;registrar(x,y);n++;
waitpadup();}
plot(x,y,z);
delay(50);
}}

int cuenta(unsigned char xd,unsigned char yd){
z=0;
for(k=yd-1;k<yd+2;k++){
if(getpix(xd-1,k)==BLACK||getpix(xd-1,k)==2){z++;}
if(getpix(xd+1,k)==BLACK||getpix(xd+1,k)==2){z++;}
if(getpix(xd,k)==BLACK||getpix(xd,k)==2){    z++;}
}color(WHITE,BLACK,SOLID);gotogxy(9,0);gprintf("Ve %u",z);
return z;
}
void muerantodos(unsigned char xs,unsigned char ys){
for(k=ys-1;k<ys+2;k++){
if(getpix(xs-1,k)==BLACK){plot(xs-1,k,2);}
if(getpix(xs+1,k)==BLACK){plot(xs+1,k,2);}
if(getpix(xs,k)==BLACK){  plot(xs,k,2);}
}
}

void verificavacio(unsigned char xc,unsigned char yc){
for(y=yc-1;y<yc+2;y++){
if(cuenta(xc-1,y)==3){if(getpix(xc-1,y)==BLACK){plot(xc-1,y,35);}else{plot(xc-1,y,1);registrar(xc-1,y);}}
if(cuenta(xc+1,y)==3){if(getpix(xc+1,y)==BLACK){plot(xc+1,y,35);}else{plot(xc+1,y,1);registrar(xc+1,y);}}
if(cuenta(xc,y)==3){
if(getpix(xc,y)==BLACK){plot(xc,y,35);}else{plot(xc,y,1);registrar(xc,y);}}
if(joypad()==J_A){break;}
}
}


void LaLeyDeLaVida(unsigned char xx,unsigned char yy){
if(getpix(xx,yy)==BLACK){z=cuenta(xx,yy);n++;
if(z<3){plot(xx,yy,2);}
verificavacio(xx,yy);
if(z>4){muerantodos(xx,yy);}
}
}


void eliminar(){

for(x=0;x<n;x++){
if(getpix(Xpos[x],Ypos[x])==2||getpix(Xpos[x],Ypos[x])==4){//Xpos[x]=0;Ypos[x]=0;
plot(Xpos[x],Ypos[x],4);
 for(y=x;y<n;y++){
 Xpos[y]=Xpos[y+1];
 Ypos[y]=Ypos[y+1];
 Xpos[y]=Xpos[y+1];
 Ypos[y]=Ypos[y+1];
 }n--;
}
if(getpix(Xpos[x],Ypos[x])==1){plot(Xpos[x],Ypos[x],35);}
if(joypad()==J_A){break;}
}
}

void eliminared(unsigned char g){
   for(i=g;i<n;i++){
       Xpos[i]=Xpos[i+1];
       Ypos[i]=Ypos[i+1];
       Xpos[i]=Xpos[i+1];
       Ypos[i]=Ypos[i+1];
   }n--;
}

void eliminarep(unsigned char u){
for(y=u;y<n;y++){
 if(Xpos[y]==Xpos[u]&&Ypos[y]==Ypos[u]){
   Xpos[y]==0xFF;Ypos[y]==0xFF;eliminared(y);break;
   }
  }
}



void IniciaLaVida(){
while(1){n=0;
for(Xpos[0]=Xpos[1];Xpos[0]<Xpos[2];Xpos[0]++){
color(WHITE,BLACK,SOLID);
gotogxy(0,0);gprintf("p %u",Xpos[0]);
gotogxy(4,0);gprintf("Ha %u",n);
gotogxy(13,0);gprintf("C %u",Xpos[3]);
for(Ypos[0]=Ypos[1];Ypos[0]<Ypos[2];Ypos[0]++){
if(getpix(Xpos[0],Ypos[0])==4){}
else{LaLeyDeLaVida(Xpos[0],Ypos[0]);}
}}
for(Xpos[0]=Xpos[1];Xpos[0]<Xpos[2];Xpos[0]++){
color(WHITE,BLACK,SOLID);
gotogxy(0,0);gprintf("P %u",Xpos[0]);
gotogxy(4,0);gprintf("ha %u",n);
for(Ypos[0]=Ypos[1];Ypos[0]<Ypos[2];Ypos[0]++){
if(getpix(Xpos[0],Ypos[0])==2){plot(Xpos[0],Ypos[0],4);n--;}
if(getpix(Xpos[0],Ypos[0])==1){plot(Xpos[0],Ypos[0],35);}
}}Xpos[3]++;
if(joypad()==J_A){x=10;y=10;waitpadup();break;}
delay(50);
}
}

void clenners(){
DISPLAY_OFF;
gotogxy(0,0);
for(z=0;z<40;z++){gprintf("               ");}
DISPLAY_ON;
}

int main(){
Ypos[1]=0xFF;
gotogxy(5,1);
gprintf("Game of life");
gotogxy(1,15);
gprintf("Press Start");
waitpad(J_START);
clenners();
while(1){
x=10;y=10;
raiz();
IniciaLaVida();
}return 0;
}

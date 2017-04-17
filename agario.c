#include<stdio.h>
#include<gb/gb.h>
#include<gb/drawing.h>
#include<time.h>
#include<stdlib.h>
#include<rand.h>


/*                  VARIABLES                 */



unsigned char i=0;    //fors
unsigned char k=0;
unsigned char x=0;    //aux para limpiar la pantalla
unsigned char y=0;
unsigned char r=0;

unsigned char s=0;   


//bolas 

//posiciones en el eje X
UBYTE BallsX[]={
0x32,0x01,0x05,0x08,0x0A,0x10,0x15,0x20,0x25,0x30
};
//posiciones en el eje Y
UBYTE BallsY[]={
0x32,0x01,0x05,0x08,0x0A,0x10,0x15,0x20,0x25,0x30
};
//radios
UBYTE BallsR[]={
0x06,0x06,0x02,0x06,0x04,0x05,0x03,0x04,0x05,0x04
};
//Paleta
UWORD Palette[] = {
  0, 0, 0, 0
};





/*                 FUNCIONES                  */ 
  


//Cambia de color la paleta
void colores(){
    Palette[1]+=1;
    if (Palette[1]> 32767) Palette[1]=0;
    Palette[2]+=10;
    if (Palette[2]> 32767) Palette[2]=0;
    Palette[3]+=100;
    if (Palette[3]> 32767) Palette[3]=0;
    set_bkg_palette (0,1,Palette);
    delay (50);
}


//ENTADRA
void inputt(UBYTE p,UBYTE in){
 switch(in){
  case J_UP:   BallsY[p]--;break;
  case J_DOWN: BallsY[p]++;break;
  case J_RIGHT:BallsX[p]++;break;
  case J_LEFT: BallsX[p]--;break;
  case J_UP+J_RIGHT:   BallsY[p]--;BallsX[p]++;break;
  case J_UP+J_LEFT:    BallsY[p]--;BallsX[p]--;break;
  case J_DOWN+J_RIGHT: BallsY[p]++;BallsX[p]++;break;
  case J_DOWN+J_LEFT:  BallsY[p]++;BallsX[p]--;break;
  default: if(joypad()!=in){inputt(i,rand());}
}
while(BallsX[p]>159-BallsR[p]||BallsX[p]<BallsR[p]+1){BallsX[p]=rand();}//si se sale de rango
while(BallsY[p]>143-BallsR[p]||BallsY[p]<BallsR[p]+1){BallsY[p]=rand();}
}

//Colisiones
//si la distancia entre dos bolas es menor a la suma de sus radios
int colision(UBYTE a,UBYTE b){
if(BallsX[a]>BallsX[b]&&BallsY[a]>BallsY[b]){
if(BallsX[a]-BallsX[b]<BallsR[a]+BallsR[b]&&BallsY[a]-BallsY[b]<BallsR[a]+BallsR[b]){return 1;}}
if(BallsX[a]>BallsX[b]&&BallsY[a]<BallsY[b]){
if(BallsX[a]-BallsX[b]<BallsR[a]+BallsR[b]&&BallsY[b]-BallsY[a]<BallsR[a]+BallsR[b]){return 1;}}
if(BallsX[a]<BallsX[b]&&BallsY[a]>BallsY[b]){
if(BallsX[b]-BallsX[a]<BallsR[a]+BallsR[b]&&BallsY[a]-BallsY[b]<BallsR[a]+BallsR[b]){return 1;}}
if(BallsX[a]<BallsX[b]&&BallsY[a]<BallsY[b]){
if(BallsX[b]-BallsX[a]<BallsR[a]+BallsR[b]&&BallsY[b]-BallsY[a]<BallsR[a]+BallsR[b]){return 1;}}
}

//La bola con mayor radio es la que come a las de menor radio :V
//siempre y cuando colisionen entre si
void comer(UBYTE p){
for(k=0;k<10;k++){
  if(colision(k,p)==1&&k!=p){if(k==0||p==0){colores();}
  if(BallsR[k]>BallsR[p]){BallsR[p]=0x01;BallsX[p]=rand();BallsY[p]=rand();BallsR[k]++;}
  else{BallsR[k]=0x01;BallsX[k]=rand();BallsY[k]=rand();BallsR[p]++;}break;
}
}
}


//IA
//si la bola tiene mayor radio que s la persigue sino se escapa
int io(UBYTE p){/*s=mascerca(p);*/s=p-1;
if(BallsR[s]<BallsR[p]){
 if(BallsX[s]>BallsX[p]&&BallsY[s]>BallsY[p]){return J_RIGHT+J_DOWN;}
 if(BallsX[s]>BallsX[p]&&BallsY[s]<BallsY[p]){return J_RIGHT+J_UP;}
 if(BallsX[s]<BallsX[p]&&BallsY[s]>BallsY[p]){return J_LEFT+J_DOWN;}
 if(BallsX[s]<BallsX[p]&&BallsY[s]<BallsY[p]){return J_LEFT+J_UP;}
 if(BallsX[s]>BallsX[p]){return J_RIGHT;}
 if(BallsX[s]<BallsX[p]){return J_LEFT;}
 if(BallsY[s]>BallsY[p]){return J_DOWN;}
 if(BallsY[s]<BallsY[p]){return J_UP;}
}else{
 if(BallsX[s]>BallsX[p]&&BallsY[s]>BallsY[p]){return J_LEFT+J_UP;}
 if(BallsX[s]>BallsX[p]&&BallsY[s]<BallsY[p]){return J_LEFT+J_DOWN;}
 if(BallsX[s]<BallsX[p]&&BallsY[s]>BallsY[p]){return J_RIGHT+J_UP;}
 if(BallsX[s]<BallsX[p]&&BallsY[s]<BallsY[p]){return J_RIGHT+J_DOWN;}
 if(BallsX[s]>BallsX[p]){return J_LEFT;}
 if(BallsX[s]<BallsX[p]){return J_RIGHT;}
 if(BallsY[s]>BallsY[p]){return J_UP;}
 if(BallsY[s]<BallsY[p]){return J_DOWN;}
}
}

//para comer los otros puntitos
void comida(UBYTE p){
if(getpix(BallsX[p]+BallsR[p]+1,BallsY[p])==1||getpix(BallsX[p],BallsY[p]+BallsR[p]+1)==1){
BallsR[p]++;if(p==0){colores();}}
if(getpix(BallsX[p]-BallsR[p]-1,BallsY[p])==1||getpix(BallsX[p],BallsY[p]-BallsR[p]-1)==1){
BallsR[p]++;if(p==0){colores();}}
}

//para limpiar la pantalla
void clenners(){color(WHITE,WHITE,SOLID);gotogxy(0,0);DISPLAY_OFF;
for(k=0;k<20;k++){
gprintf("                              ");
}DISPLAY_ON;
}

//para achicar las bolas si hay una demaciado grande
void recortaradio(){
for(k=0;k<10;k++){
if(BallsR[k]>4){BallsR[k]=BallsR[k]/2;}
}clenners();
}



//Para dibujar las bolas, la entrada, en si todo el juego
void drawballs(){
for(i=0;i<10;i++){
x=BallsX[i];y=BallsY[i];r=BallsR[i];                      //guardamos la posion anterior

//si la bola es la 0 usamos los controles caso contrario la IA
if(i==0){inputt(i,joypad());}
else{inputt(i,io(i));}
comer(i);
comida(i);

if(BallsR[i]>30){recortaradio();}
if(x==BallsX[i]&& y==BallsY[i]){                     //si no se movio lo dejamos como estaba
color(BLACK,WHITE,SOLID);if(i==0){color(2,2,SOLID);}
circle(x,y,r,1);
}
else{
color(WHITE,WHITE,SOLID);                         //si se movio borramos la posion anterior
circle(x,y,r,1);
color(BLACK,WHITE,SOLID);if(i==0){color(2,2,SOLID);}
circle(BallsX[i],BallsY[i],BallsR[i],1);        //y actualizamos
}

}
}

//Genera un juego con posiones al azar
void randpos(){
for(i=0;i<10;i++){
BallsX[i]=rand();BallsY[i]=rand();
}
}



void main(){randpos();randpos();drawballs();
gotogxy(2,13);gprintf("github/djarky");delay(100);
for(i=0;i<20;i++){colores();}delay(200);gotogxy(2,13);gprintf("             ");
gotogxy(5,3);gprintf("AGAR.GB");gotogxy(6,5);gprintf("by ARKY");
while(joypad()!=J_START){randpos();}                               //generamos varios juegos 
clenners();                                                       
while(1){
drawballs();
plot(rand(),rand(),1);                                          //dibujamos la comida
color(BLACK,WHITE,SOLID);gotogxy(0,0);gprintf("%u",BallsR[0]); //contador de radio
delay(35);
}
}
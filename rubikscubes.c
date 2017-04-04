#include<stdio.h>
#include<gb/gb.h>
#include<gb/drawing.h>
#include<time.h>
#include<stdlib.h>
#include<rand.h>
#include<gb/cgb.h>            		   		 //para las paletas
#include"colors.c"           			        //tiles


/*                            VARIABLES                       */


unsigned char i=0;         			     //to fors
unsigned char k=0;
unsigned char cubo=0;      			    //tipo de cubo ej 2x2 3x3

UWORD Palette[]= {                                 //paleta GBC only
RGB_YELLOW,RGB_BLUE,RGB_RED,0
};

                                                 //Caras del cubo

UBYTE cup[]={        
0x03,0x03,0x03,
0x03,0x03,0x03,
0x03,0x03,0x03
};
UBYTE cdown[]={
0x06,0x06,0x06,
0x06,0x06,0x06,
0x06,0x06,0x06
};
UBYTE cleft[]={
0x02,0x02,0x02,
0x02,0x02,0x02,
0x02,0x02,0x02
};
UBYTE cright[]={
0x01,0x01,0x01,
0x01,0x01,0x01,
0x01,0x01,0x01
};
UBYTE cfront[]={
0x04,0x04,0x04,
0x04,0x04,0x04,
0x04,0x04,0x04
};
UBYTE cback[]={
0x05,0x05,0x05,
0x05,0x05,0x05,
0x05,0x05,0x05
};

                     //Aux Multiuso
UBYTE pieza[]={
0x05,0x05,0x05,
0x05,0x04,0x04,
0x04,0x04,0x04
};

                  //Cursor
unsigned char chose[] =
{
  0x00,0xFF,0x0C,0xFF,0x1C,0xFF,0x3C,0xFF,
  0x3C,0xFF,0x1C,0xFF,0x0C,0xFF,0x00,0xFF,
  0x00,0xFF,0x30,0xFF,0x38,0xFF,0x3C,0xFF,
  0x3C,0xFF,0x38,0xFF,0x30,0xFF,0x00,0xFF,
  0xFF,0x00,0xFF,0x0C,0xFF,0x1C,0xFF,0x3C,
  0xFF,0x3C,0xFF,0x1C,0xFF,0x0C,0xFF,0x00,
  0xFF,0x00,0xFF,0x30,0xFF,0x38,0xFF,0x3C,
  0xFF,0x3C,0xFF,0x38,0xFF,0x30,0xFF,0x00,
  0xFE,0xFE,0xFE,0x82,0xFC,0x84,0xFC,0x84,
  0xFE,0x82,0xFF,0xB1,0xCF,0xC9,0x07,0x07
};





/*            FUNCIONES         */


//PARA DIBUJAR EL CUBO

                                             //convierte una pieza del cubo de un color
int cuadrar(UBYTE color,UBYTE pieza[] ){
for(i=0;i<9;i++){
 pieza[i]=color;
}return pieza;
}

                                                          //dibuja las caras frontales

void draweibleF(UBYTE lado[],UBYTE x,UBYTE y,UBYTE parte[]){   //Cubo 3x3
set_bkg_tiles(0+x,0+y,2,2,cuadrar(lado[0],parte));            //dibuja pieza por pieza
set_bkg_tiles(3+x,0+y,2,2,cuadrar(lado[1],parte));           //toma una pieza de la cara
set_bkg_tiles(6+x,0+y,2,2,cuadrar(lado[2],parte));          //y la convierte en 
set_bkg_tiles(0+x,3+y,2,2,cuadrar(lado[3],parte));         //una pieza mas grande
set_bkg_tiles(3+x,3+y,2,2,cuadrar(lado[4],parte));        //y la setea al mapa
set_bkg_tiles(6+x,3+y,2,2,cuadrar(lado[5],parte));
set_bkg_tiles(0+x,6+y,2,2,cuadrar(lado[6],parte));
set_bkg_tiles(3+x,6+y,2,2,cuadrar(lado[7],parte));
set_bkg_tiles(6+x,6+y,2,2,cuadrar(lado[8],parte));
SHOW_BKG;
}
void drawF2x2(UBYTE lado[],UBYTE x,UBYTE y,UBYTE parte[]){   //Cubo 2x2
set_bkg_tiles(0+x,0+y,3,3,cuadrar(lado[0],parte));
set_bkg_tiles(4+x,0+y,3,3,cuadrar(lado[2],parte));
set_bkg_tiles(0+x,4+y,3,3,cuadrar(lado[6],parte));
set_bkg_tiles(4+x,4+y,3,3,cuadrar(lado[8],parte));
SHOW_BKG;
}
                                                   //dibuja las caras superiores e inferiores

void draweibleUD(UBYTE lado[],UBYTE x,UBYTE y,UBYTE parte[]){ //Cubo 3x3
set_bkg_tiles(0+x,0+y,2,1,cuadrar(lado[0],parte));
set_bkg_tiles(3+x,0+y,2,1,cuadrar(lado[1],parte));
set_bkg_tiles(6+x,0+y,2,1,cuadrar(lado[2],parte));
set_bkg_tiles(0+x,2+y,2,1,cuadrar(lado[3],parte));
set_bkg_tiles(3+x,2+y,2,1,cuadrar(lado[4],parte));
set_bkg_tiles(6+x,2+y,2,1,cuadrar(lado[5],parte));
set_bkg_tiles(0+x,4+y,2,1,cuadrar(lado[6],parte));
set_bkg_tiles(3+x,4+y,2,1,cuadrar(lado[7],parte));
set_bkg_tiles(6+x,4+y,2,1,cuadrar(lado[8],parte));
SHOW_BKG;
}
void drawUD2x2(UBYTE lado[],UBYTE x,UBYTE y,UBYTE parte[]){ //Cubo 2x2
set_bkg_tiles(0+x,0+y,3,2,cuadrar(lado[0],parte));
set_bkg_tiles(4+x,0+y,3,2,cuadrar(lado[2],parte));
set_bkg_tiles(0+x,3+y,3,2,cuadrar(lado[6],parte));
set_bkg_tiles(4+x,3+y,3,2,cuadrar(lado[8],parte));
SHOW_BKG;
}
void drawUDfloppy(UBYTE lado[],UBYTE x,UBYTE y,UBYTE parte[]){ //Cubo Floppy 3x3x1
set_bkg_tiles(0+x,2+y,2,1,cuadrar(lado[3],parte));
set_bkg_tiles(3+x,2+y,2,1,cuadrar(lado[4],parte));
set_bkg_tiles(6+x,2+y,2,1,cuadrar(lado[5],parte));
}

                                                    //dibuja las caras  laterales

void draweibleRL(UBYTE lado[],UBYTE x,UBYTE y,UBYTE parte[]){  //Cubo 3x3
set_bkg_tiles(0+x,0+y,1,2,cuadrar(lado[0],parte));
set_bkg_tiles(2+x,0+y,1,2,cuadrar(lado[1],parte));
set_bkg_tiles(4+x,0+y,1,2,cuadrar(lado[2],parte));
set_bkg_tiles(0+x,3+y,1,2,cuadrar(lado[3],parte));
set_bkg_tiles(2+x,3+y,1,2,cuadrar(lado[4],parte));
set_bkg_tiles(4+x,3+y,1,2,cuadrar(lado[5],parte));
set_bkg_tiles(0+x,6+y,1,2,cuadrar(lado[6],parte));
set_bkg_tiles(2+x,6+y,1,2,cuadrar(lado[7],parte));
set_bkg_tiles(4+x,6+y,1,2,cuadrar(lado[8],parte));
SHOW_BKG;
}
void drawRL2x2(UBYTE lado[],UBYTE x,UBYTE y,UBYTE parte[]){ //Cubo 2x2
set_bkg_tiles(0+x,0+y,2,3,cuadrar(lado[0],parte));
set_bkg_tiles(3+x,0+y,2,3,cuadrar(lado[2],parte));
set_bkg_tiles(0+x,4+y,2,3,cuadrar(lado[6],parte));
set_bkg_tiles(3+x,4+y,2,3,cuadrar(lado[8],parte));
SHOW_BKG;
}
void drawRLfloppy(UBYTE lado[],UBYTE x,UBYTE y,UBYTE parte[]){ //Cubo Floppy
set_bkg_tiles(2+x,0+y,1,2,cuadrar(lado[1],parte));
set_bkg_tiles(2+x,3+y,1,2,cuadrar(lado[4],parte));
set_bkg_tiles(2+x,6+y,1,2,cuadrar(lado[7],parte));
}

                                                             //Dibuja Todo el Cubo

void drawkubik3x3(){                                       //Cubo 3x3
set_bkg_tiles(0,0,3,3,cback);                             //dibuja el cubo cara por cara
draweibleUD(cup,6,0,pieza);
draweibleUD(cdown,6,13,pieza);
draweibleRL(cleft,1,5,pieza);
draweibleRL(cright,14,5,pieza);
draweibleF(cfront,6,5,pieza);
}
void drawkubik2x2(){                                  //Cubo 2x2
set_bkg_tiles(0,0,2,2,cuadrar(cback[0],pieza));
set_bkg_tiles(0,3,2,2,cuadrar(cback[2],pieza));
set_bkg_tiles(3,0,2,2,cuadrar(cback[6],pieza));
set_bkg_tiles(3,3,2,2,cuadrar(cback[8],pieza));
drawUD2x2(cup,7,1,pieza);
drawUD2x2(cdown,7,13,pieza);
drawRL2x2(cleft,2,6,pieza);
drawRL2x2(cright,14,6,pieza);
drawF2x2(cfront,7,6,pieza);
}
void drawkubikfloppy(){                           //Cubo Floppy
set_bkg_tiles(0,0,3,3,cback);
drawUDfloppy(cup,6,1,pieza);
drawUDfloppy(cdown,6,12,pieza);
drawRLfloppy(cleft,2,5,pieza);
drawRLfloppy(cright,13,5,pieza);
draweibleF(cfront,6,5,pieza);
}

//PARA ROTAR EL CUBO

void rotarA(UBYTE cara[]){               //rota una cara del cubo SOLO esa cara
pieza[0]=cara[0];cara[0]=cara[6];       //en sentido de las agujas del relog
cara[6]=cara[8];cara[8]=cara[2];
cara[2]=pieza[0];pieza[0]=cara[1];
cara[1]=cara[3];cara[3]=cara[7];
cara[7]=cara[5];cara[5]=pieza[0];
}
void rotarB(UBYTE cara[]){            //y en sentido contrario
pieza[0]=cara[0];cara[0]=cara[2];
cara[2]=cara[8];cara[8]=cara[6];
cara[6]=pieza[0];pieza[0]=cara[1];
cara[1]=cara[5];cara[5]=cara[7];
cara[7]=cara[3];cara[3]=pieza[0];
}


                                  //rota las piezas del cubo 
void kup(UBYTE p){               //rota todas las piezas en esa columna hacia arriba
for(i=p;i<9;i+=3){
pieza[i]=cup[i];cup[i]=cfront[i];
cfront[i]=cdown[i];cdown[i]=cback[i];
cback[i]=pieza[i];
}
}
void kdown(UBYTE p){
for(i=p;i<9;i+=3){
pieza[i]=cback[i];cback[i]=cdown[i];
cdown[i]=cfront[i];cfront[i]=cup[i];
cup[i]=pieza[i];
}
}
                                                      //rota las piezas en esa fila
void kright(UBYTE p){rotarA(cback);rotarA(cback);    //NOTA necesita rotar la cara posterior
for(i=p;i<p+3;i++){                                 //por que para ver esa cara es necesario
pieza[i]=cfront[i];cfront[i]=cleft[i];             //rotarla XDXD
cleft[i]=cback[i];cback[i]=cright[i];
cright[i]=pieza[i];
}rotarA(cback);rotarA(cback);
}
void kleft(UBYTE p){rotarA(cback);rotarA(cback);
for(i=p;i<p+3;i++){
pieza[i]=cright[i];cright[i]=cback[i];
cback[i]=cleft[i];cleft[i]=cfront[i];
cfront[i]=pieza[i];
}rotarA(cback);rotarA(cback);
}

//PARA LOS CONTROLES

void registrar(UBYTE X){    //hace un registro de pasos para poder deshacerlos
if(X==joypad()){
if(grises[0]<128){        //reutilizacion de variables ya que se usa solo al inicio
grises[0]++;
colors[grises[0]]=X;}
}
}

void inputt(UBYTE X);    //Declaracion de lafuncion de abajo para poder utilizarla antes :v

void ctrZ(){            //deshace un paso   
if(grises[0]>0x00){
inputt(colors[grises[0]]);   //Repite el paso tres veces 
inputt(colors[grises[0]]);  //Porque asi es como si se hiciera un contrario :v
inputt(colors[grises[0]]);
grises[0]--;
}}


void mesclar(){                          //mescla el cubo con la logica del movimiento natural 
for(k=0;k<20;k++){                      //por que sino no se podria armar XDXDXD
inputt(rand());if(joypad()!=0){break;} 
}grises[0]=0x00;
}


                           //ENTRADA Y CONTROLES
                                                  //toma el valor realiza la accion y lo registra
void inputt(UBYTE X){                            //waitpad(espera a que se deje de presionar)
  switch(X){  
     case J_UP:   kup(1);   registrar(X);waitpadup(); break; 
     case J_DOWN: kdown(1); registrar(X);waitpadup(); break;
     case J_RIGHT:kright(3);registrar(X);waitpadup(); break;
     case J_LEFT: kleft(3); registrar(X);waitpadup(); break;
     case J_B+J_UP :  kup(0);   rotarB(cleft); registrar(X);waitpadup();  break;
     case J_B+J_DOWN: kdown(0); rotarA(cleft); registrar(X);waitpadup();  break;
     case J_A+J_UP:   kup(2);   rotarA(cright);registrar(X);waitpadup();  break;
     case J_A+J_DOWN: kdown(2); rotarB(cright);registrar(X);waitpadup();  break;
     case J_B+J_RIGHT:kright(6);rotarA(cdown); registrar(X);waitpadup();  break;
     case J_B+J_LEFT: kleft(6); rotarB(cdown); registrar(X);waitpadup();  break;
     case J_A+J_RIGHT:kright(0);rotarB(cup);   registrar(X);waitpadup();  break;
     case J_A+J_LEFT: kleft(0); rotarA(cup);   registrar(X);waitpadup();  break;
     case J_SELECT+J_UP:   inputt(J_B+J_UP);   inputt(J_A+J_UP);   kup(1);   registrar(X);waitpadup(); break;
     case J_SELECT+J_DOWN: inputt(J_B+J_DOWN); inputt(J_A+J_DOWN); kdown(1); registrar(X);waitpadup(); break;
     case J_SELECT+J_RIGHT:inputt(J_B+J_RIGHT);inputt(J_A+J_RIGHT);kright(3);registrar(X);waitpadup(); break;
     case J_SELECT+J_LEFT: inputt(J_B+J_LEFT); inputt(J_A+J_LEFT); kleft(3); registrar(X);waitpadup(); break;
     case J_SELECT+J_A: inputt(J_SELECT+J_UP);inputt(J_A+J_LEFT); inputt(J_SELECT+J_DOWN);registrar(X);waitpadup(); break;
     case J_SELECT+J_B: inputt(J_SELECT+J_UP);inputt(J_A+J_RIGHT);inputt(J_SELECT+J_DOWN);registrar(X);waitpadup(); break;
     case J_A+J_B: ctrZ();waitpadup();break;
     case J_SELECT+J_START:mesclar();break;
     default: if(joypad()!=X){inputt(rand());}  //SOLO cuando esta Mesclando
}
}
                          //Exepcion Cubo Floppy (Logica distinta)
void inputtf(UBYTE X){
if(X==J_SELECT+J_START){
inputtf(rand());
}else{
inputt(X);inputt(X);   //necesita rotarse dos veces
}
}

//DIBUJAR CUBO CURSOR Y DEMAS FUNCIONES


void drawcubo(unsigned char Cube){     //llama la funcion de dibujo segun el cubo
  switch(Cube){
  case 0: drawkubik3x3();    break;
  case 1: drawkubik2x2();    break;
  case 2: drawkubikfloppy(); break;
  case 3: drawkubik3x3();    break;
} 
}
void drawcursor(UBYTE X){
switch(X){
 case J_A :     	 move_sprite(0,110,65); break;
 case J_B :     	 move_sprite(0,65,110); break;
 case J_SELECT: 	 move_sprite(0,40,40);  break;
 case J_RIGHT:  	 move_sprite(0,95,87);  break;
 case J_LEFT :  	 move_sprite(0,80,87);  break;
 case J_UP :    	 move_sprite(0,87,80);  break;
 case J_DOWN:   	 move_sprite(0,87,95);  break;
 case J_A+J_UP: 	 move_sprite(0,110,60); break;
 case J_A+J_DOWN :       move_sprite(0,110,70); break;
 case J_B+J_UP  :        move_sprite(0,65,100); break;
 case J_B+J_DOWN :       move_sprite(0,65,120); break;
 case J_A+J_RIGHT:       move_sprite(0,120,65); break;
 case J_A+J_LEFT:        move_sprite(0,100,65); break;
 case J_B+J_RIGHT :      move_sprite(0,70,110); break;
 case J_B+J_LEFT :       move_sprite(0,60,110); break;
 case J_SELECT+J_UP:     move_sprite(0,40,30);  break;
 case J_SELECT+J_DOWN:   move_sprite(0,40,50);  break;
 case J_SELECT+J_RIGHT:  move_sprite(0,50,40);  break;
 case J_SELECT+J_LEFT:   move_sprite(0,30,40);  break;
 case J_SELECT+J_A:      move_sprite(0,80,40);  break;
 case J_SELECT+J_B:      move_sprite(0,40,80);  break;
 default: move_sprite(0,87,87);
}
}

                                                        //limpia la pantalla
void clenners(){
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


//CUBO VOID

void ahuecar(){
cfront[4]=0x00;cback[4]=0x00;cleft[4]=0x00;
cright[4]=0x00;cup[4]=0x00;cdown[4]=0x00;
}
void tapar(){
cfront[4]=0x04;cback[4]=0x05;cleft[4]=0x02;
cright[4]=0x01;cup[4]=0x03;cdown[4]=0x06;
}

//MENU DE SELECCION

void selecube(){
clenners();
set_sprite_data(0,5,chose);   //carga los datos de los sprites
while(1){
set_sprite_tile(0,0);       //flecha izquierda
move_sprite(0,20,130);
set_sprite_tile(1,1);      //flecha derecha
move_sprite(1,150,130);
SHOW_SPRITES;

if(joypad()==J_RIGHT){cubo++;       //Cambia de Cubo
set_sprite_tile(1,3);waitpadup();  //muestra que se presiono el boton
DISPLAY_OFF;clenners();}          //Limpia la pantalla para mostrar el siguiente cubo
if(joypad()==J_LEFT){cubo--;
set_sprite_tile(0,2);waitpadup();
DISPLAY_OFF;clenners();}
if(cubo==3){ahuecar();}                    //cubo void 
if(cubo>3){cubo=0;tapar();}               //para mostrar el primer cubo si no hay mas
drawcubo(cubo);DISPLAY_ON;               //Muestra el cubo seleccionado
if(joypad()==J_A){HIDE_SPRITES;break;}  //oculta las flechitas 
}
}



/*            PRINCIPAL             */




void main(){
set_bkg_palette(0,1, & chose[2]);          //Cargamos una paleta de colores que no sea
printf("     \n");                        //la principal POR QUE NO QUIERO que sea AMARILLO
printf("http://github.com/djarky");      //que es el color 0
for(i=0;i<10;i++){delay(400);}          //retraso
DISPLAY_OFF;                           //apaga la pantalla para que no se vea el desliz
clenners();                           //limpia la pantalla
printf("  RUbIK`s CUbEs \n\n");      //titulo
printf("       by arky");
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
printf("  > > > PRESS START"); 
DISPLAY_ON;                       //ensendemos la pantalla nuevamente
waitpad(J_START);                //espera a que se presione start
DISPLAY_OFF;                    //apagamos la pantalla
clenners();                    //limpiamos la pantalla

printf("CONTROL COMANDS\n\n");                 //ESTOS SON LOS CONTROLES DETALLADOS
printf(" A/B to SeL RU/LD\n");
printf(" A+R/L to U'/U \n");
printf(" B+R/L to D/D' \n");
printf(" A+U/D to R/R' \n");
printf(" B+U/D to L'/L \n");
printf(" SELECT+A/B to F/F'\n");
printf(" R/L to ME/ME'\n");
printf(" U/D to M/M'  \n");
printf(" SELECT+R/L to X/X'\n");
printf(" SELECT+U/D to Y/Y'\n");
printf(" SELECT+START to MIX");
printf(" START Hide/Show CUR");
printf(" A+B to Ctr+Z \n");
printf("\nPRESS A to CONTINUE\n");
DISPLAY_ON;  
waitpad(J_A);
DISPLAY_OFF; 
clenners(); 

DISPLAY_ON;
set_bkg_palette(0, 1, & Palette [0]);            //esta es la paleta OFICIAL 
set_sprite_palette(0,1,& Palette[0]);           //solo se carga en GBColor
if(_cpu==DMG_TYPE){set_bkg_data(0,7,grises);}  //si es un DMG carga texturas para hacerlo
else{set_bkg_data(0,7,colors);}               //retro-compatible     si no colores
selecube();                                  //para seleccionar el cubo
set_sprite_tile(0,4);                       //usamos el mismo sprite anterior para el cursor
move_sprite(1,200,200);                    //y mandamos al otro fuera de la pantalla
grises[0]=0x00;                           //reutilizamos la variable parra poder contar
SHOW_SPRITES;                            //los pasos y mostramos el cursor



while(1){                              //bucle infinito                 
drawcubo(cubo);                       //mostramos el cubo
if(get_sprite_tile(1)==1){           //como cuando utilizas un sprite como switch
if(joypad()==J_START){HIDE_SPRITES;set_sprite_tile(1,0);waitpadup();}}      //para ocultar o
else{if(joypad()==J_START){SHOW_SPRITES;set_sprite_tile(1,1);waitpadup();}}//mostrar el cursor

drawcursor(joypad());                        //movemos el cursor 
if(cubo==2){inputtf(joypad());}else         //si el cubo es el floppy utilizamos otros controles
{inputt(joypad());}                        //si no los clasicos 
}
}
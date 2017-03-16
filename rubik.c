#include<stdio.h>
#include<gb/gb.h>
#include<gb/drawing.h>
#include<time.h>
#include<stdlib.h>
#include<rand.h>
#include<gb/cgb.h>                //para las paletas
#include"colors.c"               //tiles

unsigned char i=0;             //fors
unsigned char k=0;
unsigned char AUX=0;          //para rotar los Arrays
unsigned char score=16;      //puntaje 
unsigned char level=0;      //nivel
unsigned char niv=0;       //para subir de nivel

//es el lado que podemos mover
UBYTE cara[]={
0x02,0x03,0x03,
0x03,0x03,0x03,
0x03,0x03,0x01
};
//para poder dibujar la cara del cubo
UBYTE cuadrado[]={
0x00,0x00,0x00,
0x00,0x00,0x00,
0x00,0x00,0x00
};
//es la solucion a la que hay que llegar
UBYTE base[]={
0x03,0x03,0x03,
0x03,0x03,0x03,
0x03,0x03,0x01
};

//paleta de colores para CBG
UWORD Palette[]= {
RGB_WHITE,RGB_RED,RGB_BLUE,0
};



/*FUNCIONES*/



/*PARA MOVER EL ARRAY*/

//para mover el Array hacia arriba
int Kup(UBYTE c[]){
for(i=0;i<3;i++){
 AUX=c[i];c[i]=c[i+3];c[i+3]=c[i+6];c[i+6]=AUX;
}return c;
}
//para mover el Array hacia abajo
int Kdown(UBYTE c[]){
for(i=0;i<3;i++){
 AUX=c[i+6];c[i+6]=c[i+3];c[i+3]=c[i];c[i]=AUX;
}return c;
}
//para mover el Array hacia arriba
int Kleft(UBYTE c[]){
for(i=0;i<9;i+=3){
 AUX=c[i];c[i]=c[i+1];c[i+1]=c[i+2];c[i+2]=AUX;
}return c;
}
//para mover el Array hacia la derecha
int Kright(UBYTE c[]){
for(i=0;i<9;i+=3){
 AUX=c[i+2];c[i+2]=c[i+1];c[i+1]=c[i];c[i]=AUX;
}return c;
}
//para rotar el Array en sentido contrario de las agujas del rejog
int RotarB(UBYTE c[]){
 AUX=c[0];c[0]=c[1];
 c[1]=c[2];c[2]=c[5];
 c[5]=c[8];c[8]=c[7];
 c[7]=c[6];c[6]=c[3];c[3]=AUX;
return c;
}
//para rotar el Array en sentido de las agujas del rejog
int RotarA(UBYTE c[]){
 AUX=c[0];c[0]=c[3];
 c[3]=c[6];c[6]=c[7];
 c[7]=c[8];c[8]=c[5];
 c[5]=c[2];c[2]=c[1];c[1]=AUX;
}


//crea una pieza de 3x3 tiles de una posicion del Array 
int cuadrar(UBYTE color,UBYTE pieza[] ){
for(i=0;i<9;i++){
 pieza[i]=color;
}return pieza;
}

//Dibuja una cara del cubo en una posicion
//lado es el Array que queremos dibujar
//X es la poscion inicial en el eje de las x
//Y es la poscion inicial en el eje de las Y
//parte es la pieza a generar con la anterior funcion
void draweible(UBYTE lado[],UBYTE x,UBYTE y,UBYTE parte[]){
set_bkg_tiles(0+x,0+y,3,3,cuadrar(lado[0],parte));
set_bkg_tiles(4+x,0+y,3,3,cuadrar(lado[1],parte));
set_bkg_tiles(8+x,0+y,3,3,cuadrar(lado[2],parte));
set_bkg_tiles(0+x,4+y,3,3,cuadrar(lado[3],parte));
set_bkg_tiles(4+x,4+y,3,3,cuadrar(lado[4],parte));
set_bkg_tiles(8+x,4+y,3,3,cuadrar(lado[5],parte));
set_bkg_tiles(0+x,8+y,3,3,cuadrar(lado[6],parte));
set_bkg_tiles(4+x,8+y,3,3,cuadrar(lado[7],parte));
set_bkg_tiles(8+x,8+y,3,3,cuadrar(lado[8],parte));
SHOW_BKG;
}


//para los controles
//ca es el Array que queremos modificar y X es la entrada
//si es Arriba llamamos a la funcion que lo mueva arriba ect.
int inputt(UBYTE ca[],unsigned char X ){
  switch(X){   /*llama a la f ,espera que se deje de presionar*/
     case J_UP:    Kup(ca);   waitpadup(); break; 
     case J_DOWN:  Kdown(ca); waitpadup(); break;
     case J_RIGHT: Kright(ca);waitpadup(); break;
     case J_LEFT:  Kleft(ca); waitpadup(); break;
     case J_A:     RotarA(ca);waitpadup(); break;
     case J_B:     RotarB(ca);waitpadup(); break;
     default :     draweible(ca,5,3,cuadrado);
}AUX=0;      //por si queda algun valor
 return ca; //retornamos el Array
}

//convierte un a un valor dentro del rango de los controles ver simon_main.c
int convertir(UBYTE s){
   switch(s){
     case 1   : return J_UP;      break;
     case 2   : return J_DOWN;    break;
     case 3   : return J_RIGHT;   break;
     case 4   : return J_LEFT;    break;
     case 5   : return J_A;       break;
     case 6   : return J_B;       break;
     default  : return convertir(rand()); 
 }
}

//para llenar el Array con los colores
int llenar(UBYTE s){
   switch(s){
     case 1   : return 1;   break;
     case 2   : return 2;   break;
     case 3   : return 3;   break;
     default  : return llenar(rand()); 
 }
}


/*NIVELES*/

void Facil(){
 k=llenar(rand());                      //toma una posicion al azar        
 base[k]=llenar(rand());               //genera una pieza de un color al azar
 cara[k]=base[k];                     //copia la pieza a la solucion
 inputt(cara,convertir(rand()));     //mueve la pieza a una posion al azar 
}
void Medio(){k=llenar(rand());                               //toma una posicion al azar 
 for(i=k;i<5;i++){base[i]=llenar(rand());cara[i]=base[i];}  //genera piezas al azar y las copia
 for(k=0;k<5;k++){inputt(cara,convertir(rand()));}         //mezcla el cubo
}
void Dificil(){k=llenar(rand());                             //toma una posicion al azar 
 for(i=k;i<9;i++){base[i]=llenar(rand());cara[i]=base[i];}  //genera piezas al azar y las copia
 for(k=0;k<20;k++){inputt(cara,convertir(rand()));}        //mezcla el cubo
}



//Verifica si esta armado
int estarmado(UBYTE car[],UBYTE bas[]){
 k=0;                          //k como Kontador
 AUX=0;                       //swicth comienza en falso
 for(i=0;i<9;i++){           //recorre todo el Array
  if(bas[i]==car[i]){k++;}  //incrementa el kontador si son iguales
 }if(k==9){AUX=1;}         //si todas las piezas son iguales swicth=1
return AUX;               //retorna el valor del swicth
}




//inicia el problema y su solucion
void iniciar(unsigned char nivel){
for(i=0;i<9;i++){cara[i]=0x03;base[i]=0x03;}                 //limpia los Arrays

//para mostrar en que nivel se encuentra solo si se inicia una vez
if(cuadrado[0]==0xFF){printf("");}else{cuadrado[0]=0xFF; 
 switch(nivel){
  case 0 : printf("Easy");  break;
  case 1 : printf("Medium");break;
  case 2 : printf("Hard");  break;
  default :printf("Hard");
}}
//para iniciar en ese nivel
 switch(nivel){
  case 0 : Facil();   break;
  case 1 : Medio();   break;
  case 2 : Dificil(); break;
  default : Dificil();
}if(estarmado(cara,base)==1){iniciar(nivel);} //si esta armado vuelve a iniciar
}



//al elegir un nivel visualiza que nivel vas a elegir
void drawlevel(unsigned char levr){
 switch(levr){
  case 0 : cara[0]=0x01;cara[1]=0x01;cara[2]=0x01; break;                //facil
  case 1 : cara[3]=0x02;cara[4]=0x02;cara[5]=0x02;drawlevel(0); break;  //medio
  case 2 : cara[6]=0x02;cara[7]=0x02;cara[8]=0x02;drawlevel(1); break; //dificil
} draweible(cara,5,3,cuadrado); 
}


//para seleccionar un nivel al inicio
void seleclevel(){
while(1){
 if(joypad()==J_DOWN){level++;waitpadup();}             //sube de nivel 
 if(joypad()==J_UP){level--;waitpadup();}              //baja de nivel
 if(level>2){level=0;}                                //si el nivel no existe lo pone en cero
 draweible(cara,5,3,cuadrado);                
 for(i=0;i<9;i++){cara[i]=0x03;}drawlevel(level);   //visualiza el nivel a elegir
 if(joypad()==J_A){break;}                         //rompe el bucle
} iniciar(level);                                 //inicia en ese nivel
}

//Limpia la pantalla
void cleners(){
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

//intercala niveles por ejemplo si eligio facil genera dos faciles y un medio
int subnivel(unsigned char lev){
if(lev<4){                    //si el nivel no es dificil
niv++;                       //incrementa el contador
if(niv==3){                 
lev++;                     //sube de nivel
niv=0;                    //pone el contador en cero
}
}
return lev;            //retorna el nuevo nivel
}



//Es la animacion que se muestra al encender el juego
void animar(){
 draweible(cara,5,3,cuadrado);delay(200);
 cara[1]=0x02;cara[7]=0x01;
 draweible(cara,5,3,cuadrado);delay(200);
 cara[2]=0x02;cara[6]=0x01;
 draweible(cara,5,3,cuadrado);delay(200);
 cara[3]=0x02;cara[5]=0x01;
 draweible(cara,5,3,cuadrado);delay(200);
 cara[4]=0x01; draweible(cara,5,3,cuadrado);delay(200);
 cara[1]=0x03;cara[7]=0x03;
 draweible(cara,5,3,cuadrado);delay(200);
 cara[2]=0x03;cara[6]=0x03;
 draweible(cara,5,3,cuadrado);delay(200);
 for(k=0;k<4;k++){ RotarA(cara); draweible(cara,5,3,cuadrado);delay(200);}
 for(k=0;k<9;k++){cara[k]=0x03;}
 cara[0]=0x02;cara[1]=0x02;cara[3]=0x02;
 cara[5]=0x01;cara[7]=0x01;cara[8]=0x01;
 draweible(cara,5,3,cuadrado);delay(200);cara[4]=0x02;
 for(k=0;k<4;k++){RotarB(cara);draweible(cara,5,3,cuadrado);delay(200);} 
 for(k=0;k<9;k++){cara[k]=0x03;}
 cara[2]=0x02;cara[6]=0x01;draweible(cara,5,3,cuadrado);delay(800);
}




//Principal
int main(){
set_bkg_palette(0, 1, & Palette [0]);      //selecciona la paleta solo CGB
printf("     \n");
printf("http://github.com/djarky");
for(i=0;i<10;i++){delay(400);}          //retraso
DISPLAY_OFF;                           //apaga la pantalla para que no se vea el desliz
cleners();                            //limpia la pantalla
printf("RUBIK SLIDE < < <\n\n");     //muestra el titulo del juego          
printf("        >  by ARKY\n");
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
printf("  > > > PRESS START"); 
DISPLAY_ON;                        //enciende la pantalla
waitpad(J_START);                 //espera a que se presione START
cleners();
if(_cpu==DMG_TYPE){set_bkg_data(0,4,grises);}  //verifica si es gb o gbc 
else{set_bkg_data(0,4,colors);}               //si es gb setea texturas
 animar();                                   //muestra la animacion
 seleclevel();                              //selecciona el nivel
 draweible(cara,5,3,cuadrado);
while(1){                                 //bucle infinitoo
 if(joypad()=!0){inputt(cara,joypad());  //mueve el cubo segun el joypad
 draweible(cara,5,3,cuadrado);          //dibuja el cubo
 
//si se presiona selec te muestra cuantos resolviste
 if(joypad()==J_SELECT){printf("YOU SOLVED : "); 
 printf(& score);waitpadup();cleners();}         //no se como imprimir esa cosa LOL
//si se presiona start te muestra la solucion 
 if(joypad()==J_START){draweible(base,5,3,cuadrado);
 waitpadup();draweible(cara,5,3,cuadrado);}
 }
//si esta armado incrementa el puntaje y vuelve a iniciar
 if(estarmado(cara,base)==1){score++;
 printf("SOLVED");cleners();iniciar(subnivel(level));}
}
return 0;
}
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
  
     mmmmmmmmmm   mmm  mmmmmmmmmmmm         mmmmmmmmm        mmmmmmmmm             P
    mmmmmmmmmmm   mmm  mmmmmmmmmmmmm     m mmmmmmmmmmm m     mmmmmmmmmm            R
   mmm            mmm  mmm  mmm  mmm    mmm mmmmmmmmm mmm    mmm    mmm            O
   mmm            mmm  mmm  mmm  mmm   mmmmm         mmmmm   mmm    mmm            G
    mmmmmmmmmm    mmm  mmm  mmm  mmm   mmmmm  SIMON  mmmmm   mmm    mmm            R
            mmm   mmm  mmm  mmm  mmm   mmmmm         mmmmm   mmm    mmm            A
            mmm   mmm  mmm  mmm  mmm    mmm mmmmmmmmm mmm    mmm    mmm            M
    mmmmmmmmmm    mmm  mmm  mmm  mmm     m mmmmmmmmmmm m     mmm    mmm
    mmmmmmmmm     mmm  mmm  mmm  mmm        mmmmmmmmm        mmm    mmm       BY  ARKY

mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm */



#include<stdio.h>
#include<gb/gb.h>
#include<gb/drawing.h>
#include<time.h>
#include<stdlib.h>
#include<rand.h>
#include "tile_simon.c" //tiles
#include "map_simon.c"  //mapa

/*--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==
                                       VARIABLES
--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==*/

unsigned char i=0;   //para los fors
unsigned char k=0;  
unsigned char score = 0; //puntaje

//vector de secuencia a seguir
UBYTE secuencia[] ={
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00
};


/*--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==
                                      FUNCIONES
--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==*/


//convierte el valor a un rango utilizado por los controles
int convertir(UBYTE s){
   switch(s){
     case 1   : return J_UP;
     case 2   : return J_RIGHT;
     case 3   : return J_LEFT;
     case 4   : return J_DOWN;
     default  : return convertir(rand()); //vuelve hasta que el valor este en el rango
 }
}

//inicia
void iniciar(){score=0; //resetea el puntaje
set_bkg_data(0,67,Tiles); //carga los tiles
set_win_data(0,67,Tiles);
//para generar la secuencia
for(i=0;i<40;i++){ 
    secuencia[i]=convertir(rand()); //llena la secuencia con un valor random
 }
}


//para hacer encender las luces

//arriba
void Sup(){
set_bkg_tiles(0,0,20,17,up);//carga el fondo
set_win_tiles(0,0,20,17,up);
SHOW_BKG;SHOW_WIN; //muestra el fondo
}
//abajo
void Sdown(){
set_bkg_tiles(0,0,20,17,down);//carga el fondo
set_win_tiles(0,0,20,17,down);
SHOW_BKG;SHOW_WIN; //muestra el fondo
}
//derecha
void Sright(){
set_bkg_tiles(0,0,20,17,right);//carga el fondo
set_win_tiles(0,0,20,17,right);
SHOW_BKG;SHOW_WIN;//muestra el fondo
}
//izquierda
void Sleft(){
set_bkg_tiles(0,0,20,17,left);//carga el fondo
set_win_tiles(0,0,20,17,left);
SHOW_BKG;SHOW_WIN; //muestra el fondo
}
//cuando no estan encendidas
void Medio(){
set_bkg_tiles(0,0,20,17,simon);//carga el fondo
set_win_tiles(0,0,20,17,simon);
SHOW_BKG;SHOW_WIN;//muestra el fondo
}




//muestra el boton presionado o la parte de la secuencia
void Mostrar(unsigned char x){
 switch(x){
     case J_UP   : Sup();   break;
     case J_RIGHT: Sright();break;
     case J_LEFT : Sleft(); break;
     case J_DOWN : Sdown(); break;
     default     : i=40;k=40;
 }
}



//para jugar una parte de la secuencia
int Jugar(unsigned char x){
while(joypad()==0){Medio();}          //espera a que se presione un boton
    Mostrar(joypad());               //muestra el boton presionado
    if(joypad()==secuencia[x]){     //verifica que el boton presionado sea el correcto
    waitpadup();                   //espera hasta que se deje de presionar
    Medio();                      //apaga las luces
    return 1;}                   //retorna verdadero si el boton presionado es el correcto
    else{waitpadup();           //espera a que se deje de presionar
    Medio();                   //apaga las luces
    return 0;}                //retorna falso si el boton no es el correcto
}



//muestra una parte de la secuencia
void MostrarSecuencia(UBYTE s){
  Medio();                  //apaga las luces
  delay(300-i);            //retraso disminuye dependiendo el nivel
  Mostrar(secuencia[s]);  //muestra la respectiva parte
  delay(300-i);          //retraso 
}



//muestra la cantidad de haciertos al finalizar el juejo
void puntaje(unsigned char p){

//animacion para saber que finalizo el juego
Sup();Sright();Sdown();Sleft();
Sup();Sright();Sdown();Sleft();
Sup();Sright();Sdown();Sleft();
Sup();Sright();Sdown();Sleft();

//empieza a mostrar el puntaje
for(i=0;i<p;i++){
                               //va mostrando por partes de diez en diez
 if(i<10){Sleft();}           //si el puntaje es menor a diez solo muestra a la izquierda
 if(i>10&&i<20){Sup();}      //si es mayor a diez muestra arriba 
 if(i>20&&i<30){Sright();}  //a la derecha
 if(i>30){Sdown();}        //y termina de dar la vuelta
                          //hace un espacio entre cada pitido
     delay(100);         //retraso 
     Medio();           //apaga las luces
     delay(100);       //retraso
 }Sleft();            //deja la luz encendida en la izquierda para continuar
}




//desase el patron de juegos que se genera cada vez que se inicia
void desacersecuencia(unsigned char x){Sleft(); //muestra la izquierda si se desea jugar
 for(i=0;i<x;i++){iniciar();                   //genera la secuencia muchas veces 
 if(joypad()!=0){break;}}                     // se detiene cuando presionas iniciar
}                                            // asi el juego generado depende del tiempo 
                                            //que tardas en iniciar o de un valor random 


/*--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==
QQQQQQQQQQP`     `'QQQQQQQP'`  .tQQQ       QQ     \     `^'<QQQQQ yyyyyyyyyy
QQQQQQQQP` .qQ$$Qp. `4QQQ[   .tQQQQQ NNNNNNQQ:   -   .qZZp.  '/QQ NNNNNNNSSS
QQQQQQP` .tNNNNNNNNk. `4QQk, `4QQQQQyyyyyy QQQk,_/  j$$$$$$k  :QQyyyyy   lll
                                                              .\MMMMMMM   xxx
--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==
                                        MAIN               

--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==*/


//principal
int main(){

printf("     \n");
printf("    SIMON   GAME\n");                  //muestra el titulo del juego
printf("       by ARKY\n");
printf("\n\n\n\n\n\n\n\n\n\n\n\n");
printf("    PRESS   START"); 
waitpad(J_START);                           //espera a que que se presione START
iniciar();                                 //inicia el juego

//siclo infinito SI NO SE PONE SE DEBE RESETEAR EL JUEGO CADA VEZ
while(1){        
desacersecuencia(rand());         //desase el patron de juegos generado al iniciar el juego 
waitpad(J_LEFT);                 //espera a que se presione la tecla izquierda si se desea jugar
Medio();                        //apaga las luces
delay(100);                    //retraso para ver mejor y diferenciar el primer paso

 //este for sirve para contar el numero de pasos primero uno luego dos y asi
 for(i=1;i<40;i++){

  //para mostrar los pasos a seguir
  for(k=0;k<i;k++){
   MostrarSecuencia(k);   //muestra un paso de la secuencia
  }

  //para jugar
  for(k=0;k<i;k++){
   if(Jugar(k)==0){
   i=40;break;}       // si se equivoca termina el juego
   else{score++;}    //si no continua y aumenta el puntaje
  }

 }//fin primer for


puntaje(score); //muestra el puntaje obtenido
}//fin while

return 0;     //no retorna nada por que no hay por que retornar
}            //finaliza el main es decir nunca finaliza porque se queda en el while


#include<stdio.h>
#include<gb/gb.h>
#include<gb/drawing.h>
int main(){
unsigned char x=0;
unsigned char y=0;
unsigned char  a=250;
printf("Etch A Sketch emulador by Arky\n");
printf("press START\n");
waitpad(J_START);
while (x!=20){
printf("10101010001010101");
x++;
}
while (1<2){
if (joypad()==J_DOWN){y++;}
if (joypad()==J_UP){y--;}
if (joypad()==J_LEFT){x--;}
if (joypad()==J_RIGHT){x++;}
if (joypad()==J_UP+J_LEFT){y--;x--;}
if (joypad()==J_UP+J_RIGHT){y--;x++;}
if (joypad()==J_DOWN+J_LEFT){y++;x--;}
if (joypad()==J_DOWN+J_RIGHT){y++;x++;}
if (joypad()==J_A){
gotogxy(0,0);
while (a!=0){
gprintf("   ");
a--;
}
a=250;}

plot(x,y,35);
delay(35);
}
return 0;
}
// Mohammad hasan Shammakhi 89515172
// jam konnade 2raghami
#include <mega16.h>  
#include <delay.h>
#include <stdlib.h>
#include <stdio.h>
#asm                   
   .equ __lcd_port=0x12 ;// PORTA
#endasm
#include <lcd.h>

flash char row[]={0xfe,0xfd,0xfb,0xf7};
flash char data_key[]={
'1','2','3','-',
'4','5','6','*',
'7','8','9','/',
'C','0','=','+'};
unsigned char ac,table,j[5],adad[3];
unsigned int r,n=0;
char b=0;
int ;
//________________________________________
void keypad(){    
 while (1){
 for (r=0;r<4;r++){
   ac=4;
   PORTB=row[r];
   DDRB=0x0f;   
   if (PINB.4==0)  ac=0; 
   if (PINB.5==0)  ac=1;  
   if (PINB.6==0)  ac=2;    
   if (PINB.7==0)  ac=3; 
   if (!(ac==4)){            
   table=data_key[(r*4)+ac];
   while (PINB.4==0){} 
   while (PINB.5==0){} 
   while (PINB.6==0){} 
   while (PINB.7==0){} 
        if(table==42 | table==45 | table==47) {}
   else if(table==43) { if(n==0) {lcd_gotoxy(15,0);lcd_putchar('+');n++;} if (n==1) {}}
   else if(table==61) { if (n==1) {adad[2]=adad[1]+adad[0];n++;goto akhar;}}
   else if(table==67) {lcd_clear();lcd_gotoxy(0,0);n=adad[0]=adad[1]=0;}
   else             
   {
     b=(table)-48;
    PORTA=adad[n];
   if (n==1 | adad[1] !=0) {lcd_clear();}
    adad[n]=10*adad[n]+b;
    PORTC=adad[n];
    lcd_gotoxy(0,0);
    sprintf(j,"%u",adad[n]);
    lcd_puts(j);
   } 
    
   delay_ms(50);                          
   akhar: if (n==2) {lcd_clear();lcd_gotoxy(15,0);lcd_putchar('=');lcd_gotoxy(0,1);sprintf(j,"%u",adad[2]);lcd_puts(j);}
    }
  }  
  
 }
}
//_________________________________________
void main(){  

PORTB=0xff;
DDRB=0x0f;
PORTA=0x00;
DDRA=0xff;
PORTC=0x00;
DDRC=0xff;

lcd_init(16);
lcd_gotoxy(0,0);
keypad(); 
}
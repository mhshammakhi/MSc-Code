//<<<<<> Author: Jaber Alvandi <<<<>>>> Book: Microcontrollers AVR  
//>>>>>>>>>>>>>>>>>>>>> www.mcs-51a.blogfa.com <<<<<<<<<<<<<<<<
#include <mega16.h>
#include <delay.h>
#include <stdio.h> 
#include <stdlib.h> 
unsigned char hour=0,minute=0,second=0,year=0,month=0,day=0,set_k=0;  
#asm
   .equ __i2c_port=0x15 ;PORTC
   .equ __sda_bit=1
   .equ __scl_bit=0
#endasm
#include <i2c.h>
#include <ds1307.h>
#asm
   .equ __lcd_port=0x1B ;PORTA
#endasm
#include <lcd.h> 

void main(){ 
char lcd_buffer1[16];  
char lcd_buffer2[16]; 
PORTC=0X00;
DDRC=0X00;
PORTB=0X00;
DDRB=0X00;
i2c_init();
rtc_init(0,0,0);
lcd_init(16);    
lcd_gotoxy(0,0); 
lcd_putsf("RTC");
rtc_set_time(0,0,0); 
delay_ms(20);         
while (1){ 
rtc_get_time(&hour,&minute,&second);  
sprintf(lcd_buffer1,"Time=%02u:%02u:%02u",hour,minute,second);
lcd_clear();     
  
lcd_gotoxy(0,0);
lcd_puts(lcd_buffer1);


delay_ms(250); 
 };
}
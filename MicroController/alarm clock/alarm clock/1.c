#include <mega16.h>
#include <delay.h>
#include <stdio.h> 
#include <stdlib.h> 
#asm
   .equ __i2c_port=0x15 ;PORTC
   .equ __sda_bit=1
   .equ __scl_bit=0
#endasm
#include <i2c.h>
#include <ds1307.h>
#asm
   .equ __lcd_port=0x12 ;PORTD
#endasm
#include <lcd.h> 
int x=0,a=0;
char zaman[16],taghvim[16];
unsigned char hour=0,minute=0,alarmhour=0,alarmon=0,alarmminute=0,second=0,year=0,month=0,day=0,week=0;
//----------------
void key(){
x++; 
if(x==6) 
{x=0;goto set_end;} 
_lcd_ready(); 
switch(x){
case 1 : sprintf(zaman,"%02d:  :  ",hour);lcd_gotoxy(0,0);lcd_puts(zaman);break;
case 2 : sprintf(zaman,"  :%02d:  ",minute);lcd_gotoxy(0,0);lcd_puts(zaman);break;
case 3 : sprintf(taghvim,"  /  /20%02d",year);lcd_gotoxy(0,0);sprintf(zaman,"%02u:%02u:%02u",hour,minute,second);lcd_puts(zaman);lcd_gotoxy(0,1);lcd_puts(taghvim);break; 
case 4 : sprintf(zaman,"  /%02d/    ",month);lcd_gotoxy(0,1);lcd_puts(zaman);break;
case 5 : sprintf(zaman,"%02d/  /    ",day);lcd_gotoxy(0,1);lcd_puts(zaman);break;
 }
delay_ms(500);
set_end:
}  
//----------------
void alarm(){
a++; 
if(a==3) 
{a=0;goto alarm_end;} 
_lcd_ready(); 
switch(a){
case 1 : sprintf(zaman,"alarm(%02d:  :  )",alarmhour);lcd_gotoxy(0,0);lcd_puts(zaman);break;
case 2 : sprintf(zaman,"alarm(  :%02d:  )",alarmminute);lcd_gotoxy(0,0);lcd_puts(zaman);break;
 }
delay_ms(500);
alarm_end:
}  
//----------------
void inc(){
if(x==1){
hour++;
if(hour==24) hour=0;
rtc_set_time(hour,minute,second);
delay_ms(10); 
sprintf(zaman,"%02d:  :  ",hour);lcd_gotoxy(0,0);lcd_puts(zaman);
}
if(a==2){
alarmminute++;
if(alarmminute==60) alarmminute=0;
sprintf(zaman,"alarm(  :%02d:  )",alarmminute);lcd_gotoxy(0,0);lcd_puts(zaman);
}
if(a==1){
alarmhour++;
if(alarmhour==24) alarmhour=0;
sprintf(zaman,"alarm(%02d:  :  )",alarmhour);lcd_gotoxy(0,0);lcd_puts(zaman);
}
if(x==2){
minute++;
if(minute==60) minute=0;
rtc_set_time(hour,minute,second); 
delay_ms(10);
sprintf(zaman,"  :%02d:  ",minute);lcd_gotoxy(0,0);lcd_puts(zaman);
}
if(x==3){
rtc_get_date(&week,&day,&month,&year);
year++;
if (year==100) year=0; 
rtc_set_date(0,day,month,year);   
sprintf(zaman,"  /  /20%02d",year);lcd_gotoxy(0,1);lcd_puts(zaman);
}
if(x==4){
rtc_get_date(&week,&day,&month,&year);
month++;
if (month==13) month=1; 
rtc_set_date(0,day,month,year); 
sprintf(zaman,"  /%02d/  ",month);lcd_gotoxy(0,1);lcd_puts(zaman);
}
if(x==5){
rtc_get_date(&week,&day,&month,&year);
day++;
if (day==32) day=1;   
rtc_set_date(0,day,month,year);
sprintf(zaman,"%02d/  /  ",day);lcd_gotoxy(0,1);lcd_puts(zaman); 
}
}
//------------------
void main(){ 
PORTC=0X00;
DDRC=0X00;
PORTB=0Xf0;
DDRB=0Xff;
PORTA=0X0f;
DDRA=0Xf0;

i2c_init();
rtc_init(0,0,0);
lcd_init(16);    
lcd_gotoxy(0,0); 
rtc_set_time(0,0,0); 
rtc_set_date(0,0,1,13);  
delay_ms(20);         
while (1){ 
    if(PINA.0==0 & a==0)  key();
    if(PINA.1==0)  inc();
    if(PINA.2==0 & x==0)  alarm();
    if(PINA.3==0) alarmon=~alarmon;
if(x==0 & a==0) {
rtc_get_time(&hour,&minute,&second);  
rtc_get_date(&week,&day,&month,&year);  

    if ((alarmon) & (alarmminute==minute) & (alarmhour==hour) & (second==0)) PORTA.7=1;
    if ((alarmon==0)|(alarmminute!=minute) | (alarmhour!=hour) ) PORTA.7=0;      
sprintf(zaman,"%02u:%02u:%02u",hour,minute,second);
sprintf(taghvim,"%02u/%02u/20%02u",day,month,year);
lcd_clear();     
if (alarmon) { lcd_gotoxy(15,0); lcd_putsf("*");} else { lcd_gotoxy(15,0); lcd_putsf(" ");} 
lcd_gotoxy(0,0);
lcd_puts(zaman);
lcd_gotoxy(0,1);
lcd_puts(taghvim);
  }
delay_ms(200); 
 };
}
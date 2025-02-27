/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
� Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 6/7/2013
Author  : mh
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>
#include <lcd.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
int ef;
unsigned long int f,p;
unsigned char a=0,x=0,n=0,str[10];
// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
x++;
PORTB=0xf0;
if (x==18) {n++;x=0;}


}

#define ADC_VREF_TYPE 0x60
#asm
   .equ __lcd_port=0x12 ;PORTD
#endasm
// Read the 8 most significant bits
// of the AD conversion result
unsigned char read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCH;
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;
PORTB=0x00;
DDRB=0xff;
PORTC=0x00;
DDRC=0xff;

TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AVCC pin
// ADC Auto Trigger Source: Free Running
// Only the 8 most significant bits of
// the AD conversion result are used
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0xA3;
SFIOR&=0x1F;


// Global enable interrupts
#asm("sei")

while (1)
      {
   if ((read_adc(0)==0xff)&a==0) {TCCR0=0x0D;TCNT0=0x00;OCR0=0xD9;a=1;}
else if ((read_adc(0)!=0xff)&a==1) {a=2;}
else if (read_adc(0)==0xff&a==2) 
{f=(TCNT0+(18*n+x)*217);TCCR0=0x0D;TCNT0=0x00;OCR0=0xD9;a=3;x=0;n=0;}
else if (a==3&read_adc(1)==0xff)
{p=(TCNT0+(18*n+x)*217);TCCR0=0x00;a=4;}
else if(a==4) 
{ef=((360*p)/f);lcd_init(16);lcd_clear();sprintf(str,"Phase= %d",f);lcd_puts(str);a=5;}

      }
}

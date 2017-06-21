
/* LPF.cpp
 *
 * Created: 01-02-2017 17:12:12
 * Author : DIVYA
 */ 

#include <avr/delay.h>

#define _ADC_H_		1
#include <avr/io.h>
#include <util/delay.h>

void adc_init(void);
int read_adc_channel(unsigned char channel);

void adc_init(void)
{
	
	ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2);
	SFIOR=0x00;
}

int read_adc_channel(unsigned char channel)
{
	int adc_value;
	unsigned char temp;
	ADMUX=(1<<REFS0)|channel;
	_delay_ms(10);
	temp=ADCL;
	adc_value=ADCH;
	adc_value=(adc_value<<8)|temp;
	return adc_value;
}


int main(void)  
{
	int rs,ms,ls;
    adc_init();
	DDRA=0x00;
	DDRD=0xff;
	
    while (1) 
    {
		rs=read_adc_channel(0);
		ls=read_adc_channel(1);
		ms=read_adc_channel(2);
		
		if(ms<512)
		{
			PORTD=0b00001010;
			if (rs<512)
			{
				PORTD=0b00001000;
			}
			if(ls<512)
			{
				PORTD=0b00000010;
			}
		}
		else
		{
			if (rs<512)
			{
				PORTD=0b00001000;
			} 
			if(ls<512)
			{
				PORTD=0b00000010;
			}
		}
    }
}

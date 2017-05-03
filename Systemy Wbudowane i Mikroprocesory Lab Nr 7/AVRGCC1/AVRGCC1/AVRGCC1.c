#include <avr/io.h>
#include <lcd.h>

#define F_CPU 16000000UL

int flaga_tekstu;
float zmierzone_napiecie;
double wynik, wynik2;
int temp;
int a,b;
char bity[8];
char pasek[16];

void init_lcd()
{
	_delay_ms(20);
	COMM_LCD = 0x30;
	_delay_ms(10);
	COMM_LCD = 0x30;
	_delay_ms(10);
	COMM_LCD = 0x30;
	test_bf();
	COMM_LCD = 0x38;
	test_bf();
	pisz_com(0x0C);
	pisz_com(0x01);
	pisz_com(0x06);
}

void init()
{
	ADMUX = 0b01000001;
	ADCSRA = 0b11101111;
}

int main(void)
{
	MCUCR = _BV(SRE)|_BV(SRW10);
	XMCRA = _BV(SRW00)|_BV(SRW01)|_BV(SRW11);
	MMnet104_CONF = 0x13;
	
	init_lcd();
	
	init();
	
	DDRD = 0x00;
	PORTD = 0xFF;

	for (int i = 0; i < 8; i++)
		bity[i] = ' ';
		
	bity[0] = 'V';
	bity[1] = 'i';
	bity[2] = 'n';
	bity[3] = '=';
	bity[5] = '.';
	bity[7] = 'V';
	
    while(1)
    {
		_delay_ms(1000);
		
		wynik = ADC/204.8;
		wynik2 = wynik*10;
		
		a = wynik;
		b = wynik2 - 10*a;
		
		a += 48;
		b += 48;
		
		bity[4] = a;
		bity[6] = b;
		
		pisz_com(0x01);
		for (int i = 0; i < 8; i++)
		{
			pisz_ws(bity[i]);
		}
		pisz_com(0xC0);
		for (double i = 0.; i < 5.; i += 0.3)
		{
			if (i > wynik)
				break;
				
			pisz_ws('+');
		}
		
    }
}
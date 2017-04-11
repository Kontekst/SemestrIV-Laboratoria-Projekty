#include <avr/io.h>
#include <lcd.h>

#define F_CPU 16000000UL

int flaga_tekstu;

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

void add_chars()
{
	pisz_com(0x40);
	
	pisz_ws(0b00000100);
	pisz_ws(0b00001000);
	pisz_ws(0b00011111);
	pisz_ws(0b00010001);
	
	pisz_ws(0b00010001);
	pisz_ws(0b00010001);
	pisz_ws(0b00010001);
	pisz_ws(0b00011111);
	
	pisz_com(0x48);
	
	pisz_ws(0b00010000);
	pisz_ws(0b00010000);
	pisz_ws(0b00010000);
	pisz_ws(0b00010010);
	
	pisz_ws(0b00010100);
	pisz_ws(0b00011000);
	pisz_ws(0b00010000);
	pisz_ws(0b00011111);
}

int main(void)
{
	MCUCR = _BV(SRE)|_BV(SRW10);
	XMCRA = _BV(SRW00)|_BV(SRW01)|_BV(SRW11);
	MMnet104_CONF = 0x13;
	
	init_lcd();
	
	DDRD = 0x00;
	PORTD = 0xFF;
	
	add_chars();
	
	flaga_tekstu = 0;
	
    while(1)
    {
		flaga_tekstu = PIND;
		flaga_tekstu = ~flaga_tekstu;
		flaga_tekstu &= 0x0f;
		
		//_delay_ms(100);
		if (flaga_tekstu == 0x01) {
			pisz_com(0x01);
			pisz_ws(0x4c);
			pisz_ws(0x45);
			pisz_ws(0x57);
			pisz_ws(0x4f);
			//flaga_tekstu = 4;
		}
		if (flaga_tekstu == 0x02) {
			pisz_com(0x01);
			pisz_com(0x86);
			pisz_ws('G');
			pisz_ws(0x00);
			pisz_ws('R');
			pisz_ws('A');
			//flaga_tekstu = 4;
		}
		if (flaga_tekstu == 0x04) {
			pisz_com(0x01);
			pisz_com(0xC6);
			pisz_ws('D');
			pisz_ws(0x00);
			pisz_ws(0x01);
		//	flaga_tekstu = 4;
		}
		if (flaga_tekstu == 0x08) {
			pisz_com(0x01);
			pisz_com(0xCB);
			pisz_ws('P');
			pisz_ws('R');
			pisz_ws('A');
			pisz_ws('W');
			pisz_ws('A');
			//flaga_tekstu = 4;
		}
				
    }
}
/*
 * OLED_ex_pic.c
 *
 * Created: 31-12-2017 15:05:02
 * Author : osc
 */ 

#include <avr/io.h>
//http://www.avrfreaks.net/forum/ssd1306-lcd-initialization-commands


#include <math.h>
#include <string.h>
#include "I2C.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "ssd1306.h"



uint8_t _i2c_address;
uint8_t display_buffer[1024];
enum state{init,st1,st2,st3,st4,st5};
char state=init;



///////////////////////////////////////////////////////////
// Transfers the local buffer to the CGRAM in the SSD1306
void TransferBuffer()
{
	uint8_t j=0;
	
	// set the Column and Page addresses to 0,0
	setColAddress();
	setPageAddress();
	
	I2C_Start(_i2c_address);
	//I2C_Write(_i2c_address);
	I2C_Write(0X40); // data not command
	for(j=0;j<1024;j++)
	{
		I2C_Write(display_buffer[j]);
	}

	I2C_Stop();
}

void setup()
{
	// Initialze SSD1306 OLED display
	reset_display();              // Clear screen
	setXY(0,0);              // Set cursor position, start of line 0
	sendStr("ACROBOTIC");
	setXY(1,0);              // Set cursor position, start of line 1
	sendStr("industries");
	setXY(2,0);              // Set cursor position, start of line 2
	sendStr("Pasadena,");
	setXY(2,10);             // Set cursor position, line 2 10th character
	sendStr("CA");
	setXY(3,10);             // Set cursor position, line 2 10th character
	sendStr("TEST");
}
int main()
{
// 	output_high(PIN_C1);// keep power ON
// 
// 	output_float(PIN_C3);
// 	output_float(PIN_C4);
  
	// fill buffer with something for test
	memset( display_buffer, 0X04, 1024); // tried other values
	
	_i2c_address = 0X78; // this works 0X3C or 0X3D does not
	
	//InitializeDisplay();
	
	

		
		/* Replace with your application code *getchUSART0()*/
		while (1)
		{
			switch(state) {
				case init: I2C_Init();  state=st1;break;
				break;
				case st1:  _delay_ms(10); InitializeDisplay(); state=st2; break;  // bmp(boot_logo);
				case st2:  setup();state=st3; break;   // setup();
				
				
				case st3: printBigNumber('2',4,0); setXY(5,0);printBigTime("23:00"); state=st4;break;
				case st4: break;
				default: break;
			}
			
		}
	
return 0;
}

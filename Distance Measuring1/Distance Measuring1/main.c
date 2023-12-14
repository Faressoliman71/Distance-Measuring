#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "Timers.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "RGB.h"
#include "ULTRASONIC.h"

#include <avr/io.h>
#include <Util/delay.h>

u16 distance = 0  ;


int main(void)
{
	   sei();
      Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED);

      DIO_init_all_pins();
	  LCD_init();
	  ULTRASONIC_Init();
	  
	   while (1)
	   {
		   
		  
	     if (ULTRASONIC_GetDistance(US1, &distance))
	     {
		 LCD_write_number(distance);
	     }
	    
		
		  
	   }

}


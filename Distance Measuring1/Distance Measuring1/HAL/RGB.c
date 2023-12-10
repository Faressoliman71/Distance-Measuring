#include "RGB.h"
#include "LCD_interface.h"
#include "TIMERS.h"
#include "LCD_interface.h"

static u8 color_array[][3]={
	{255,0,0}, 
	{0,255,0},
	{0,0,255},
	{255,255,0},
	{255,0,255},
	{0,255,255},
	{255,255,255},
	{255,39,0},
	{255,0,39},
	{20,255,0},
	{0,255,39},
	{20,0,255},
	{0,39,255},
	{158,39,255}};
		
void RGB_Init(void)
{
	Timer0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	Timer0_OC0_Mode(OCO_NON_INVERTING);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER0_SCALER_8,OCRA_NON_INVERTING,OCRB_NON_INVERTING);
	ICR1=255;
}

void RGB_set_color(Color_t local_color)
{
	OCR0=color_array[local_color][0];
	OCR1A=color_array[local_color][1];  
	OCR1B=color_array[local_color][2];
}

typedef enum 
{
	increment,
	decrement
}status_t;

typedef enum
{
	first,
	second,
	third
}location_t;
//show room

void fun_change(location_t location,u8 old,u8 new,status_t status)
{
	s16 i=old;
	if(status==decrement)
	{
		for(i;i>new;i=i-10)
		{
			LCD_write_number(1);
			if(location==first)
			{
				OCR0=i;
			    _delay_ms(10);
			}
			if(location==second)
			{
				OCR1A=i;
				   _delay_ms(10);
			}
			if(location==third)
			{
				OCR1B=i;
				  _delay_ms(10);
			}
		}
	}
	else if(status==increment)
	{
		for(i;i<new;i=i+10)
		{
			LCD_write_number(2);
			if(location==first)
			{
				OCR0=i;
				   _delay_ms(10);
			}
			if(location==second)
			{
				OCR1A=i;
				   _delay_ms(10);
			}
			if(location==third)
			{
				OCR1B=i;
				  _delay_ms(10);
			}
		}
	}
}

void RGB_show_room(Color_t color1,Color_t color2)
{
	RGB_set_color(color1);
	LCD_set_cursor(0,0);
	u8 old_color_0  = color_array[color1][0];
	u8 old_color_1A = color_array[color1][1];
	u8 old_color_1B  = color_array[color1][2];
	
	u8 new_color_0  = color_array[color2][0];
	u8 new_color_1A = color_array[color2][1];
	u8 new_color_1B  = color_array[color2][2];
	 
	 //OC0
	if(old_color_0>new_color_0)
	{
		fun_change(first,old_color_0,new_color_0,decrement);	
	}
	if(old_color_0<new_color_0)
	{
	    fun_change(first,old_color_0,new_color_0,increment);
	}
	//OC1A
	if(old_color_1A>new_color_1A)
	{
	   fun_change(second,old_color_1A,new_color_1A,decrement);	
	}
	if(old_color_1A<new_color_1A)
	{
		fun_change(second,old_color_1A,new_color_1A,increment);
	}
	//OC1B
	if(old_color_1B>new_color_1B)
	{
		fun_change(third,old_color_1B,new_color_1B,decrement);
	}
	if(old_color_1B<new_color_1B)
	{
		fun_change(third,old_color_1B,new_color_1B,increment);
	}	
}



//show room asmaa
/******************************show Room Asynch*******************************/
/*  Global Variables will be shared between showRoom Function and interrupt function */
static s8 redStep , greenStep , bluestep;
static u8 newRed,newGreen,newBlue;

/* Interrupt  Function  */
static void RGB_ChangeFunc(void)
{
	if(OCR0!=newRed)
	{
		OCR0+=redStep;
		if(abs(OCR0-newRed)<=13)
		{
			OCR0=newRed;
		}
		
	}
	
	if(OCR1A!=newGreen)
	{
		OCR1A+=greenStep;
		if(abs(OCR1A-newGreen)<=13)
		{
			OCR1A=newGreen;
		}
		
	}
	
	if(OCR1B!=newBlue)
	{
		OCR1B+=bluestep;
		if(abs(OCR1B-newBlue)<=13)
		{
			OCR1B=newBlue;
		}
		
	}
}


/*  ShowRoom Asynch Function */
void RGB_ShowroomAsynch(Color_t local_color)
{
	static u8 flag=0;
	static u8 oldRed=0,oldGreen=0,oldBlue=0;
	s16 redDiff=0,greenDiff=0,blueDiff=0;
	
	if(flag==0) //set color for first time ,it will be accessed only one time then flag =1
	{
		OCR0     = color_array[local_color][0];
		OCR1A    = color_array[local_color][1];
		OCR1B    = color_array[local_color][2];
		
		oldRed   = color_array[local_color][0];
		oldGreen = color_array[local_color][1];
		oldBlue  = color_array[local_color][2];
		/* set Timer2 and Enable over flow Interrupt */
		Timer2_Init(TIMER2_NORMAL_MODE,TIMER2_SCALER_1024);
		Timer2_OC2_Mode(OC2_DISCONNECTED);
		Timer2_OVF_SetCallBack(RGB_ChangeFunc);
		Timer2_OV_InterruptEnable();
		flag=1;
	}
	else if(flag==1)
	{
		newRed   = color_array[local_color][0];
		newGreen = color_array[local_color][1];
		newBlue  = color_array[local_color][2];
		/*  Get Differences between values of new color and old color */
		redDiff   = newRed   - oldRed;
		greenDiff = newGreen - oldGreen;
		blueDiff  = newBlue  - oldBlue;
		
		
		oldRed   =	newRed  ;
		oldGreen =	newGreen;
		oldBlue  =	newBlue ;
		/* calculation to get step which every register will change by this step rate */
		if(abs(redDiff)<=20)
		{
			if(redDiff<0)
			{
				redStep=-1;
			}
			else if(redDiff>0)
			{
				redStep=+1;
			}
		}
		else if(abs(redDiff)>20)
		{
			if(redDiff<0)
			{
				redStep=(redDiff/20)-1;
			}
			else if(redDiff>0)
			{
				redStep=(redDiff/20)+1;
			}
			
		}
		
		if(abs(greenDiff)<=20)
		{
			if(greenDiff<0)
			{
				greenStep=-1;
			}
			else if(greenDiff>0)
			{
				greenStep=+1;
			}
		}
		else if(abs(greenDiff)>20)
		{
			if(greenDiff<0)
			{
				greenStep=(greenDiff/20)-1;
			}
			else if(greenDiff>0)
			{
				greenStep=(greenDiff/20)+1;
			}
			
		}
		
		if(abs(blueDiff)<=20)
		{
			if(blueDiff<0)
			{
				bluestep=-1;
			}
			else if(blueDiff>0)
			{
				bluestep=+1;
			}
		}
		else if(abs(blueDiff)>20)
		{
			if(blueDiff<0)
			{
				bluestep=(blueDiff/20)-1;
			}
			else if(blueDiff>0)
			{
				bluestep=(blueDiff/20)+1;
			}
			
		}
		
		
	}
	
	
	
}

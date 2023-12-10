
#ifndef LCD_CFG_H_
#define LCD_CFG_H_


#define _4_BIT 1 //private
#define _8_BIT 2 //private
                                                                   
//LCD mood configura_BIT
#define LCD_MOOD _4_BIT

//LCD RS and ENABLE config
 #define RS PINA1
 
 #define ENABLE PINA2
 
//LCD Pins configuration (mood 8_bit)
 #define LCD_PORT PA
 
 //LCD Pins configuration (mood 4_bit)
 #define LCD_D4 PINA3
 #define LCD_D5 PINA4
 #define LCD_D6 PINA5
 #define LCD_D7 PINA6

#endif /* LCD_CFG_H_ */
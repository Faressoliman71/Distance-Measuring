#ifndef RGB_H_
#define RGB_H_

typedef enum{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	CYAN,
	WHITE,
	ORANGE,
	PURBLE,
	LEMON,
	TEAL,
	VIOLET,
	COBALT,
	PINK
}Color_t;


	
static char * colors_names[]={"RED","GREEN","BLUE","YELLOW","MAGENTA","CYAN","WHITE","ORANGE","PURBLE","LEMON","TEAL","VIOLET","COBALT","PINK"};

void RGB_Init(void);
void RGB_set_color(Color_t local_color);

void RGB_show_room(Color_t color1,Color_t color2);

#endif /* RGB_H_ */
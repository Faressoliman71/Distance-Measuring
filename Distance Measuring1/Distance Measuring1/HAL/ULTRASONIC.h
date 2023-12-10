

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_



#define  US1   PIND2
#define  US2   PIND7
#define  US3   PIND3
#define  US4   PIND5

typedef   DIO_PIN_TYPE ULTRASONIC_type;

typedef enum{
	ULTRASONIC_1=PIND2,
	ULTRASONIC_2=PIND6,
	ULTRASONIC_3=PIND3,
	ULTRASONIC_4=PIND5,
	}ULTRASONIC_type2;



void ULTRASONIC_Init(void);


u8 ULTRASONIC_GetDistance(ULTRASONIC_type us,u16*pdistance);
//u16 ULTRASONIC_GetDistance2(ULTRASONIC_type2 us);





#endif /* ULTRASONIC_H_ */
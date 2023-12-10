
#ifndef UTILS_H_
#define UTILS_H_

#define SET_BIT(REG,BIT) (REG|=(1<<BIT))
#define CLR_BIT(REG,BIT) (REG&=~(1<<BIT))
#define READ_BIT(REG,BIT) ((REG>>BIT)&1)
#define TOG_BIT(REG,BIT) (REG=REG^(1<<BIT))
#define WRITE_BIT(REG,BIT,VALUE) ((REG)=(REG)&(~(1<<(BIT)))|((VALUE)<<(BIT)))
#define SIZE_OF(x) (((char*)(&x+1)-(char*)&x))
#define TOG_PORT(PORT) (PORT=PORT^0XFF)


#endif /* UTILS_H_ */
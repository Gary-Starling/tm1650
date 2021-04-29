
#define _a      (1<<0)
#define _b      (1<<1)
#define _c      (1<<2)
#define _d      (1<<3)
#define _e      (1<<4)
#define _f      (1<<5)
#define _g      (1<<6)
#define _h      (1<<7)

#define _0      (uint8_t)(_a|_b|_c|_d|_e|_f)  
#define _1      (uint8_t)(_b|_c)
#define _2      (uint8_t)(_a|_b|_d|_e|_g)
#define _3      (uint8_t)(_a|_b|_c|_d|_g)
#define _4      (uint8_t)(_b|_c|_g|_f)
#define _5      (uint8_t)(_a|_c|_d|_f|_g)
#define _6      (uint8_t)(_a|_f|_d|_e|_g|_c)
#define _7      (uint8_t)(_a|_b|_c)
#define _8      (uint8_t)(_a|_b|_c|_d|_e|_f|_g)
#define _9      (uint8_t)(_a|_b|_c|_d|_f|_g)




#define TM1650_MAX_POS           4
#define TM1650_DISPMODE_4x8   0x01
#define TM1650_DISPMODE_4x7   0x09
#define TM1650_CMD_MODE       0x48
#define TM1650_CMD_DATA_READ  0x49
#define TM1650_CMD_ADDRESS    0x68


#define ON  1
#define OFF 0

#define INTEN_1  1
#define INTEN_2  2
#define INTEN_3  3
#define INTEN_4  4
#define INTEN_5  5
#define INTEN_6  6
#define INTEN_7  7
#define INTEN_8  0


void tm1650_send_data(uint8_t adress, uint8_t data);
void tm1650_clear(void);
void TM1650_setup(uint8_t active, uint8_t intensity); //TM1650_setup(ON,INTEN_7);
void out_value(int value);
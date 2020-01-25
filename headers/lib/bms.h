#ifndef BMS_H
#define BMS_H
struct BMS
{
        char bufBms[200];
        char rcv_ch;
        unsigned short bufIxBms = 0;
        //void (*getUartData)(char);
        //void (*parseUartData)(char*)
};
typedef struct BMS* Bms;
Bms Init_Bms( void );

//void _getUartData(char, unsigned short);
//void _parseUartData(char*);


#endif
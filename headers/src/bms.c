#include "headers/lib/bms.h"
#include <stdlib.h>
#include <stdio.h>
Bms Init_Bms( void ){
    Bms thiss;
    thiss = (Bms)malloc(sizeof(struct Bms));
    thiss->getUartData = &_getUartData;
    thiss->parseUartData = &_parseUartData;

    return thiss;
}

//void _getUartData(char rcv_ch){
    
}
#include "./include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include <string.h>
Main init_main(){
    Main thiss;
    thiss = (Main)malloc(sizeof(struct MAIN));
    thiss->opening_test = &_opening_test;
    thiss->init_pins = &_init_pins;
    thiss->init_uart = &_init_uart;
    thiss->set_wiper = &_set_wiper;
    thiss->run_wiper = &_run_wiper;
    thiss->stop_wiper = &_stop_wiper;
    thiss->hall_test = &_hall_test;
    thiss->get_velocity = &_get_velocity;
    thiss->millis = &_millis;
    thiss->get_circumference = &_get_circumference; //parametre
    return thiss;
}

void _opening_test(void){
  BUZZER = ON;
  //DEBUG_LED1 = ON;
  Delay_ms(500);
  //DEBUG_LED1 = OFF;
  DEBUG_LED2 = ON;
  Delay_ms(500);
  DEBUG_LED2 = OFF;
  DEBUG_LED3 = ON;
  Delay_ms(500);
  DEBUG_LED3 = OFF;
  DEBUG_LED4 = ON;
  Delay_ms(500);
  DEBUG_LED4 = OFF;
  BUZZER = OFF;
}
void _init_pins(void){
  DEBUG_LED1_Direction = OUTPUT;
  DEBUG_LED2_Direction = OUTPUT;
  DEBUG_LED3_Direction = OUTPUT;
  DEBUG_LED4_Direction = OUTPUT;
  BUZZER_Direction = OUTPUT;
  ////////////////
  Wiper_PWM_Direction = OUTPUT;
  Headlight_Output_Direction = OUTPUT;
  Right_Signal_Output_Direction = OUTPUT;
  Left_Signal_Output_Direction = OUTPUT;
  Inlight_Output_Direction = OUTPUT;
  Horn_Output_Direction = OUTPUT;
  Wiper_Output_Direction = OUTPUT;
  //////////////
  HALL_SENSOR_Direction = INPUT;
  Inlight_Direction = INPUT;
  Horn_Direction = INPUT;
  Wiper_Direction = INPUT;
  Headlight_Direction = INPUT;
  Right_Signal_Direction = INPUT;
  Left_Signal_Direction = INPUT;
  Hazard_Direction = INPUT;
}
void _init_uart(void){
    UART4_Init(9600); //BMS
    UART3_Init(9600); //XBEE
    UART1_Init(9600); //Nextion
}
void _set_wiper(void){

}
void _run_wiper(void){

}
void _stop_wiper(void){

}
void _hall_test(void){

}
void _get_velocity(void){

}
float _get_circumference(float RADIUS){
  float cf;
  
  return cf;
}
unsigned long _millis(void){

}
int main(){
Main main_func = init_main();
  while(1){

  }
}

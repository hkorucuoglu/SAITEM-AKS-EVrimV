#include "/lib/lib/nextion.h"
#include <string.h>
#include <stdlib.h>
#include<stdio.h>

Nextion Init_Nextion(char *TEMPERATURE_T_,char *VELOCITY_T_,char *VOLTAGE_T_,char *CURRENT_T_){
  Nextion thiss;
  thiss = (Nextion)malloc(sizeof(struct Nextion));
  thiss->CURRENT_TEXT = CURRENT_T_;
  thiss->TEMPERATURE_TEXT = TEMPERATURE_T_;
  thiss->VELOCITY_TEXT = VELOCITY_T_;
  thiss->VOLTAGE_TEXT = VOLTAGE_T_;

  thiss->send_data = &_send_data;
  thiss->get_data = &_get_data;

  return thiss;
}


void _send_data(int temp, int velocity, float current, float voltage, struct Nextion *nex){
  struct Nextion* nex_ = (Nextion)malloc(sizeof(struct Nextion));
  nex_ = nex;
  sprintf(nex_->TEMPERATURE_TEXT,"/%d",temp);
  sprintf(nex_->VELOCITY_TEXT,"/%d",velocity);
  sprintf(nex_->CURRENT_TEXT,"/%d",current);
  sprintf(nex_->VOLTAGE_TEXT,"/%d",voltage);

  UART1_Write_Text(nex_->TEMPERATURE_TEXT);
  UART1_Write(0xFF);
  UART1_Write(0xFF);
  UART1_Write(0xFF);
  UART1_Write_Text(nex_->VELOCITY_TEXT);
  UART1_Write(0xFF);
  UART1_Write(0xFF);
  UART1_Write(0xFF);  
  UART1_Write_Text(nex_->CURRENT_TEXT);
  UART1_Write(0xFF);
  UART1_Write(0xFF);
  UART1_Write(0xFF);  
  UART1_Write_Text(nex_->VOLTAGE_TEXT);
  UART1_Write(0xFF);
  UART1_Write(0xFF);
  UART1_Write(0xFF);
}

void _get_data(void){
  // this func is empty for now
}
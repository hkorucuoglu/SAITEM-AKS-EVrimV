#include <string.h>
#include <stdlib.h>
#include<stdio.h>
//**//
#include "test.h"          // Pin defination and state defination
#include "wiper.h"
#include "hall.h"
#include "nextion.h"
//** GLOBAL VEHICLE VERIABLES **//
int VELOCITY,TEMPERATURE;
float CURRENT,VOLTAGE;
//** WIPER GLOBAL VARIABLES **//
const int wiper_upper_limit = 110;
const int wiper_under_limit = 54;
const unsigned int wiper_first_location = 54;
//** HALL SENSOR GLOBAL VARIABLES **//
const float radius = 0.15; // in meters
//** NEXTION TEXT DEFINATION **//
char TEMPERATURE_T[] = "Sicaklik.val=";
char VELOCITY_T[] = "Hiz.val=";
char VOLTAGE_T[] = "Gerilim.val=";
char CURRENT_T[] = "Akim.val=";

Wiper Init_Wiper(int upper,int under, unsigned int current_duty){
    Wiper thiss;
    thiss = (Wiper)malloc(sizeof(struct Wiper));
    thiss->Current_duty = current_duty; // begin of servo position. if you want to begin 0 degree, this variable should be 54
    thiss->Upper_limit = upper; // this variable should not pass 110
    thiss->Under_limit = under; // this variable should not be under 54
    thiss->Pwm_period = PWM_Init(55, 1, 64, 2); //pwm frequence setup
    thiss->Wiper_rate = thiss->Pwm_period/1000; // servo step sensitivity

    thiss->run_wiper = &_run_wiper;
    thiss->stop_wiper = &_stop_wiper;
    
    return thiss;
}
Hall Init_Hall(float Radius){
  Hall thiss;
  thiss = (Hall)malloc(sizeof(struct Hall));
  thiss->Hall_state = 0; 
  thiss->Radius = Radius;

  thiss->Calculate_Circumference = &_calculate_cf;
  thiss->Calculate_Velocity = &_calculate_vc;
  
  thiss->Circumference = thiss->Calculate_Circumference(thiss->Radius);

  return thiss;
}
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
void InitTimer1(){
  T1CON         = 0x8000;
  T1IP0_bit         = 1;
  T1IP1_bit         = 1;
  T1IP2_bit         = 1;
  T1IF_bit         = 0;
  T1IE_bit         = 1;
  PR1                 = 8000;
  TMR1                 = 0;
}
void Timer1Interrupt() iv IVT_TIMER_1 ilevel 7 ics ICS_SRS {
  T1IF_bit         = 0;
  //Enter your code here
  millis_counter++;
}
//Timer2
//Prescaler 1:64; PR2 Preload = 62500; Actual Interrupt Time = 500 ms
 
//Place/Copy this part in declaration section
void InitTimer2(struct Hall*){
  T2CON         = 0x8060;
  T2IP0_bit         = 1;
  T2IP1_bit         = 1;
  T2IP2_bit         = 1;
  T2IF_bit         = 0;
  T2IE_bit         = 1;
  PR2                 = 62500;
  TMR2                 = 0;
}
 
void Timer2Interrupt(struct Hall* hall) iv IVT_TIMER_2 ilevel 7 ics ICS_SRS {
  T2IF_bit         = 0;
  //Enter your code here 
  _calculate_time(hall);
}

void main() {
  Wiper wiper = Init_Wiper(wiper_upper_limit,wiper_under_limit,wiper_first_location);
  Hall hall = Init_Hall(radius);
  InitTimer2(hall);
  EnableInterrupts();
    while(1){

    }

}





void init_uart(){
  UART4_Init(9600); //BMS
  UART3_Init(9600); //XBEE
  UART1_Init(9600); //Nextion
}
void opening_test (){
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
void init_pins(){
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
unsigned long millis(void){
  return millis_counter;
}

//**WIPER**//
void _run_wiper(int upper, int under, unsigned int current_duty, unsigned int wiper_rate){
 while(current_duty < upper){
  current_duty ++;
  PWM_Set_Duty(wiper_rate*current_duty,1);
  Delay_ms(15);
  }
  while(current_duty > under){
  current_duty --;
  PWM_Set_Duty(wiper_rate*current_duty,1);
  Delay_ms(15);
  }
}

void _stop_wiper(int upper, int under, unsigned int current_duty, unsigned int wiper_rate){
  if(current_duty > under){
    while(current_duty == 82){
      current_duty --;
      PWM_Set_Duty(wiper_rate*current_duty,1);
      Delay_ms(15);
    }
  }
  else if(current_duty < upper){
    while(current_duty == 82){
      current_duty ++;
      PWM_Set_Duty(wiper_rate*current_duty,1);
      Delay_ms(15);
    }
  }

}

//**HALL**//

float _calculate_cf(float Radius){
  return 2*PI*Radius;
}

int _calculate_vc(float Distance, float Time){
  return Distance/Time*3.6;
}

void _calculate_time(struct Hall *hall){
  struct Hall *hall_ = (Hall)malloc(sizeof(struct Hall));
  hall_ = hall;
  if (HALL_SENSOR && !hall_->Hall_state)
  {
    hall_->Total_time = millis();
    hall_->Hall_state = 1;
  }
  else if(HALL_SENSOR && hall_->Hall_state && millis() - hall_->Total_time > 10){
    hall_->Time = (millis() - hall_->Total_time)/1000.f;
    VELOCITY = hall_->Calculate_Velocity(hall_->Circumference,hall_->Time);
    hall_->Hall_state = 0;
  }
  else if(!HALL_SENSOR && millis() - hall_->Total_time > 2000) VELOCITY = 0;

}

//** NEXTION **//

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
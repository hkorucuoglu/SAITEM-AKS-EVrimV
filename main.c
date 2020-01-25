#include "headers/lib/main.h"
#include "headers/src/nextion.c"
#include "headers/src/wiper.c"
#include "headers/src/hall.c"
#include "headers/src/xbee.c"
////
#include <string.h>
#include <stdlib.h>
#include<stdio.h>

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

void InitTimer2(struct Hall*, struct Nextion*, struct Xbee*){
  T2CON         = 0x8060;
  T2IP0_bit         = 1;
  T2IP1_bit         = 1;
  T2IP2_bit         = 1;
  T2IF_bit         = 0;
  T2IE_bit         = 1;
  PR2                 = 62500;
  TMR2                 = 0;
}
 
void Timer2Interrupt(struct Hall* hall,struct Nextion* nextion, struct Xbee* xbee) iv IVT_TIMER_2 ilevel 7 ics ICS_SRS {
  T2IF_bit         = 0;
  //Enter your code here 
   VELOCITY = _calculate_time(hall);
   nextion->send_data(TEMPERATURE,VELOCITY,CURRENT,VOLTAGE,nextion);
   xbee->send_data(VELOCITY,CURRENT,VOLTAGE,TEMPERATURE);
}
void main() {
    Wiper wiper = Init_Wiper(wiper_upper_limit,wiper_under_limit,wiper_first_location);
    Hall hall = Init_Hall(radius);
    Nextion nextion = Init_Nextion(TEMPERATURE_T ,VELOCITY_T, VOLTAGE_T, CURRENT_T);
    Xbee xbee = Init_Xbee();    
    opening_test();
    init_pins();
    init_uart();
    InitTimer1();
    InitTimer2(hall,nextion,xbee);
    EnableInterrupts();
    while (1)
        {
            //** Hazard **//
        if(Hazard){
            Hazard_State = 1;
            while (Hazard)
            {
            Left_Signal_Output = ON;
            Right_Signal_Output = ON;
            Delay_ms(500);
            Left_Signal_Output = OFF;
            Right_Signal_Output = OFF;
            Delay_ms(500);
            }

        }
        else if(!Hazard && Hazard_State){
            Left_Signal_Output = OFF;
            Right_Signal_Output = OFF;
            Hazard_State = 0;
        }

            /*Left Signal*/
        if(Left_Signal){
            LeftSignal_State = 1;
            Left_Signal_Output = ON;
            Delay_ms(15);
        }
        else if(!Left_Signal && LeftSignal_State){
            ///
            Left_Signal_Output = OFF;
            ///
            LeftSignal_State = 0;
            Delay_ms(15);
        }

            /*Right Signal*/
        if(Right_Signal){
            RightSignal_State = 1;
            Right_Signal_Output = ON;
            //DEBUG_LED1 = ON;
            Delay_ms(15);
        }
        else if(!Right_Signal && RightSignal_State){
            ///
            Right_Signal_Output = OFF;
            ///
            RightSignal_State = 0;
            Delay_ms(15);
        }
            /*Headlight*/
        if(Headlight){
            Headlight_State = 1;
            Headlight_Output = ON;
            Delay_ms(15);
        }
        else if(!Headlight && Headlight_State){
            ///
            Headlight_Output = OFF;
            Delay_ms(15);
            ///
            Headlight_State = 0;
        }
            /*WIPER*/
        if(Wiper){
            Wiper_Output = ON;
            Delay_ms(5);
            PWM_Start(1);
            //run wiper
            wiper->run_wiper(wiper_upper_limit, wiper_under_limit, wiper_first_location, wiper->Wiper_rate);
            DEBUG_LED2 = ON;
            Wiper_State = 1;
        }
        else if(!Wiper && Wiper_State){       
            DEBUG_LED2 = OFF;
            Wiper_State = 0;
            Wiper_Output = OFF;
            wiper->stop_wiper(wiper_upper_limit, wiper_under_limit, wiper_first_location, wiper->Wiper_rate);
            Pwm_Stop(1);  
        }

            /*HORN*/
        if(Horn){
            Horn_State = 1;
            DEBUG_LED1 = ON;
            Delay_ms(15);
        }
        else if (!Horn && Horn_State){
            Horn_State = 0;
            DEBUG_LED1 = OFF;
            Delay_ms(15);
        }

            /*INLIGHT*/
        if(Inlight){
            Inlight_State = 1;
            Inlight_Output = ON;
            //DEBUG_LED1 = ON;
            Delay_ms(15);
        }
        else if(!Inlight && Inlight_State){
            Inlight_State = 0;
            ///
            Inlight_Output = OFF;
            Delay_ms(15);
            ///
        }   
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
void parseUartData( char * data ){

     int index = 0;
     int bmsId = 0;
     int opCode = 0;

     unsigned char * found;

    found = strtok(data,",");
    if( found==NULL)
    {
        return;
    }
    while(found)
    {

        found = strtok(NULL," ");
        
        if( index == 0 ){

              bmsId = atoi(found);
        }
        
        
        index++;
    }


}

void getUartData(char rcv_ch){
    if( bufIxBms == 0 && rcv_ch !='[')
        return;

    bufBms[bufIxBms++] = rcv_ch;
        
    if( rcv_ch == '\n'){ //LF

        parseUartData(bufBms);
        
        memset( bufBms, '\0', sizeof(bufBms));
        bufIxBms = 0;
        
    }
}

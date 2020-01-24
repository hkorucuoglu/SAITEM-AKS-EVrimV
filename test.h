#ifndef MAIN_H
#define MAIN_H

/**PIN definition**/

    #define INPUT 1
    #define OUTPUT 0
    #define ON 1
    #define OFF 0
    #define LOW 0
    #define HIGH 1
    #define Read 0
    #define Write 1
    #define True 0
    #define False 1
    /////////////---////////////////////
    #define DEBUG_LED1 PORTB.B5
    #define DEBUG_LED1_Direction TRISB.B5
    //////////////
    #define DEBUG_LED2 PORTB.B4
    #define DEBUG_LED2_Direction TRISB.B4
    //////////////
    #define DEBUG_LED3 PORTB.B2
    #define DEBUG_LED3_Direction TRISB.B2
    //////////////
    #define DEBUG_LED4 PORTB.B3
    #define DEBUG_LED4_Direction TRISB.B3
    /////////////
    #define BUZZER PORTF.F3
    #define BUZZER_Direction TRISF.F3
    /////////////   INPUT ////////////////////

    sbit HALL_SENSOR at RE0_bit;
    sbit HALL_SENSOR_Direction at TRISE0_bit;

    sbit Inlight at RE1_bit;
    sbit Inlight_Direction at TRISE1_bit;

    sbit Horn at RE2_bit;
    sbit Horn_Direction at TRISE2_bit;
    ///
    sbit Wiper at RE3_bit;
    sbit Wiper_Direction at TRISE3_bit;

    sbit Headlight at RE4_bit;
    sbit Headlight_Direction at TRISE4_bit;

    sbit Right_Signal at RE5_bit;
    sbit Right_Signal_Direction at TRISE5_bit;

    sbit Left_Signal at RE6_bit;
    sbit Left_Signal_Direction at TRISE6_bit;

    sbit Hazard at RE7_bit;
    sbit Hazard_Direction at TRISE7_bit;

    //////////////// OUTPUT ///////////////////

    sbit Wiper_PWM at RD0_bit;
    sbit Wiper_PWM_Direction at TRISD0_bit;

    sbit Headlight_Output at RB6_bit;
    sbit Headlight_Output_Direction at TRISB6_bit;

    sbit Right_Signal_Output at RB7_bit;
    sbit Right_Signal_Output_Direction at TRISB7_bit;

    sbit Left_Signal_Output at RB9_bit;
    sbit Left_Signal_Output_Direction at TRISB9_bit;

    sbit Inlight_Output at RB15_bit;
    sbit Inlight_Output_Direction at TRISB15_bit;

    sbit Horn_Output at RB13_bit;
    sbit Horn_Output_Direction at TRISB13_bit;

    sbit Wiper_Output at RB14_bit;
    sbit Wiper_Output_Direction at TRISB14_bit;

    //sbit Hazard_Output at RB15_bit;
    //sbit Hazard_Output_Direction at TRISB15_bit;


//* STATE definition *//
  int i;
  int Horn_State = 0;
  int Wiper_State = 0;
  int Headlight_State = 0;
  int Inlight_State = 0;
  int LeftSignal_State = 0;
  int RightSignal_State = 0;
  int Hazard_State = 0;
  int HALL_state = 0;
/*************************/

const float PI = 3.14;
unsigned long millis_counter=0;

void opening_test (void);
void init_pins (void);
void init_uart(void);
unsigned long millis(void);
#endif
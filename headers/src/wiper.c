#include "headers/lib/wiper.h"
#include <stdlib.h>
#include<stdio.h>

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

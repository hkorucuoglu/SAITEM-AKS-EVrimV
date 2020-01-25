#include "./lib/lib/hall.h"
#include <stdlib.h>
#include<stdio.h>
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

float _calculate_cf(float Radius){
  return 2*PI*Radius;
}

int _calculate_vc(float Distance, float Time){
  return Distance/Time*3.6;
}

int _calculate_time(struct Hall *hall){
  struct Hall *hall_;
  hall_ = hall;
  if (HALL_SENSOR && !hall_->Hall_state)
  {
    hall_->Total_time = millis();
    hall_->Hall_state = 1;
    // its must return as velocity
  }
  else if(HALL_SENSOR && hall_->Hall_state && millis() - hall_->Total_time > 10){
    hall_->Time = (millis() - hall_->Total_time)/1000.f;
    hall_->Hall_state = 0;
    return hall_->Calculate_Velocity(hall_->Circumference,hall_->Time);
  }
  else if(!HALL_SENSOR && millis() - hall_->Total_time > 2000) return 0;

  
}
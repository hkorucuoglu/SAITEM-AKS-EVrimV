#ifndef HALL_H
#define HALL_H

struct HALL
{
    int Hall_state;
    unsigned long Total_time;
    float Radius, Time, Circumference, Distance;

    float (*Calculate_Circumference)(float); // param is an radius
    int (*Calculate_Velocity)(float,float); // first param is distance, second is time
    //void (*Calculate_Time)(void); // no param
};

typedef struct HALL* Hall;

Hall Init_Hall(float); // this struct is only take a radius as param. /*Constructor*/

float _calculate_cf(float);
int _calculate_vc(float,float);
void _calculate_time(struct Hall *); // this is like a private func because we cannot reach with struct

#endif
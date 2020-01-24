#ifndef WIPER_H
#define WIPER_H

struct WIPER
{
    unsigned int Current_duty; 
    unsigned int Pwm_period;
    unsigned int Wiper_rate;

    int Upper_limit;
    int Under_limit;

    void (*run_wiper)(int,int,unsigned int, unsigned int); // upper,under,curren&first location,
    void (*stop_wiper)(int,int,unsigned int, unsigned int);
};
typedef struct WIPER* Wiper;

Wiper Init_Wiper(int,int,unsigned int); //Constructor

void _run_wiper(int,int,unsigned int, unsigned int);
void _stop_wiper(int,int,unsigned int, unsigned int);

#endif
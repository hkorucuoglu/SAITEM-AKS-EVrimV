#ifndef NEXTION_H
#define NEXTION_H

struct NEXTION
{
    char *TEMPERATURE_TEXT;
    char *VELOCITY_TEXT;
    char *CURRENT_TEXT;
    char *VOLTAGE_TEXT;

    void (*send_data)(int,int,float,float,struct Nextion *);
    void (*get_data)(void);
};
typedef struct  NEXTION* Nextion;
Nextion Init_Nextion(char[],char[],char[],char[]); // temp,vel,voltage,current
void _send_data(int,int,float,float,struct Nextion *);
void _get_data(void);
#endif
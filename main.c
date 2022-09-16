/*
 * main.c
 *
 *  Created on: Apr 15, 2022
 *      Author: Yasser
 */

#include <stdio.h>
#include <stdlib.h>

#define WITH_ENGINE_TEMP_CONTROLLER 1

enum AC_State {AC_ON, AC_OFF}; //State of AC
typedef enum AC_State AC;

enum engineState {engineON, engineOFF, engineQuit};  //State of engine
typedef enum engineState ES;

enum engineController {engineControllerON, engineControllerOFF}; //State of engine controller
typedef enum engineController EC;

//****************************Prototypes**************************************************
void displayMainMenu(void);
void displaySensorsSetMenu(void);
void sensorsSetAction(char op);
void trafficLightAction(char color,unsigned char * VehicleSpeedPtr);
void thirtySpeedAction(void);
void displayState(void);
void engineTemperatureAction(EC * e);
void roomTemperatureAction(AC * a);

//***********************Global Variables with initial Values*****************************

char trafficLightColor = 'G';
unsigned char vehicleSpeed = 100;
int roomTemperature = 20;
AC ac = AC_OFF;
EC ec = engineControllerOFF; //engine temperature controller
ES es = engineOFF; //engine state
int engineTemperature = 30;

//***********************************main*************************************************
int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char mainOption;
    char sensorsSetOption;

    while(es == engineOFF)
    {
        displayMainMenu();
        scanf(" %c",&mainOption);
        switch(mainOption)
        {
        case 'a': //Turn on
        case 'A':
            printf("%s\n","The System is Turned ON");
            es = engineON;
            while(es != engineOFF) //loop until state is off
            {
                displaySensorsSetMenu();
                scanf(" %c",&sensorsSetOption);
                sensorsSetAction(sensorsSetOption);
                if(vehicleSpeed == 30)
                {
                    thirtySpeedAction();
                }
                if (es != engineOFF){
                    displayState();
                }

            }

            break;
        case 'b': //Turn off
        case 'B':
            es = engineOFF;
            printf("%s\n","The System is Turned OFF");
            break;
        case 'c': //Quit
        case 'C':
            printf("%s\n","The System is Quit");
            es = engineQuit;
            break;
        default:
            printf("%s\n","Invalid Option");
        }
    }

    return 0;
}
//*********************************Main Menu Options*******************************************
void displayMainMenu(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf("%s\n","Choose Option:");
    printf("%s\n","a. Turn on the vehicle engine");
    printf("%s\n","b. Turn off the vehicle engine");
    printf("%s\n","c. Quit the system");

}
//*******************************Sensors Set Menu Options************************************
void displaySensorsSetMenu(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf("%s\n","Choose Option:");
    printf("%s\n","a. Turn off the engine");
    printf("%s\n","b. Set the traffic light color");
    printf("%s\n","c. Set the room temperature");
    #if WITH_ENGINE_TEMP_CONTROLLER
    printf("%s\n","d. Set the engine temperature");
    #endif
}
//*******************************Sensors Actions************************************
void sensorsSetAction(char op)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	switch(op)
    {
    case 'a': //Turn off
    case 'A':
        es = engineOFF;
        break;
    case 'b': //Set Traffic Light Color
    case 'B':
        printf("%s\n","Enter Color (G/O/R):");
        scanf(" %c",&trafficLightColor);
        trafficLightAction(trafficLightColor,&vehicleSpeed);
        break;
    case 'c': //Set Room Temperature
    case 'C':
        printf("%s\n","Enter Room Temperature:");
        scanf(" %d",&roomTemperature);
        roomTemperatureAction(&ac);
        break;
    #if WITH_ENGINE_TEMP_CONTROLLER
    case 'd': //Set Engine Temperature
    case 'D':
        printf("%s\n","Enter Engine Temperature:");
        scanf(" %d",&engineTemperature);
        engineTemperatureAction(&ec);
        break;
    #endif
        default:
            printf("%s\n", "Invalid Option");
            break;

    }
}
//*********************Action taken after user chooses traffic light color********************

void trafficLightAction(char color,unsigned char * VehicleSpeedPtr)
{
    switch(color)
    {
    case 'G':
    case 'g':
        *VehicleSpeedPtr = 100;
        break;
    case 'O':
    case 'o':
        *VehicleSpeedPtr = 30;
        break;
    case 'R':
    case 'r':
        *VehicleSpeedPtr = 0;
        break;
    default:
        *VehicleSpeedPtr = 100;
    }
}

//*********************Action taken after user chooses room temperature********************

void roomTemperatureAction(AC * a)
{
    if(roomTemperature < 10 || roomTemperature > 30)
    {
        *a = AC_ON;
        roomTemperature = 20;
    }
    else
    {
        *a = AC_OFF;
    }
}

//*********************Action taken after user chooses engine temperature********************

void engineTemperatureAction(EC * e)
{
    if(engineTemperature < 100 || engineTemperature > 150)
    {
        *e = engineControllerON;
        engineTemperature = 125;
    }
    else
    {
        *e = engineControllerOFF;
    }
}
//****************************Action taken when speed is 30********************************

void thirtySpeedAction(void)
{
    if(ac == AC_OFF)
    {
        ac = AC_ON;
    }
    roomTemperature = ((5 * roomTemperature) / 4) + 1;
    #if WITH_ENGINE_TEMP_CONTROLLER
    if(ec == engineControllerOFF)
    {
        ec = engineControllerON;
    }

    engineTemperature = ((5 * engineTemperature) / 4) + 1;
    #endif
}

//********************Display state and the parameters of the system**************************
void displayState(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	if(es == engineON)
    {
        printf("%s\n", "Engine is ON");
    }
    else
    {
        printf("%s\n", "Engine is OFF");
    }

    #if WITH_ENGINE_TEMP_CONTROLLER
    if(ec == engineControllerON)
    {
        printf("%s\n", "Engine Temperature Controller is ON");
    }
    else
    {
        printf("%s\n", "Engine Temperature Controller is OFF");
    }
    #endif

    if(ac == AC_ON)
    {
        printf("%s\n", "AC is ON");
    }
    else
    {
        printf("%s\n", "AC is OFF");
    }

    printf("Vehicle speed: %d km/h\n",vehicleSpeed);
    #if WITH_ENGINE_TEMP_CONTROLLER
    printf("Engine temperature: %d\n",engineTemperature);
    #endif
    printf("Room temperature: %d\n",roomTemperature);
}

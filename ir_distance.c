/*******************************************************************************
* Title                 :   IR Distance Click
* Filename              :   ir_distance.c
* Author                :   Sladjan Kantar
* Origin Date           :   12/27/2016
* Notes                 :   This module contains functions for calculating 
                            the distance between the IR Distance click 
                            and an object
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/

#include "ir_distance.h"
#include <math.h>

/******************************************************************************
* Function Definitions
*******************************************************************************/
double ir_measure_cm(uint16_t read_channel)
{
    uint16_t read = ADC1_Read( read_channel );
    float vadc;
    float vref33;
    float b3;

    float a3;
    float threshold;
    double y;
    float a;
    float b;

    a = 49.96f;
    b  = -1.34f;
    vref33 = 0.0008058608f;
    vadc;
    threshold = 3.0f;
    y = 0.0;

    vadc = ( float ) read * vref33;

    if ( vadc > threshold )
        return 0.0;

    y = pow( vadc, b );
    y *= a;

    if( y <= 20.0 )
        return y;
    else if( y > 20.0 && y <= 110.0 )
        return y - 3.0f;
}
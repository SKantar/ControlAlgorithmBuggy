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

    vadc = ( float ) read * 0.000804878f;

    if ( vadc > 3.0f )
        return 0.0;

    y = pow( vadc, -1.49 );
    y *= 49.956f;

    return y + 0.37f;
}
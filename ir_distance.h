/*******************************************************************************
* Title                 :   IR Distance
* Filename              :   ir_distance.h
* Author                :   Sladjan Kantar
* Origin Date           :   27/12/2016
* Notes                 :   None
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief ir_measure_cm
 * - Function calculates ADC value and returns distance measured in cm
 * @return
 * - Returns distance measured in cm
 */
double ir_measure_cm(uint16_t read_channel);
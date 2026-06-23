/*
 * gnss.h
 *
 *  Created on: Jun 23, 2026
 *      Author: LalinPrasadC
 */

#ifndef GNSS_H_
#define GNSS_H_

#include "stm32l433xx.h"

void read_gga(const char *str);

void read_rmc(const char *str);

int convert(const char* str);


typedef struct
{
   char time[20];
    char lat[20];
    char lon[20];
    char speed[10];
    char date[10];
    char status[2];

    char quality[10];
    char satelites[10];
    char hdop[10];
    char alt[10];
}gps;


extern gps gp1;

#endif /* GNSS_H_ */

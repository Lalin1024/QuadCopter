/*
 * gnss.c
 *
 *  Created on: Jun 23, 2026
 *      Author: LalinPrasadC
 */

#include "gnss.h"
#include <stddef.h>

gps gp1;

void read_gga(const char *str)
{
    char *dist=NULL;
    int j=0,count=0,k=0;


    while(str[j]!='\0')
    {
        if(str[j]==',')
        {
        count++;
        j++;


    switch(count)
    {
        case 6:
        dist=gp1.quality;
            break;

        case 7:

        dist=gp1.satelites;
            break;


        case 8:
        dist=gp1.hdop;
            break;

        case 9:
        dist=gp1.alt;
        break;

        default:
        dist = NULL;
        break;

    }
    if(dist!=NULL)
    {
    while(str[j]!=',' && str[j]!='\0')
    {
        if(k<=18)
        {
            dist[k++]=str[j];
        }
        j++;
    }
    dist[k] = '\0';
    k=0;
}
        }
else
{
    j++;
}

}
}


void read_rmc(const char *str)
{
    char *dist= 0;
    int j=0,count=0,k=0;


    while(str[j]!='\0')
    {
        if(str[j]==',')
        {
        count++;
        j++;


    switch(count)
    {
        case 1:
        dist=gp1.time;
            break;

        case 2:
        dist=gp1.status;
            break;

        case 3:

        dist=gp1.lat;
            break;


        case 5:
        dist=gp1.lon;
            break;

        case 7:
        dist=gp1.speed;
            break;

        case 9:
        dist=gp1.date;
            break;

        default:
        dist = NULL;
        break;

    }
    if(dist!=NULL)
    {
    while(str[j]!=',' && str[j]!='\0')
    {
        if(k<=18)
        {
            dist[k++]=str[j];
        }
        j++;
    }
    dist[k] = '\0';
    k=0;
}
        }
else
{
    j++;
}

}
}


int convert(const char* str)
{
    int i=0;
    int deci=0;

    while(str[i]!='\0')
    {
    if(str[i]=='.')
    {
        i++;
        continue;
    }
        deci*=10;
        deci+=(str[i]-'0');
        i++;
    }

    return (deci);
}

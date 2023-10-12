/*
 * Data.c
 *
 *  Created on: Aug 30, 2023
 *      Author: nguye
 */
#include "Data.h"


void DeleteAllData(Data *Source)
{
    int i;
    for(i = 0 ; i < Source->lenght; i++){
        Source->DataStore[i] = 0;
    };
    Source->lenght = 0;
};

void AddStringData(Data *Source, char *Data){
    while(*Data != '\0'){
        Source->DataStore[Source->lenght++] = *Data;
        Data++;
    }
};

void AddCharData(Data *Source, char *Data){
//    if(Source->lenght >= 32) {DeleteAllData(Source); return;};
    Source->DataStore[Source->lenght] = *Data;
    Source->lenght++;
};

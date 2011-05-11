#include "../include/OutputDevice.h"
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
cOutputDevice::cOutputDevice()
{
    //ctor
}

cOutputDevice::~cOutputDevice()
{
    //dtor
}

void cOutputDevice::Output(  char * TextToOutput, ... )
{
    va_list argptr;
    va_start (argptr, TextToOutput);
    vprintf( TextToOutput, argptr );
    va_end (argptr);
}


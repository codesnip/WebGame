/*
Copyright (C) 2011 WebGame project.
*/

#include "../include/OutputDevice.h"
#include "../include/ThreadSynhronization.h"
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
cOutputDevice::cOutputDevice( cThreadSynhronization * ThreadSynhronization )
{
    //ctor
    cOutputDevice::ThreadSynhronization = ThreadSynhronization;
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

void cOutputDevice::Output_ThreadSafe(  char * TextToOutput, ... )
{
    ThreadSynhronization->EnterCriticalSection();
    va_list argptr;
    va_start (argptr, TextToOutput);
    vprintf( TextToOutput, argptr );
    va_end (argptr);
    ThreadSynhronization->LeaveCriticalSection();
}

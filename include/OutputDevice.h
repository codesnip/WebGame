#ifndef COUTPUTDEVICE_H
#define COUTPUTDEVICE_H
#include "../include/ThreadSynhronization.h"

class cOutputDevice
{
    public:
        cOutputDevice( cThreadSynhronization * ThreadSynhronization );
        ~cOutputDevice();
        void Output(  char * TextToOutput, ... );
        void Output_ThreadSafe(  char * TextToOutput, ... );
    protected:
     cThreadSynhronization * ThreadSynhronization;
    private:
};

#endif // COUTPUTDEVICE_H

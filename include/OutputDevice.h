#ifndef COUTPUTDEVICE_H
#define COUTPUTDEVICE_H


class cOutputDevice
{
    public:
        cOutputDevice();
        ~cOutputDevice();

        void Output(  char * TextToOutput, ... );
    protected:
    private:
};

#endif // COUTPUTDEVICE_H

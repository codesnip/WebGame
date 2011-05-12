#ifndef CSOCKETS_H
#define CSOCKETS_H
#include "../include/OutputDevice.h"
#include <stdlib.h>  //for timeval
#include "../include/ThreadSynhronization.h"






#define SERVER_PORT 8080
#define MAX_NUM_CLIENTS 10000

#define SELECT_TIMEOUT_SEC 0

class cSockets
{
    public:
       cSockets(cOutputDevice * OutputDevice);
        ~cSockets();
        void CreateListeningSocket();
        void MainLoop();
    protected:

    private:
    fd_set MainReadDescriptor; // Main descriptor for reading for select();
    fd_set TemporaryReadDescriptor; // Temporary descriptor for reading for select();
    int BigestSocketNum;
    timeval *SelectTimeout;
    int SocketMAX;

    cOutputDevice * OutputDevice;
    int ListenerSocket;
    void CloseSocket(int SocketNo);
};

#endif // CSOCKETS_H

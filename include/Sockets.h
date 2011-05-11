#ifndef CSOCKETS_H
#define CSOCKETS_H
#include "../include/OutputDevice.h"
#include <stdlib.h>  //for timeval







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
    timeval *SelectTimeout;
    int SocketMAX;

    cOutputDevice * OutputDevice;
    int ListenerSocket;
    void CloseSocket(int SocketNo);
};

#endif // CSOCKETS_H
